//
//  Shot.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/9/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__Shot__
#define __SFML_Test_1__Shot__

#include <stdio.h>
#include "Entity.h"

namespace sub {
    class Shot : public sub::Entity {
    public:
        Shot();
        ~Shot();

        void update(float delta);
        
        bool load(const std::string& texture);
        
        void activate(sf::Vector2f pos, float angle, float speed);
        
        sf::Vector2f direction;
        float speed;
    };
}

#endif
