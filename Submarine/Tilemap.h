//
//  MyEntity.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/2/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__Tilemap__
#define __SFML_Test_1__Tilemap__

#include <stdio.h>
#include "Entity.h"

class Tilemap : public sub::Entity
{
public:
    Tilemap();
    ~Tilemap();
    
    void update(float delta);
    
    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);
};

#endif /* defined(__SFML_Test_1__MyEntity__) */
