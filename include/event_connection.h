//
// Created by user1 on 24/12/2024.
//

#ifndef EVENT_CONNECTION_H
#define EVENT_CONNECTION_H

#include "event.h"

namespace m24
{

template<typename... Args>
class Event;

template<typename... Args>
class EventConnection
{
private:
    bool _disconnected = false;
    std::size_t _id;
    Event<Args...>* _event;

public:
    EventConnection(std::size_t _id, Event<Args...>* event)
        : _id(_id),
          _event(event)
    {
    }

    ~EventConnection() = default;

    [[nodiscard]] std::size_t Id() const
    {
        return _id;
    }
    
    Event<Args...> const& Event() const
    {
        return _event;
    }

    void Detach()
    {
        if (_disconnected) return;

        _event->DetachById(_id);
        _disconnected = true;
    }
};

} // namespace m24


#endif // _observer_CONNECTION_H
