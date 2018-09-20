# OpenGL
## 最初的开始
这个是由于在大三上学期所开的计算机图形学课程而同步建立的一个小随笔，大部分是根据老师课上一步步的讲解进行整理，注释编写，还参考了关于OpenGL的一个网站[LearnOpenGL](https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/04%20Hello%20Triangle/)进行同步学习<br>
## 配置
首先是关于OpenGL配置的问题，配置需要先下载GLEW和GLFW包，本人利用VS2017+GLEW+GLFW进行OpenGL的配置，具体步骤是按照[B站上是一个网站](https://www.bilibili.com/read/cv183332)进行配置，不过似乎有几个与我实际配置不一样的部分需要更改<br>
第六步配置连接器包含的库文件指定，本人只指定了其中的三个如下，并且将GLEW/bin/release/win32中的文件glew32.dll复制到mian.cpp文件所在的目录下<br>
*opengl32.lib<br>
*glfw3.lib<br>
*glew32.lib<br>
接下来的测试文件我是用老师给的一段测试代码
```cpp
#include <iostream>
//GLEW
#define GLEW_STATIC
#include <GL/glew.h>
//GLFW
#include <GLFW/glfw3.h>
const GLint WIDTH = 800, HEIGHT = 600;
int main()
{
glfwInit();
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // must for Mac
 glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, “Learn OpenGL”, nullptr,
nullptr);
// next two lines are for mac retina display
int screenWidth, screenHeight;
glfwGetFramebufferSize( window, &screenWidth, &screenHeight);
if (nullptr == window)
{
std::cout << “Failed to create GLFW window” << std::endl;
glfwTerminate();
return -1;
}
glfwMakeContextCurrent( window );
glewExperimental = GL_TRUE;
if (GLEW_OK != glewInit() )
{
std::cout << “Failed to initialise GLEW” << std::endl;
return -1;
}
glViewport( 0, 0, screenWidth, screenHeight );
while (!glfwWindowShouldClose (window))
{
glfwPollEvents();
glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
glClear (GL_COLOR_BUFFER_BIT);
glfwSwapBuffers (window);
}
glfwTerminate();
return 0;
}
```
如果最终出现了一个黑色的框框，并且没有其他地方报错，就说明所有的东西都配置好了
## 最后
如果一切都已经准备好了，那么，就开始我们学画画的快乐旅程吧~
