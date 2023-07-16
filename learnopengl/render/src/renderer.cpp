#include <render/renderer.h>
#include <filesystem>

void Renderer::Init()
{
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
}

void Renderer::BeforeRender()
{
    float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
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
	vertexs_->UnBind();
}

void Renderer::Render(float time)
{
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // draw our first triangle
    shaderobj_->UseShader(); // 激活shaderProgram，怎么画
    glBindVertexArray(vertexs_->GetId()); // 画什么
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::AfterRender()
{
}
