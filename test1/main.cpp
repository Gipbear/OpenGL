#include <iostream>
//GLEW
#include <GL/glew.h>
#define GLEW_STATIC
//GLFW
#include <GLFW/glfw3.h>

#include "Shader.h"
const GLint WIDTH = 800, HEIGHT = 600;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);				//指定OpenGL的主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);				//指定OpenGL的子版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//使用OpenGL的核心模式（可编程渲染管道模式）
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);						//使得窗口不可改变，防止三角形原本形状改变 
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);	//创建窗口
	if (nullptr == window)			//测试窗口能不能打开
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

	//顶点数组， 以逆时针方向画顶点
	GLfloat vertices[] =
	{
		//三角形位置			
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	//物体信息是由VBO进行管理
	GLuint VAO, VBO;				//vertex array object关联数据	vertex buffer object 传输数据
	glGenVertexArrays(1, &VAO);			//生成唯一ID
	glGenBuffers(1, &VBO);				//生成唯一ID
	glBindVertexArray(VAO);				//指定为顶点对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		//说明类型，指定为顶点缓存对象
	
	// 将顶点数据复制到VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//参数：1、顶点数据拷贝到的地方（之前绑定的VBO），2、数组的大小，3、数组的地址
	//4、指定显卡用什么方式来管理我们的数据，此处表示这些数据不会经常改变
		
	// 指明顶点格式
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	// 参数：1、想要配置的顶点属性，类似编号，location=0，2、顶点属性大小，vec3，3、数据类型float
	//       4、是否规范化，flase已经规范化过了，5、属性跨度，12就是3倍的GLfloat，6、数据起始的偏移量
	glEnableVertexAttribArray(0);		//让顶点属性生效，参数0就是之前配置的location位置

	glBindBuffer(GL_ARRAY_BUFFER, 0);		//解绑
	glBindVertexArray(0);				//解绑
	//渲染循环
	while (!glfwWindowShouldClose(window))			//检查是否关闭窗口
	{
		glfwPollEvents();				//收集键盘鼠标等操作信息，处理输入事件
		//渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);		//设置清屏颜色
		glClear(GL_COLOR_BUFFER_BIT);			//清屏
		//画图
		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);		//0表示顶点数组的起始索引，3表示有三个顶点
		glBindVertexArray(0);

		glfwSwapBuffers(window);			//将显示缓存和离屏缓存交换（显示高屏缓存中的内容）
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	glfwTerminate();			//终止进程
	return 0;
}
