#pragma once
#include "context.h"
#include "object.h"

class Character: public Object{
public:
    // Character () = default;
    // using Object::Object;
    Character (GameContext& new_context,
              Coordinate& new_coord, bool vis):
     Object(new_context, new_coord, vis)
    {};

    Direction GetDirection() const{
        return dir_;
    }

    void SetDirection (const Direction& new_dir){
        dir_ = new_dir;
    };

private:
    Direction dir_;

};
