#ifndef PLAYER_H
#define PLAYER_H
#include "state.h"
#include <SFML/Graphics.hpp>

class Player : public Entity {
    public:
        int vx = 0;
        int vy = 0;
        bool grounded = true;
        Player(float x_, float y_, float sx_, float sy_, float spriteScaleX_, float spriteScaleY_, int num_states_, State * first_state_) :
        Entity {x_, y_, sx_, sy_, spriteScaleX_, spriteScaleY_, num_states_, first_state_} {}
        void handleInput (bool * keys, bool gravityFlipped);
        void update();
};
#endif
