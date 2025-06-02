
#pragma once

#include "qevent.h"
#include "utility/geometry.h"
#include "game.h"

class Controller {
public:
    Controller(Game& game) : game_{game} {}

    void OnMoveKey(Direction dir) {
        qInfo() << "<<< Moving in direction "<< ToString(dir);
        if (game_.GetPlayer().GetDirection() == dir){
            qInfo() << "Trying to go";
            game_.GetPlayer().GoCommand(dir);
        }
        else{
            qInfo() << "Changing direction";
            game_.GetPlayer().SetDirection(dir);
        }

        qInfo() << ">>> New player position: "<< ToString(game_.GetPlayer().GetPosition())
                <<" dir " <<ToString(game_.GetPlayer().GetDirection());
    }

    void OnReleaseMoveKey(Direction dir) {
        // Этот метод пока ничего не будет делать.
    }

private:
    Game& game_;
};
