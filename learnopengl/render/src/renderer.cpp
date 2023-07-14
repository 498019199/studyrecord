#include <render/renderer.h>
#include <filesystem>
#include <fstream>
#include <sstream>

void renderer::init()
{
    shaderobj_ = std::make_shared<shader_object>();
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
                shaderobj_->init_shader(GL_VERTEX_SHADER);
                shaderobj_->load_pixel(content.c_str());
            }
            else
            {
                shaderobj_->init_shader(GL_FRAGMENT_SHADER);
                shaderobj_->load_fragment(content.c_str());
            }
        }
        
    }

    indexs_ = std::make_shared<index_buffer>();
    vertexs_ = std::make_shared<vertex_buffer>();
}

void renderer::before_render()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 
 
    shaderobj_->attach_shader();
    //创建VAO对象
    vertexs_->bind();
	//创建VBO对象，把顶点数组复制到一个顶点缓冲中，供OpenGL使用
    indexs_->bind(vertices, sizeof(vertices));
}

void renderer::render(float time)
{
    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw our first triangle
    shaderobj_->use_shader(); // 激活shaderProgram，怎么画
    glBindVertexArray(vertexs_->get_id()); // 画什么
    glDrawArrays(GL_TRIANGLES, 0, 3); // 开始画
}

void renderer::after_render()
{
    vertexs_->unbind();
    indexs_->unbind();

    // optional: de-allocate all resources
    shaderobj_->use_shader();
}
