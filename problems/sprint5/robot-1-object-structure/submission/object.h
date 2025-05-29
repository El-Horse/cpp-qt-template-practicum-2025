#pragma once

#include "context.h"
#include"utility/geometry.h"

class Object{
public:
    // Object() = default;
    Object(GameContext& new_context,
           Coordinate& new_coord, bool vis):
    context_(new_context),
        coordinate_(new_coord),
        visibility_(vis)
    {
        context_.object_map.Place(coordinate_,this);

    };

    ~Object(){
        context_.object_map.Remove(coordinate_,this);
    }
    const Coordinate GetPosition () const{
        return coordinate_;
    };

    void SetPosition (const Coordinate& new_position){
        context_.object_map.Remove(coordinate_,this);
        coordinate_ = new_position;
        context_.object_map.Place(coordinate_,this);
    };

    bool IsVisible () const{
        return visibility_;
    };

    void Disappear (){
        visibility_ = false;
        context_.object_map.Remove(coordinate_,this);
    };

    GameContext& GetContext () const{
        return context_;
    };

private:
    void PlaceToMap();

    void RemoveFromMap();


private:
    GameContext& context_;
    Coordinate coordinate_;
    bool visibility_ = false;
};
