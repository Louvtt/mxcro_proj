#ifndef _MX_COREEVENTS_H_
#define _MX_COREEVENTS_H_

#include "../io/event.hpp"
#include "types.hpp"

namespace mx {

/** Core event codes */
enum class CoreEventCode : int {
    Resize    = 0,
    MouseMove = 1,
    Scroll    = 2,
    Button    = 3,
    Key       = 4,
    Close     = 5,
    Count
};

/** Arguments of a key event */
struct KeyEventArgs {
    /** True if the key is pressed, false if released */
    bool isDown;
    /** Key code (@see keycodes.h)*/
    u32 keyCode;
    /** Scan code (system key code)*/
    u32 scanCode;
    /** Mods (Alt, Shift, Ctrl, ...)*/
    u32 mods;
};
declareEvent(Key, CoreEventCode::Key);

/** Arguments of a button event */
struct ButtonEventArgs {
    /** True if the key is pressed, false if released */
    bool isDown;
    /** Button code (@see keycodes.h)*/
    u32 buttonCode;
    /** Mods (Alt, Shift, Ctrl, ...)*/
    u32 mods;
};
declareEvent(Button, CoreEventCode::Button);

class Context;
/** Arguments of a resize event */
struct ResizeEventArgs {
    /** Size X of the window */
    u32 sizeX;
    /** Size Y of the window */
    u32 sizeY;
};
declareEvent(Resize, CoreEventCode::Resize);

struct MouseMoveEventArgs {
    /** Pos X of the cursor inside the window */
    u32 posX;
    /** Pos Y of the cursor inside the window */
    u32 posY;
};
declareEvent(MouseMove, CoreEventCode::MouseMove);

struct ScrollEventArgs {
    /** Delta Y of the scroll */
    i32 delta;
};
declareEvent(Scroll, CoreEventCode::Scroll);

struct CloseEventArgs {
    /** Exit code */
    u32 exitCode = 0;
};
declareEvent(Close, CoreEventCode::Close);

void invokeEvent(mx::CoreEventCode code, u32 arg0, u32 arg1=0L, u32 arg2=0L, u32 arg3=0L, void* extra=0);

} // namespace mx

#endif //_MX_COREEVENTS_H_