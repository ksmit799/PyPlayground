#include "core/_Wrapper.h"
#include "render/Renderer.h"

#include <pybind11/pybind11.h>

#include <GL/glew.h>
#include <SDL_opengl.h>
#include <glm/mat4x4.hpp>

namespace playground
{

namespace py = pybind11;

Renderer::Renderer()
{
	// OpenGL version.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// OpenGL attributes.
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Antialiasing.
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);

	glEnable(GL_DEPTH_TEST); // Enable depth testing.

	// Enable GLEW experimental.
	// Allows us to use OpenGL 3.X.
	glewExperimental = GL_TRUE;
}

void Renderer::render()
{
	for (auto window : this->windows)
	{
		SDL_GL_MakeCurrent(window->window, window->context);

		glClearColor(0.5f, 0.0, 0.0, 1.0);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		if (window->activeCamera)
		{
			//UpdateShaderMatrices();

			/*
			// pass projection matrix to shader (note that in this case it could change every frame)
        	glm::mat4 projection = glm::perspective(glm::radians(window->activeCamera.zoom), (float)window->width / (float)window->height, 0.1f, 100.0f);
        	ourShader.setMat4("projection", projection);

        	// camera/view transformation
        	glm::mat4 view = window->activeCamera.getViewMatrix();
        	ourShader.setMat4("view", view);
			*/

			this->drawNode(window->rootNode);
		}

		SDL_GL_SwapWindow(window->window);
	}
}

void Renderer::drawNode(SceneNode *node)
{
	// Determine whether we need to 're-use' the shader.
	unsigned int nodeProgramId = node->shader->programId;
	if (nodeProgramId != this->currentProgramId)
	{
		this->currentProgramId = nodeProgramId;
		glUseProgram(nodeProgramId);
	}

	// Draw.
	glDrawArrays(GL_TRIANGLES, 0, 3);

	// Draw each child of our node.
	for (auto childNode : node->children)
	{
		this->drawNode(childNode);
	}
}

void Renderer::addWindow(Window *window)
{
	this->windows.push_back(window);
}

void Renderer::setClearColor(const float &r, const float &g, const float &b, const float &a)
{
	glClearColor(r, g, b, a);
}

void wrap_render_renderer(py::module &m)
{
	py::class_<Renderer>(m, "Renderer")
		.def("render", &Renderer::render, ""); // TODO: Use TaskManager and don't expose.
}

} // namespace playground