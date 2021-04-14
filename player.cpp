#include "state.h"
#include "entity.h"
#include "player.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void Player::handleInput (bool * keys, bool gravityFlipped) {
    if(*keys == true) {
        vx = 8;
        currentState = 1;
    }

    if(*(keys + 1) == true) {
        vx = -8;
        currentState = 1;
    }

    if(*(keys + 2) == true && grounded == true) {
        if(gravityFlipped == false) {
            vy = -15;
        } else {
            vy = 15;
        }
        currentState = 2;
    }
};

void Player::update() {
    if(sprite.getScale().x < 0 && vx < 0) {
        sprite.scale(-1, 1);
    } else if(sprite.getScale().x > 0 && vx > 0) {
        sprite.scale(-1, 1);
    }

    if(std::abs(vy) != 0) grounded = false;

    if(vy > 20) vy = 20;
    if(vy < -20) vy = -20;

    x += vx;
    y += vy;

    if(vx > 0) {
        vx -= 0.2f;
    } else if(vx < 0) {
        vx += 0.2f;
    }

    sprite.setPosition(sprite.getPosition().x, y + 300);

    if(grounded == false) {
        if(vy <= 0 && currentState != 2) {
            currentState = 2;
        } else if(vy > 0 && currentState != 3) {
            currentState = 3;
        }
    } else if(grounded == true && vx == 0 && currentState != 0) {
        currentState = 0;
    }
};
