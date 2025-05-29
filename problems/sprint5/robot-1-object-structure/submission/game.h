#pragma once
#include "context.h"
#include "utility/utility.h"

class Game {
public:
    Game() {}

    GameContext& GetContext() {
        return context_;
    }

private:
    ObjectMap<Object> object_map_;
    GameContext context_{.object_map = object_map_,};
};
