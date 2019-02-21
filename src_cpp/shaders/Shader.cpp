#include "core/_Wrapper.h"
#include "shaders/Shader.h"

#include "core/PlaygroundBase.h"

#include <pybind11/pybind11.h>

namespace playground
{

namespace py = pybind11;

Shader::Shader(const std::string &vertSource, const std::string &fragSource)
{
	const char *vertCode = vertSource.c_str();
	const char *fragCode = fragSource.c_str();

	unsigned int vertex, fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertCode, NULL);
	glCompileShader(vertex);

	this->checkCompileErrors(vertex, "VERTEX");
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragCode, NULL);
	glCompileShader(fragment);

	this->checkCompileErrors(fragment, "FRAGMENT");

	this->shaderId = glCreateProgram();
	glAttachShader(this->shaderId, vertex);
	glAttachShader(this->shaderId, fragment);
	glLinkProgram(this->shaderId);

	this->checkCompileErrors(this->shaderId, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(this->shaderId);
}

void Shader::checkCompileErrors(const GLuint &shader, const std::string &type)
{
	GLint success;
	GLchar infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			PlaygroundBase::instance()->notify->error(
				"An error occoured while attempting to compile the shader. Error log: " + std::string(infoLog));
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			PlaygroundBase::instance()->notify->error(
				"An error occoured while attempting to link the shader. Error log: " + std::string(infoLog));
		}
	}
}

void wrap_shaders_shader(py::module &m)
{}

} // namespace playground