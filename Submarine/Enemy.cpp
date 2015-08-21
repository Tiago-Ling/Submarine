//
//  Enemy.cpp
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/8/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "Enemy.h"
#include "Util.h"

//TODO: Remove animation from this class

sub::Enemy::Enemy() : playerPosition(sf::Vector2f(512, 300))
{
    collisionType = 777;
	bulletTime = 4.0;

	active = false;
	isCollisionEnabled = false;

	health = 3;
	vColor = 255;
}

sub::Enemy::~Enemy()
{
    
}

bool sub::Enemy::load(const std::string& texture, sf::Vector2f spd, int w, int h, int fps)
{
    speed = spd;
    
    frame_width = w;
    frame_height = h;
    frame_time = 1 / fps;
    current_time = frame_time;
    
    active = false;
    
    if (!m_texture.loadFromFile(texture)) {
        std::cout << "Error loading enemy texture\n";
        return false;
    }
    
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);
    
    sf::Vector2u texSize = m_texture.getSize();
    
    cols = static_cast<int>(texSize.x / frame_width);
    rows = static_cast<int>(texSize.y / frame_height);
    total_frames = cols * rows;
    current_frame = 0;
    
    m_vertices[0].position = sf::Vector2f(0, 0);
    m_vertices[1].position = sf::Vector2f(frame_width, 0);
    m_vertices[2].position = sf::Vector2f(frame_width, frame_height);
    m_vertices[3].position = sf::Vector2f(0, frame_height);
    
    m_vertices[0].texCoords = sf::Vector2f(0, 0);
    m_vertices[1].texCoords = sf::Vector2f(frame_width, 0);
    m_vertices[2].texCoords = sf::Vector2f(frame_width, frame_height);
    m_vertices[3].texCoords = sf::Vector2f(0, frame_height);
    
    float aX = sub::Util::randomRange(64, 256);
    float aY = sub::Util::randomRange(64, 256);
    amplitude = sf::Vector2f(aX, aY);

	direction = sf::Vector2f(0, 0);

	if (!bullet.load("en_shot.png")) {
		std::cout << "Error loading enemy bullet texture\n";
	}
    
    return true;
}

//Too many parameters
void sub::Enemy::activate(const sf::Vector2f& spd, const sf::Vector2f& amp, const sf::Vector2f& pos, const sf::Vector2f& dir, float angle, float fps)
{
    speed = spd;
    amplitude = amp;
	//direction = sf::Vector2f(dir.x, dir.y);
	direction = dir;

    frame_time = 1 / fps;
    current_time = frame_time;
    
	setRotation(angle);

	setPosition(pos);
    
    active = true;
	isCollisionEnabled = true;
	vColor = 255;
	health = 3;
}

void sub::Enemy::update(float delta)
{
    sf::Vector2f pos = getPosition();
	//Destoy if outside the screen
    if ((pos.x <= -frame_width && direction.x == -1) || (pos.x >= 1024 && direction.x == 1) || (pos.y <= -frame_height && direction.y == -1) || (pos.y >= 600 && direction.y == 1)) {
        pos.x = 1024;
        pos.y = -frame_height;
        ticks = 0;
        
        active = false;
		isCollisionEnabled = false;
    } else {
        ticks += delta;
        
		//Alternate fabsf for x and y to create interesting variations
        float x = fabsf(amplitude.x * cos(speed.x * ticks));
        float y = amplitude.y * sin(speed.y * ticks);
        
        pos -= sf::Vector2f(x, y) + direction;
    }
    
    setPosition(pos);
    
    //Updating animation
    if (current_time > 0)
    {
        current_time -= delta;
    } else {
        
        int i = static_cast<int>(current_frame / cols);
        int j = static_cast<int>(current_frame % cols);
        
        m_vertices[0].texCoords = sf::Vector2f(j * frame_width, i * frame_height);
        m_vertices[1].texCoords = sf::Vector2f(j * frame_width + frame_width, i * frame_height);
        m_vertices[2].texCoords = sf::Vector2f(j * frame_width + frame_width, i * frame_height + frame_height);
        m_vertices[3].texCoords = sf::Vector2f(j * frame_width, i * frame_height + frame_height);
        
		m_vertices[0].color = sf::Color(vColor, vColor, vColor);
		m_vertices[1].color = sf::Color(vColor, vColor, vColor);
		m_vertices[2].color = sf::Color(vColor, vColor, vColor);
		m_vertices[3].color = sf::Color(vColor, vColor, vColor);

        if (current_frame == total_frames - 1)
            current_frame = 0;
        else
            current_frame++;
        
        current_time = frame_time;
    }

	if (bulletTime > 0) {
		bulletTime -= delta;
	} 
	else {
		bulletTime = 5.0f;
		float bulletSpeed = 4.0f;
		//Shoot bullet at the player (substitute screen center for player position)
		sf::Vector2f bulletPath = playerPosition - getPosition();

		bullet.direction = sub::Util::normalize(bulletPath);
		bullet.direction *= bulletSpeed;

		sf::Vector2f bPos = getPosition() + bullet.direction;
		bullet.setPosition(bPos);
		bullet.collisionType = 999;
		bullet.active = true;
		bullet.isCollisionEnabled = true;

		shotSfx.play();
	}

	//Testing look at
	//float angle = getRotation() - sub::Util::lookAt(getPosition(), sf::Vector2f(0.0f, 0.0f));
	//setRotation(angle);
}