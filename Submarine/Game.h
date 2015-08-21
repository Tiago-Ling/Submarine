//
//  Game.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/2/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__Game__
#define __SFML_Test_1__Game__

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Scene.h"

namespace sub {
    
class Game
{
public:
    Game(sf::RenderWindow &aWindow, sf::RenderTexture &aTexture, sub::Scene &initialScene);
    ~Game();
    
    int execute();
    bool init();
    bool handleEvents(sf::Event event);
    void update(float delta);
    void render(float delta);
    
    void changeScene(sub::Scene newScene);
    
    //SFML Window
    sf::RenderTexture &r_texture;
    sf::RenderWindow &window;
    
private:
    
    //Approximation of 60 FPS in milisseconds ( 1 / 60 = 0.01666666666667 )
    const int MS_PER_UPDATE = 17;
    
    //sub::Scene* currentScene;

	int currentScene;
	std::vector<Scene *> scenes;
    
};
    
} //namespace game
#endif /* defined(__SFML_Test_1__Game__) */
