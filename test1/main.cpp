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

//	Shader ourShader = Shader("shader/core.vs", "shader/core.frag");
	Shader ourShader = Shader("shader/core1.vs", "shader/core1.frag");

	/*
	//����������ɫ������
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);			//����ֵ����������ΨһID
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);		//��Դ�븽�ӵ���ɫ��������
	glCompileShader(vertexShader);									//���������ɫ������

	//����ƬԪ��ɫ������
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);			//����ֵ����������ΨһID
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);		//��Դ�븽�ӵ���ɫ��������
	glCompileShader(fragmentShader);									//������ɫ������

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//������ɫ��
	GLuint shaderProgram = glCreateProgram();			//������ɫ���������
	glAttachShader(shaderProgram, vertexShader);		//��������ɫ�����ӵ���ɫ��������
	glAttachShader(shaderProgram, fragmentShader);		//��ƬԪ��ɫ�����ӵ���ɫ��������
	glLinkProgram(shaderProgram);						//������ɫ������
	
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	//������ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	*/

	//�������飬 ����ʱ�뷽�򻭶���
	GLfloat vertices[] =
	{
		//������λ��			//��ɫ
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	//��
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	//��
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f	//��
	};
	//������Ϣ����VBO���й���
	GLuint VAO, VBO;						//vertex array object��������		vertex buffer object ��������
	glGenVertexArrays(1, &VAO);				//����ΨһID
	glGenBuffers(1, &VBO);					//����ΨһID
	glBindVertexArray(VAO);					//ָ��Ϊ�������
	glBindBuffer(GL_ARRAY_BUFFER, VBO);		//˵�����ͣ�ָ��Ϊ���㻺�����
	
	// ���������ݸ��Ƶ�VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//������1���������ݿ������ĵط���֮ǰ�󶨵�VBO����2������Ĵ�С��3������ĵ�ַ
	//4��ָ���Կ���ʲô��ʽ���������ǵ����ݣ��˴���ʾ��Щ���ݲ��ᾭ���ı�
		
	// ָ�������ʽ
/*	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
	// ������1����Ҫ���õĶ������ԣ����Ʊ�ţ�location=0��2���������Դ�С��vec3��3����������float
	//       4���Ƿ�淶����flase�Ѿ��淶�����ˣ�5�����Կ�ȣ�12����3����GLfloat��6��������ʼ��ƫ����
	glEnableVertexAttribArray(0);		//�ö���������Ч������0����֮ǰ���õ�locationλ��
*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);		//���
	glBindVertexArray(0);					//���
	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))			//����Ƿ�رմ���
	{
		glfwPollEvents();							//�ռ��������Ȳ�����Ϣ�����������¼�
		//��Ⱦ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);		//����������ɫ
		glClear(GL_COLOR_BUFFER_BIT);				//����
		//Bind the shader
//		glUseProgram(shaderProgram);
		//��ͼ
		ourShader.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);			//0��ʾ�����������ʼ������3��ʾ����������
		glBindVertexArray(0);

		glfwSwapBuffers(window);					//����ʾ������������潻������ʾ���������е����ݣ�
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	
	glfwTerminate();			//��ֹ����
	return 0;
}



/*����֮ǰ�����е��������ݶ������ȥ*/