#include <render/app.h>
#include <iostream>
//#include <math/math.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
 
// 顶点着色器，GLSL语言
const char *vertexShaderSource = "#version 330 core\n" 
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" 
    "}\0";
// 片元着色器
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";



int main()
{
    
    app* main_app = new app();
    if (nullptr == main_app)
    {
        return 0;
    }
    main_app->create_windows(800, 600, "OpenGLLearn");
    main_app->run();
 
    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f, // left  
    //      0.5f, -0.5f, 0.0f, // right 
    //      0.0f,  0.5f, 0.0f  // top   
    // }; 
 
    // unsigned int VBO, VAO;
	// //创建VAO对象
    // glGenVertexArrays(1, &VAO);
	// glBindVertexArray(VAO);
	// //创建VBO对象，把顶点数组复制到一个顶点缓冲中，供OpenGL使用
    // glGenBuffers(1, &VBO);
    // glBindBuffer(GL_ARRAY_BUFFER, VBO); // 缓冲绑定到GL_ARRAY_BUFFER
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // 顶点数据复制到缓冲的内存中
 
	// //解释顶点数据方式
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // 顶点数据的解释
    // glEnableVertexAttribArray(0);
 
    // // 解绑VAO
	// glBindVertexArray(0); 
	// // 解绑VBO
    // glBindBuffer(GL_ARRAY_BUFFER, 0); 
 

 
    // // optional: de-allocate all resources
    // glDeleteVertexArrays(1, &VAO);
    // glDeleteBuffers(1, &VBO);
    // glDeleteProgram(shaderProgram);
    // glfwTerminate();
    
    return 0;
}


