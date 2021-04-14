#ifndef STATE_H
#define STATE_H
#include <SFML/Graphics.hpp>

class State {
    public:
        int id;
        int numSprites;
        sf::Texture * textures;
        int spriteCounter = 0;
        int freq = 1;

        State();
        State(int id_, int numSprites_, sf::Texture * firstTexture_, int freq_);
};

#endif
