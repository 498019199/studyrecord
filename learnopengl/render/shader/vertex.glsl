#version 420 core
layout (location = 0) in vec3 aPos;   // 位置变量的属性位置值为 0 
layout (location = 1) in vec3 aColor; // 颜色变量的属性位置值为 
layout (location = 2) in vec2 aTexCoord;
// in 位置（x,y,z），颜色(rgb)，图片(x,y)
// out 颜色(rgb)，图片(x,y)
out vec3 ourColor;
out vec2 TexCoord;
uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    ourColor = aColor; // 将ourColor设置为我们从顶点数据那里得到的输入颜色
    TexCoord = aTexCoord;
}