#include "core/_Wrapper.h"
#include "display/Window.h"

#include "core/PlaygroundBase.h"

#include <stdexcept>

namespace playground
{

namespace py = pybind11;

Window::Window(const char *title, const int &width, const int &height,
	const bool &fullscreen, const bool &resizable, const bool &grabInput) : width(width), height(height)
{
	// Window constructor flags.
	unsigned int flags = 0;
	if (fullscreen)
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (resizable)
		flags |= SDL_WINDOW_RESIZABLE;
	if (grabInput)
		flags |= SDL_WINDOW_INPUT_GRABBED;

	// Force OpenGL.
	flags |= SDL_WINDOW_OPENGL;

	this->window = SDL_CreateWindow(
		title ? title : "My Game - Created with PyPlayground",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		flags
	);

	// Check that the window was successfully created.
	if (!this->window)
	{
		// Throw an exception if window creation failed.
		//PlaygroundBase::instance()->notify->error("Could not create window:" + SDL_GetError());
		throw std::exception();
	}

	// Create a new OpenGL context for our window.
	this->context = SDL_GL_CreateContext(this->window);
	if (!this->context)
	{
		// If an OpenGL context could not be acquired...
		//PlaygroundBase::instance()->notify->error("Could not create OpenGL context:" + SDL_GetError());
		throw std::exception();
	}

	// Initialize GLEW.
	if (glewInit() != GLEW_OK)
	{
		// Throw an exception if GLEW couldn't be initialized (OpenGL).
		//PlaygroundBase::instance()->notify->error("Failed to initialize GLEW (OpenGL):" + SDL_GetError());
		throw std::exception();
	}

	// Create our root node.
	this->rootNode = new SceneNode();

	// No active camera;
	this->activeCamera = nullptr;

	glViewport(0, 0, width, height);

	// Inject this window into the renderer.
	PlaygroundBase::instance()->renderer->addWindow(this);
}

Window::~Window()
{
	// Destroy this windows scene graph.
	delete this->rootNode;

	// Delete our OpenGL context/window.
	SDL_GL_DeleteContext(this->context);
	SDL_DestroyWindow(this->window);
}

void Window::addChild(SceneNode *node)
{
	this->rootNode->addChild(node);
}

void Window::setTitle(const char *title)
{
	SDL_SetWindowTitle(this->window, title);
}

void Window::setBordered(const bool &state)
{
	SDL_SetWindowBordered(this->window, (SDL_bool)state);
}

void Window::setIcon(const std::string &iconPath)
{
	// TODO.
	SDL_Surface *surface;
	SDL_SetWindowIcon(this->window, surface);
	SDL_FreeSurface(surface);
}

void wrap_display_window(py::module &m)
{	
	py::class_<Window>(m, "Window")

		// __init__
		.def(py::init<char*, int&, int&, bool&, bool&, bool&>(),
			py::arg("title") = nullptr, py::arg("width") = 640,
			py::arg("height") = 480, py::arg("fullscreen") = false,
			py::arg("resizable") = true, py::arg("grabInput") = false)

		.def("addChild", &Window::addChild, "")
		.def("setTitle", &Window::setTitle, "Test function")
		.def("setBordered", &Window::setBordered, "");
}

} // namespace playground