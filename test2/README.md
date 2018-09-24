# 每天起床第一句，先给自己打个气！

## 加油！ 加油！加油！

# 变身的三角形

## 区别
本次和上一次test的略有区别，是关于对着色器颜色的使用，主体的大部分都没有改变，学完之后会对OpenGL编程有一个大概的了解（了解大概的编写套路）。

## 顶点数组
首先是定义的数组问题
```cpp
GLfloat vertices[] =
{
    //三角形位置			    //颜色
    -0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	//左
    0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	//右
    0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f	//上
};
```
在上面关于数组的定义上可以发现，数组并不是只单纯的表示三角形的位置，他还表示了三角形的颜色，是每个顶点的颜色（很神奇的变化，我还不是很懂为什么最后会变成那个样子，先写吧~装死ing~），这是一个3X6的数组，关于为什么要这样子定义会在后面具体说明。

## 修改的顶点着色器
由于顶点数组定义的变化，所以需要修改顶点着色器的内容，除了之前对顶点位置的读取，还需要对顶点的颜色进行读取，并且建立一个输出，传输到片段着色器中。
```cpp
#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
out vec3 ourColor;
void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0f);
	ourColor = color;
}
```

## 修改的片段着色器
关于片段着色器的修改，仅仅是将原来固定赋值的颜色数据变成由外输入进来的数据，然后再输出出去。
```cpp
#version 330 core
in vec3 ourColor;
out vec4 color;
void main()
{
	color = vec4(ourColor, 0.7f);
}
```

## 指明顶点格式
```cpp
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) 0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*) (3*sizeof(GLfloat)));
glEnableVertexAttribArray(1);
```
在顶点格式的读取这边，第一个参数是之前.vs文件中定义的location = 0,1；第二个参数是读取几个数据；第五个参数后面的3改成了6，是因为之前读取3X3的数组的时候是每隔三个开始读数据，这里是3X6的数组需要每隔6个才能读取数据；最后一个参数是从哪一个参数开始读，显然颜色应该从第三个也就是第四个数据开始读取。

## END
差不多就是这些内容了，现在再看一遍之前的和现在的修改对比一下，应该就可以清除的知道相应的代码是控制哪一部分的了。<br>
那先这样，中秋快乐哟~下个礼拜见~
