#pragma once
#include"context.h"

#include "object.h"

class Stairs: public Object{

public:
Stairs(GameContext& new_context,
       Coordinate& new_coord, bool vis, Direction new_dir, bool down):
Object(new_context,new_coord,vis)
    // dir_(new_dir),
    // down_(down)
    {
    dir_=new_dir;
    down_ = down;
    };

private:
    Direction dir_;
    bool down_;
};
