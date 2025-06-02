#pragma once

// #include "field.h"
#include "mainwindow.h"



class FloorTile: public Tile{

};

class EmptyTile: public Tile{

};



class Door: public Wall{
public:
    void Interact(Character& character, Direction) override{
        if (character.IsActive()){
            is_opened_ = true;
            qInfo() << "Opening door";
        }
    }

    bool CanPass(const Character&, Direction)const override{
        if (is_opened_)
            return true;
        return false;
    }

private:
    bool is_opened_ = false;
};


class EmptyWall: public Wall{
public:
    bool CanPass(/*const Character&, Direction*/){
        return true;
    }
};

class EdgeWall: public Wall{
public:
    bool CanPass(const Character&, Direction) const override {
        return false;
    }
};
