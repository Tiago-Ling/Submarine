//
//  GameScene.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/7/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__TitleScene__
#define __SFML_Test_1__TitleScene__

#include <stdio.h>
#include "Scene.h"

namespace sub {
    class TitleScene : public sub::Scene
    {
    public:
		TitleScene(bool persist) : Scene(persist) {
            this->persist = persist;
        }
        
		~TitleScene();
        
        Scene* handleEvents(sf::Event event, sf::RenderTarget& target);
        void update(float delta, sf::RenderTarget& target);
        void render(float delta, sf::RenderTarget& target);
        bool init(sf::RenderTarget& target);
        bool exit();
    };
}
#endif /* defined(__SFML_Test_1__GameScene__) */
