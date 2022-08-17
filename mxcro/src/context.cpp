#include "mx/context.h"

#include <glad/gl.h>

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

mx::Context::PlatformHandle mx::Context::getPlatformHandle() const
{
    return handle;
}

bool mx::Context::shouldClose() const
{
    return close;
}

mx::ContextDesc mx::Context::getDesc() const
{
    return desc;
}

mx::ContextRender* mx::Context::get2DRenderer() const
{
    return render;
}



// EVENT REGISTER

void mx::Context::registerOnResize(mx::ContextEvent::RESIZEFN _callback, void* _params)
{
    if(eventCallbacks.find(mx::ContextEvent::RESIZE) == eventCallbacks.end())
        eventCallbacks.insert({mx::ContextEvent::RESIZE, std::vector<EventDescriptor>()});

    eventCallbacks.at(mx::ContextEvent::RESIZE).push_back(mx::Context::EventDescriptor{
        (void*)_callback,
        _params
    });
}
void mx::Context::registerOnMouseMove(mx::ContextEvent::MOUSEMOVEFN _callback, void* _params)
{
    if(eventCallbacks.find(mx::ContextEvent::MOUSEMOVE) == eventCallbacks.end())
        eventCallbacks.insert({mx::ContextEvent::MOUSEMOVE, std::vector<EventDescriptor>()});
    
    eventCallbacks.at(mx::ContextEvent::MOUSEMOVE).push_back(mx::Context::EventDescriptor{
        (void*)_callback,
        _params
    });
}
void mx::Context::registerOnScroll(mx::ContextEvent::SCROLLFN _callback, void* _params)
{
    if(eventCallbacks.find(mx::ContextEvent::SCROLL) == eventCallbacks.end())
        eventCallbacks.insert({mx::ContextEvent::SCROLL, std::vector<EventDescriptor>()});
    
    eventCallbacks.at(mx::ContextEvent::SCROLL).push_back(mx::Context::EventDescriptor{
        (void*)_callback,
        _params
    });
}
void mx::Context::registerOnButtonPress(mx::ContextEvent::BUTTONPRESSFN _callback, void* _params)
{
    if(eventCallbacks.find(mx::ContextEvent::BUTTONPRESS) == eventCallbacks.end())
        eventCallbacks.insert({mx::ContextEvent::BUTTONPRESS, std::vector<EventDescriptor>()});
    
    eventCallbacks.at(mx::ContextEvent::BUTTONPRESS).push_back(mx::Context::EventDescriptor{
        (void*)_callback,
        _params
    });
}
void mx::Context::registerOnButtonRelease(mx::ContextEvent::BUTTONRELEASEFN _callback, void* _params)
{
    if(eventCallbacks.find(mx::ContextEvent::BUTTONRELEASE) == eventCallbacks.end())
        eventCallbacks.insert({mx::ContextEvent::BUTTONRELEASE, std::vector<EventDescriptor>()});
    
    eventCallbacks.at(mx::ContextEvent::BUTTONRELEASE).push_back(mx::Context::EventDescriptor{
        (void*)_callback,
        _params
    });
}
void mx::Context::registerOnKeyPress(mx::ContextEvent::KEYPRESSFN _callback, void* _params)
{
    if(eventCallbacks.find(mx::ContextEvent::KEYPRESS) == eventCallbacks.end())
        eventCallbacks.insert({mx::ContextEvent::KEYPRESS, std::vector<EventDescriptor>()});
    
    eventCallbacks.at(mx::ContextEvent::KEYPRESS).push_back(mx::Context::EventDescriptor{
        (void*)_callback,
        _params
    });
}
void mx::Context::registerOnKeyRelease(mx::ContextEvent::KEYRELEASEFN _callback, void* _params)
{
    if(eventCallbacks.find(mx::ContextEvent::KEYRELEASE) == eventCallbacks.end())
        eventCallbacks.insert({mx::ContextEvent::KEYRELEASE, std::vector<EventDescriptor>()});
    
    eventCallbacks.at(mx::ContextEvent::KEYRELEASE).push_back(mx::Context::EventDescriptor{
        (void*)_callback,
        _params
    });
}

#define INVKEVENT(name, ...)                                             \
    case mx::ContextEvent::name:                                          \
    for(const auto& desc : eventCallbacks.at(_code))                     \
    ((mx::ContextEvent::name##FN)desc.callback)(__VA_ARGS__, desc.params);\
    break;

void mx::Context::invokeEvent(mx::ContextEvent::code _code, u32 _arg0, u32 _arg1, u32 _arg2)
{
    if(eventCallbacks.find(_code) == eventCallbacks.end()) return;
    switch(_code)
    {
        INVKEVENT(RESIZE,        _arg0, _arg1);
        INVKEVENT(MOUSEMOVE,     _arg0, _arg1);
        INVKEVENT(SCROLL,        (i32)_arg0);
        INVKEVENT(BUTTONPRESS,   _arg0, _arg1);
        INVKEVENT(BUTTONRELEASE, _arg0, _arg1);
        INVKEVENT(KEYPRESS,      _arg0, _arg1, _arg2);
        INVKEVENT(KEYRELEASE,    _arg0, _arg1, _arg2);
    }
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
    glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
    glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, desc.sizex, desc.sizey);
    if((int)desc.flags & (int)mx::ContextFlags::Support3D != 0) {
        glEnable(GL_DEPTH);
    }

    registerOnResize([](u32 _sizex, u32 _sizey, void* params){
        mx::ContextDesc* target = (mx::ContextDesc*)params;
        target->sizex = _sizex;
        target->sizey = _sizey;
        glViewport(0, 0, _sizex, _sizey);
    }, &this->desc);

    render = new ContextRender({
        4096,
        this
    });
} 

void mx::Context::clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    if(((int)desc.flags & 0x10) != 0) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    } else {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}