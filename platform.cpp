#include "state.h"
#include "entity.h"
#include "platform.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Platform::Platform() {};

void Platform::init() {
    for(int i = 0; i < 6; i++) {
        stalks[i] = Entity(x, y + 24 + 32 * i, 32, 16, spriteScaleX, spriteScaleY, 1, stalkState);
    }
};

void Platform::display(sf::RenderWindow &w, int frameCount) {
    mushroom.display(w, frameCount);
    for(int i = 0; i < 6; i++) {
        stalks[i].display(w, frameCount);
    }
};

void Platform::updatePos(float scrollDist) {
    mushroom.updatePos(scrollDist);
    for(int i = 0; i < 6; i++) {
        stalks[i].updatePos(scrollDist);
    }
};

bool Platform::checkCollision(Entity entity, bool gravityFlipped) {
    if(entity.x + entity.sx/2 > x - 112 && entity.x - entity.sx/2 < x + 112 && (entity.y + entity.sy/2) - y + 16 <= 16 && (entity.y + entity.sy/2) - y + 24 >= 0 && gravityFlipped == false) {
        return true;
    } else {
        return false;
    }
};
