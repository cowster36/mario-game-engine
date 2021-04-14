#ifndef ENTITY_H
#define ENTITY_H
#include "state.h"
#include <SFML/Graphics.hpp>

class Entity {
    public:
        float x, y, sx, sy;
        sf::Sprite sprite;
        int num_states;
        State * states;
        int currentState = 0;
        int timer = 0;

        Entity();
        Entity(float x_, float y_, float sx_, float sy_, float spriteScaleX_, float spriteScaleY_, int num_states_, State * first_state_);
        void display(sf::RenderWindow &w, int frameCount);
        void updatePos(float scrollDist);
        bool checkCollision(Entity entity);
};

#endif
