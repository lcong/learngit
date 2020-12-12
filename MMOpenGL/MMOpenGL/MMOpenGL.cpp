// MMOpenGL.cpp: 定义应用程序的入口点。
//
#define GLM_FORCE_SWIZZLE

/*
步骤：
1-初始化：GLFW窗口，GLAD
2-数据处理：给定顶点数据，生成并绑定VAO&VBO（准备再GPU中进行处理），设置顶点属性指针（本质上就是告诉OpenGL如何处理数据）。
3-着色器：给出顶点和片段着色器，然后链接为着色器程序，渲染时使用着色器程序。
4-渲染：清空缓冲，绑定纹理，使用着色器程序，绘制三角形，交换缓冲区检查触发时间后释放资源
*/
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include "../MMGLShader/MMGLShader.hpp"
#include "../MMHelloStatic/MMHelloStatic.hpp"


#include <glm/gtc/constants.hpp>
#include <glm/gtc/vec1.hpp>
#include <glm/ext/vector_relational.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <windows.h>


//using namespace std;

#define STRINGIZE(x)  #x
#define SHADER(shader) "" STRINGIZE(shader)

typedef std::unordered_map<std::string, std::string> stringmap;



static glm::vec1 g1;
static glm::vec1 g2(1);

int test_vec1_operators()
{
	int Error = 0;

	glm::ivec1 A(1);
	glm::ivec1 B(1);
	{
		bool R = A != B;
		bool S = A == B;

		Error += (S && !R) ? 0 : 1;
	}

	{
		A *= 1;
		B *= 1;
		A += 1;
		B += 1;

		bool R = A != B;
		bool S = A == B;

		Error += (S && !R) ? 0 : 1;
	}

	return Error;
}

int test_vec1_ctor()
{
	int Error = 0;

#	if GLM_HAS_TRIVIAL_QUERIES
	//	Error += std::is_trivially_default_constructible<glm::vec1>::value ? 0 : 1;
	//	Error += std::is_trivially_copy_assignable<glm::vec1>::value ? 0 : 1;
	Error += std::is_trivially_copyable<glm::vec1>::value ? 0 : 1;
	Error += std::is_trivially_copyable<glm::dvec1>::value ? 0 : 1;
	Error += std::is_trivially_copyable<glm::ivec1>::value ? 0 : 1;
	Error += std::is_trivially_copyable<glm::uvec1>::value ? 0 : 1;

	Error += std::is_copy_constructible<glm::vec1>::value ? 0 : 1;
#	endif

	/*
	#if GLM_HAS_INITIALIZER_LISTS
		{
			glm::vec1 a{ 0 };
			std::vector<glm::vec1> v = {
				{0.f},
				{4.f},
				{8.f}};
		}

		{
			glm::dvec2 a{ 0 };
			std::vector<glm::dvec1> v = {
				{0.0},
				{4.0},
				{8.0}};
		}
	#endif
	*/

	{
		glm::vec2 A = glm::vec2(2.0f);
		glm::vec2 B = glm::vec2(2.0f, 3.0f);
		glm::vec2 C = glm::vec2(2.0f, 3.0);
		//glm::vec2 D = glm::dvec2(2.0); // Build error TODO: What does the specification says?
		glm::vec2 E(glm::dvec2(2.0));
		glm::vec2 F(glm::ivec2(2));
	}

	return Error;
}

static int test_vec1_size()
{
	int Error = 0;

	Error += sizeof(glm::vec1) == sizeof(glm::mediump_vec1) ? 0 : 1;
	Error += 4 == sizeof(glm::mediump_vec1) ? 0 : 1;
	Error += sizeof(glm::dvec1) == sizeof(glm::highp_dvec1) ? 0 : 1;
	Error += 8 == sizeof(glm::highp_dvec1) ? 0 : 1;
	Error += glm::vec1::length() == 1 ? 0 : 1;
	Error += glm::dvec1::length() == 1 ? 0 : 1;

	return Error;
}

static int test_vec1_operator_increment()
{
	int Error(0);

	glm::ivec1 v0(1);
	glm::ivec1 v1(v0);
	glm::ivec1 v2(v0);
	glm::ivec1 v3 = ++v1;
	glm::ivec1 v4 = v2++;

	Error += glm::all(glm::equal(v0, v4)) ? 0 : 1;
	Error += glm::all(glm::equal(v1, v2)) ? 0 : 1;
	Error += glm::all(glm::equal(v1, v3)) ? 0 : 1;

	int i0(1);
	int i1(i0);
	int i2(i0);
	int i3 = ++i1;
	int i4 = i2++;

	Error += i0 == i4 ? 0 : 1;
	Error += i1 == i2 ? 0 : 1;
	Error += i1 == i3 ? 0 : 1;

	return Error;
}

static int test_swizzle()
{
	int Error = 0;

#	if GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR
	{
		glm::vec1 A = glm::vec1(1.0f);
		//glm::vec1 B = A.x;
		glm::vec1 C(A.x);

		//Error += glm::all(glm::equal(A, B)) ? 0 : 1;
		Error += glm::all(glm::equal(A, C, glm::epsilon<float>())) ? 0 : 1;
	}
#	endif//GLM_CONFIG_SWIZZLE == GLM_SWIZZLE_OPERATOR

	return Error;
}

static int test_constexpr()
{
#if GLM_HAS_CONSTEXPR
	static_assert(glm::vec1::length() == 1, "GLM: Failed constexpr");
	static_assert(glm::vec1(1.0f).x > 0.0f, "GLM: Failed constexpr");
#endif

	return 0;
}


int gmlvectortest()
{
	int Error = 0;

	Error += test_vec1_size();
	Error += test_vec1_ctor();
	Error += test_vec1_operators();
	Error += test_vec1_operator_increment();
	Error += test_swizzle();
	Error += test_constexpr();

	return Error;
}

int foo0()
{

	int Error = 0;

	Error += test_vec1_size();
	Error += test_vec1_ctor();
	Error += test_vec1_operators();
	Error += test_vec1_operator_increment();
	Error += test_swizzle();
	Error += test_constexpr();
	return 0;
}


int foo1()
{
	glm::mat4 trans(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0, 1, 0));
	//0  0  1  0
	//0  1  0  0
	//-1 0  0  0
	//0  0  0  1
	float* p = glm::value_ptr(trans);
	std::cout << typeid(p).name() << std::endl;
	for (int i = 0; i < 16; i++)
	{
		std::cout << *p << ' ';
		p++;
	}
	std::cout << std::endl;
	return 0;
}




stringmap merge(stringmap a, stringmap b)
{
	stringmap temp(a);
	temp.insert(b.begin(), b.end());
	return temp;
}

//三角形顶点数据
const GLfloat triangle[] =
{
	//位置
	-0.5,-0.5,0.0,//左下
	0.5f,-0.5f,0.0f,//右下
	0.0f,0.5f,0.0f//正上
};
//屏幕宽，高
int screen_width = 800;
int screen_height = 600;


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);

	}
}

int main()
{
	stringmap first; // empty

	// 一个元素为：{key, value}
	stringmap second({ {"apple","red"}, {"lemon","yellow"} });       // init list
	stringmap third({ {"orange","orange"}, {"strawberry","red"} });  // init list
	stringmap fourth(second);                     // copy
	stringmap fifth(merge(third, fourth));        // move
	stringmap sixth(fifth.begin(), fifth.end());  // range

	std::cout << "sixth contains: \n" << std::endl;
	for (auto& x : sixth)
	{
		std::cout << x.first << " : " << x.second;
		std::cout << "\n" << x.second;
	}
	std::cout << std::endl;

	//return 0;

	std::cout << "Hello CMake." << std::endl;
	MMHelloStatic breakingbad;
	std::cout << breakingbad.SayMyName() << std::endl;

	foo1();

	//初始化GLFW
	glfwInit();
	//OpenGL版本为3.3，主次版本号均设为3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_ANY_PROFILE, GLFW_OPENGL_CORE_PROFILE);//使用核心模式，无需向后兼容
	glfwWindowHint(GLFW_RELEASE, false);
	//创建窗口（宽、高、窗口名称）
	auto window = glfwCreateWindow(screen_width, screen_height, "Triangle", nullptr, nullptr);
	if (window == nullptr)//如果窗口创建失败
	{
		std::cout << "Failed to Create OpenGL ConText" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);//将窗口的上下文设置为当前线程的主上下文

	//初始化GLAD,加载OpenGL函数指针地址的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	std::cout << (char*)glGetString(GL_VERSION) << std::endl;


	//指定当前视口尺寸(前两个参数为左下角位置，后两个参数是渲染窗口宽、高)
	glViewport(0, 0, screen_width, screen_height);

	//生成并绑定VAO和VBO
	GLuint vertex_array_object;//VAO
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	GLuint vertex_buffer_object;//VBO
	glGenBuffers(1, &vertex_buffer_object);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
	//将顶点数据绑定至当前默认的缓存中
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	//设置顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//解绑VAO和VBO
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//顶点着色器和片段着色器源码
	char* vertexShaderSource = SHADER(
		#version 460\n
		layout(location = 0) in vec3 pos;
	out vec3 outPos;

	void main()
	{
		outPos = pos;
		gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
	}
	);


	char* fragmentShaderSource = SHADER(
		#version 460\n
		out vec4 rgbaColor;
	in vec3 outPos;

	void main()
	{
		rgbaColor = vec4(outPos, 1.0);
	}
	);



	/*
	*
	* 	const char* vertexShaderSource =
		"#version 330 core\n"
		"layout (location=0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position=vec4(aPos,1.0);\n"
		"}\n\0";
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor=vec4(0.5f,1.5f,0.2f,1.0f);\n"//三角形的颜色
		"}\n\0";

	*/

	//生成并编译着色器
	//顶点着色器
	GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLint success;
	GLchar info_log[512];
	//检查着色器是否编译成功，如果编译失败，打印错误信息
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}



	//片段着色器
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	//检查着色器是否成功编译，如果编译失败，打印错误信息
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	//链接顶点和片段着色器至一个着色器程序
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//检查着色器是否成功链接，如果链接失败，打印错误信息
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}
	//删除着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//线框模式
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//渲染循环
	while (!glfwWindowShouldClose((window)))
	{

		// 输入
		processInput(window);

		//清空颜色缓冲
		//glClearColor(1.0f, 0.34f, 0.57f, 1.0f);//背景色
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//使用着色器程序
		glUseProgram(shaderProgram);

		//绘制三角形
		glBindVertexArray(vertex_array_object);//绑定VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);//绑定三角形
		glBindVertexArray(0);//解除绑定


		// 检查并调用事件，交换缓冲
		//交换缓冲并且检查是否有触发事件(比如键盘输入、鼠标移动等)
		glfwSwapBuffers(window);
		glfwPollEvents();
		Sleep(1);

	}

	//删除VAO和VBO
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteBuffers(1, &vertex_buffer_object);

	//清理所有的资源并正确退出程序
	glfwTerminate();
	return 0;
}