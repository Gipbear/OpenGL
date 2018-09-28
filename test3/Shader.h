#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>


class Shader
{
	GLuint vertex, fragment;
public:
	GLuint Program;
	Shader(const GLchar *vertexPath, const GLchar *fragmentPath)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		vShaderFile.exceptions(std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::badbit);

		try {
			//���ļ�
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			std::stringstream vShaderStream, fShaderStream;
			//��ȡ�������ݵ�������
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//�ر��ļ�������
			vShaderFile.close();
			fShaderFile.close();
			//ת����������string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}
		//����ת��
		const GLchar *vShaderCode = vertexCode.c_str();
		const GLchar *fShaderCode = fragmentCode.c_str();

		//����������ɫ������
		vertex = glCreateShader(GL_VERTEX_SHADER);			//����ֵ����������ΨһID
		glShaderSource(vertex, 1, &vShaderCode, NULL);		//��Դ�븽�ӵ���ɫ��������
		glCompileShader(vertex);									//���������ɫ������

		GLint success;
		GLchar infoLog[512];

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//����ƬԪ��ɫ������
		fragment = glCreateShader(GL_FRAGMENT_SHADER);			//����ֵ����������ΨһID
		glShaderSource(fragment, 1, &fShaderCode, NULL);		//��Դ�븽�ӵ���ɫ��������
		glCompileShader(fragment);									//������ɫ������

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//������ɫ��
		this->Program = glCreateProgram();			//������ɫ���������
		glAttachShader(this->Program, vertex);		//��������ɫ�����ӵ���ɫ��������
		glAttachShader(this->Program, fragment);		//��ƬԪ��ɫ�����ӵ���ɫ��������
		glLinkProgram(this->Program);						//������ɫ������

		glValidateProgram(this->Program);
		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}

	~Shader()
	{
		//������ɫ��
		glDetachShader(this->Program, vertex);
		glDetachShader(this->Program, fragment);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteProgram(this->Program);
	}

	void  Use()			//ʹ��
	{
		glUseProgram(this->Program);
	}
};

