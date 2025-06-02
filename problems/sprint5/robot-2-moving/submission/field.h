#pragma once


#include "character.h"
#include "qevent.h"
#include "utility/utility.h"


class Wall{
public:
    Wall();

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
        cells_ {w+1,h+1}
    {};

    int GetLevel() const{
        return level_;
    }

    void SetTile(Coordinate2D where, Tile* tile){
        tile = cells_.Get(where).floor;
    } // тут какая-то шляпа

    void SetWall(Coordinate2D where, Direction dir, Wall* wall){
        wall = GetWallPtr(where,dir);
    };

    Wall* GetWall(Coordinate2D where, Direction dir){
        return GetWallPtr(where,dir);
    }

    Wall*& GetWallPtr(Coordinate2D where, Direction dir){
        switch (dir) {
        case Direction::kUp:
            return cells_.Get(where).top_wall;
            break;
        case Direction::kDown:
            ++where.y_pos;
            return cells_.Get(where).top_wall;
            break;
        case Direction::kLeft:
            return cells_.Get(where).left_wall;
            break;
        case Direction::kRight:
            ++where.x_pos;
            return cells_.Get(where).left_wall;
        default:
            break;
        }
// тут я не понимаю, что надо сделать// вроде так
    }

private:
    int level_;
    int w_;
    int h_;
    Array2D<Cell> cells_;
};

class Field{
public:
    Field(int w, int h):
            w_(w), h_(h)
        {};

    int GetWidth() const{
        return w_;
    }
    int GetHeight() const{
        return h_;
    }

    Size GetRect() const {
        return {GetWidth(), GetHeight()};
    }

    void AddFloor(int level){
        floor_[level];
    }

    Floor& GetFloor(int floor){
        return floor_[floor];

    }

    const Floor& GetFloor(int floor) const{
        auto iter = floor_.find(floor);
        return iter->second;
    }
private:
    int w_ = 0;
    int h_ = 0;
    std::map <int,Floor> floor_;
};
