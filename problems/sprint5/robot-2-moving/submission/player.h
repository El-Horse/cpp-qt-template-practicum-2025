#pragma once

#include"character.h"

class Player: public Character{
public:
    Player(GameContext& new_context,
           Coordinate& new_coord, bool vis):
        Character(new_context,new_coord,vis)
    {};

private:


};



