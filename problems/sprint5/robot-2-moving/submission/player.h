#pragma once

#include"character.h"
#include "qdebug.h"
#include "qlogging.h"

class Player: public Character{
public:
    // Player(GameContext& new_context, Coordinate& new_coord):
    //     Character (new_context,new_coord){};
    Player(GameContext& new_context,
           Coordinate& new_coord, Direction dir):
        Character(new_context,new_coord,dir)
    {
            qInfo()<<"Player spawned on "
                << ToString(this->GetPosition())
                <<" dir " << ToString(this->GetDirection());
    };

    void GoCommand(Direction dir){
        Coordinate next_pos = GetPosition() + Coordinate::FromDirection(dir);

        if(this->CanPassWall(dir) == false){
            auto wall = GetWall(dir);
            wall->Interact(this,dir);
            qInfo() << "Player stoped on wall";
            return;
        }

        if (this->CanGo(dir) == false){ // подозрительно
            auto sets = GetContext().object_map.Get(next_pos);
            for (auto it : sets){
                it->Interact(this,dir);
            }
            qInfo() <<"Player stoped on object";
            return;
        }
        int old_lvl = this->GetPosition().z_pos;
        SetPosition(next_pos);
        int new_lvl = this->GetPosition().z_pos;
        if (new_lvl > old_lvl){
            qInfo() << "Go stairs up";
        }
        else if (new_lvl < old_lvl){
            qInfo() << "Go stairs up";
        }
        else
            qInfo() << "Player moves";
    }

    bool IsActive ()const override{
        return true;
    }

private:


};



