//#pragma once
// MMOpenGL.h: 标准系统包含文件的包含文件
// 或项目特定的包含文件。


#include <glad/glad.h>
#include <GLFW/glfw3.h>



enum MMGLShaderType
{
	MMGL_SHADER_VERTEX = 1,
	MMGL_SHADER_FRAGMENT = 2,

};


class MMGLShader
{
public:
	MMGLShader(GLchar* shaderstr, MMGLShaderType type);
	~MMGLShader();
private:
	GLuint shader = 0;

};