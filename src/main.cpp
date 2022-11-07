#include <mx/mxcro.hpp>
#include <mx/gfx/texture.hpp>

#include <iostream>
#include <chrono>
float vertices[] = {
        // pos               // normals
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

int main(int argc, char** argv)
{
    // render setup
    std::unique_ptr<mx::Context> ctx = std::make_unique<mx::Context>(
    mx::ContextDesc{
        "Test proj",
        400, 400,
        mx::ContextFlags::Support3D
    });
    mx::ContextRender3D* render = ctx->get3DRenderer();

    // phsx

    mx::ShapeDrawData* shape = new mx::ShapeDrawData({
        new mx::VertexBuffer(
        mx::BufferDesc{
            36,
            false,
            6 * sizeof(float),
            &vertices[0]
        }),
        nullptr,
        {
            mx::AttributeType::Pos3D,
            mx::AttributeType::Float3
        }
    });
    mx::Shader shader("assets/shaders/simple.shader");
    mx::ShapeInstance instance(shape, &shader, 10);
    instance.add(mx::vec3{0.f, 0.f,  0.f});
    instance.add(mx::vec3{0.f, 2.f,  0.f});
    instance.add(mx::vec3{0.f, -2.f,  0.f});
    render->addInstance(&instance);

    float radius = 10.f;
    mx::mat4 view = mx::mat4::lookAt(
        mx::vec3{0.f, 0.f, radius},
        mx::vec3{0.f, 0.f, 0.f}
    );
    render->setCameraView(view);


    // main loop
    double time = 0.;
    std::chrono::duration<double> delta{.01666667};
    auto lastTime = std::chrono::high_resolution_clock::now();
    while(!ctx->shouldClose())
    {
        // clear
        ctx->clear(0.f, .5f, .6f);

        // update cam
        float camX = (float)std::sin(time) * radius;
        float camZ = (float)std::cos(time) * radius;
        view = mx::mat4::lookAt(
            mx::vec3{camX, 0.f, camZ},
            mx::vec3{0.f, 0.f, 0.f}
        );
        render->setCameraView(view);

        // draw
        render->draw();

        // update buffers
        ctx->swapBuffers();
        ctx->pollEvents();

        // update time
        delta    = std::chrono::high_resolution_clock::now() - lastTime;
        lastTime = std::chrono::high_resolution_clock::now();
        time    += delta.count();
    }

    delete shape;

    ctx.reset();

    return 0;
}