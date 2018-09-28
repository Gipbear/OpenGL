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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						//ָ��OpenGL�����汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						//ָ��OpenGL���Ӱ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//ʹ��OpenGL�ĺ���ģʽ���ɱ����Ⱦ�ܵ�ģʽ��
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);							//ʹ�ô��ڲ��ɸı䣬��ֹ������ԭ����״�ı� 
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);		//��������
	if (nullptr == window)		//���Դ����ܲ��ܴ�
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();		//�����������ֹ����
		return -1;
	}
	glfwMakeContextCurrent(window);		//�����ڵ������Ļ�������Ϊ��ǰ���̵߳������Ļ���

	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		return -1;
	}

	Shader ourShader = Shader("shader/core.vs", "shader/core.frag");

	//�������飬����ʱ�뷽�򻭶���
	GLfloat vertices[] = {
		//λ��					//����
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

	//��������
	GLuint texture;
	glGenTextures(1, &texture);				//������֮ǰ�ȼ�������Ԫ
	glBindTexture(GL_TEXTURE_2D, texture);	//��

	//Ϊ��ǰ�󶨵�����������û��ƣ����˷�ʽ
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//��һ������ָ��������Ŀ�ꣻ�ڶ�������ָ�����õ�ѡ����Ӧ�õ������᣻���һ�������ǻ��Ʒ�ʽ������ѡ����ǶԳ�
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//�ڶ���������ͼƬ�Ŵ����С�����һ�������������Թ���

	//���ز���������
	int width, height;		//ͼƬ��С
	unsigned char* image = SOIL_load_image("image/bare_bears.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
	//���ĸ�������˵����Ҫ��ȡʲô��Ϣ������ֻ������ɫ�����Զ�ȡ��һ���ܴ������
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
