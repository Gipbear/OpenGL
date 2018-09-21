# 三角形的诞生
第一节首先是创建一个三角形，那么如何来实现三角形的创建呢，就让我们一起开始学习吧！！

## 头文件
在最开始动手进行编写之前，需要先添加头文件来使得程序能够正常运作
```Cpp
#include <iostream>
//GLEW
#include <GL/glew.h>
#define GLEW_STATIC
//GLFW
#include <GLFW/glfw3.h>
```
注意：此处的#define GLEW_STATIC与#include <GL/glew.h>之间的位置关系可能会影响报错，但是具体原因还是不明。。。_(: 」∠)_<br>

## 定义main()函数
首先在main()函数之上，先定义一个全局变量
>const GLint WIDTH = 800, HEIGHT = 600;   //定义创建的图像所在窗口的大小

然后定义main()函数
```cpp
int main()
{
	glfwInit();                                                         //初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);						//指定OpenGL的主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);						//指定OpenGL的子版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);		//使用OpenGL的核心模式（可编程渲染管道模式）
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);							//使得窗口不可改变，防止三角形原本形状随窗口变化而改变
                                                                        //例如原本的等边三角形随窗口的拉伸而变成了等腰三角形
    return 0;
}
```
接下来我们创建一个窗口对象，所有和窗口相关的数据都会被存放在这块，而且会被GLEW的其他函数经常性使用
```cpp
GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", nullptr, nullptr);		//创建窗口
if (nullptr == window)		//测试窗口能不能打开
{
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();		//如果出错则终止进程
	return -1;
}
glfwMakeContextCurrent(window);		//将窗口的上下文环境设置为当前主线程的上下文环境
```
创建窗口函数glfwCreateWindow的前两个参数是代表了所创的窗口的宽高，第三个参数是窗口的名字，最后两个参数暂时还不用（其实是现在我也不懂。。。），之后用if语句检查窗口是否确实被创建成功，并显示提示信息终止程序。一旦窗口建立成功，则将该窗口定义为当前主线程的上下文环境。<br>
接下来初始化GLEW，GLEW主要是用来管理指针的
```cpp
glewExperimental = GL_TRUE;
if (GLEW_OK != glewInit())
{
	std::cout << "Failed to initialise GLEW" << std::endl;
	return -1;
}
```
讲道理，其实第一句干嘛的也不是很清楚，但是却是需要写的，据说是在后面一些比较腻害的地方如果设置GL_FALSE会出错

## 设置三角形位置
用矩阵来表示三角形的三个点
```cpp
GLfloat vertices[] =
{
    //三角形位置
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f
};
```
这是一个三维坐标，坐标的建立是以标准化设备坐标（x,y,z的值都在-1到1之间，所有超过的值都将被剪切，原点是在图像的中心）的项式呈现，由于现在画出来的三角形是平面图形，所以，就将三角形的高度均设置为0。

## OpenGL对象
话说到现在都没出现OpenGL对象我都有点捉急了，所以接下来我们就介绍一下VAO和VBO这两个对象吧！先上代码_(: 」∠)_
```cpp

```
### VAO
首先介绍顶点数组对象VAO，VAO全名是Vertex Array Object，将随后的顶点属性绑定到VAO之上，

### VBO
VBO是顶点缓冲对象，全称是Vertex Buffer Object，他可以在CPU上存放大量的顶点，之后需要使用大量顶点的时候就可以一次性发送，而不需要多次发送，由于CPU到显卡发送数据较慢，所有应减少发送次数，所以这样做可提高绘制的效率



## 循环渲染
对于渲染的操作，我们都要将其进行循环，因为我们并不希望将图像画出来之后就会被立刻关闭，我们需要的是不断的绘制图形，保证其能够在窗口显示
```cpp
//渲染循环
while (!glfwWindowShouldClose(window))			//检查是否关闭窗口
{
	glfwPollEvents();							//收集键盘鼠标等操作信息，处理输入事件
	//渲染
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);		//设置清屏颜色
	glClear(GL_COLOR_BUFFER_BIT);				//清屏
	//画图
	ourShader.Use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);			//0表示顶点数组的起始索引，3表示有三个顶点
	glBindVertexArray(0);
	glfwSwapBuffers(window);					//将显示缓存和离屏缓存交换（显示高屏缓存中的内容）
}
```
其中的glfwWindowShouldClose是来检查GLFW创建的窗口是否有被要求退出；glfwPollEvents检查是否有鼠标等操作事件，然后决定是否需要调用其他对应函数；glClearColor()是设置对应的清屏颜色，当调用glClear是时候就会将屏幕清屏成相应的颜色；      glfwSwapBuffers是交换颜色缓冲，使得每次重新渲染显得真实

## 最后
当绘制结束之后将之前所有的资源全都进行释放，并终止进程
```cpp
glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);
glfwTerminate();			//终止进程
return 0;
```

