#ifndef _MX_COREEVENTS_H_
#define _MX_COREEVENTS_H_

#include "event.hpp"
#include "types.hpp"

namespace mx {

enum class CoreEventCode : int {
    Resize    = 0,
    MouseMove = 1,
    Scroll    = 2,
    Button    = 3,
    Key       = 4,
    Close     = 5,
    Count
};

struct KeyEventArgs {
    bool isDown;
    u32 keyCode;
    u32 scanCode;
    u32 mods;
};
declareEvent(Key, CoreEventCode::Key);

struct ButtonEventArgs {
    bool isDown;
    u32 buttonCode;
    u32 mods;
};
declareEvent(Button, CoreEventCode::Button);

struct ResizeEventArgs {
    u32 sizeX;
    u32 sizeY;
};
declareEvent(Resize, CoreEventCode::Resize);

struct MouseMoveEventArgs {
    u32 posX;
    u32 posY;
};
declareEvent(MouseMove, CoreEventCode::MouseMove);

struct ScrollEventArgs {
    i32 delta;
};
declareEvent(Scroll, CoreEventCode::Scroll);

struct CloseEventArgs {
    u32 exitCode = 0;
};
declareEvent(Close, CoreEventCode::Close);

} // namespace mx

#endif //_MX_COREEVENTS_H_