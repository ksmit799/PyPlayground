#ifndef DISPLAY_WINDOW_H
#define DISPLAY_WINDOW_H

#include "display/Camera.h"
#include "scene/SceneNode.h"

#include <pybind11/pybind11.h>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <string>

namespace playground
{

namespace py = pybind11;

class Window
{

public:
	Window(const char *title = nullptr, const int &width = 640, const int &height = 480,
		const bool &fullscreen = false, const bool &resizable = true, const bool &grabInput = false);
	~Window();

	int width;
	int height;

	SDL_Window *window;
	SDL_GLContext context;
	Camera *activeCamera;
	SceneNode *rootNode;

	void addChild(SceneNode *node);

	void setTitle(const char *title);
	void setBordered(const bool &state);
	void setIcon(const std::string &iconPath);

private:

};

} // namespace playground

#endif // DISPLAY_WINDOW_H