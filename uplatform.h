#ifndef UPLATFORM_H
#define UPLATFORM_H
#include "state.h"
#include "entity.h"
#include <SFML/Graphics.hpp>

class uPlatform {
    public:
        float x, y, spriteScaleX, spriteScaleY;
        State mushroomState;
        State  * stalkState;
        Entity mushroom;
        Entity stalks [6];

        uPlatform(float x_, float y_, float spriteScaleX_, float spriteScaleY_, State * mushroomState_, State * stalkState_) :
        x(x_), y(y_), spriteScaleX(spriteScaleX_), spriteScaleY(spriteScaleY_), stalkState(stalkState_), mushroom(x_, y_, 224, 32, spriteScaleX_, spriteScaleY_, 1, mushroomState_) {};
        uPlatform();
        void init();
        void display(sf::RenderWindow &w, int frameCount);
        void updatePos(float scrollDist);
        bool checkCollision(Entity entity, bool gravityFlipped);
};

#endif
