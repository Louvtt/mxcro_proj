#pragma once
#ifndef _MX_EVENT_H_
#define _MX_EVENT_H_

#include <vector>
#include <functional>

#define declareEvent(name, code)\
using name ## Event         = class Event<name ## EventArgs, (int)code>; \
using name ## EventCallback = EventCallback<name ## EventArgs>;

namespace mx {

class EventBase
{
public:
    virtual int getCode() const { return -1; };
protected:
    virtual void internalDispatch(void* args) = 0;
    friend class EventManager;
};

template <typename Args>
using EventCallback = std::function<void (Args, void* userParams)>;

template <typename _Args, int _Code>
class Event
: public EventBase
{
public:
    
    using CallbackType           = EventCallback<_Args>;
    using ArgsType               = _Args;
    inline static const int Code = _Code;

    Event() : m_callbacks({}) {}
    virtual ~Event()
    {
        m_callbacks.clear();
    };

    void dispatch(ArgsType args) {
        for(EventDescriptor& desc : m_callbacks) {
            desc.callback(args, desc.userParams);
        }
    }

    void registerCallback(CallbackType callback, void* userParams)
    {
        m_callbacks.push_back({
            callback, userParams
        });
    }

    bool unregisterCallback(CallbackType callback, void* userParams)
    {
        CallbackType* found = m_callbacks.find(callback);
        if(found != m_callbacks.end()) {
            m_callbacks.remove(found - m_callbacks.begin());
            return true;
        }
        return false;
    }

    int getCode() const {
        return Code;
    }
private:
    void internalDispatch(void* args) override {
        dispatch(*(_Args*)args);
    }

protected:
    inline static int s_eventCount = 0;
    struct EventDescriptor {
        CallbackType callback;
        void* userParams;
    };

    std::vector<EventDescriptor> m_callbacks;
};

}

#endif //_MX_EVENT_H_