//
// Created by user1 on 23/12/2024.
//

#ifndef EVENT_H
#define EVENT_H

#include <algorithm>
#include <functional>
#include <vector>

#include "../../FunctionalCpp/include/option.h"
#include "../../FunctionalCpp/include/option_prelude.h"
#include "event_connection.h"

namespace m24
{

template<typename... Args>
struct EventConnection;

template<typename... Args>
class Event
{
private:
    using Callable = std::function<void(Args...)>;
    using CallableWithId = std::pair<std::size_t, Callable>;
    std::vector<CallableWithId> _listeners;
    std::size_t _lastId = 0;

    friend class EventConnection<Args...>;

public:
    EventConnection<Args...> Attach(Callable const& cb)
    {
        std::size_t id = _lastId++;

        auto listener = CallableWithId{id, cb};
        _listeners.push_back(listener);

        return EventConnection<Args...>{id, this};
    }

private:
    void DetachById(std::size_t const id)
    {
        auto index = GetIndexById(id);
        if (index.IsNone()) return;

        auto iterator = _listeners.begin();
        std::advance(iterator, index.Unwrap());

        _listeners.erase(iterator);
    }

    [[nodiscard]] Option<std::size_t> GetIndexById(std::size_t id) const
    {
        using namespace m24::Prelude;

        std::size_t index = 0;

        for (auto& [cbId, cb]: _listeners)
        {
            if (cbId == id)
            {
                break;
            }

            index++;
        }

        if (index == _listeners.size())
        {
            return Prelude::None;
        }

        return Some(index);
    }

public:
    void Notify(Args... args)
    {
        for (auto [id, cb]: _listeners)
        {
            cb(args...);
        }
    }
};

} // namespace m24

#endif // EVENT_H
