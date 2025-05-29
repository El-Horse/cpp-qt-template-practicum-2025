#pragma once

#include"character.h"

class Victim: public Character{
public:
    Victim(GameContext& new_context,
           Coordinate& new_coord, bool vis):
        Character(new_context, new_coord, vis)
    {};

private:


};
