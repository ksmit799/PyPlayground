#include "core/_Wrapper.h"
#include "scene/SceneNode.h"

#include <pybind11/pybind11.h>

namespace playground
{

namespace py = pybind11;

SceneNode::SceneNode()
{
	this->parent = nullptr;
	this->mesh = 1;
	this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
	this->color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

SceneNode::~SceneNode()
{
	for (auto child : this->children)
		delete child;
}

void SceneNode::draw()
{
	// TODO: Draw mesh.
	if (this->mesh) { return; }
}

void SceneNode::update()
{
	// Child node, relative transform.
	if (this->parent)
	{
		this->worldTransform = this->parent->worldTransform * this->transform;
	}

	// Root node, world transform.
	else
	{
		this->worldTransform = this->transform;
	}

	for (auto child : this->children)
		child->update();
}

void SceneNode::addChild(SceneNode *node)
{
	// We can't be our own child.
	if (node == this) { return; }

	this->children.push_back(node);
	node->parent = this;
}

void wrap_scene_scenenode(py::module &m)
{}

} // namespace playground