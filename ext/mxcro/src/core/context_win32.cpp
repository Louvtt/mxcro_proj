#include "mx/core/context.hpp"

#include "mx/io/keycodes.hpp"

// INCLUDE WIN32 API
#undef _UNICODE
#undef UNICODE
#include <windows.h>
#include <windowsx.h>
#include <dwmapi.h>
#define WINASSERT(expr, err) if(expr) MessageBox(NULL, err, TEXT("WINAPI ERROR"), MB_OK | MB_ICONEXCLAMATION)

#include <iostream>
#define ERR(msg) std::cerr << "ERROR: " << msg << std::endl;
#define LOG(msg) std::cout << "LOG: " << msg << std::endl;

// INCLUDE GL
#include <GL/gl.h>
#include <GL/wglext.h>
#include <GL/glext.h>
#include <GL/glcorearb.h>

#pragma comment lib("opengl32.lib")
#pragma comment lib("dwmapi.lib")

// VIRTUAL KEYS TO MX KEYS
constexpr int vkToKeyCodes[] =
{
    MX_KEY_UNKNOWN, // padding because vk starts at 1
    // buttons
    MX_MBUTTON_LEFT,  // VK_LBUTTON
    MX_MBUTTON_RIGHT, // VK_RBUTTON
    MX_KEY_UNKNOWN,   // VK_CANCEL
    MX_MBUTTON_MIDDLE,// VK_MBUTTON
    MX_MBUTTON_4,     // VK_XBUTTON1
    MX_MBUTTON_5,     // VK_XBUTTON2
    MX_KEY_UNKNOWN,   // UNDEFINED

    // keys
    MX_KEY_BACKSPACE,    // VK_BACK
    MX_KEY_TAB,          // VK_TAB
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // VK_CLEAR     5 (keypad without Num Lock)
    MX_KEY_ENTER,        // VK_RETURN     Enter
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_LEFT_SHIFT,   // VK_SHIFT     Shift (either one)
    MX_KEY_LEFT_CONTROL, // VK_CONTROL     Ctrl (either one)
    MX_KEY_LEFT_ALT,     // VK_MENU     Alt (either one)
    MX_KEY_PAUSE,        // VK_PAUSE     Pause
    MX_KEY_CAPS_LOCK,    // VK_CAPITAL     Caps Lock
    MX_KEY_UNKNOWN,      // RESERVED KANA / HANGUEL / HANGUL
    MX_KEY_UNKNOWN,      // RESERVED IME ON
    MX_KEY_UNKNOWN,      // RESERVED JUNJA
    MX_KEY_UNKNOWN,      // RESERVED FINAL
    MX_KEY_UNKNOWN,      // RESERVED HANJA / KANJI
    MX_KEY_UNKNOWN,      // RESERVED IME OFF
    MX_KEY_ESCAPE,       // VK_ESCAPE     Esc
    MX_KEY_UNKNOWN,      // RESERVED IME CONVERT
    MX_KEY_UNKNOWN,      // RESERVED IME NON CONVERT
    MX_KEY_UNKNOWN,      // RESERVED IME ACCEPT
    MX_KEY_UNKNOWN,      // RESERVED IME MODE CHANGE
    MX_KEY_SPACE,        // VK_SPACE     Spacebar
    MX_KEY_PAGE_UP,      // VK_PRIOR     Page Up
    MX_KEY_PAGE_DOWN,    // VK_NEXT     Page Down
    MX_KEY_END,          // VK_END     End
    MX_KEY_HOME,         // VK_HOME     Home
    MX_KEY_LEFT,         // VK_LEFT     Left Arrow
    MX_KEY_UP,           // VK_UP     Up Arrow
    MX_KEY_RIGHT,        // VK_RIGHT     Right Arrow
    MX_KEY_DOWN,         // VK_DOWN     Down Arrow
    MX_KEY_UNKNOWN,      // VK_SELECT     Select
    MX_KEY_PRINT_SCREEN, // VK_PRINT     Print (only used by Nokia keyboards)
    MX_KEY_UNKNOWN,      // VK_EXECUTE     Execute (not used)
    MX_KEY_PRINT_SCREEN, // VK_SNAPSHOT     Print Screen
    MX_KEY_INSERT,       // VK_INSERT     Insert
    MX_KEY_DELETE,       // VK_DELETE     Delete
    MX_KEY_UNKNOWN,      // VK_HELP     Help
    MX_KEY_0,            // VK_0     0
    MX_KEY_1,            // VK_1     1
    MX_KEY_2,            // VK_2     2
    MX_KEY_3,            // VK_3     3
    MX_KEY_4,            // VK_4     4
    MX_KEY_5,            // VK_5     5
    MX_KEY_6,            // VK_6     6
    MX_KEY_7,            // VK_7     7
    MX_KEY_8,            // VK_8     8
    MX_KEY_9,            // VK_9     9
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_A,            // VK_A     A
    MX_KEY_B,            // VK_B     B
    MX_KEY_C,            // VK_C     C
    MX_KEY_D,            // VK_D     D
    MX_KEY_E,            // VK_E     E
    MX_KEY_F,            // VK_F     F
    MX_KEY_G,            // VK_G     G
    MX_KEY_H,            // VK_H     H
    MX_KEY_I,            // VK_I     I
    MX_KEY_J,            // VK_J     J
    MX_KEY_K,            // VK_K     K
    MX_KEY_L,            // VK_L     L
    MX_KEY_M,            // VK_M     M
    MX_KEY_N,            // VK_N     N
    MX_KEY_O,            // VK_O     O
    MX_KEY_P,            // VK_P     P
    MX_KEY_Q,            // VK_Q     Q
    MX_KEY_R,            // VK_R     R
    MX_KEY_S,            // VK_S     S
    MX_KEY_T,            // VK_T     T
    MX_KEY_U,            // VK_U     U
    MX_KEY_V,            // VK_V     V
    MX_KEY_W,            // VK_W     W
    MX_KEY_X,            // VK_X     X
    MX_KEY_Y,            // VK_Y     Y
    MX_KEY_Z,            // VK_Z     Z
    MX_KEY_UNKNOWN,      // VK_LWIN  Left Start Menu key
    MX_KEY_UNKNOWN,      // VK_RWIN  Right Start Menu key
    MX_KEY_MENU,         // VK_APPS  Context Menu key
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // SLEEP
    MX_KEY_KP_0,         // VK_NUMPAD0     0 (keypad with Num Lock)
    MX_KEY_KP_1,         // VK_NUMPAD1     1 (keypad with Num Lock)
    MX_KEY_KP_2,         // VK_NUMPAD2     2 (keypad with Num Lock)
    MX_KEY_KP_3,         // VK_NUMPAD3     3 (keypad with Num Lock)
    MX_KEY_KP_4,         // VK_NUMPAD4     4 (keypad with Num Lock)
    MX_KEY_KP_5,         // VK_NUMPAD5     5 (keypad with Num Lock)
    MX_KEY_KP_6,         // VK_NUMPAD6     6 (keypad with Num Lock)
    MX_KEY_KP_7,         // VK_NUMPAD7     7 (keypad with Num Lock)
    MX_KEY_KP_8,         // VK_NUMPAD8     8 (keypad with Num Lock)
    MX_KEY_KP_9,         // VK_NUMPAD9     9 (keypad with Num Lock)
    MX_KEY_KP_MULTIPLY,  // VK_MULTIPLY     * (keypad)
    MX_KEY_KP_ADD,       // VK_ADD     + (keypad)
    MX_KEY_UNKNOWN,      // VK_SEPARATOR     Separator (never generated by the keyboard)
    MX_KEY_KP_SUBTRACT,  // VK_SUBTRACT     - (keypad)
    MX_KEY_KP_DECIMAL,   // VK_DECIMAL     . (keypad with Num Lock)
    MX_KEY_KP_DIVIDE,    // VK_DIVIDE     / (keypad)
    MX_KEY_F1,           // VK_F1     F1
    MX_KEY_F2,           // VK_F2     F2
    MX_KEY_F3,           // VK_F3     F3
    MX_KEY_F4,           // VK_F4     F4
    MX_KEY_F5,           // VK_F5     F5
    MX_KEY_F6,           // VK_F6     F6
    MX_KEY_F7,           // VK_F7     F7
    MX_KEY_F8,           // VK_F8     F8
    MX_KEY_F9,           // VK_F9     F9
    MX_KEY_F10,          // VK_F10     F10
    MX_KEY_F11,          // VK_F11     F11
    MX_KEY_F12,          // VK_F12     F12
    MX_KEY_F13,          // VK_F13     F13
    MX_KEY_F14,          // VK_F14     F14
    MX_KEY_F15,          // VK_F15     F15
    MX_KEY_F16,          // VK_F16     F16
    MX_KEY_F17,          // VK_F17     F17
    MX_KEY_F18,          // VK_F18     F18
    MX_KEY_F19,          // VK_F19     F19
    MX_KEY_F20,          // VK_F20     F20
    MX_KEY_F21,          // VK_F21     F21
    MX_KEY_F22,          // VK_F22     F22
    MX_KEY_F23,          // VK_F23     F23
    MX_KEY_F24,          // VK_F24     F24

    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED

    MX_KEY_NUM_LOCK,     // VK_NUMLOCK     Num Lock
    MX_KEY_SCROLL_LOCK,  // VK_OEM_SCROLL     Scroll Lock

    MX_KEY_UNKNOWN,      // OEM SPECIFICS
    MX_KEY_UNKNOWN,      // OEM SPECIFICS
    MX_KEY_UNKNOWN,      // OEM SPECIFICS
    MX_KEY_UNKNOWN,      // OEM SPECIFICS
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED
    
    MX_KEY_LEFT_SHIFT,   // VK_LSHIFT
    MX_KEY_RIGHT_SHIFT,  // VK_RSHIFT
    MX_KEY_LEFT_CONTROL, // VK_LCONTROL
    MX_KEY_RIGHT_CONTROL,// VK_RCONTROL
    MX_KEY_LEFT_ALT,     // VK_LMENU
    MX_KEY_RIGHT_ALT,    // VK_RMENU

    // BROWSER KEYS AND OS KEYS
    MX_KEY_UNKNOWN,      // VK_BROWSER_BACK
    MX_KEY_UNKNOWN,      // VK_BROWSER_FORWARD
    MX_KEY_UNKNOWN,      // VK_BROWSER_REFRESH
    MX_KEY_UNKNOWN,      // VK_BROWSER_STOP
    MX_KEY_UNKNOWN,      // VK_BROWSER_SEARCH
    MX_KEY_UNKNOWN,      // VK_BROWSER_FAVORITES
    MX_KEY_UNKNOWN,      // VK_BROWSER_HOME
    MX_KEY_UNKNOWN,      // VK_VOLUME_MUTE
    MX_KEY_UNKNOWN,      // VK_VOLUME_DOWN
    MX_KEY_UNKNOWN,      // VK_VOLUME_UP
    MX_KEY_UNKNOWN,      // VK_MEDIA_NEXT_TRACK
    MX_KEY_UNKNOWN,      // VK_MEDIA_PREV_TRACK
    MX_KEY_UNKNOWN,      // VK_MEDIA_STOP
    MX_KEY_UNKNOWN,      // VK_MEDIA_PLAY_PAUSE
    MX_KEY_UNKNOWN,      // VK_LAUNCH_MAIL
    MX_KEY_UNKNOWN,      // VK_LAUNCH_MEDIA_SELECT
    MX_KEY_UNKNOWN,      // VK_LAUNCH_APP1
    MX_KEY_UNKNOWN,      // VK_LAUNCH_APP2

    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED

    MX_KEY_SEMICOLON,    // VK_OEM_1        ;
    MX_KEY_EQUAL,        // VK_OEM_PLUS     =
    MX_KEY_COMMA,        // VK_OEM_COMMA    ,
    MX_KEY_MINUS,        // VK_OEM_MINUS    -
    MX_KEY_PERIOD,       // VK_OEM_PERIOD   .
    MX_KEY_SLASH,        // VK_OEM_2        /
    MX_KEY_GRAVE_ACCENT, // VK_OEM_3        `

    // RESERVED (0xC1-0xD7 => 22)
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // RESERVED
    MX_KEY_UNKNOWN,      // UNDEFINED
    MX_KEY_UNKNOWN,      // UNDEFINED

    MX_KEY_LEFT_BRACKET, // VK_OEM_4        [
    MX_KEY_BACKSLASH,    // VK_OEM_5        \ //
    MX_KEY_RIGHT_BRACKET,// VK_OEM_6        ]
    MX_KEY_APOSTROPHE,   // VK_OEM_7     '
    MX_KEY_OEM_1,        // VK_OEM_8
    MX_KEY_F17,          // VK_ICO_F17     F17 on Olivetti extended keyboard (internal use only)
    MX_KEY_F18,          // VK_ICO_F18     F18 on Olivetti extended keyboard (internal use only)
    MX_KEY_UNKNOWN,      // VK_OEM_102     < or | on IBM-compatible 102 enhanced non-U.S. keyboard
    MX_KEY_UNKNOWN,      // VK_ICO_HELP     Help on Olivetti extended keyboard (internal use only)
    MX_KEY_UNKNOWN,      // VK_ICO_00     00 on Olivetti extended keyboard (internal use only)
    MX_KEY_UNKNOWN,      // VK_ICO_CLEAR     Clear on Olivette extended keyboard (internal use only)
    MX_KEY_UNKNOWN,      // VK_OEM_RESET     Reset (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_JUMP     Jump (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_PA1     PA1 (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_PA2     PA2 (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_PA3     PA3 (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_WSCTRL     WSCTRL (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_CUSEL     CUSEL (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_ATTN     ATTN (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_FINNISH     FINNISH (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_COPY     COPY (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_AUTO     AUTO (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_ENLW     ENLW (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_OEM_BACKTAB     BACKTAB (Nokia keyboards only)
    MX_KEY_UNKNOWN,      // VK_ATTN     ATTN
    MX_KEY_UNKNOWN,      // VK_CRSEL     CRSEL
    MX_KEY_UNKNOWN,      // VK_EXSEL     EXSEL
    MX_KEY_UNKNOWN,      // VK_EREOF     EREOF
    MX_KEY_UNKNOWN,      // VK_PLAY     PLAY
    MX_KEY_UNKNOWN,      // VK_ZOOM     ZOOM
    MX_KEY_UNKNOWN,      // VK_NONAME     NONAME
    MX_KEY_UNKNOWN,      // VK_PA1     PA1
    MX_KEY_UNKNOWN       // VK_OEM_CLEAR
};

// STD
#include <unordered_map>

std::unordered_map<int, mx::Context*> hwndIDToContext{};
void mx::createGLContext(int _targetID)
{
    if(hwndIDToContext.find(_targetID) == hwndIDToContext.end()) return;
    mx::Context* targetWin = hwndIDToContext[_targetID];

    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),                  // Size Of This Pixel Format Descriptor
        1,                                      // Version Number
        PFD_DRAW_TO_WINDOW |                    // Format Must Support Window
        PFD_SUPPORT_OPENGL |                    // Format Must Support OpenGL
        PFD_DOUBLEBUFFER,                       // Must Support Double Buffering
        PFD_TYPE_RGBA,                          // Request An RGBA Format
        32,                                     // Select Our Color Depth
        8, 8, 8, 8, 8, 8,                       // Color Bits set to 8Bits
        8,                                      // 8Bits Alpha Buffer
        0,                                      // Shift Bit Ignored
        0,                                      // No Accumulation Buffer
        0, 0, 0, 0,                             // Accumulation Bits Ignored
        32,                                     // 32Bit Z-Buffer (Depth Buffer)
        16,                                     // 16Bit Stencil Buffer
        0,                                      // No Auxiliary Buffer
        PFD_MAIN_PLANE,                         // Main Drawing Layer
        0,                                      // Reserved
        0, 0, 0                                 // Layer Masks Ignored
    };

    HDC hdc = GetDC((HWND)targetWin->handle.wHandle);
    WINASSERT(hdc == NULL, "[Context creation] Missing DC.");
    int pf = ChoosePixelFormat(hdc, &pfd);
    WINASSERT(pf == 0, "[Context creation] Failed to choose pixel format.");
    WINASSERT(SetPixelFormat(hdc, pf, &pfd) == FALSE, "[Context creation] Failed to set pixel format");
    
    // simple context
    targetWin->handle.glHandle = wglCreateContext(hdc);
    WINASSERT(targetWin->handle.glHandle == NULL, "Context creation failed");
    if(targetWin->handle.glHandle)
        wglMakeCurrent(hdc, (HGLRC)targetWin->handle.glHandle);
    
    // Extended creation of context
    #if defined(WGL_ARB_create_context_profile) && defined(WGL_ARB_create_context)
    // Create context attribs ARB loader
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
    if(wglCreateContextAttribsARB != NULL) {
        mx::ContextDesc tDesc = targetWin->getDesc();
        int* hints = tDesc.hints;
    
        int wglAttributes[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, hints[(int)mx::ContextHint::GLVERSION_MAJOR], // major version (3..)
            WGL_CONTEXT_MINOR_VERSION_ARB, hints[(int)mx::ContextHint::GLVERSION_MINOR], // minor version (..2)
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,           // Context profile (Core or compat)
            // WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,              // allow debug output (not recommanded)
            // WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, // allow forward compatibility (not recommanded)
            0 // END
        };
        if(hints[(int)mx::ContextHint::GL_COMPATIBILITY_CORE])
            wglAttributes[5] = WGL_CONTEXT_CORE_PROFILE_BIT_ARB;

        // delete previous context
        if(targetWin->handle.glHandle) {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext((HGLRC)targetWin->handle.glHandle);
        }

        // create context
        LOG("Targetting version: " << wglAttributes[1] << "." << wglAttributes[3] << " - " << (hints[2] ? "Core" : "Compatibility"));
        targetWin->handle.glHandle = wglCreateContextAttribsARB(hdc, 0, wglAttributes);
        WINASSERT(targetWin->handle.glHandle == NULL, "Context extended creation failed");
        if(targetWin->handle.glHandle)
            wglMakeCurrent(hdc, (HGLRC)targetWin->handle.glHandle);
    }
    #endif

    LOG("GL_VERSION: " << (char*)glGetString(GL_VERSION));
}

void mx::invoke(int _targetID, mx::CoreEventCode _code, u32 _arg0, u32 _arg1, u32 _arg2, u32 extra)
{
    if(hwndIDToContext.find(_targetID) == hwndIDToContext.end()) return;
    mx::Context* targetWin = hwndIDToContext[_targetID];
    if(_code == mx::CoreEventCode::Close)
    {
        targetWin->setShouldClose(true);
        return;
    }
    mx::invokeEvent(_code, _arg0, _arg1, _arg2, extra, (void*)targetWin);
}


HBRUSH hbrBack;
LRESULT _stdcall WindowProc(HWND _hwnd, UINT _uMsg, WPARAM _wParam, LPARAM _lParam)
{
    int targetID = GetDlgCtrlID(_hwnd);
    switch(_uMsg)
    {
        // handled events
        case WM_SIZE:
            mx::invoke(targetID, mx::CoreEventCode::Resize, (u32)LOWORD(_lParam), (u32)HIWORD(_lParam), 0, 0);
            return 0;
        // MOUSE
        case WM_MOUSEMOVE:
            mx::invoke(targetID, mx::CoreEventCode::MouseMove, (u32)GET_X_LPARAM(_lParam), (u32)GET_Y_LPARAM(_lParam), 0, 0);
            return 0;
        case WM_MOUSEWHEEL:
            mx::invoke(targetID, mx::CoreEventCode::Scroll, (u32)GET_WHEEL_DELTA_WPARAM(_wParam), 0, 0, 0);
            return 0;
        // BUTTONS
        case WM_LBUTTONDOWN:
            mx::invoke(targetID, mx::CoreEventCode::Button, (u32)MX_MBUTTON_LEFT, _wParam, 0, true);
            return 0;
        case WM_MBUTTONDOWN:
            mx::invoke(targetID, mx::CoreEventCode::Button, (u32)MX_MBUTTON_MIDDLE, _wParam, 0, true);
            return 0;
        case WM_RBUTTONDOWN:
            mx::invoke(targetID, mx::CoreEventCode::Button, (u32)MX_MBUTTON_RIGHT, _wParam, 0, true);
            return 0;
        case WM_LBUTTONUP:
            mx::invoke(targetID, mx::CoreEventCode::Button, (u32)MX_MBUTTON_LEFT, _wParam, 0, false);
            return 0;
        case WM_MBUTTONUP:
            mx::invoke(targetID, mx::CoreEventCode::Button, (u32)MX_MBUTTON_MIDDLE, _wParam, 0, false);
            return 0;
        case WM_RBUTTONUP:
            mx::invoke(targetID, mx::CoreEventCode::Button, (u32)MX_MBUTTON_RIGHT, _wParam, 0,false);
            return 0;
        case WM_XBUTTONDOWN: 
        {
            int button = HIWORD(_wParam);
            if(button & 1) mx::invoke(targetID, mx::CoreEventCode::Button, MX_MBUTTON_4, _wParam, 0, true);
            if(button & 2 == 2) mx::invoke(targetID, mx::CoreEventCode::Button, MX_MBUTTON_5, _wParam, 0, true);
            return 0;
        }
        case WM_XBUTTONUP:
        {
            int button = HIWORD(_wParam);
            if(button & 1) mx::invoke(targetID, mx::CoreEventCode::Button, MX_MBUTTON_4, _wParam, 0, false);
            if(button & 2 == 2) mx::invoke(targetID, mx::CoreEventCode::Button, MX_MBUTTON_5, _wParam, 0, false);
            return 0;
        }

        // KEYBOARD
        case WM_KEYDOWN:
        {
            int key = vkToKeyCodes[_wParam];
            int scancode = HIWORD(_lParam) & (KF_EXTENDED | 0xff); // get extended key
            int mods = _lParam >> 24 & 1;
            mx::invoke(targetID, mx::CoreEventCode::Key, key, scancode, mods, true);
            return 0;
        }
        case WM_KEYUP:
        {
            int key = vkToKeyCodes[_wParam];
            int scancode = HIWORD(_lParam) & (KF_EXTENDED | 0xff); // get extended key
            int mods = _lParam >> 24 & 1; // check if alt or ctrl is down
            mx::invoke(targetID, mx::CoreEventCode::Key, key, scancode, mods, false);
            return 0;
        }
        
        // Closing events
        case WM_CLOSE:
            PostQuitMessage(0);
        case WM_QUIT:
            mx::invoke(targetID, mx::CoreEventCode::Close, 0, 0, 0);
            return 0;
    }
    return DefWindowProcA(_hwnd, _uMsg, _wParam, _lParam);
}

mx::Context::Context(const mx::ContextDesc& _desc)
: desc(_desc)
{
    this->setupEvents();
    
    // unpack
    u32 sizex = desc.sizex;
    u32 sizey = desc.sizey;
    mx::ContextFlags flags = desc.flags;

    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = { };
    wc.lpfnWndProc   = WindowProc;
    wc.style         = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.lpszClassName = TEXT("MXCRO WINDOW");
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = NULL;
    wc.lpszMenuName  = NULL;

    WINASSERT(RegisterClass(&wc) == 0, "Failed to register window class");

    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);

    // handle flags to stylize the window
    DWORD wstyle = WS_OVERLAPPEDWINDOW | WS_TABSTOP;
    bool borderless = ((int)flags & (int)mx::ContextFlags::Borderless) == (int)mx::ContextFlags::Borderless;
    if(borderless) wstyle = WS_POPUPWINDOW;

    DWORD wExStyle = 0;
    if(((int)flags & (int)mx::ContextFlags::AlwaysOnTop) == (int)mx::ContextFlags::AlwaysOnTop) 
            wExStyle |= WS_EX_TOPMOST;

    // adjust the size of the window to fit the client rect defined in parameters
    // by _sizex and _sizey
    RECT rect;
    rect.left = 0; rect.right  = sizex;
    rect.top  = 0; rect.bottom = sizey;
    AdjustWindowRect(&rect, wstyle, FALSE);
    int clientW = rect.right - rect.left;
    int clientH = rect.bottom - rect.top;


    // create the windows
    HWND hWnd = CreateWindowEx(
        wExStyle,
        TEXT("MXCRO WINDOW"),
        desc.name.c_str(),
        wstyle,
        (screenW - clientW) / 2, (screenH - clientH) / 2, // center
        rect.right - rect.left, rect.bottom - rect.top,
        0,
        0,
        hInstance,
        NULL
    );
    hbrBack = CreateSolidBrush(RGB(20, 20, 30));

    handle.wHandle = (void*)hWnd;
    handle.wID = GetDlgCtrlID(hWnd);
    hwndIDToContext.insert({handle.wID, this});

    mx::createGLContext(handle.wID);

    if((int)flags & (int)mx::ContextFlags::Fullscreen == (int)mx::ContextFlags::Fullscreen)
        ShowWindow(hWnd, SW_SHOWMAXIMIZED);
    else
        ShowWindow(hWnd, SW_SHOW);
    WINASSERT(UpdateWindow(hWnd) == 0, "Failed to update the window");
    SetBkColor(GetDC(hWnd), RGB(20,20,30));
    
    close = false;

    this->setupBase();
}
mx::Context::~Context()
{   
    render.reset();
    render3D.reset();
    close = true;
    // release hglrc
    wglMakeCurrent(NULL, NULL);
    if((HGLRC)handle.glHandle) WINASSERT(wglDeleteContext((HGLRC)handle.glHandle) == 0, "Failed to delete the wgl context");
    // destroy window after everything
    if((HWND)handle.wHandle)   WINASSERT(DestroyWindow((HWND)handle.wHandle) == 0, "Failed to destroy the window");
}

void mx::Context::makeCurrent()
{
    if(wglMakeCurrent(GetDC((HWND)handle.wHandle), (HGLRC)handle.glHandle) == FALSE)
    {
        LPSTR errorMsg = NULL;
        FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM
            |FORMAT_MESSAGE_ALLOCATE_BUFFER
            |FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, // unused from system
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR)&errorMsg,
            0,
            NULL
        );
        ERR("WGLERROR: Failed to make wglcontext current :" << errorMsg);
    }
}
void mx::Context::swapBuffers()
{
    if(SwapBuffers(GetDC((HWND)handle.wHandle)) == FALSE)
    {
        LPSTR errorMsg = NULL;
        FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM
            |FORMAT_MESSAGE_ALLOCATE_BUFFER
            |FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, // unused from system
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR)&errorMsg,
            0,
            NULL
        );
        ERR("WIN32_ERROR: Failed to swap buffers :" << errorMsg);
    }
}

void mx::Context::pollEvents()
{
    MSG msg;
    while(PeekMessage(&msg, (HWND)handle.wHandle, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}




mx::GLAPIFN mx::glGetProcAddress(const char* _name)
{
    mx::GLAPIFN proc = (mx::GLAPIFN)wglGetProcAddress(_name);
    if(proc == 0 ||
    (proc == (void*)0x1) || (proc == (void*)0x2) || (proc == (void*)0x3) ||
    (proc == (void*)-1) )
    {
        HMODULE module = LoadLibraryA("opengl32.dll");
        proc = (GLAPIFN)GetProcAddress(module, _name);
    }

  return proc;
}

