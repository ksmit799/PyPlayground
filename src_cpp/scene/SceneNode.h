#ifndef SCENE_SCENENODE_H
#define SCENE_SCENENODE_H

#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace playground
{

class SceneNode
{

public:
	SceneNode();
	~SceneNode();

	virtual void draw();
	virtual void update();

	void addChild(SceneNode *node);

protected:
	SceneNode *parent;
	int mesh;
	int worldTransform;
	int transform;
	glm::vec3 scale;
	glm::vec4 color;
	std::vector<SceneNode*> children;

};

} // namespace playground

#endif // SCENE_SCENENODE_H