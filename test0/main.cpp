#include <iostream>
//GLEW
#include <GL/glew.h>
#define GLEW_STATIC
//GLFW
#include <GLFW/glfw3.h>
//SOIL2
#include "SOIL2/SOIL2.h"
#include "SOIL2/stb_image.h"

#include "Shader.h"
const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						//指定OpenGL的主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						//指定OpenGL的子版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//使用OpenGL的核心模式（可编程渲染管道模式）
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);							//使得窗口不可改变，防止三角形原本形状改变 
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);		//创建窗口
	if (nullptr == window)		//测试窗口能不能打开
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();		//如果出错则终止进程
		return -1;
	}
	glfwMakeContextCurrent(window);		//将窗口的上下文环境设置为当前主线程的上下文环境

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		return -1;
	}

	Shader ourShader = Shader("shader/core.vs", "shader/core.frag");

	//顶点数组，以逆时针方向画顶点
	GLfloat vertices[] = {
		//位置					//纹理
		0.5f,0.5f,0.0f,			1.0f, 1.0f,
		0.5f,-0.5f,0.0f,		1.0f, 0.0f,
		-0.5f,-0.5f,0.0f,		0.0f, 0.0f,
		-0.5f,0.5f,0.0f,		0.0f, 1.0f
	};

	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};

	GLuint VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//生成纹理
	GLuint texture;
	glGenTextures(1, &texture);				//绑定纹理之前先激活纹理单元
	glBindTexture(GL_TEXTURE_2D, texture);	//绑定

	//为当前绑定的纹理对象设置环绕，过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//第一个参数指定了纹理目标；第二个参数指定设置的选项与应用的纹理轴；最后一个参数是环绕方式，这里选择的是对称
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//第二个参数是图片放大或缩小，最后一个参数代表线性过滤

	//加载并生成纹理
	int width, height;		//图片大小
	unsigned char* image = SOIL_load_image("image/bare_bears.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	//第四个参数的说明需要读取什么信息，这里只关心颜色，所以读取成一个很大的数组
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ourShader.Use();

		//
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture0"), 0);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &texture);

	glfwTerminate();
	return 0;
}
