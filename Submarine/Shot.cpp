//
//  Shot.cpp
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/9/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#include "Shot.h"
#include <iostream>

sub::Shot::Shot()
{
    active = false;
    collisionType = 666;
    isCollisionEnabled = false;
}

sub::Shot::~Shot()
{
    
}

bool sub::Shot::load(const std::string &texture)
{
    if (!m_texture.loadFromFile(texture))
        return false;
    
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
    
	//if (!sf::Shader::isAvailable()) {
	//	std::cout << "Shader not available\n";
	//	return false;
	//}

	//if (!m_shader.loadFromFile("grayscale.frag", sf::Shader::Fragment)) {
	//	std::cout << "Could not load shader\n";
	//	return false;
	//}
	//else {
	//	hasShader = true;
	//	m_shader.setParameter("color_r", 0.299);
	//	m_shader.setParameter("color_g", 0.587);
	//	m_shader.setParameter("color_b", 0.114);
	//}

    direction = sf::Vector2f(0.0, 0.0);
    speed = 300;
    
    return true;
}

void sub::Shot::update(float delta)
{
    sf::Vector2f pos = getPosition();
    setPosition(pos + direction);
    
    //Deactivate when off screen
    if (pos.x < -25 || pos.x > 1024 || pos.y < -4 || pos.y > 600)
        active = false;
}

void sub::Shot::activate(sf::Vector2f pos, float angle, float speed)
{
    float angInRad = sub::Util::toRadians(angle);
    direction = sub::Util::newBySizeAngle(speed, angInRad);
    
    //Sub offset
    sf::Vector2f offset(100, 30);
    
    setPosition(offset + pos + direction);
    
    active = true;
	isCollisionEnabled = true;
}


