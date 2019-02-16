#ifndef RENDERER_RENDERER_H
#define RENDERER_RENDERER_H

#include "display/Window.h"
#include "scene/SceneNode.h"

#include <memory>

namespace playground
{

class Renderer
{

public:
	Renderer();

	void render();
	void drawNode(SceneNode *node);
	void addWindow(Window *window);

	void setClearColor(const float &r, const float &g, const float &b, const float &a);

private:
	std::vector<Window*> windows;

};

} // namespace playground

#endif // RENDERER_RENDERER_H