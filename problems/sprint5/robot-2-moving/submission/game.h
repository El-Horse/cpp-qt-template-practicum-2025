#pragma once
// #include "context.h"
// #include "field.h"
// #include "player.h"
#include "utility/utility.h"
#include "mainwindow.h"

class Game {
public:
    Game(int w, int h):
        game_world_ (Field{w,h})
    {};

    GameContext& GetContext() {
        return context_;
    }

    Floor& AddFloor(int level){
        game_world_.AddFloor(level);
        return game_world_.GetFloor(level);
    }

    void SetPlayer(Player* player){
        robot_ = player;
    }

    Field& GetField(){
        return game_world_;
    }

    Player& GetPlayer(){
        return *robot_;
    }

    Floor& GetCurrentFloor(){
        int lvl = robot_->GetPosition().z_pos;
        return game_world_.GetFloor(lvl);

    }
private:
    Field game_world_;
    Player* robot_;
    ObjectMap<Object> object_map_;
    GameContext context_{.object_map = object_map_,};
};
