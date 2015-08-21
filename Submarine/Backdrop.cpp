//
//  Backdrop.cpp
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/6/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#include "Backdrop.h"
#include <iostream>

sub::Backdrop::Backdrop()
{
    
}

sub::Backdrop::~Backdrop()
{
    
}

bool sub::Backdrop::load(const std::string& texture, float spd, float dir)
{
    count = 0.0f;
    canRun = false;
    speed = spd;
    direction = dir;
    
    if (!m_texture.loadFromFile(texture))
        return false;
    
	m_texture.setRepeated(true);

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);
    
    sf::Vector2u texSize = m_texture.getSize();
    
    m_vertices[0].position = sf::Vector2f(0, 0);
    m_vertices[1].position = sf::Vector2f(texSize.x, 0);
    m_vertices[2].position = sf::Vector2f(texSize.x, texSize.y);
    m_vertices[3].position = sf::Vector2f(0, texSize.y);
    
    m_vertices[0].texCoords = sf::Vector2f(0, 0);
    m_vertices[1].texCoords = sf::Vector2f(texSize.x, 0);
    m_vertices[2].texCoords = sf::Vector2f(texSize.x, texSize.y);
    m_vertices[3].texCoords = sf::Vector2f(0, texSize.y);
    
    canRun = true;
    return canRun;
}

void sub::Backdrop::update(float delta)
{
    if (!canRun)
        return;

	sf::Vector2u texSize = m_texture.getSize();
	float amount = speed * direction * delta;
	float tx = m_vertices[0].texCoords.x;

	if (tx >= texSize.x) {
		m_vertices[0].texCoords.x = 0;
		m_vertices[1].texCoords.x = texSize.x;
		m_vertices[2].texCoords.x = texSize.x;
		m_vertices[3].texCoords.x = 0;
	}
	else {
		m_vertices[0].texCoords.x += amount;
		m_vertices[1].texCoords.x += amount;
		m_vertices[2].texCoords.x += amount;
		m_vertices[3].texCoords.x += amount;
	}
}




