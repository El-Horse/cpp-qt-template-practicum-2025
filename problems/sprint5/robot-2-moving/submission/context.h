#pragma once

#include "utility/utility.h"

class Field;
class Object;

struct GameContext {
    ObjectMap<Object>& object_map;
    Field& field;
};
