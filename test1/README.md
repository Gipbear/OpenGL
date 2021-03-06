# 每天起床第一句！先给自己打个气！
## 加油！加油！加油！

# 三角形的诞生
第一节首先是创建一个三角形，那么如何来实现三角形的创建呢，就让我们一起开始学习吧！！

## 头文件
在最开始动手进行编写之前，需要先添加头文件来使得程序能够正常运作。
```Cpp
#include <iostream>
//GLEW
#include <GL/glew.h>
#define GLEW_STATIC
//GLFW
#include <GLFW/glfw3.h>
```
注意：此处的#define GLEW_STATIC与#include <GL/glew.h>之间的位置关系可能会影响报错，但是具体原因还是不明。。。。_(: 」∠)_<br>

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
接下来我们创建一个窗口对象，所有和窗口相关的数据都会被存放在这块，而且会被GLEW的其他函数经常性使用。
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
讲道理，其实第一句干嘛的也不是很清楚，但是却是需要写的，据说是在后面一些比较腻害的地方如果设置GL_FALSE会出错。

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

## 着色器
着色器有很多的种类，先简单介绍一下顶点着色器和片段着色器：

### 顶点着色器
先上代码？好，就先上代码！以下内容存放在一个.vs的文件中，至于为什么是vs就不要问我啦！
```cpp
#version 330 core
layout(location = 0) in vec3 position;
void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0f);
}
```
咳咳，由于我还是个萌新，而且也不想照抄哪些资料，所以就写一点我理解的吧（懒是真的~）。第一个“#”这句话是说明了版本3.3，至于为什么是330.。。可能是他开心，在着色器上，需要有输入和输出，使得着色器之间能够交换信息，所以有了in和out的存在，在定义输入in的时候需要（好像不一定需要）指定输入的位置，即location=0，这个在之后的程序上会经常使用，out好像就不需要了，因为out输出之后用in调用时只需要名字匹配就好了。in后面的vec3代表向量(x,y,z)指的是坐标位置，在主函数内依次赋值给预定义的gl_Position，他所设置的值将会成为顶点着色器的输出。

## 片段着色器
以下内容存放在.frag文件中，原因同上！
```cpp
#version 330 core
out vec4 color;
void main()
{
	color = vec4(1.0f, 0.5f, 0.2f, 0.7f);
}
```
这里是设置颜色的，定义输出对象为color，然后将其设置成四分量向量，最后一个1.0f是说明透明度。

## VBO
VBO是顶点缓冲对象，全称是Vertex Buffer Object，他可以在CPU上存放大量的顶点，之后需要使用大量顶点的时候就可以一次性发送，而不需要多次发送，由于CPU到显卡发送数据较慢，所有应减少发送次数，所以这样做可提高绘制的效率。创建VBO的时候
>GLuint VBO;<br>glGenBuffers(1, &VBO);		//声明VBO对象，并生成唯一的ID=1，可以在之后使用。

顶点缓冲对象的类型是GL_ARRAY_BUFFER，利用glBindBuffer将VBO绑定到GL_ARRAY_BUFFER上
>glBindBuffer(GL_ARRAY_BUFFER, VBO);

之后将之前定义的顶点坐标输入到顶点对象上
>glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);<br>
第四个参数是指定我们希望如何来管理给定的数据，由于现在较为初级，所以保证三角形的位置不变，当然，他还有其他的几个形式:

* GL_STATIC_DRAW ：数据不会或几乎不会改变。
* GL_DYNAMIC_DRAW：数据会被改变很多。
* GL_STREAM_DRAW ：数据每次绘制时都会改变。

## VAO
VAO是顶点数组对象，VAO全名是Vertex Array Object，将随后的顶点属性绑定到VAO之上，在之后的绘制中只需要绑定相应的VAO就可以很方便的画图了，VAO的创建过程和VBO类似
>GLuint VBO;<br>glGenBuffers(1, &VBO);		//声明VAO对象，并生成唯一的ID=1，可以在之后使用。

和VBO进行绑定的时候大概是这个样子的
```cpp
// 1. 绑定VAO
glBindVertexArray(VAO);
// 2. 把顶点数组复制到缓冲中供OpenGL使用
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
// 3. 设置顶点属性指针
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
glEnableVertexAttribArray(0);
//4. 解绑VAO，VBO
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);
```
第三步中的几个参数说明一下，第一个，想要配置的顶点编号，此处location=0，在core的文件中建立；第二个，顶点属性的大小，vec3；第三个，数据类型float；第四个，是否规范化，此处false是因为已经规范化过了；第五个，属性选择跨度，在建立坐标的时候是3X3的矩阵,所以每个顶点的跨度为3；第六个，起始偏移量为0。<br>
下面那个参数0就是location=0中代表位置的0。

## Shader.h
关于着色器对象的创建编译等步骤，将其放入.h文件中编写（实际上是老师后来又从main（）文件中拿出来的），这里面主要是处理着色器对象
首先是头文件的编写，需要的是关于文件读写的包
```cpp
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
```
之后定义一个Shader类来表示着色器类，以供生成着色器对象，在Shader类的定义中，首先声明变量，顶点着色器和片段着色器，还有着色器程序。在Shader的构造函数中，需要传入的参数就是顶点着色器和片段着色器的文件地址，就是之前创建的.vs和.frag文件
> Shader(const GLchar *vertexPath, const GLchar *fragmentPath);

之后就是简单的读取文件内容，将文件格式转化为字符串格式，再转化为字符形式（虽然觉得字符串格式已经很好，但是后面用到取地址的方式，似乎还是字符数组比较合适）。读完文件之后就应该进行对着色器对象的创建了
```cpp
//创建顶点着色器对象
vertex = glCreateShader(GL_VERTEX_SHADER);			//返回值是这个对象的唯一ID
glShaderSource(vertex, 1, &vShaderCode, NULL);		//将源码附加到着色器对象上
glCompileShader(vertex);							//编译这个着色器对象
GLint success;
GLchar infoLog[512];
glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
if (!success) {
	glGetShaderInfoLog(vertex, 512, NULL, infoLog);
	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
```
以上的具体操作总(da)结(gai)来说就是，利用glCreateShader创建对象，然后用glShaderSource将之前读取的文件源码附加到创建的着色器对象上，最后用glCompileShader来编译着色器对象。建立编译结束做着色器对象之后可能会有点不放心，而且也经常会在这里出错（可能还是个新手的原因），所以需要检查一下是否编译成功，利用标志success和错误说明字符串infolog来显示错误情况，顶点着色器和片段着色器类似。在这之后就将两个着色器都和着色器程序对象链接起来。
```cpp
//链接着色器
this->Program = glCreateProgram();		//创建着色器程序对象
glAttachShader(this->Program, vertex);		//将顶点着色器附加到着色器程序上
glAttachShader(this->Program, fragment);	//将片元着色器附加到着色器程序上
glLinkProgram(this->Program);			//链接着色器程序

glValidateProgram(this->Program);
```
至此，Shader类的构造函数就完成了，当然，有构造函数就需要析构函数，来将运行结束不需要的东西进行回收
```cpp
~Shader() 
{
	//清理着色器
	glDetachShader(this->Program, vertex);
	glDetachShader(this->Program, fragment);
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteProgram(this->Program);
}
```
最后还需要有一个函数来提供接口使用
>void  Use()			//使用 <br>
	{ <br>
		glUseProgram(this->Program); <br>
	} <br>

## 调用Shader.h
定义完Shader.h的头文件之后，当然需要调用啦，首先将头文件导入main.cpp中
> #include "Shader.h"

然后创建一个Shader对象ourShader来构造Shader着色器对象，以供之后使用，其中传入的文件路径千万不要弄错了，关于在当前目录还是子目录的情况要自己分清楚，不然调用文件不成功还是会有各种各样奇奇怪怪的错误的。

## 循环渲染
对于渲染的操作，我们都要将其进行循环，因为我们并不希望将图像画出来之后就会被立刻关闭，我们需要的是不断的绘制图形，保证其能够在窗口显示。
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
其中的glfwWindowShouldClose是来检查GLFW创建的窗口是否有被要求退出；glfwPollEvents检查是否有鼠标等操作事件，然后决定是否需要调用其他对应函数；glClearColor()是设置对应的清屏颜色，当调用glClear是时候就会将屏幕清屏成相应的颜色；调用之前在Shader中定义的函数接口Use()来使用着色器；将定义好的VAO顶点数组对象进行绑定；glDrawArrays顾名思义就是按照数组对象进行绘制图形；glfwSwapBuffers是交换颜色缓冲，使得每次重新渲染显得真实。

## 最后
当绘制结束之后将之前所有的资源全都进行释放，并终止进程。
```cpp
glDeleteVertexArrays(1, &VAO);
glDeleteBuffers(1, &VBO);
glfwTerminate();			//终止进程
return 0;
```

# 完工！
最后就可以看见一个美腻的三角形啦，虽然大概叙述了整个编写的过程，但是还是有很多地方表达不够清晰，或者我自己都没有完全理解，不过没关系，我们有在之前提到的OpenGL一份完整的教程，不懂的地方去翻一下还是可以轻松解决问题的，小白白我也会在后期的课程中不断改进，修正错误不断更新的！

