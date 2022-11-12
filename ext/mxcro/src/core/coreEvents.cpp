#include "mx/core/coreEvents.hpp"
#include "mx/io/eventManager.hpp"

#define INVKEVENT(name, ...)                          \
    case mx::CoreEventCode::name:                     \
    mx::EventManager::Get()->dispatchEvent<mx::name##Event>(\
        mx::name##EventArgs{ __VA_ARGS__ }\
    );\
    break

void mx::invokeEvent(mx::CoreEventCode code, u32 arg0, u32 arg1, u32 arg2, u32 arg3, void* extra) {
    switch(code)
    {
        INVKEVENT(Resize,        arg0, arg1, (mx::Context*)extra);
        INVKEVENT(MouseMove,     arg0, arg1);
        INVKEVENT(Scroll,   (i32)arg0);
        INVKEVENT(Button,  (bool)arg3, arg0, arg1);
        INVKEVENT(Key,     (bool)arg3, arg0, arg1, arg2);
        INVKEVENT(Close,         arg0, (mx::Context*)extra);
    }
}