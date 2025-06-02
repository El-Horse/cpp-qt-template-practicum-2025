#pragma once
#include "context.h"
#include "object.h"
#include "field.h"

class Character: public Object{
public:
    // Character ();
    // using Object::Object;
    Character (GameContext& new_context,
              Coordinate& new_coord, Direction dir):
        Object(new_context, new_coord, true),
        dir_(dir)
    {};
    Character (GameContext& new_context,
              Coordinate& new_coord, bool vis):
     Object(new_context, new_coord, vis)
    {};

    Direction GetDirection() const{
        return dir_;
    }

    Wall* GetWall(Direction dir) const{
        return this->GetWall(dir);
    }

    void SetDirection (const Direction& new_dir){
        dir_ = new_dir;
    };

    bool CanPassWall(Direction dir) const{
        auto wall = GetWall(dir);
        if (wall != nullptr){
            return wall->CanPass(this,dir);
        }
        return false;
    }

    bool CanGo(Direction dir) const{
        auto next_pos = GetPosition() + Coordinate::FromDirection(dir);
        auto obj = GetContext();
        auto sets = obj.object_map.Get(next_pos);
        for (auto it: sets){
            if (it->CanCover(this,next_pos) == false){
                return false;
            }
        }
        return true;
    }

    virtual bool IsActive() const {
        return false;
    }

private:
    Direction dir_;

};
