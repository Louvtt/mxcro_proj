#include <mx/mxcro.h>

#include <iostream>

int main(int argc, char** argv)
{
    std::unique_ptr<mx::Context> ctx = std::make_unique<mx::Context>(
    mx::ContextDesc{
        "Test proj",
        400, 400
    });

    mx::ContextRender* render = ctx->get2DRenderer();

    while(!ctx->shouldClose())
    {
        ctx->clear(0.f, .5f, .6f);

        render->drawRect(mx::vec2{10.f, -40.f}, mx::vec2{10.f, 10.f});
        render->drawRect(mx::vec2{20.F,   0.f}, mx::vec2{10.f, 10.f});
        render->drawLine(
            mx::vec2{10.f,  10.f}, mx::vec2{50.f, 50.f},
            mx::Color(1.f, 1.f, 0.f, 0.f), mx::Color(1.f, 1.f, 0.f)
        );
        render->draw();
        
        ctx->swapBuffers();
        ctx->pollEvents();
    }

    ctx.reset();

    return 0;
}