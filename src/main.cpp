#include <mx/mxcro.hpp>
#include <mx/gfx/texture.hpp>
#include <mx/maths/quaternion.hpp>

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
    std::unique_ptr<mx::Context> ctx =
    std::make_unique<mx::Context>(
        mx::ContextDesc{
            "Test proj",
            400, 400,
            mx::ContextFlags::Support3D
        }
    );
    mx::ContextRender3D* render = ctx->get3DRenderer();

    // phsx

    mx::ShapeGeometry* shape = new mx::ShapeGeometry(mx::ShapeGeometryDesc{
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
    mx::Shader shader("../assets/shaders/simple.shader");
    mx::ShapeInstance instance(shape, 10);
    instance.add(mx::vec3{0.f, 0.f,  0.f});
    instance.add(mx::vec3{0.f, 2.f,  0.f});
    instance.add(mx::vec3{0.f, -2.f,  0.f});
    instance.add(mx::vec3{-6.f, -2.f,  0.f});
    instance.add(mx::vec3{7.f, -2.f,  3.f});
    render->addInstance(&instance);

    mx::Quaternion quat = mx::Quaternion::fromEulerAngles(.0f, .0f, .0f);
    mx::mat4 model = quat.toMat4();
    shader.setMat4("uModel", model);

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

        // update cubes
        float rotX = (float)std::sin(time);
        float rotY = (float)std::cos(time);
        float rotZ = (float)std::cos(time * 2);
        quat = mx::Quaternion::fromEulerAngles(rotX, rotY, rotZ);
        model = quat.toMat4();
        shader.setMat4("uModel", model);

        // update camera
        view = mx::mat4::lookAt(
            mx::vec3{rotX * radius, 0.f, rotY * radius},
            mx::vec3{0.f, 0.f, 0.f}
        );
        render->setCameraView(view);

        // draw
        render->draw(&shader);

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
