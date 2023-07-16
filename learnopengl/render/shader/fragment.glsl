#version 330 core
out vec4 FragColor;

uniform vec4 outColor; // 在OpenGL程序代码中设定这个变量
void main()
{
    FragColor = outColor;
};