#include "MMGLShader.hpp"
#include <iostream>

MMGLShader::MMGLShader(GLchar* shaderStr, MMGLShaderType type)
{

	if (MMGL_SHADER_VERTEX == type)
	{
		shader = glCreateShader(GL_VERTEX_SHADER);

	}
	else if (MMGL_SHADER_FRAGMENT == type)
	{
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}

	//顶点着色器和片段着色器源码
	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position=vec4(aPos,1.0);\n"
		"}\n\0";

	glShaderSource(shader, 1, &vertexShaderSource, NULL);
	glCompileShader(shader);

	GLint success = 0;
	GLchar info_log[512];

	//检查着色器是否编译成功，如果编译失败，打印错误信息
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}

}




MMGLShader::~MMGLShader()
{
	if (shader)
	{
		glDeleteShader(shader);
		shader = 0;
	}
}