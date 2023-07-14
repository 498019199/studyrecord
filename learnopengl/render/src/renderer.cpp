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

    indexs_ = std::make_shared<IndexBuffer>();
    vertexs_ = std::make_shared<VertexBuffer>();
}

void Renderer::BeforeRender()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 
 
    shaderobj_->AttachShader();
    //创建VAO对象
    vertexs_->Bind(vertices, sizeof(vertices));
	//创建VBO对象，把顶点数组复制到一个顶点缓冲中，供OpenGL使用
    indexs_->Bind(vertices, sizeof(vertices));
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
    glDrawArrays(GL_TRIANGLES, 0, 3); // 开始画
}

void Renderer::AfterRender()
{
    vertexs_->UnBind();
    indexs_->UnBind();

    // optional: de-allocate all resources
    shaderobj_->DetachShader();
}
