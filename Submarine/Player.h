//
//  Player.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/9/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__Player__
#define __SFML_Test_1__Player__

#include <stdio.h>
#include <vector>
#include "Entity.h"
#include "Shot.h"

namespace sub {
    class Player : public Entity {
    public:
        Player();
        ~Player();
        
        void update(float delta);
        
        bool load(const std::string& texture);
        
        sf::Vector2f direction;
        float speed;
        
        std::vector<Shot *> shots;
        int totalShots;
        int currentShot;

		int health;

		sf::Sound shotSfx;
		sf::Sound dmgSfx;
        
    private:
        float shotCooldown;
    };
}

#endif /* defined(__SFML_Test_1__Player__) */
