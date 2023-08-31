#include <render/renderer.h>
#include <filesystem>
#include <math/matrix.h>
#include <math/math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace MathWorker;

namespace RenderWorker
{

void Renderer::Init(int width, int height)
{
    width_ = width; 
    height_ = height;
    
    shaderobj_ = std::make_shared<ShaderObject>();
    if (!shaderobj_)
    {
        return;
    }

    auto path = std::filesystem::current_path();
    path += "\\render\\shader\\";
    shaderobj_->LoadShader(path.string() + "vertex.glsl",
        path.string() + "fragment.glsl");

    vertexs_ = std::make_shared<VertexArray>();
    vertex_buf_ = std::make_shared<VertexBuffer>();
    indexs_ = std::make_shared<IndexBuffer>();
    texture2d_ = std::make_shared<Texture2D>();

    texture2d_->LoadImage(path.string() + "container.jpg");
    shaderobj_->UseShader(); 
    shaderobj_->Uniform1i("ourTexture", 0);
}

void Renderer::BeforeRender()
{
    float vertices[] = {
        //     ---- 位置 ----  - 纹理坐标 -
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    // unsigned int indices[] = {
    //     // 注意索引从0开始! 
    //     // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
    //     // 这样可以由下标代表顶点组合成矩形

    //     0, 1, 3, // 第一个三角形
    //     1, 2, 3  // 第二个三角形
    // };
 
    shaderobj_->AttachShader();
    //创建VAO对象
    vertexs_->Bind();
    //创建VBO对象，把顶点数组复制到一个顶点缓冲中，供OpenGL使用
    vertex_buf_->Bind(vertices, sizeof(vertices));
    //indexs_->Bind(indices, sizeof(indices));
    texture2d_->BindTexture();
}

void Renderer::Render(float time)
{
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    float4x4 model = MatrixRotate(float3(0.5f, 1.0f, 0.0f), time);
    float4x4 view = MatrixMove(0.0f, 0.0f, -3.0f);
    float4x4 projection = PerspectiveFovRH(Deg2Rad(45.f), float(width_)/float(height_), 0.1f, 100.f);
    float4x4 mvp = projection * view * model;

    glm::mat4 model2         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 view2          = glm::mat4(1.0f);
    glm::mat4 projection2    = glm::mat4(1.0f);
    model2 = glm::rotate(model2, time, glm::vec3(0.5f, 1.0f, 0.0f));
    view2  = glm::translate(view2, glm::vec3(0.0f, 0.0f, -3.0f));
    projection2 = glm::perspective(glm::radians(45.0f), float(width_)/float(height_), 0.1f, 100.0f);
    glm::mat4 mvp2  = projection2 * view2 * model2;
    std::cout << mvp2[0][0] << " " << mvp2[0][1] << " " << mvp2[0][2] << " " << mvp2[0][3] << std::endl;
    std::cout << mvp2[1][0] << " " << mvp2[1][1] << " " << mvp2[1][2] << " " << mvp2[1][3] << std::endl;
    std::cout << mvp2[2][0] << " " << mvp2[2][1] << " " << mvp2[2][2] << " " << mvp2[2][3] << std::endl;
    std::cout << mvp2[3][0] << " " << mvp2[3][1] << " " << mvp2[3][2] << " " << mvp2[3][3] << std::endl;


    shaderobj_->UniformMatrix4fv("model", model);
    shaderobj_->UniformMatrix4fv("view", float4x4::Identity());
    shaderobj_->UniformMatrix4fv("projection", float4x4::Identity());
    //glUniformMatrix4fv(glGetUniformLocation(shaderobj_->GetId(), name), 1, GL_FALSE, mat.data());

    // draw our first triangle
    shaderobj_->UseShader(); // 激活shaderProgram，怎么画
    
    // render box
    glBindVertexArray(vertexs_->GetId()); // 画什么
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Renderer::AfterRender()
{
    vertexs_->UnBind();
}


}