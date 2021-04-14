#include "state.h"
#include "entity.h"
#include <SFML/Graphics.hpp>

Entity::Entity() {};

Entity::Entity(float x_, float y_, float sx_, float sy_, float spriteScaleX_, float spriteScaleY_, int num_states_, State * first_state_) {
    x = x_;
    y = y_;
    sx = sx_;
    sy = sy_;
    num_states = num_states_;

    states = new State [num_states_];
    for(int i = 0; i < num_states_; i++) {
        states[i] = *(first_state_ + i);
    }

    sprite.setScale(sf::Vector2f(spriteScaleX_, spriteScaleY_));
    sprite.setOrigin(sx_/(2 * spriteScaleX_), sy_/(2 * spriteScaleY_));
    sprite.setPosition(x_ + 300, y_ + 300);
};

void Entity::display(sf::RenderWindow &w, int frameCount) {
    int currentSprite = states[currentState].spriteCounter;
    sf::Texture currentTexture = states[currentState].textures[currentSprite];
    sprite.setTexture(currentTexture);
    int spriteSizeX = currentTexture.getSize().x;
    int spriteSizeY = currentTexture.getSize().y;
    sprite.setTextureRect(sf::IntRect(0, 0, spriteSizeX, spriteSizeY));

    w.draw(sprite);

    if(frameCount % states[currentState].freq == 0) {
        if(currentSprite < states[currentState].numSprites - 1) {
            states[currentState].spriteCounter += 1;
        } else {
            states[currentState].spriteCounter = 0;
        }
    }
};

void Entity::updatePos(float scrollDist) {
    sprite.setPosition(x + 300 - scrollDist, y + 300);
};

bool Entity::checkCollision(Entity entity) {
    if(entity.x + entity.sx/2 >= x - sx/2 && entity.x - entity.sx/2 <= x + sx/2 && (entity.y - entity.sy/2) <= y + sy/2 && (entity.y + entity.sy/2) >= y - sy/2) {
        return true;
    } else {
        return false;
    }
};
