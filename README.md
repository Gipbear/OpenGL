# OpenGL
## 最初的开始
这个是由于在大三上学期所开的计算机图形学课程而同步建立的一个小随笔，大部分是根据老师课上一步步的讲解进行整理，注释编写，还参考了关于OpenGL的一个网站[LearnOpenGL](https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/04%20Hello%20Triangle/)进行同步学习。<br>
## 配置GLEW和GLFW
首先是关于OpenGL配置的问题，配置需要先下载GLEW和GLFW包，本人利用VS2017+GLEW+GLFW进行OpenGL的配置，具体步骤是按照[B站上是一个网站](https://www.bilibili.com/read/cv183332)进行配置，不过似乎有几个与我实际配置不一样的部分需要更改。<br>
在第六步配置连接器包含的库文件指定，本人只指定了其中的三个如下，并且将GLEW/bin/release/win32中的文件glew32.dll复制到mian.cpp文件所在的目录下。<br>
>opengl32.lib<br>
>glfw3.lib<br>
>glew32.lib<br>

接下来的测试文件我是用老师给的一段测试代码
```cpp
#include <iostream>
//GLEW
#include <GL/glew.h>
#define GLEW_STATIC
//GLFW
#include <GLFW/glfw3.h>
const GLint WIDTH = 800, HEIGHT = 600;
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // must for Mac
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr,nullptr);
	// next two lines are for mac retina display
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialise GLEW" << std::endl;
		return -1;
	}
	glViewport(0, 0, screenWidth, screenHeight);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
```
如果最终出现了一个黑色的框框，并且没有其他地方报错，就说明所有的东西都配置好了

## SOIL配置
2018.9.18更新哦~
在进一步的学习后，我们开始学习纹理，不过对于纹理的使用会需要图片，读取图片的话可以自己写一个图片加载器进行读写，不是很难（大家都这么说。。。虽然我。。。），但是还是比较麻烦的，所以我们需要利用一个现成的库，也就是接下来要介绍的SOIL库来解决这个问题。
首先我们需要先下载SOIL，可以在[SOIL](http://www.lonesock.net/soil.html)的网站下载，下载的压缩包进行解压，之后再下载一个[premake 4.4](https://premake.github.io/download.html#v4)，（似乎不需要最新版本？老师让我们下4.4的），然后将premake解压，得到的一个exe文件复制粘贴到之前解压的SOIL文件中。按住WIN+R打开cmd使用命令窗口的命令转到SOIL所解压的文件夹目录下 运行premake4.exe vs2012，等运行结束之后就会产生一个新的文件make，打开make文件中的SOIL2.sln在vs中打开，运行一下，运行成功之后关闭vs，这个时候就会得到一个src文件夹，将其中的SOIL文件再复制到以后需要创建的项目下，之后再将lib文件中的soil2-debug.lib文件复制一下，在桌面创建一个SOIL的文件夹，在里面创建一个lib文件夹，然后将之前复制的那个文件粘贴进去，最后将SOIL文件夹复制粘贴到GLEW和GLFW的文件夹一起。现在为止所有的基础准备都已经完成了，然后让我们创建一个新的项目，在项目中按照之前先将GLEW和GLFW先配置好，然后在库目录添加的时候加上SOIL的库目录（就是之前自己创建的lib），然后在链接器的输入中再添加一个soil2-debug.lib，在main.cpp中导入#include "SOIL2/SOIL2.h"，如果未报错就说明配置成功。
当然啦，我相信很多人不会一次性就配置成功，所有建议大家能够多参考一下百度的意见，毕竟百度是一个人必备的技能，很多人不会一直帮助你解决各种各样的问题，百度就不一样了，就跟保姆一样跟着你（啦啦啦啦啦啦~）。

## 启航
如果一切都已经准备好了，那么，就开始我们学画画的快乐旅程吧~
