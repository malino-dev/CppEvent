//
// Created by user1 on 29/12/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
    Event<int> _damaged;
    EventProxy<int> Damaged{_damaged};

    void TakeDamage(int damage)
    {
        _damaged.Notify(damage);
    }
};

#endif //PLAYER_H
