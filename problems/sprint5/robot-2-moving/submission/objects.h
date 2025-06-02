#pragma once
#include"context.h"

#include "object.h"
#include "qdebug.h"
#include "qlogging.h"

class Stairs: public Object{

public:
    Stairs(GameContext& new_context,
           Coordinate& new_coord(int x, int y, int z), Direction new_dir, bool down):
    Object(new_context,new_coord,true)
        // dir_(new_dir),
        // down_(down)
        {
        dir_=new_dir;
        down_ = down;
        };
    void Interact(Character& character, Direction dir){
        if (dir == Invert(dir_)){
            auto new_pos = GetPosition() + Coordinate{0, 0, down_ ? -1 : 1} + Coordinate::FromDirection(dir);
            SetPosition(new_pos);
        }
        else{
            qInfo() << "Trying to go stairs in the wrong dir";
        }
    }
private:
    Direction dir_;
    bool down_;
};
