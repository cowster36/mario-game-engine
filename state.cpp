#include "state.h"
#include <SFML/Graphics.hpp>

State::State(int id_, int numSprites_, sf::Texture * firstTexture_, int freq_) {
    id = id_;
    numSprites = numSprites_;
    freq = freq_;

    textures = new sf::Texture [numSprites_];
    for(int i = 0; i < numSprites_; i++) {
        textures[i] = *(firstTexture_ + i);
    }
}

State::State(){}
