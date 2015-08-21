//
//  MenuScene.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/7/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__GameScene__
#define __SFML_Test_1__GameScene__

#include <stdio.h>
#include "Scene.h"

namespace sub {
    class GameScene : public sub::Scene
    {
    public:
		GameScene(bool persist, int level, int score);
        
		~GameScene();
        
        Scene* handleEvents(sf::Event event, sf::RenderTarget& target);
        void update(float delta, sf::RenderTarget& target);
        void render(float delta, sf::RenderTarget& target);
        bool init(sf::RenderTarget& target);
        bool exit();

		int level;
		int score;
    };
}

#endif
