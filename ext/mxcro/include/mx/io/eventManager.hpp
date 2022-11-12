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

/**
 * @brief Class to manage events
 */
class EventManager
{
public:
    /**
     * @brief Construct a new Event Manager
     */
    EventManager() {
        m_registeredEvents = {};
    }
    /**
     * @brief Destroy the Event Manager
     */
    ~EventManager() {
        m_registeredEvents.clear();
    }

    /**
     * @brief Register a new Event
     * @tparam EventType Type of the Event to register
     * (must be a derived class from mx::Event)
     */
    template <class EventType>
    void registerEvent() {
        m_registeredEvents.push_back(new EventType());
    }

    /**
     * @brief Dispatch an event
     * 
     * @tparam EventType Type of the Event to register
     * (must be a derived class from mx::Event) 
     * @tparam EventArgsType argument of the EventType (see EventType::ArgsType)
     * @param args argument to dispatch to the event
     */
    template <class EventType, typename EventArgsType>
    void dispatchEvent(const EventArgsType& args) {
        for(auto& event : m_registeredEvents) {
            if(EventType::Code == event->getCode()) {
                event->internalDispatch((void*)&args);
                break;
            }
        }
    }

    /**
     * @brief Get a registered event (or nullptr)
     * 
     * @tparam EventType Type of the Event to dispatch
     * (must be a derived class from mx::Event) 
     * @return EventType* nullptr if not found
     */
    template <class EventType>
    EventType* getEvent() {
        for(auto& event : m_registeredEvents) {
            if(EventType::Code == event->getCode()) {
                return (EventType*)event;
            }
        }
        return nullptr;
    }
    
    /**
     * @brief Dispatch an event
     * 
     * @param code code of the Event to dispatch
     * (must be a derived class from mx::Event) 
     * @param args argument to dispatch to the event
     */
    void dispatchEvent(int code, void* args) {
        for(auto& event : m_registeredEvents) {
            if(code == event->getCode()) {
                event->internalDispatch(args);
                break;
            }
        }
    }

    /**
     * @brief Return the Singleton
     * @return EventManager* 
     */
    static EventManager* Get() {
        if(!sInstance)
            sInstance = new EventManager();
        return sInstance;
    }
private:
    /** List of registered events */
    std::vector<EventBase*> m_registeredEvents{};
    /** Singleton */
    inline static EventManager* sInstance;
};

} // namespace mx


#endif //_MX_EVENTMANAGER_H_