#pragma once
#ifndef _MX_EVENTMANAGER_H_
#define _MX_EVENTMANAGER_H_

#include <functional>
#include <array>
#include <vector>
#include "../core/types.hpp"
#include "event.hpp"

namespace mx
{

class EventManager
{
public:
    EventManager() {
        m_registeredEvents = {};
    }
    ~EventManager() {
        m_registeredEvents.clear();
    }

    template <class EventType>
    void registerEvent() {
        m_registeredEvents.push_back(new EventType());
    }

    template <class EventType, typename EventArgsType>
    void dispatchEvent(const EventArgsType& args) {
        for(auto& event : m_registeredEvents) {
            if(EventType::Code == event->getCode()) {
                event->internalDispatch((void*)&args);
                break;
            }
        }
    }

    template <class EventType>
    EventType* getEvent() {
        for(auto& event : m_registeredEvents) {
            if(EventType::Code == event->getCode()) {
                return (EventType*)event;
            }
        }
        return nullptr;
    }

    void dispatchEvent(int code, void* args) {
        for(auto& event : m_registeredEvents) {
            if(code == event->getCode()) {
                event->internalDispatch(args);
                break;
            }
        }
    }

    static EventManager* Get() {
        if(!sInstance)
            sInstance = new EventManager();
        return sInstance;
    }
private:
    std::vector<EventBase*> m_registeredEvents{};
    inline static EventManager* sInstance;
};

} // namespace mx


#endif //_MX_EVENTMANAGER_H_