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
    // // build and compile our shader program
    // // ------------------------------------
    // // vertex shader
    // int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // 把这个着色器源码附加到着色器对象。着色器对象，源码字符串数量，VS真正的源码
    // glCompileShader(vertexShader);
    // // check for shader compile errors
    // int success;
    // char infoLog[512];
    // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    // if (!success)
    // {
    //     glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    // }
    // // fragment shader
    // int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // glCompileShader(fragmentShader);
    // // check for shader compile errors
    // glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    // if (!success)
    // {
    //     glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    // }
    // // link shaders
    // int shaderProgram = glCreateProgram(); // shaderProgram 是多个着色器合并之后并最终链接完成的版本
    // glAttachShader(shaderProgram, vertexShader); // 附加
    // glAttachShader(shaderProgram, fragmentShader);
    // glLinkProgram(shaderProgram);
    // // check for linking errors
    // glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    // if (!success) {
    //     glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    //     std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    // }
    // glDeleteShader(vertexShader);
    // glDeleteShader(fragmentShader);
 
 
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


