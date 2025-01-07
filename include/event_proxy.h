//
// Created by user1 on 24/12/2024.
//

#ifndef EVENT_PROXY_H
#define EVENT_PROXY_H

#include "event.h"

namespace m24
{

template<typename... Args>
class EventProxy
{
private:
    using Callable = std::function<void(Args...)>;
    Event<Args...>& _event;

public:
    explicit EventProxy(Event<Args...>& observer)
        : _event(observer)
    {
    }

    EventConnection<Args...> Attach(Callable const& cb)
    {
        return _event.Attach(cb);
    }
};

} // namespace m24

#endif // EVENT_PROXY_H
