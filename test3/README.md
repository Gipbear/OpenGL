# 好看的纹理

## 每天起床第一句，先给自己打个气！

## 映射
这一章是关于纹理的，所谓纹理就是将在图形上贴上你已有的图片，这里我们只介绍2D的纹理，为什么呢，因为1D和3D的我没学（理直气壮）。<br>
为了将纹理贴在我们定制好的图片上，需要一个叫做映射的方式，所谓映射就像拿着一个手电筒照一张照片，会在墙上留下照片的阴影，至于阴影的大小方向，就根据手电筒的大小和反向进行改变。我们这里是根据纹理坐标来调整的，以图片的左下角为(0,0)，右上角为(1,1)的形式建立坐标，将图片映射到建立的图形上。
```cpp
GLfloat vertices[] = {
		//位置					//纹理
		0.5f,0.5f,0.0f,			1.0f, 1.0f,
		0.5f,-0.5f,0.0f,		1.0f, 0.0f,
		-0.5f,-0.5f,0.0f,		0.0f, 0.0f,
		-0.5f,0.5f,0.0f,		0.0f, 1.0f
};
```
添加了纹理的坐标之后我们应该告诉OpenGL纹理坐标的存在，就和之前的关于顶点的一样，不过在这之前需要先修改一下顶点着色器和片段着色器。<br>
在顶点着色器中添加下列作为输入
> layout(location = 1) in vec2 texCoords;

并添加下面作为输出
> out vec2 TexCoords;

在main函数中同时也要将输入作用在输出上
> TexCoords = vec2(texCoords.x, 1.0f-texCoords.y);

在片段着色器中，将TexCoords输入
> in vec2 TexCoords;

同时利用下面用到的纹理来编辑颜色color，其实和之前赋值颜色坐标一样，纹理也是类似的各种颜色组合
> color = vec4(texture(ourTexture0, TexCoords).rgb, 1.0f);


```cpp
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
glEnableVertexAttribArray(1);
```
这个同样是在顶点着色器中使得顶点能够一一对应。


## 长方形的建立
在这里我们采用长方形来设计，不是因为和三角形设计不一样，而是因为长方形的绘制采用两个三角形的方式拼凑绘制，以后混合图形就可以触类旁通了。<br>
那么接下来先绘制长方形，关于VAO和VBO那部分和之前画三角形的类似，这里我们要多一个EBO，EBO也是一个缓冲，用来存储索引，原理类似不再多说。

## 生成纹理
首先定义一个纹理对象并激活绑定，
```cpp
GLuint texture;
glGenTextures(1, &texture);				//绑定纹理之前先激活纹理单元
glBindTexture(GL_TEXTURE_2D, texture);	//绑定
````
接下来就是选择纹理的一些设置了，关于纹理的设置有以下几种：
### 纹理环绕方式
纹理的坐标一般的在0到1.0之间的，若是超过了这个范围，则会使得纹理的映射并不是整个图像的大小，以后我们可能只会需要所给纹理的一部分，那么纹理的坐标就会在0到1之内，而纹理坐标一旦超过了这个范围，OpenGL则会默认重复复制这个纹理图像，但是OpenGL给了更多的选项

环绕方式|描述
-|:-
GL_REPEAT|对纹理的默认行为，重复纹理图像
GL_MIRRORED_REPEAT|和GL_REPEAT一样，但每次重复图片都是镜像放置的
GL_CLAMP_TO_EDGE|纹理坐标会被约束在0到1之间，超出部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果
GL_CLAMP_TO_BORDER|超出的坐标为用户指定的边缘颜色

![unfind image](https://learnopengl-cn.readthedocs.io/zh/latest/img/01/06/texture_wrapping.png)
之前提到的每个参数的使用都要对每个坐标轴设置，这里坐标轴的XYZ对应的是STR

### 纹理过滤
纹理坐标不依赖于分辨率，可以是任意浮点值，所以，OpenGL需要知道如何将纹理像素映射到纹理坐标上，当我们使用的是一很大的物体，但是纹理的分辨率很低，这个的设置就很重要了，同样的纹理的过滤设置也有很多选项，接下来我们介绍两个：GL_NEAREST和GL_LINEAR。<br>
GL_NEAREST是OpenGL的默认过滤方式，会主动选择离几个纹理像素中心最近的纹理作为样本颜色<br>
GL_LINEAR是线性过滤，基于纹理坐附近的纹理像素，计算出一个插值，近似出这些纹理之间的颜色，一个纹理像素的中心距离离纹理坐标越近，这个纹理像素对最终样本的贡献越大，最终的颜色其实就是这个纹理坐标附近的几个样本像素颜色的混合。
![unfind image](https://learnopengl-cn.readthedocs.io/zh/latest/img/01/06/texture_filtering.png)

## 加载并生成纹理
对纹理设置的准备工作已经准备好，接下来就是对纹理的获取了，纹理的获取是通过SOIL库进行读取的，关于SOIL库的配置在最开始的README.md中已经介绍过，所以这里就直接使用了。<br>
首先是导入
> #include "SOIL2/SOIL2.h" <br>
#include "SOIL2/stb_image.h"

对于纹理图片的加载，首先定义一个无符号的字符数组用来存放读取的纹理图像的信息，而我们读取的信息只有关于图像的颜色
```cpp
int width, height;		//图片大小
unsigned char* image = SOIL_load_image("image/bare_bears.jpg", &width, &height, 0, SOIL_LOAD_RGBA);
//第四个参数的说明需要读取什么信息，这里只关心颜色，所以读取成一个很大的数组
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
glGenerateMipmap(GL_TEXTURE_2D);
SOIL_free_image_data(image);
glBindTexture(GL_TEXTURE_2D, 0);
```
第二行是利用SOIL库中的函数SOIL_load_image来读取纹理图片，其中的参数解释一下，第一个参数是纹理的文件地址，第二三个是大小，最后一个是指明读取的纹理要关于什么的信息，这里我们只采集纹理的颜色，故只需要读取纹理的颜色RGB就可以，这些读取的纹理的颜色最终会以一个字符数组的形式存储下来。<br>
第三行是将已经绑定的纹理生成出来，第一个参数的纹理目标，第二个参数是指定多级渐远纹理的级别，这里只是基本级别，所以设置为0，第三个是我们想将纹理存储为什么格式，我们只读取了颜色，所以只存储为RGB格式，第四五个是之前设置的纹理的宽度和高度，第六个是历史版本遗留下来的问题，总是设置为0，第七八个是定义图像的格式和数据类型，使用RGB加载图像，并存储为char数组，最后一个就是我们之前读取的图像的值传入进来。<br>
第四行是在生成纹理之后调用glGenerateMipmap为当前绑定好的纹理自动生成需要的多级渐远纹理。<br>
之后的两行就是将图像内存释放，并且解绑纹理对象。

## 应用纹理
接下来就是在主函数内将纹理单元进行激活和绑定使用，并用uniform采样器选择相应的纹理单元
```cpp
//激活纹理单元并使用
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture);
glUniform1i(glGetUniformLocation(ourShader.Program, "ourTexture0"), 0);
```

## 收工
到这里纹理的设置和使用就差不多了，有很多疑问请点击[这里](www.baidu.com)，并输入你的疑问，回车！一切就迎刃而解了！，学习愉快！
