//#pragma once
// MMOpenGL.h: ��׼ϵͳ�����ļ��İ����ļ�
// ����Ŀ�ض��İ����ļ���


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