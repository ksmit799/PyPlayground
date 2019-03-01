#ifndef SHADERS_SHADER_H
#define SHADERS_SHADER_H

#include <string>
#include <GL/glew.h>

namespace playground
{

class Shader
{

public:
	Shader(const std::string &vertSource, const std::string &fragSource);
	~Shader();

	unsigned int programId;

private:
	void checkCompileErrors(const GLuint &shader, const std::string &type);

};

} // namespace playground

#endif // SCENE_SCENENODE_H