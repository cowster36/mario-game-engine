#include "state.h"
#include "entity.h"
#include "uplatform.h"
#include <SFML/Graphics.hpp>
#include <iostream>

uPlatform::uPlatform() {};

void uPlatform::init() {
    for(int i = 0; i < 6; i++) {
        stalks[i] = Entity(x, y - 40 - 32 * i, 32, 16, spriteScaleX, spriteScaleY, 1, stalkState);
    }
    mushroom.sprite.scale(1, -1);
};

void uPlatform::display(sf::RenderWindow &w, int frameCount) {
    mushroom.display(w, frameCount);
    for(int i = 0; i < 6; i++) {
        stalks[i].display(w, frameCount);
    }
};

void uPlatform::updatePos(float scrollDist) {
    mushroom.updatePos(scrollDist);
    for(int i = 0; i < 6; i++) {
        stalks[i].updatePos(scrollDist);
    }
};

bool uPlatform::checkCollision(Entity entity, bool gravityFlipped) {
    if(entity.x + entity.sx/2 > x - 112 && entity.x - entity.sx/2 < x + 112 && entity.y - entity.sy/2 - y - 16 <= 16 && entity.y - entity.sy/2 - y > 0 && gravityFlipped == true) {
        return true;
    } else {
        return false;
    }
};
