#include <render/renderer.h>
#include <filesystem>
#include <fstream>
#include <sstream>

void Renderer::Init()
{
    shaderobj_ = std::make_shared<ShaderObject>();
    if (!shaderobj_)
    {
        return;
    }

    auto path = std::filesystem::current_path();
    path += "\\render\\shader\\";
    for (auto it : {"fragment.glsl", "vertex.glsl"})
    {
        auto file_name = path.string() + it;
        if (std::filesystem::exists(file_name))
        {
            std::ifstream fp(file_name);
            if (!fp.is_open()) 
            {
                continue;
            }
            std::ostringstream oss;
            oss << fp.rdbuf();
            std::string content = oss.str();
            fp.close();

            if (0 == strcmp("vertex.glsl", it))
            {
                shaderobj_->InitShader(GL_VERTEX_SHADER);
                shaderobj_->LoadPixel(content.c_str());
            }
            else
            {
                shaderobj_->InitShader(GL_FRAGMENT_SHADER);
                shaderobj_->LoadFragment(content.c_str());
            }
        }
        
    }

    vertexs_ = std::make_shared<VertexArray>();
    vertex_buf_ = std::make_shared<VertexBuffer>();
    indexs_ = std::make_shared<IndexBuffer>();
}

void Renderer::BeforeRender()
{
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    unsigned int indices[] = {
        // 注意索引从0开始! 
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形

        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
 
    shaderobj_->AttachShader();
    //创建VAO对象
    vertexs_->Bind();
    //创建VBO对象，把顶点数组复制到一个顶点缓冲中，供OpenGL使用
    vertex_buf_->Bind(vertices, sizeof(vertices));
    indexs_->Bind(indices, sizeof(indices));
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
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::AfterRender()
{
}
