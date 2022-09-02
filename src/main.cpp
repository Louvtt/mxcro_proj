#include <mx/mxcro.h>
#include <mxphsx/mxphsx.h>

#include "object.h"

#include <iostream>
#include <chrono>

int main(int argc, char** argv)
{
    // render setup
    std::unique_ptr<mx::Context> ctx = std::make_unique<mx::Context>(
    mx::ContextDesc{
        "Test proj",
        400, 400
    });
    mx::ContextRender* render = ctx->get2DRenderer();

    // phsx
    mx::World* world = new mx::World();
    std::vector<Object*> objects = {
        new Object(mx::vec2{10.f,  20.f}, 30.f, ObjectShapeType::Box, world),
        new Object(mx::vec2{10.f, 200.f}, 50.f, ObjectShapeType::Box, world, true)
    };

    // main loop
    double time = 0.;
    std::chrono::duration<double> delta{.01666667};
    auto lastTime = std::chrono::high_resolution_clock::now();
    while(!ctx->shouldClose())
    {
        // clear
        ctx->clear(0.f, .5f, .6f);

        // update
        world->step(delta.count());

        // draw
        for(const auto& o : objects) {
            o->render(render);
        }
        render->draw();

        // update buffers
        ctx->swapBuffers();
        ctx->pollEvents();

        // update time
        delta = std::chrono::high_resolution_clock::now() - lastTime;
        lastTime = std::chrono::high_resolution_clock::now();
        time += delta.count();
    }

    ctx.reset();

    return 0;
}