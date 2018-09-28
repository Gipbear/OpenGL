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
			//打开文件
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			std::stringstream vShaderStream, fShaderStream;
			//读取缓冲内容到数据流
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			//关闭文件处理器
			vShaderFile.close();
			fShaderFile.close();
			//转换数据流到string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
		}
		//类型转换
		const GLchar *vShaderCode = vertexCode.c_str();
		const GLchar *fShaderCode = fragmentCode.c_str();

		//创建顶点着色器对象
		vertex = glCreateShader(GL_VERTEX_SHADER);			//返回值是这个对象的唯一ID
		glShaderSource(vertex, 1, &vShaderCode, NULL);		//将源码附加到着色器对象上
		glCompileShader(vertex);									//编译这个着色器对象

		GLint success;
		GLchar infoLog[512];

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//创建片元着色器对象
		fragment = glCreateShader(GL_FRAGMENT_SHADER);			//返回值是这个对象的唯一ID
		glShaderSource(fragment, 1, &fShaderCode, NULL);		//将源码附加到着色器对象上
		glCompileShader(fragment);									//编译着色器对象

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		//链接着色器
		this->Program = glCreateProgram();			//创建着色器程序对象
		glAttachShader(this->Program, vertex);		//将顶点着色器附加到着色器程序上
		glAttachShader(this->Program, fragment);		//将片元着色器附加到着色器程序上
		glLinkProgram(this->Program);						//链接着色器程序

		glValidateProgram(this->Program);
		glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
	}

	~Shader()
	{
		//清理着色器
		glDetachShader(this->Program, vertex);
		glDetachShader(this->Program, fragment);
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteProgram(this->Program);
	}

	void  Use()			//使用
	{
		glUseProgram(this->Program);
	}
};

