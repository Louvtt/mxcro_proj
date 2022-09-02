#include "mx/context.h"

#include "mx/keycodes.h"

// X11
#include <X11/Xatom.h>
// GL X11
#include <GL/glxext.h>
#pragma comment lib("opengl32.lib")

#include <iostream>
#define ERR(msg) std::cerr << "ERROR: " << msg << std::endl;
#define LOG(msg) std::cout << "LOG: " << msg << std::endl;



// create context arb
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

constexpr static int translateXKeycode(const KeySym& key)
{
    switch(key)
    {
        // specials keys
        case XK_Escape:         return MX_KEY_ESCAPE;
        case XK_Return:         return MX_KEY_ENTER;
        case XK_Tab:            return MX_KEY_TAB;
        case XK_BackSpace:      return MX_KEY_BACKSPACE;
        case XK_Insert:         return MX_KEY_INSERT;
        case XK_Delete:         return MX_KEY_DELETE;
        // arrows
        case XK_Right:          return MX_KEY_RIGHT;
        case XK_Left:           return MX_KEY_LEFT;
        case XK_Down:           return MX_KEY_DOWN;
        case XK_Up:             return MX_KEY_UP;
        // strange keys
        case XK_Page_Up:        return MX_KEY_PAGE_UP;
        case XK_Page_Down:      return MX_KEY_PAGE_DOWN;
        case XK_Home:           return MX_KEY_HOME;
        case XK_End:            return MX_KEY_END;
        case XK_Caps_Lock:      return MX_KEY_CAPS_LOCK;
        case XK_Scroll_Lock:    return MX_KEY_SCROLL_LOCK;
        case XK_Num_Lock:       return MX_KEY_NUM_LOCK;
        case XK_Print:          return MX_KEY_PRINT_SCREEN;
        case XK_Pause:          return MX_KEY_PAUSE;
        // function keys
        case XK_F1:             return MX_KEY_F1;
        case XK_F2:             return MX_KEY_F2;
        case XK_F3:             return MX_KEY_F3;
        case XK_F4:             return MX_KEY_F4;
        case XK_F5:             return MX_KEY_F5;
        case XK_F6:             return MX_KEY_F6;
        case XK_F7:             return MX_KEY_F7;
        case XK_F8:             return MX_KEY_F8;
        case XK_F9:             return MX_KEY_F9;
        case XK_F10:            return MX_KEY_F10;
        case XK_F11:            return MX_KEY_F11;
        case XK_F12:            return MX_KEY_F12;
        case XK_F13:            return MX_KEY_F13;
        case XK_F14:            return MX_KEY_F14;
        case XK_F15:            return MX_KEY_F15;
        case XK_F16:            return MX_KEY_F16;
        case XK_F17:            return MX_KEY_F17;
        case XK_F18:            return MX_KEY_F18;
        case XK_F19:            return MX_KEY_F19;
        case XK_F20:            return MX_KEY_F20;
        case XK_F21:            return MX_KEY_F21;
        case XK_F22:            return MX_KEY_F22;
        case XK_F23:            return MX_KEY_F23;
        case XK_F24:            return MX_KEY_F24;
        case XK_F25:            return MX_KEY_F25;

        // punctuation
        case XK_space:          return MX_KEY_SPACE;
        case XK_apostrophe:     return MX_KEY_APOSTROPHE;
        case XK_comma:          return MX_KEY_COMMA;
        case XK_minus:          return MX_KEY_MINUS;
        case XK_period:         return MX_KEY_PERIOD;
        case XK_slash:          return MX_KEY_SLASH;
        case XK_semicolon:      return MX_KEY_SEMICOLON;
        case XK_equal:          return MX_KEY_EQUAL;
        case XK_bracketleft:    return MX_KEY_LEFT_BRACKET;
        case XK_backslash:      return MX_KEY_BACKSLASH;
        case XK_bracketright:   return MX_KEY_RIGHT_BRACKET;
        case XK_grave:          return MX_KEY_GRAVE_ACCENT;
        // numbers
        case XK_0:      return MX_KEY_0;
        case XK_1:      return MX_KEY_1;
        case XK_2:      return MX_KEY_2;
        case XK_3:      return MX_KEY_3;
        case XK_4:      return MX_KEY_4;
        case XK_5:      return MX_KEY_5;
        case XK_6:      return MX_KEY_6;
        case XK_7:      return MX_KEY_7;
        case XK_8:      return MX_KEY_8;
        case XK_9:      return MX_KEY_9;
        // letters uppercase
        case XK_A:      return MX_KEY_A;
        case XK_B:      return MX_KEY_B;
        case XK_C:      return MX_KEY_C;
        case XK_D:      return MX_KEY_D;
        case XK_E:      return MX_KEY_E;
        case XK_F:      return MX_KEY_F;
        case XK_G:      return MX_KEY_G;
        case XK_H:      return MX_KEY_H;
        case XK_I:      return MX_KEY_I;
        case XK_J:      return MX_KEY_J;
        case XK_K:      return MX_KEY_K;
        case XK_L:      return MX_KEY_L;
        case XK_M:      return MX_KEY_M;
        case XK_N:      return MX_KEY_N;
        case XK_O:      return MX_KEY_O;
        case XK_P:      return MX_KEY_P;
        case XK_Q:      return MX_KEY_Q;
        case XK_R:      return MX_KEY_R;
        case XK_S:      return MX_KEY_S;
        case XK_T:      return MX_KEY_T;
        case XK_U:      return MX_KEY_U;
        case XK_V:      return MX_KEY_V;
        case XK_W:      return MX_KEY_W;
        case XK_X:      return MX_KEY_X;
        case XK_Y:      return MX_KEY_Y;
        case XK_Z:      return MX_KEY_Z;
        // letters lowercase
        case XK_a:      return MX_KEY_A;
        case XK_b:      return MX_KEY_B;
        case XK_c:      return MX_KEY_C;
        case XK_d:      return MX_KEY_D;
        case XK_e:      return MX_KEY_E;
        case XK_f:      return MX_KEY_F;
        case XK_g:      return MX_KEY_G;
        case XK_h:      return MX_KEY_H;
        case XK_i:      return MX_KEY_I;
        case XK_j:      return MX_KEY_J;
        case XK_k:      return MX_KEY_K;
        case XK_l:      return MX_KEY_L;
        case XK_m:      return MX_KEY_M;
        case XK_n:      return MX_KEY_N;
        case XK_o:      return MX_KEY_O;
        case XK_p:      return MX_KEY_P;
        case XK_q:      return MX_KEY_Q;
        case XK_r:      return MX_KEY_R;
        case XK_s:      return MX_KEY_S;
        case XK_t:      return MX_KEY_T;
        case XK_u:      return MX_KEY_U;
        case XK_v:      return MX_KEY_V;
        case XK_w:      return MX_KEY_W;
        case XK_x:      return MX_KEY_X;
        case XK_y:      return MX_KEY_Y;
        case XK_z:      return MX_KEY_Z;
        // keypad
        case XK_KP_0:               return MX_KEY_KP_0;
        case XK_KP_1:               return MX_KEY_KP_1;
        case XK_KP_2:               return MX_KEY_KP_2;
        case XK_KP_3:               return MX_KEY_KP_3;
        case XK_KP_4:               return MX_KEY_KP_4;
        case XK_KP_5:               return MX_KEY_KP_5;
        case XK_KP_6:               return MX_KEY_KP_6;
        case XK_KP_7:               return MX_KEY_KP_7;
        case XK_KP_8:               return MX_KEY_KP_8;
        case XK_KP_9:               return MX_KEY_KP_9;
        case XK_KP_Decimal:         return MX_KEY_KP_DECIMAL;
        case XK_KP_Divide:          return MX_KEY_KP_DIVIDE;
        case XK_KP_Multiply:        return MX_KEY_KP_MULTIPLY;
        case XK_KP_Subtract:        return MX_KEY_KP_SUBTRACT;
        case XK_KP_Add:             return MX_KEY_KP_ADD;
        case XK_KP_Enter:           return MX_KEY_KP_ENTER;
        case XK_KP_Equal:           return MX_KEY_KP_EQUAL;

        // mods
        case XK_Shift_L:            return MX_KEY_LEFT_SHIFT;
        case XK_Control_L:          return MX_KEY_LEFT_CONTROL;
        case XK_Alt_L:              return MX_KEY_LEFT_ALT;
        case XK_Super_L:            return MX_KEY_LEFT_SUPER;
        case XK_Shift_R:            return MX_KEY_RIGHT_SHIFT;
        case XK_Control_R:          return MX_KEY_RIGHT_CONTROL;
        case XK_Alt_R:              return MX_KEY_RIGHT_ALT;
        case XK_Super_R:            return MX_KEY_RIGHT_SUPER;
        case XK_Menu:               return MX_KEY_MENU;
    }

    return MX_KEY_UNKNOWN;
}
constexpr static int translateXButtonCode(int button)
{
    switch(button)
    {}

    return MX_KEY_UNKNOWN;
}

mx::Context::Context(const char* name, u32 sizex, u32 sizey, ContextFlags flags)
{
    // open x server
    display = XOpenDisplay(NULL);
    if(display == NULL) {
        ERR("X11: Cannot open display");
        return;
    }
    // get the screen number
    screen = DefaultScreen(display);

    // get white and black pixel
    u32 black, white;
    black = BlackPixel(display, screen);
    white = WhitePixel(display, screen);

    // setup visual
    #ifdef GLX_ARB_create_context
    GLint glxAttribs[] = {
		GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , True,
		None
    };

    int fbcount;
    GLXFBConfig* fbc = glXChooseFBConfig(display, screen, glxAttribs, &fbcount);
    LOG("GLX: Found " << fbcount << " compatible framebuffers.");
    XVisualInfo* visual = glXGetVisualFromFBConfig(display, fbc[0]);

    // load createcontextattribARB
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = NULL;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc)glXGetProcAddressARB((const GLubyte*)"glXCreateContextAttribsARB");
    if(glXCreateContextAttribsARB != NULL)
    {
        int glxContextAttributes[] = {
            GLX_CONTEXT_MAJOR_VERSION_ARB, hints[(int)WindowHint::GLVERSION_MAJOR], // major version (3..)
            GLX_CONTEXT_MINOR_VERSION_ARB, hints[(int)WindowHint::GLVERSION_MINOR], // minor version (..2)
            GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,           // Context profile (Core or compat)
            None // END
        };
        if(hints[(int)WindowHint::GL_COMPATIBILITY_CORE])
            glxContextAttributes[5] = GLX_CONTEXT_CORE_PROFILE_BIT_ARB;

        glxc = glXCreateContextAttribsARB(display, fbc[0], 0, true, glxContextAttributes);

    }
    #else 
    GLint glxAttribs[] = {
	    GLX_RGBA,
	    GLX_DOUBLEBUFFER,
	    GLX_DEPTH_SIZE,     24,
	    GLX_STENCIL_SIZE,   8,
	    GLX_RED_SIZE,       8,
	    GLX_GREEN_SIZE,     8,
	    GLX_BLUE_SIZE,      8,
	    GLX_SAMPLE_BUFFERS, 0,
	    GLX_SAMPLES,        0,
	    None
    };
    XVisualInfo* visual = glXChooseVisual(display, screen, glxAttribs);
    glxc = glXCreateContext(display, visual, NULL, GL_TRUE);
    #endif

    // set window attributes
    XSetWindowAttributes winAttribs;
    winAttribs.event_mask       = ExposureMask | KeyPressMask | KeyReleaseMask;
    winAttribs.background_pixel = black;
    winAttribs.border_pixel     = white;
    winAttribs.colormap         = XCreateColormap(display, DefaultRootWindow(display), visual->visual, AllocNone);
    winAttribs.override_redirect = true;
    // create simple x window
    win = XCreateWindow(
        display, DefaultRootWindow(display),
        0, 0,         // pos
        sizex, sizey, // size
        0,            // border
        visual->depth,
        InputOutput,
        visual->visual,
        CWBackPixel | CWColormap | CWBorderPixel | CWEventMask,
        &winAttribs
    );

    // set propreties (title, minimised title etc...)
    XSetStandardProperties(display, win, name, name, None, NULL, 0, NULL);

    // set authorised inputs (keyboard)
    XSelectInput(display, win, 
        ExposureMask|
        KeyPressMask|KeyReleaseMask|
        PointerMotionMask|ButtonPressMask|ButtonReleaseMask
    );

    // test gl
    GLint majorGLX, minorGLX = 0;
    glXQueryVersion(display, &majorGLX, &minorGLX);
    LOG("GLX_VERSION:" << majorGLX << "." << minorGLX);

    // create context
    glXMakeCurrent(display, win, glxc);

    // enable v-sync
    XSync(display, true);

    LOG("GLVERSION:   " << glGetString(GL_VERSION));
    // print("GL_VENDOR:   ", glGetString(GL_VENDOR));
    // print("GL_RENDERER: ", glGetString(GL_RENDERER));
    // print("GL_LANG:     ", glGetString(GL_SHADING_LANGUAGE_VERSION));

    // show window
    XClearWindow(display, win);
    XMapRaised(display, win);

    // cleanup
    XFree(visual);

    /////////////////////////////////
    // Event subscribing

    // close event
    wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, win, &wmDeleteMessage, 1);


    setupBase();
}

mx::Context::~Context()
{
    glXDestroyContext(display, glxc);
    XDestroyWindow(display, win);
    XCloseDisplay(display);
    screen = 0;
}

bool mx::Context::shouldClose() const
{
    return close;
}
void mx::Context::makeCurrent()
{
    glXMakeCurrent(display, win, glxc);
}
void mx::Context::swapBuffers()
{
    glXSwapBuffers(display, win);
}
void mx::Context::pollEvents()
{
    XEvent e;       // xevent
    KeySym key = 0;     // key press handler
    char text[256]; // key press buffer

    // if there is pending events
    while(XPending(display) > 0)
    {
        // Get next event
        XNextEvent(display, &e);

        switch(e.type)
        {
            // keyboard
            case KeyPress:
                XLookupString(&e.xkey, text, 256, &key, NULL);
                invokeEvent(mx::ContextEvent::KEYPRESS, translateXKeycode(key), key, 0L);
                break;
            case KeyRelease:
                XLookupString(&e.xkey, text, 256, &key, NULL);
                invokeEvent(mx::ContextEvent::KEYRELEASE, translateXKeycode(key), key, 0L);
                break;
            // keyboard mapping
            case MappingNotify:
                XRefreshKeyboardMapping(&e.xmapping);
                break;

            // mouse
            case ButtonPress:
                LOG("MousePress: " << e.xbutton.button);
                break;
            case ButtonRelease:
                LOG("MouseRelease: " << e.xbutton.button);
                break;
            case MotionNotify: // mouse move
                invokeEvent(mx::ContextEvent::MOUSEMOVE, e.xmotion.x, e.xmotion.y, 0L);
                break;


            // window
            case Expose: // first creation ?
            case ResizeRequest: // resize
                ContextAttributes wattr;
                XGetWindowAttributes(display, win, &wattr);
                invokeEvent(mx::ContextEvent::RESIZE, wattr.width, wattr.height, 0L);
                break;
            case ClientMessage:
                if(e.xclient.data.l[0] == wmDeleteMessage) { // close
                    invokeEvent(mx::ContextEvent::CLOSE, 0L, 0L, 0L);
                    close = true;
                }
                break;
        }
    }
}

// OPENGL ENTRY
mx::GLAPIFN mx::glGetProcAddress(const char* _name)
{
    mx::GLAPIFN fn = (mx::GLAPIFN)glXGetProcAddress((const GLubyte*)_name);
    if(fn == NULL)
        fn = (mx::GLAPIFN)glXGetProcAddressARB((const GLubyte*)_name);
    return fn;
}
