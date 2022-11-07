#ifndef _MX_CONTEXT_H_
#define _MX_CONTEXT_H_

#include <vector>
#include <unordered_map>
#include <functional>
#include <memory.h>
#include "../gfx/contextRender.hpp"
#include "../gfx/contextRender3D.hpp"
#include "../core/types.hpp"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#elif defined(__unix__)
    // X11 Includes
    #include <X11/Xlib.h>
    #include <X11/Xutil.h>
    #include <X11/Xos.h>
    #include <GL/glx.h>
#endif

namespace mx
{

// OpenGL load function definition
typedef void (*GLLOADFN)(const char* name);
typedef void (*GLAPIFN)();
/**
 * @brief Return the process address of the OpenGL function
 * @param name Process name
 * @return GLAPIFN 
 */
GLAPIFN glGetProcAddress(const char* name);
void createGLContext(int targetID);

/**
 * @brief Flags for the context creation state
 */
enum class ContextFlags
{
    Default     = 0x00,
    Fullscreen  = 0x01,
    Borderless  = 0x02,
    AlwaysOnTop = 0x08,
    Support3D   = 0x10
};

/**
 * @brief Hints for loading OpenGL
 * 
 */
enum class ContextHint
{
    GLVERSION_MAJOR,
    GLVERSION_MINOR,
    // default to FORWARD COMPATIBILITY
    GL_COMPATIBILITY_CORE,
    // total hint count
    _LAST
};

namespace ContextEvent {
    typedef int code;
    constexpr code RESIZE        = 0;
    constexpr code MOUSEMOVE     = 1;
    constexpr code SCROLL        = 2;
    constexpr code BUTTONPRESS   = 3;
    constexpr code BUTTONRELEASE = 4;
    constexpr code KEYPRESS      = 5;
    constexpr code KEYRELEASE    = 6;
    constexpr code CLOSE         = 7;
    constexpr code LAST          = CLOSE;

    typedef void (*RESIZEFN       )(u32 _sizex, u32 _sizey, void* _params);
    typedef void (*MOUSEMOVEFN    )(u32 _x, u32 _y, void* _params);
    typedef void (*SCROLLFN       )(i32 _delta, void* _params);
    typedef void (*BUTTONPRESSFN  )(u32 _button, u32 _mods, void* _params);
    typedef void (*BUTTONRELEASEFN)(u32 _button, u32 _mods, void* _params);
    typedef void (*KEYPRESSFN     )(u32 _key, u32 _scancode, u32 _mods, void* _params);
    typedef void (*KEYRELEASEFN   )(u32 _key, u32 _scancode, u32 _mods, void* _params);
} // namespace Event
void invoke(int _targetID, mx::ContextEvent::code _code, u32 _arg0, u32 _arg1, u32 _arg2);

/**
 * @brief Context creation struct params
 */
struct ContextDesc
{
    /** Name of the window */
    std::string name = "MX";
    /** Size of the window */
    u32 sizex = 0, sizey = 0;
    /** Creation state flags */
    ContextFlags flags = ContextFlags::Default;
    /** OpenGL Hints (see ContextHints)*/
    int hints[3] = { 4, 6, 1 };
};

/**
 * @brief Platform-specific Handle of a window 
 */
struct PlatformHandle
{
    #if defined(_WIN32) || defined(_WIN64)
        int wID;
        void* wHandle;
        void* glHandle;
    #elif defined(__unix__)
        GLXContext glxc;
        Display* display;
        ::Window win;
        int screen;
        // events
        Atom wmDeleteMessage;
    #endif
};

/**
 * @brief Window with an OpenGL Context
 */
class Context
{
public:
    /**
     * @brief Construct a new Context
     * @param desc Creation state params
     */
    Context(const ContextDesc& desc);
    /**
     * @brief Destroy the OpenGL Context and the renderers associated
     */
    ~Context();

    /**
     * @brief Return true if the window should be closed
     * 
     * @return true the window should close
     * @return false the window should stay open
     */
    bool shouldClose() const;
    /**
     * @brief Make the OpenGL context current
     */
    void makeCurrent();
    /**
     * @brief Swap the buffers of the OpenGL Context
     */
    void swapBuffers();

    // events

    /**
     * @brief Update the event list and handle the events
     */
    void pollEvents();

    void registerOnResize(ContextEvent::RESIZEFN func, void* params);
    void registerOnMouseMove(ContextEvent::MOUSEMOVEFN func, void* params);
    void registerOnScroll(ContextEvent::SCROLLFN func, void* params);
    void registerOnButtonPress(ContextEvent::BUTTONPRESSFN func, void* params);
    void registerOnButtonRelease(ContextEvent::BUTTONRELEASEFN func, void* params);
    void registerOnKeyPress(ContextEvent::KEYPRESSFN func, void* params);
    void registerOnKeyRelease(ContextEvent::KEYRELEASEFN func, void* params);

    // data

    /**
     * @brief Get the Size X of the window (width)
     * @return u32 
     */
    u32 getSizeX() const;
    /**
     * @brief Get the Size Y of the window (height)
     * @return u32 
     */
    u32 getSizeY() const;

    /**
     * @brief Get the Platform Handle
     * @return PlatformHandle 
     */
    PlatformHandle getPlatformHandle() const;
    /**
     * @brief Get the Description of the Context
     * @return ContextDesc 
     */
    ContextDesc getDesc() const;

    /**
     * @brief Get the native 2D Renderer
     * @return ContextRender* 
     */
    ContextRender* get2DRenderer() const;
    /**
     * @brief Get the native 3D Renderer 
     * @return ContextRender3D* 
     */
    ContextRender3D* get3DRenderer() const;

    // Base Render methods

    /**
     * @brief Clear the buffer
     * @param red red channel [0-1]
     * @param green green channel [0-1]
     * @param blue blue channel [0-1] 
     * @param alpha channel [0-1] 
     */
    void clear(float red, float green, float blue, float alpha = 1.F);

private:
    ContextDesc desc;
    bool close = false;

    PlatformHandle handle;
    std::unique_ptr<ContextRender> render = nullptr;
    std::unique_ptr<ContextRender3D> render3D = nullptr;

    friend void createGLContext(int targetID);
    void setupBase(); 

// EVENTS
private:
    // Represent a registered event
    struct EventDescriptor
    {
        void* callback;
        void* params;
    };
    std::unordered_map<ContextEvent::code, std::vector<EventDescriptor>> eventCallbacks{};
    void invokeEvent(ContextEvent::code _code, u32 _arg0, u32 _arg1, u32 _arg2);
    friend void invoke(int targetID, mx::ContextEvent::code code, u32 arg0, u32 arg1, u32 arg2);

};


} // namespace mx


#endif //_MX_CONTEXT_H_