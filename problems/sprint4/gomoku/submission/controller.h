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
    Controller (){


        auto start_game =[&](size_t x, size_t y){
            model_.Reset(x,y);
            view_.SetupField(x,y);
            Update();

        };
        auto do_move = [&](size_t x, size_t y){
            std::optional<Symbol> move = model_.DoMove(x, y);
            if (move.value() != Symbol::kEmpty) {
                view_.UpdateCell(x, y, ToQString(move.value()));
                Update();
            }
        };
        view_.SetNewgameCallback(start_game);
        start_game(3,3);
        view_.SetMoveCallback(do_move);
        view_.show();
    }

private:
    Model model_;
    View view_;

    void Update(){
        auto winner = model_.GetWinner();
        if (!winner.has_value()){
            auto next_player = model_.GetNextPlayer();
            QString txt = "Ход игрока " + ToQString(next_player);
            view_.SetStatus(txt);
            view_.SetStatusStyle("black", false);
        }

        else if (winner.value() == Symbol::kEmpty){
            view_.SetStatus("Ничья");
            view_.SetStatusStyle("red",true);
        }
        else{
            QString txt = "Выиграл " + ToQString(winner.value());
            view_.SetStatus(txt);
            view_.SetStatusStyle("green", true);
            auto win_path = model_.GetWinnerPath();
            for (auto cell : win_path){
                view_.SetCellStyle(cell.first, cell.second, "green", true);
            }
        }
    }
};
