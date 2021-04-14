#include "entity.h"
#include "state.h"
#include "player.h"
#include "koopa.h"
#include "platform.h"
#include "uplatform.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

int main() {
    int width = 600;
    int height = 600;
    int frameCount = 0;

    sf::Music beep;
    beep.openFromFile("beep.wav");
    //beep.play();
    beep.setVolume(25.f);

    sf::Music beepLoop;
    beepLoop.openFromFile("beeploop.wav");
    beepLoop.setVolume(25.f);
    bool musicLoopStarted = false;

    sf::SoundBuffer jumpSoundBuffer;
    jumpSoundBuffer.loadFromFile("jump.wav");
    sf::Sound jumpSound;
    jumpSound.setBuffer(jumpSoundBuffer);
    jumpSound.setVolume(50.f);

    sf::SoundBuffer stompSoundBuffer;
    stompSoundBuffer.loadFromFile("stomp.wav");
    sf::Sound stompSound;
    stompSound.setBuffer(stompSoundBuffer);
    stompSound.setVolume(50.f);

    bool gravityFlipped = false;
    bool keys [4] {false, false, false, false};
    bool keysReleased [4] = {true, true, true, true};

    sf::RenderWindow window (sf::VideoMode(width, height), "physics");
    window.setFramerateLimit(30);

    sf::Texture bgTex;
    sf::Texture * texAtlas = new sf::Texture [19];

    sf::Texture bgBlueArrow;
    sf::Texture bgRedArrow;

    for(int i = 0; i < 5; i++) {
        texAtlas[i].loadFromFile("mario.png", sf::IntRect(i * 17, 4, 16, 28));
    }

    texAtlas[5].loadFromFile("mario.png", sf::IntRect(85, 1, 16, 31));

    for(int i = 6; i < 9; i++) {
        texAtlas[i].loadFromFile("mario.png", sf::IntRect(102 + (i - 6) * 19, 4, 18, 28));
    }

    texAtlas[9].loadFromFile("mario.png", sf::IntRect(159, 3, 16, 29));

    texAtlas[10].loadFromFile("mario.png", sf::IntRect(176, 0, 112, 16));
    texAtlas[11].loadFromFile("mario.png", sf::IntRect(176, 16, 16, 16));

    for(int i = 12; i < 16; i++) {
        texAtlas[i].loadFromFile("mario.png", sf::IntRect(192 + (i - 12) * 10, 16, 10, 14));
    }

    for(int i = 16; i < 19; i++) {
        texAtlas[i].loadFromFile("mario.png", sf::IntRect(289 + (i - 16) * 17, 5, 16, 27));
    }

    bgTex.loadFromFile("bg.png");
    bgBlueArrow.loadFromFile("bluearrow.png");
    bgRedArrow.loadFromFile("redarrow.png");

    State * stateAtlas = new State [9];
    //mario idle
    stateAtlas[0] = State(0, 2, texAtlas, 90);
    //mario walking
    stateAtlas[1] = State(1, 3, texAtlas + 6, 2);
    //mario jumping
    stateAtlas[2] = State(2, 1, texAtlas + 5, INFINITY);
    //mario falling
    stateAtlas[3] = State(3, 1, texAtlas + 9, INFINITY);

    //mushroom platform idle
    stateAtlas[4] = State(4, 1, texAtlas + 10, INFINITY);
    //mushroom stalk
    stateAtlas[5] = State(5, 1, texAtlas + 11, INFINITY);;

    //coin idle
    stateAtlas[6] = State(6, 4, texAtlas + 12, 6);

    //koopa walking
    stateAtlas[7] = State(7, 2, texAtlas + 16, 5);

    //koopa smashed
    stateAtlas[8] = State(8, 1, texAtlas + 18, INFINITY);

    Player mario = Player(0, 0, 32, 56, 2, 2, 4, stateAtlas);
    Platform platforms [40];
    uPlatform uplatforms [40];
    Entity coins [40];
    Koopa koopas [40];
    int numKoopas = 0;

    sf::Sprite background;
    background.setTexture(bgTex);

    sf::Sprite bgArrows [4];
    int bgArrowsX [6] = {0, 200, 400, 600};
    for(int i = 0; i < 4; i++) {
        bgArrows[i].setTexture(bgBlueArrow);
        bgArrows[i].setPosition(bgArrowsX[i], 200 + (i % 2) * 100);
    }

    std::srand(std::sin(std::time(nullptr) * 10) * 100);

    for(int i = 0; i < 40; i++) {
        float x1 = i * 400 + std::rand()/(float) RAND_MAX * 80;
        float x2 = i * 400 + std::rand()/(float) RAND_MAX * 80;
        float y1 = 100 + std::rand()/(float) RAND_MAX * 150;
        float y2 = -100 - std::rand()/(float) RAND_MAX * 150;

        float koopaR1 = std::rand()/(float) RAND_MAX;
        float koopaR2 =  2 * std::rand()/(float) RAND_MAX - 1.f;
        float koopaR3 = std::rand()/(float) RAND_MAX;

        platforms[i] = Platform(x1, y1, 2, 2, stateAtlas + 4, stateAtlas + 5);
        platforms[i].init();

        uplatforms[i] = uPlatform(x2, y2, 2, 2, stateAtlas + 4, stateAtlas + 5);
        uplatforms[i].init();

        //spawn koopa on bottom platform
        if(koopaR3 > 0.25f && i != 0) {
            koopas[numKoopas] = Koopa(x1 + koopaR2 * 20, y1 - 43, 20, 54, 2, 2, 2, stateAtlas + 7);
            koopas[numKoopas].currentPlatform = platforms + i;

            if(koopaR1 > 0.5f) {
                //start going right
                koopas[numKoopas].sprite.scale(-1, 1);
                koopas[numKoopas].vx = 2;
            } else {
                //start going left
                koopas[numKoopas].vx = -2;
            }
            numKoopas += 1;
        }

        if(i % 2 == 0) {
            coins[i] = Entity(i * 400 + std::rand()/(float) RAND_MAX * 80, y1 - 60 - std::rand()/(float) RAND_MAX * 100, 20, 28, 2, 2, 1, stateAtlas + 6);
        } else {
            coins[i] = Entity(i * 400 + std::rand()/(float) RAND_MAX * 80, y2 + 60 + std::rand()/(float) RAND_MAX * 100, 20, 28, 2, 2, 1, stateAtlas + 6);
        }
    }

    delete[] texAtlas;
    delete[] stateAtlas;

    sf::Clock gameClock;
    sf::Clock musicClock;
    bool firstClockRun = true;

    while (window.isOpen()) {
        sf::Event event;
        if(keys[2] == true) {
            keys[2] = false;
        }

        if(keys[3] == true) {
            keys[3] = false;
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if(event.type == sf::Event::KeyPressed) {
                switch(event.key.code) {
                    case (sf::Keyboard::D):
                        keys[0] = true;
                    break;
                    case (sf::Keyboard::A):
                        keys[1] = true;
                    break;
                    case (sf::Keyboard::Space):
                        if(keysReleased[2] == true) {
                            keys[2] = true;
                            keysReleased[2] = false;
                        }
                    break;
                    case (sf::Keyboard::LShift):
                        if(keysReleased[3] == true) {
                            keys[3] = true;
                            keysReleased[3] = false;
                        }
                    break;
                }
            } else if(event.type == sf::Event::KeyReleased) {
                switch(event.key.code) {
                    case (sf::Keyboard::D):
                        keys[0] = false;
                    break;
                    case (sf::Keyboard::A):
                        keys[1] = false;
                    break;
                    case (sf::Keyboard::Space):
                        keys[2] = false;
                        keysReleased[2] = true;
                    break;
                    case(sf::Keyboard::LShift):
                        keys[3] = false;
                        keysReleased[3] = true;
                    break;
                }
            }
        }

        if(keys[2] == true && mario.grounded == true) {
            jumpSound.play();
        }

        if(keys[3] == true) {
            if(gravityFlipped == false) {
                gravityFlipped = true;
                for(int i = 0; i < 6; i++) {
                    bgArrows[i].setTexture(bgRedArrow);
                }
            } else {
                gravityFlipped = false;
                for(int i = 0; i < 6; i++) {
                    bgArrows[i].setTexture(bgBlueArrow);
                }
            }
        }

        if(gravityFlipped == false) {
            window.clear(sf::Color(12, 51, 128));
        } else {
            window.clear(sf::Color(150, 30, 30));
        }

        for(int i = 0; i < 4; i++) {
            window.draw(bgArrows[i]);

            float x = bgArrowsX[i] - mario.x;
            if(x < -70) {
                bgArrowsX[i] += 800;
            }

            bgArrows[i].setPosition(x, 200 + (i % 2) * 100);
        }

        int startingIndex = std::floor(mario.x/400);
        bool grounded = false;

        for(int i = startingIndex - 1; i < startingIndex + 3; i++) {
            if(i >= 0 && i <= 39) {
                platforms[i].display(window, 1);
                platforms[i].updatePos(mario.x);

                uplatforms[i].display(window, 1);
                uplatforms[i].updatePos(mario.x);

                coins[i].display(window, frameCount);
                coins[i].updatePos(mario.x);
                if(coins[i].checkCollision(mario) == true) {
                    coins[i].y = 1000;
                }

                if(platforms[i].checkCollision(mario, gravityFlipped) == true && mario.vy >= 0) {
                    mario.vy = 0;
                    mario.y = platforms[i].y - 16 - mario.sy/2;
                    mario.grounded = true;
                    grounded = true;
                }

                if(uplatforms[i].checkCollision(mario, gravityFlipped) == true && mario.vy <= 0) {
                    mario.vy = 0;
                    mario.y = uplatforms[i].y + 16 + mario.sy/2;
                    mario.grounded = true;
                    grounded = true;
                }
            }
        }

        for(int i = numKoopas - 1; i >= 0; i--) {
            if(koopas[i].timer == 0) {
                if(koopas[i].x - mario.x > -320 && koopas[i].x - mario.x < 310) {
                    koopas[i].display(window, frameCount);
                    koopas[i].updatePos(mario.x);

                    for(int j = 0; j < 40; j++) {
                        if(koopas[i].currentPlatform == NULL && koopas[i].currentUPlatform == NULL) {
                            if(platforms[j].checkCollision(koopas[i], gravityFlipped) == true) {
                                koopas[i].y = platforms[j].y - 43;
                                koopas[i].vy = 0;
                                koopas[i].currentPlatform = platforms + j;
                                if(koopas[i].sprite.getScale().x < 0) {
                                    koopas[i].vx = 2;
                                } else {
                                    koopas[i].vx = -2;
                                }
                            }

                            if(uplatforms[j].checkCollision(koopas[i], gravityFlipped) == true) {
                                koopas[i].y = uplatforms[j].y + 43;
                                koopas[i].vy = 0;
                                koopas[i].currentUPlatform = uplatforms + j;
                                if(koopas[i].sprite.getScale().x < 0) {
                                    koopas[i].vx = 2;
                                } else {
                                    koopas[i].vx = -2;
                                }
                            }
                        }
                    }

                    koopas[i].update(gravityFlipped);

                    if(koopas[i].y < -332 || koopas[i].y > 332) {
                        for(int j = i; j < numKoopas - 1; j++) {
                            koopas[j] = koopas[j + 1];
                        }
                        numKoopas -= 1;
                    }

                    if( (gravityFlipped == false && mario.vy > 0) == true || (gravityFlipped == true && mario.vy < 0) == true) {
                        if(koopas[i].checkPlayerCollision(mario, gravityFlipped) == true) {
                            koopas[i].currentState = 1;
                            koopas[i].vx = 0;
                            koopas[i].timer += 1;
                            stompSound.play();

                            if(gravityFlipped == true) {
                                mario.vy = 15;
                            } else {
                                mario.vy = -15;
                            }
                        }
                    }
                } else {
                    if(koopas[i].currentPlatform != NULL && gravityFlipped == true) {
                        koopas[i].currentUPlatform = uplatforms + (koopas[i].currentPlatform - platforms);
                        koopas[i].y = (*(koopas[i].currentUPlatform)).y  + 43;
                        koopas[i].currentPlatform = NULL;
                    }

                    if(koopas[i].currentUPlatform != NULL && gravityFlipped == false) {
                        koopas[i].currentPlatform = platforms + (koopas[i].currentUPlatform - uplatforms);
                        koopas[i].y = (*(koopas[i].currentPlatform)).y - 43;
                        koopas[i].currentUPlatform = NULL;
                    }
                }
            } else {
                koopas[i].display(window, frameCount);
                koopas[i].updatePos(mario.x);

                if(koopas[i].timer == 3) {
                    for(int j = i; j < numKoopas - 1; j++) {
                        koopas[j] = koopas[j + 1];
                    }
                    numKoopas -= 1;
                } else {
                    koopas[i].timer += 1;
                }
            }
        }

        if(grounded == false) {
            mario.grounded = false;
            if(gravityFlipped == false) {
                mario.vy += 1;
            } else if(gravityFlipped == true) {
                mario.vy -= 1;
            }
        }

        if(gravityFlipped == true && mario.sprite.getScale().y > 0) mario.sprite.scale(1, -1);
        if(gravityFlipped == false && mario.sprite.getScale().y < 0) mario.sprite.scale(1, -1);

        mario.display(window, frameCount);

        window.display();

        mario.handleInput(keys, gravityFlipped);
        mario.update();

        if(firstClockRun == true) {
            if(gameClock.getElapsedTime().asSeconds() >= 8.1f && false == true) {
                gravityFlipped = true;

                for(int i = 0; i < 6; i++) {
                    bgArrows[i].setTexture(bgRedArrow);
                }

                gameClock.restart();
                firstClockRun = false;
            }
        } else {
            if(gameClock.getElapsedTime().asSeconds() >= 3.98f && false == true) {
                if(gravityFlipped == false) {
                    gravityFlipped = true;
                    for(int i = 0; i < 6; i++) {
                        bgArrows[i].setTexture(bgRedArrow);
                    }
                } else {
                    gravityFlipped = false;
                    for(int i = 0; i < 6; i++) {
                        bgArrows[i].setTexture(bgBlueArrow);
                    }
                }
                gameClock.restart();
            }
        }

        if(musicLoopStarted == false && musicClock.getElapsedTime().asSeconds() >= 21.95f && false == true) {
            beepLoop.play();
            beepLoop.setLoop(true);
            musicLoopStarted = true;
        }

        frameCount += 1;
    }
    return 0;
}
