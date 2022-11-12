#pragma once
#ifndef _MX_EVENT_H_
#define _MX_EVENT_H_

#include <vector>
#include <functional>

#define declareEvent(name, code)\
using name ## Event         = class Event<name ## EventArgs, (int)code>; \
using name ## EventCallback = EventCallback<name ## EventArgs>;

namespace mx {

/**
 * @brief Base Event Class. Do not define a derived class of this directly,
 * please see the Event class
 */
class EventBase
{
public:
    /**
     * @brief Return the code of the event
     * @return int 
     */
    virtual int getCode() const { return -1; };
protected:
    /**
     * @brief Dispatch the event to the callback
     * @param args event args
     */
    virtual void internalDispatch(void* args) = 0;
    friend class EventManager;
};

/**
 * @brief Callback for a specified event
 * @tparam Args argument of the event
 */
template <typename Args>
using EventCallback = std::function<void (Args, void* userParams)>;

/**
 * @brief Event class
 * @tparam _Args argument of the event
 * @tparam _Code code of the event (must be unique)
 */
template <typename _Args, int _Code>
class Event
: public EventBase
{
public:
    /** Callback function type of this event type */
    using CallbackType           = EventCallback<_Args>;
    /** Arguments of the event type */
    using ArgsType               = _Args;
    /** Code of this event type */
    inline static const int Code = _Code;

    /**
     * @brief Construct a new Event
     */
    Event() : m_callbacks({}) {}
    /**
     * @brief Destroy the Event
     */
    virtual ~Event()
    {
        m_callbacks.clear();
    };

    /**
     * @brief Dispatch the argument to the registered callbacks
     * @param args arguments
     */
    void dispatch(ArgsType args) {
        for(EventDescriptor& desc : m_callbacks) {
            desc.callback(args, desc.userParams);
        }
    }

    /**
     * @brief Register a new callback
     * 
     * @param callback callback to register
     * @param userParams extra args to pass to the callback
     */
    void registerCallback(CallbackType callback, void* userParams)
    {
        m_callbacks.push_back({
            callback, userParams
        });
    }
    
    /**
     * @brief Unregister a callback
     * @param callback callback to unregister
     * @return bool - true if it has found one to unregister, false otherwise
     */
    bool unregisterCallback(CallbackType callback)
    {
        CallbackType* found = m_callbacks.find(callback);
        if(found != m_callbacks.end()) {
            m_callbacks.remove(found - m_callbacks.begin());
            return true;
        }
        return false;
    }

    /**
     * @brief Return the code of this event
     * @return int 
     */
    int getCode() const {
        return Code;
    }
private:
    /**
     * @brief Dispatch correct type of argument to the class
     * @param args argument to pass
     */
    void internalDispatch(void* args) override {
        dispatch(*(_Args*)args);
    }

protected:
    /**
     * @brief Describe a registered callback
     */
    struct EventDescriptor {
        /** callback to call */
        CallbackType callback;
        /** extra args */
        void* userParams;
    };
    /** List of registered callbacks */
    std::vector<EventDescriptor> m_callbacks;
};

}

#endif //_MX_EVENT_H_