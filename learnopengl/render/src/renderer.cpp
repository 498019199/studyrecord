#include <render/renderer.h>
#include <filesystem>

void renderer::init()
{
    shaderobj_ = std::make_shared<shader_object>();
    if (!shaderobj_)
    {
        return;
    }
    
    shaderobj_->init();
    auto path = std::filesystem::current_path();
    auto str_path = path.append("//shader").string();
    for (auto it : {"fragment.glsl", "vertex.glsl"})
    {
        auto file_name = str_path + it;
        if (std::filesystem::exists(file_name))
        {
            //shaderobj_->
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
