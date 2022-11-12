#include <glad/gl.h>
#include "mx/core/context.hpp"

#include <iostream>
#define LOG(msg) std::cout << msg << std::endl;
#define ERR(msg) std::cerr << msg << std::endl;

#define GLCASETOSTR(name) case name: return #name;

const char* getGLSourceStr(GLenum _source)
{
    switch(_source)
    {
        GLCASETOSTR(GL_DEBUG_SOURCE_API)
        GLCASETOSTR(GL_DEBUG_SOURCE_APPLICATION)
        GLCASETOSTR(GL_DEBUG_SOURCE_OTHER)
        GLCASETOSTR(GL_DEBUG_SOURCE_SHADER_COMPILER)
        GLCASETOSTR(GL_DEBUG_SOURCE_THIRD_PARTY)
        GLCASETOSTR(GL_DEBUG_SOURCE_WINDOW_SYSTEM)
    }
    return "GL_DEBUG_SOURCE_UNKNOWN";
}

const char* getGLTypeStr(GLenum _type)
{
    switch(_type)
    {
        GLCASETOSTR(GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
        GLCASETOSTR(GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)
        GLCASETOSTR(GL_DEBUG_TYPE_ERROR)
        GLCASETOSTR(GL_DEBUG_TYPE_MARKER)
        GLCASETOSTR(GL_DEBUG_TYPE_OTHER)
        GLCASETOSTR(GL_DEBUG_TYPE_PERFORMANCE)
        GLCASETOSTR(GL_DEBUG_TYPE_POP_GROUP)
        GLCASETOSTR(GL_DEBUG_TYPE_PORTABILITY)
        GLCASETOSTR(GL_DEBUG_TYPE_PUSH_GROUP)
    }
    return "GL_DEBUG_TYPE_UNKNOWN";
}

const char* getGLSeverityStr(GLenum _severity) 
{
    switch(_severity)
    {
        GLCASETOSTR(GL_DEBUG_SEVERITY_LOW)
        GLCASETOSTR(GL_DEBUG_SEVERITY_MEDIUM)
        GLCASETOSTR(GL_DEBUG_SEVERITY_HIGH)
        GLCASETOSTR(GL_DEBUG_SEVERITY_NOTIFICATION)
        GLCASETOSTR(GL_DONT_CARE)
    }
    return "GL_SEVERITY_UNKNOWN";
}

const char* getGLIDStr(GLuint _id)
{
    switch(_id)
    {
        GLCASETOSTR(GL_INVALID_ENUM)
        GLCASETOSTR(GL_INVALID_FRAMEBUFFER_OPERATION)
        GLCASETOSTR(GL_INVALID_INDEX)
        GLCASETOSTR(GL_INVALID_OPERATION)
        GLCASETOSTR(GL_INVALID_VALUE)
    }
    return "GL_UNKNOWN";
}

#undef GLCASETOSTR

static void glDebugCallback(GLenum _source, GLenum _type, GLuint _id, GLenum _severity, GLsizei _length, const GLchar* _message, const void* _userParam)
{
    #ifdef _DEBUG
    if(_severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
        LOG("GL_LOG:[From " << getGLSourceStr(_source) << "]: " << _message);
        return;
    }
    #endif
    
    ERR(
        "GL_ERROR[" << getGLSeverityStr(_severity)  <<"]:" <<
        getGLTypeStr(_type) << ":" <<
        getGLSourceStr(_source) << ":" <<
        getGLIDStr(_id) << ":" <<
        _message
    );
}

unsigned int mx::Context::getSizeX() const { return desc.sizex; }
unsigned int mx::Context::getSizeY() const { return desc.sizey; }

mx::PlatformHandle mx::Context::getPlatformHandle() const
{
    return handle;
}

bool mx::Context::shouldClose() const
{
    return close;
}

void mx::Context::setShouldClose(bool shouldClose)
{
    close = shouldClose;
}

mx::ContextDesc mx::Context::getDesc() const
{
    return desc;
}

mx::ContextRender* mx::Context::get2DRenderer() const
{
    return render.get();
}

mx::ContextRender3D* mx::Context::get3DRenderer() const
{
    return render3D.get();
}

void mx::Context::setupEvents()
{
    mx::EventManager* eventManager = mx::EventManager::Get();
    eventManager->registerEvent<mx::ResizeEvent>();
    eventManager->registerEvent<mx::KeyEvent>();
    eventManager->registerEvent<mx::ButtonEvent>();
    eventManager->registerEvent<mx::CloseEvent>();
    eventManager->registerEvent<mx::MouseMoveEvent>();
    eventManager->registerEvent<mx::ScrollEvent>();
}


void mx::Context::setupBase()
{
    int success = gladLoadGL((GLADloadfunc)mx::glGetProcAddress);
    if(!success)
    {
        ERR("Failed to load glad.");
        return;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(glDebugCallback, NULL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, desc.sizex, desc.sizey);
    if(((int)desc.flags & (int)mx::ContextFlags::Support3D) != 0) {
        LOG("Enabling depth testing");
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    render = std::make_unique<mx::ContextRender>(
    mx::ContextRenderDesc{
        4096,
        this
    });
    render3D = std::make_unique<mx::ContextRender3D>(
    mx::ContextRender3DDesc{
        4096,
        this
    });

    // default resize callback
    EventManager::Get()->getEvent<mx::ResizeEvent>()->registerCallback(
        [](mx::ResizeEventArgs args, void* params) {
            mx::Context* target = (mx::Context*)params;
            target->desc.sizex = args.sizeX;
            target->desc.sizey = args.sizeY;
            glViewport(0, 0, args.sizeX, args.sizeY);
            target->render->resize(args.sizeX, args.sizeY);
            target->render3D->resize(args.sizeX, args.sizeY);
        }, this
    );
} 

void mx::Context::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    if(((int)desc.flags & (int)mx::ContextFlags::Support3D) != 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    } else {
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
}