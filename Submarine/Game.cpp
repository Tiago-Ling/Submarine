//
//  Game.cpp
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/2/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#include "Game.h"

sf::Event event;

sub::Game::Game(sf::RenderWindow &aWindow, sf::RenderTexture &aTexture, sub::Scene &initialScene) : window(aWindow), r_texture(aTexture)
{
	currentScene = 0;
	scenes.push_back(&initialScene);

    init();
}

sub::Game::~Game()
{

}

bool sub::Game::init()
{
    std::cout << "Game.init()\n";
    
    // Set the Icon
    sf::Image icon;
	if (!icon.loadFromFile("icon.png")) {
        return false;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
//    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

	return true;
}

bool sub::Game::handleEvents(sf::Event event)
{
    while (window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::Closed) {
			scenes[currentScene]->exit();

            window.close();

			return false;
        }
        
		Scene* newScene = scenes[currentScene]->handleEvents(event, window);
        if (newScene != NULL)
        {
			if (!scenes[currentScene]->persist) {
				scenes[currentScene]->exit();

				if (currentScene > 0) {
					scenes.pop_back();
					currentScene--;
				}

				scenes[currentScene] = newScene;
			}
			else {
				currentScene++;
				scenes.push_back(newScene);
			}
            
			scenes[currentScene]->init(window);
        }
    }

	//TODO: Fix this mega-hack (only here because i'm return new states in event handling instead of on update :/)
	Scene* newScene = scenes[currentScene]->handleEvents(event, window);
	if (newScene != NULL)
	{
		if (!scenes[currentScene]->persist) {
			scenes[currentScene]->exit();

			if (currentScene > 0) {
				scenes.pop_back();
				currentScene--;
			}

			scenes[currentScene] = newScene;
		}
		else {
			currentScene++;
			scenes.push_back(newScene);
		}

		scenes[currentScene]->init(window);
	}

	return true;
}

void sub::Game::update(float delta)
{
	if (scenes[currentScene] != NULL) {
		scenes[currentScene]->update(delta, window);
	}
}

void sub::Game::render(float delta)
{
    // Clear screen
    window.clear(sf::Color(0xFF00FFFF));
    
	r_texture.clear(sf::Color(0x0F6751FF));
	scenes[currentScene]->render(delta, r_texture);
    r_texture.display();
    
    const sf::Texture& tex = r_texture.getTexture();
    
    sf::Sprite spr(tex);
    
    bool useShader = true;
	if (useShader && scenes[currentScene]->sceneShader != NULL) {
		sf::Shader *shader = scenes[currentScene]->sceneShader;
        window.draw(spr, shader);
    } else {
        window.draw(spr);
    }
    
    // Update the window
    window.display();
}


int sub::Game::execute()
{
    std::cout << "Game.execute()\n";
    //Fixed update time step + variable rendering
    sf::Clock clock;
    sf::Time time = clock.getElapsedTime();
    double previous = time.asMilliseconds();
    double lag = 0.0;
    
    //Initial scene initialization
	scenes[currentScene]->init(window);
    
    // Start the game loop
    while (window.isOpen())
    {
        //Fixed update time step + variable rendering
        sf::Time curTime = clock.getElapsedTime();
        double current = curTime.asMilliseconds();
        double elapsed = current - previous;
        previous = current;
        lag += elapsed;
        
        while (lag >= MS_PER_UPDATE) {
//            update(elapsed / 1000);
            lag -= MS_PER_UPDATE;
        }
        
        update(elapsed / 1000);
        
        render(lag / MS_PER_UPDATE);

		if (!handleEvents(event)) {
			std::cout << "Exiting application\n";
			scenes[currentScene]->exit();
			
			window.close();

			return 0;
		}

		if (scenes[currentScene]->destroy) {
			if (currentScene > 0) {
				std::cout << "Destroying current scene\n";
				scenes[currentScene]->exit();
				scenes.pop_back();
				currentScene--;
			}
			else {
				std::cout << "Exiting application\n";
				scenes[currentScene]->exit();

				window.close();

				return 0;
			}
		}
    }
    
    return 0;
}