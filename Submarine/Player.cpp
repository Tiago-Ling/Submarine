//
//  Player.cpp
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/9/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "Player.h"
#include "Util.h"



sub::Player::Player()
{
    collisionType = 111;
    currentShot = 0;
    totalShots = 50;
    shotCooldown = 0.2;
	health = 100;
}

sub::Player::~Player()
{
    
}

bool sub::Player::load(const std::string &texture)
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
    
	//Testing per-entity shader

	//if (!sf::Shader::isAvailable()) {
	//	std::cout << "Shader not available\n";
	//	return false;
	//}

	//if (!m_shader.loadFromFile("bloom.frag", sf::Shader::Fragment)) {
	//	std::cout << "Could not load shader\n";
	//	return false;
	//}
	//else {
	//	hasShader = true;
	//	//Bloom
	//	m_shader.setParameter("texture", sf::Shader::CurrentTexture);

	//	//Grayscale
	//	//m_shader.setParameter("uImage0", sf::Shader::CurrentTexture);
	//	//m_shader.setParameter("color_r", 0.299);
	//	//m_shader.setParameter("color_g", 0.587);
	//	//m_shader.setParameter("color_b", 0.114);
	//}

	setPosition(0, 300 - texSize.y / 2);

    direction = sf::Vector2f(0.0, 0.0);
    speed = 300;
    
    return true;
}

void sub::Player::update(float delta)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        sf::Vector2f pos = getPosition();
		if (pos.y > 0) {
			float angInRad = sub::Util::toRadians(90);
			direction = sub::Util::newBySizeAngle(5, angInRad);

			setPosition(pos - direction);
		}
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        sf::Vector2f pos = getPosition();
		if (pos.y < 600 - m_texture.getSize().y) {
			float angInRad = sub::Util::toRadians(-90);
			direction = sub::Util::newBySizeAngle(5, angInRad);

			setPosition(pos - direction);
		}
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sf::Vector2f pos = getPosition();
		if (pos.x > 0) {
			float angInRad = sub::Util::toRadians(0);
			direction = sub::Util::newBySizeAngle(5, angInRad);

			setPosition(pos - direction);
		}
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sf::Vector2f pos = getPosition();
		if (pos.x < 1024 - m_texture.getSize().x) {
			float angInRad = sub::Util::toRadians(180);
			direction = sub::Util::newBySizeAngle(5, angInRad);

			setPosition(pos - direction);
		}
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shotCooldown == 0) {
        if (currentShot == totalShots - 1)
            currentShot = 0;
        if (!shots[currentShot]->active) {
            sf::Vector2f pos = getPosition();
            shots[currentShot]->activate(pos, 0, 15);
            currentShot++;
            shotCooldown = 0.2;
			shotSfx.play();
        }
    }

	//Preventing player from exiting the screen
	//sf::Vector2f pos = getPosition();
	//if (pos.x < 0) pos.x = 0;
	//if (pos.x > 1024 - m_texture.getSize().x) pos.x = 1024 - m_texture.getSize().x;
	//if (pos.y < 0) pos.x = 0;
	//if (pos.y > 600 - m_texture.getSize().y) pos.y = 1024 - m_texture.getSize().y;

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
	//	//Testing look at
	//	float angle = getRotation() + sub::Util::lookAt(getPosition(), sf::Vector2f(512, 300));
	//	setRotation(angle);
	//}
    
    if (shotCooldown <= 0)
        shotCooldown = 0;
    else
        shotCooldown -= delta;
}


