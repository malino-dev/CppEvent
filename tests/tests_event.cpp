#include <gtest/gtest.h>
#include <print>

#include "../include/event.h"
#include "../include/event_proxy.h"

using namespace m24;

#include "player.h"

void OnDamageTaken(int damage)
{
    std::println("Took damage: {}", damage);
}

TEST(Observer, SimpleTest)
{
    Event<int> obs;

    auto connection = obs.Attach(OnDamageTaken);
    obs.Notify(42);

    connection.Detach();
    obs.Notify(69);
}

TEST(Observer, ComplexTest)
{
    Player player;

    auto event = player._damaged;
    auto proxy = player.Damaged;

    auto connection = proxy.Attach(OnDamageTaken);
    player.TakeDamage(42);

    connection.Detach();
    player.TakeDamage(69);
}

TEST(Observer, IdConsistency)
{
    Player player;
    auto proxy = player.Damaged;

    for (int i = 0; i < 100; i++)
    {
        auto connection = proxy.Attach(OnDamageTaken);
        connection.Detach();
    }
}

TEST(Observer, MassAttach)
{
    Player player;
    auto proxy = player.Damaged;

    std::vector<EventConnection<int>> connections;

    for (int i = 0; i < 10; i++)
    {
        auto connection = proxy.Attach(OnDamageTaken);
        connection.Detach();
    }

    for (int i = 0; i < 10; i++)
    {
        auto connection = proxy.Attach(OnDamageTaken);
        connections.push_back(connection);
    }

    srand(time(nullptr));

    while (!connections.empty())
    {
        decltype(connections)::difference_type const index = rand() % connections.size();
        connections[index].Detach();

        connections.erase(connections.begin() + index);
    }
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
