//
//  Fader.cpp
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/7/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#include <iostream>
#include "Fader.h"
#include "Util.h"

sub::Fader::Fader()
{
    current = 0.0f;
    total = 0.0f;
    radius = softness = opacity = 0.0f;
	startRadius = startSoftness = startOpacity = 0.0f;
	targetRadius = targetSoftness = targetOpacity = 0.0f;
    
    isCollisionEnabled = false;
	isFinished = false;
}

sub::Fader::~Fader()
{
    
}

void sub::Fader::update(float delta)
{
    if (current < total) {
        current += delta;
        
        float percent = current / total;
        
        //Vignette
		radius = sub::Util::lerp(startRadius, targetRadius, sub::Util::smoothstep(percent));
		softness = sub::Util::lerp(startSoftness, targetSoftness, sub::Util::smoothstep(percent));
		opacity = sub::Util::lerp(startOpacity, targetOpacity, sub::Util::smoothstep(percent));
        
        //Pixelate
//        opacity = sub::Util::lerp(0.001, 0.01, fraction);
        
        //Grain
//        float time = sub::Util::lerp(0.001, 1000, fraction);
//        shader.setParameter("uTime", time);
        
	}
	else {
		isFinished = true;
		active = false;
	}

    //Vignette
    shader.setParameter("radius", radius);
    shader.setParameter("softness", softness);
    shader.setParameter("opacity", opacity);
    
    //Pixelate
//    shader.setParameter("pixel_threshold", opacity);
    
    //Grain (continuous effect)
    //float time = sub::Util::randomRange(0, 1000);
    //shader.setParameter("uTime", time);
    
}

bool sub::Fader::load(const std::string& vignette, float duration, sub::FadeType t, sf::RenderTarget& target)
{
    total = duration;
    
//    current = 0.0;
//    total = duration;
//    radius = 0.0;
//    softness = 0.0;
//    opacity = 0.0;
    
    if (!m_texture.loadFromFile("cute_image.jpg"))
    {
        std::cout << "Error creating texture\n";
        return false;
    }
    
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(4);
    
    sf::Vector2u texSize = m_texture.getSize();
    if (texSize.x <= 0 || texSize.y <= 0) {
        return false;
    }
    
    m_vertices[0].position = sf::Vector2f(0, 0);
    m_vertices[1].position = sf::Vector2f(texSize.x, 0);
    m_vertices[2].position = sf::Vector2f(texSize.x, texSize.y);
    m_vertices[3].position = sf::Vector2f(0, texSize.y);
    
    m_vertices[0].texCoords = sf::Vector2f(0, 0);
    m_vertices[1].texCoords = sf::Vector2f(texSize.x, 0);
    m_vertices[2].texCoords = sf::Vector2f(texSize.x, texSize.y);
    m_vertices[3].texCoords = sf::Vector2f(0, texSize.y);
    
    if (!sf::Shader::isAvailable()) {
        std::cout << "Shader not available\n";
        return false;
    }
    
    if (!shader.loadFromFile(vignette, sf::Shader::Fragment)) {
        std::cout << "Could not load shader\n";
        return false;
    }

    //Pixelate Initial values
//    shader.setParameter("texture", sf::Shader::CurrentTexture);
//    shader.setParameter("pixel_threshold", 0.001);
    
    ////Vignette Initial values
    //radius = 0.75;
    //softness = 0.45;
    //opacity = 0.5;

	radius = 0.65;
	softness = 0.45;
	opacity = 0.55;
	sf::Vector2f resolution(1024.0, 600.0);

	shader.setParameter("resolution", resolution);
    shader.setParameter("uImage0", sf::Shader::CurrentTexture);
    shader.setParameter("radius", radius);
    shader.setParameter("softness", softness);
    shader.setParameter("opacity", opacity);
    
    //Grayscale
//    shader.setParameter("uImage0", sf::Shader::CurrentTexture);
//    shader.setParameter("color_r", 0.299);
//    shader.setParameter("color_g", 0.587);
//    shader.setParameter("color_b", 0.114);
    
    //Grain
    //shader.setParameter("uImage0", sf::Shader::CurrentTexture);
    //shader.setParameter("uResolution", sf::Vector2f(800, 600));
    //shader.setParameter("uTime", 0.0);
    
    //Blur
//    shader.setParameter("texture", sf::Shader::CurrentTexture);
//    shader.setParameter("blur_radius", 500 * 0.008f);

	//Bloom
	//shader.setParameter("texture", sf::Shader::CurrentTexture);

    return true;
}

void sub::Fader::adjustVignette(float radius, float softness, float opacity)
{
	sf::Vector2f resolution(1024.0, 600.0);
	shader.setParameter("resolution", resolution);
	shader.setParameter("uImage0", sf::Shader::CurrentTexture);
	shader.setParameter("radius", radius);
	shader.setParameter("softness", softness);
	shader.setParameter("opacity", opacity);
}

//TODO: Fix fader
void sub::Fader::fade(float time, int type, bool endLevel)
{
	current = 0.0;
	total = time;
	if (type == 1) {
		startRadius = 0.0f;	
		startSoftness = 0.0f;
		startOpacity = 1.0f;
		targetRadius = 0.65f;
		targetSoftness = 0.45f;
		targetOpacity = 0.55f;
	}
	else {
		targetRadius = 0.0f;
		targetSoftness = 0.0f;
		targetOpacity = 1.0f;
		startRadius = 0.65f;
		startSoftness = 0.45f;
		startOpacity = 0.55f;
	}

	adjustVignette(startRadius, startSoftness, startOpacity);
	active = true;

}