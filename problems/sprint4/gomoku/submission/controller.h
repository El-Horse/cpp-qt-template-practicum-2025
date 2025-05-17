#pragma once

#ifdef PRAC_TESTS
#include "../tests/model.h"
#include "../tests/view.h"
#else
#include "model.h"
#include "view.h"
#endif

class Controller {
public:
    Controller() {
        // Model model;
        // View view;
        // model_ = model;
       // view_ = view;


        auto new_game =[&](size_t x, size_t y){
            model_.Reset(x,y);
            view_.SetupField(x,y);
            UpdateGame();
        };
        auto player_move =[&](size_t row, size_t col){
            Symbol player = model_.DoMove(row,col);
        if (player != Symbol::kEmpty){
                auto play = ToQString(player);
                view_.UpdateCell(row,col,play);
                UpdateGame();
                view_.show();
        }

        };

        view_ . SetNewgameCallback(new_game);
        view_.SetMoveCallback(player_move);

    }


    // Напишите контроллер.
    void UpdateGame(){
        auto game_status = model_.GetWinner();
        if ( game_status == std::nullopt){
            auto player = model_.GetNextPlayer();
            view_.SetStatus(ToQString(player));
            view_.SetStatusStyle("black",false);
        }
        else if (game_status == Symbol::kEmpty){
            view_.SetStatus("Ничья");
            view_.SetStatusStyle("red",true);
        }
        else if (game_status == Symbol::kCross
                   || game_status == Symbol::kNought){
            QString txt = "Выиграл " + ::ToQString(game_status.value());
            view_.SetStatus(txt);
            view_.SetStatusStyle("green", true);
            auto win_cell = model_.GetWinnerPath();
            for (auto cell : win_cell){
                view_.SetCellStyle(cell.first, cell.second,"green",true);
            }
        }
    }

private:
    Model model_;
    View view_;
};
