//
//  Enemy.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/8/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__Enemy__
#define __SFML_Test_1__Enemy__

#include <stdio.h>
#include "Entity.h"
#include "Shot.h"

namespace sub {
    class Enemy : public sub::Entity
    {
    public:
        Enemy();
        ~Enemy();
        
		void update(float delta);
        
        bool load(const std::string& texture, sf::Vector2f spd, int w, int h, int fps);
		void activate(const sf::Vector2f& spd, const sf::Vector2f& amp, const sf::Vector2f& pos, const sf::Vector2f& dir, float angle, float fps);
        
        float ticks;
        float offset;

		sub::Shot bullet;
		float bulletTime;
        
        sf::Vector2f speed;
        sf::Vector2f amplitude;
		sf::Vector2f direction;

        int frame_width;
        int frame_height;
        
        float frame_time;
        float current_time;
        
        int current_frame;
        int total_frames;
        
        int cols; //width in tiles
        int rows; //height in tiles

		int health;
		sf::Uint8 vColor;

		sf::Vector2f& playerPosition;

		sf::Sound shotSfx;
		sf::Sound dmgSfx;
    };
}

#endif /* defined(__SFML_Test_1__Enemy__) */
