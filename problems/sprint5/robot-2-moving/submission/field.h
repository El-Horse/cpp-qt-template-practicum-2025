#pragma once
#include "character.h"
#include "game.h"
#include "utility/utility.h"

class Wall{
public:

    virtual bool CanPass(const Character& character, Direction dir) const = 0;
    virtual void Interact(Character&, Direction) {}


private:


};

class Tile{
public:

// private: хуита тут
    int x_;
    int y_;
};

struct Cell {
    Tile* floor = nullptr;
    Wall* left_wall = nullptr;
    Wall* top_wall = nullptr;
};

class Floor{
public:
    // Floor();

    Floor(int level, int w, int h):
        level_(level),
        w_(w),
        h_(h),
        floor_ {w,h}
    {};

    int GetLevel() const{
        return level_;
    }

    void SetTile(Coordinate2D where, Tile* tile){
        tile->x_ = where.x_pos;
        tile->y_ = where.y_pos;
    } // тут какая-то шляпа

    void SetWall(Coordinate2D where, Direction dir, Wall* wall){
// все. я тут закончился
    };

    Wall*& GetWallPtr(Coordinate2D where, Direction dir);

private:
    int level_;
    int w_;
    int h_;
    Array2D<Cell> floor_;
};
