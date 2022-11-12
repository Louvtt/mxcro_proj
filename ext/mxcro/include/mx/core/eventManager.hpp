#pragma once
#ifndef _MX_EVENTMANAGER_H_
#define _MX_EVENTMANAGER_H_

#include <functional>
#include <array>
#include <vector>
#include "types.hpp"
#include "event.hpp"

namespace mx
{

class EventManager
{
public:
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

private:
    std::vector<EventBase*> m_registeredEvents{};
};

} // namespace mx


#endif //_MX_EVENTMANAGER_H_