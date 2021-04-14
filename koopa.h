#ifndef KOOPA_H
#define KOOPA_H
#include "state.h"
#include "platform.h"
#include "uplatform.h"
#include "player.h"
#include <SFML/Graphics.hpp>

class Koopa : public Entity {
    public:
        int vx = 0;
        int vy = 0;
        Platform * currentPlatform = NULL;
        uPlatform * currentUPlatform = NULL;
        Koopa();
        Koopa(float x_, float y_, float sx_, float sy_, float spriteScaleX_, float spriteScaleY_, int num_states_, State * first_state_) :
        Entity {x_, y_, sx_, sy_, spriteScaleX_, spriteScaleY_, num_states_, first_state_} {}
        void update(bool gravityFlipped);
        bool checkPlayerCollision(Player player, bool gravityFlipped);
};
#endif
