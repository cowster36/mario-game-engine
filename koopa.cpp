#include "state.h"
#include "entity.h"
#include "platform.h"
#include "uplatform.h"
#include "koopa.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

Koopa::Koopa() {};

void Koopa::update (bool gravityFlipped) {
    if(sprite.getScale().x < 0 && vx < 0) {
        sprite.scale(-1, 1);
    } else if(sprite.getScale().x > 0 && vx > 0) {
        sprite.scale(-1, 1);
    }

    if(sprite.getScale().y > 0 && gravityFlipped == true) {
        sprite.scale(1, -1);
    } else if(sprite.getScale().y < 0 && gravityFlipped == false) {
        sprite.scale(1, -1);
    }

    if(gravityFlipped == true && currentPlatform != NULL) {
        currentPlatform = NULL;
    }

    if(gravityFlipped == false && currentUPlatform != NULL) {
        currentUPlatform = NULL;
    }

    if(gravityFlipped == true && currentUPlatform == NULL) {
        vy -= 1;
        if(vx != 0) vx = 0;
    }

    if(gravityFlipped == false && currentPlatform == NULL) {
        vy += 1;
        if(vx != 0) vx = 0;
    }

    if(currentPlatform != NULL) {
        if(x > (*currentPlatform).x + 112) {
            vx *= -1;
        }

        if(x < (*currentPlatform).x - 112) {
            vx *= -1;
        }
    }

    if(currentUPlatform != NULL) {
        if(x > (*currentUPlatform).x + 112) {
            vx *= -1;
        }

        if(x < (*currentUPlatform).x - 112) {
            vx *= -1;
        }
    }

    x += vx;
    y += vy;
};

bool Koopa::checkPlayerCollision(Player player, bool gravityFlipped) {
    if(player.x + player.sx/2 > x - sx/2 && player.x - player.sx/2 < x + sx/2 && (player.y + player.sy/2) - y <= 0 && (player.y + player.sy/2) - y + 16 >= 0 && gravityFlipped == false) {
        return true;
    } else if(player.x + player.sx/2 > x - sx/2 && player.x - player.sx/2 < x + sx/2 && player.y - player.sy/2 - y - 16 <= 16 && player.y - player.sy/2 - y > 0 && gravityFlipped == true){
        return true;
    } else {
        return false;
    }
};
