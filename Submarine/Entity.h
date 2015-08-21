//
//  Entity.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/6/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__Entity__
#define __SFML_Test_1__Entity__

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Updatable.h"
#include "Util.h"

namespace sub {
    class Entity : public sf::Drawable, public sf::Transformable, public sub::Updatable
    {
    public:
    
		virtual void update(float delta) {}
    
        virtual sf::VertexArray getVertices()
        {
            return m_vertices;
        }
    
        virtual sf::Texture getTexture()
        {
            return m_texture;
        }
    
        //Copied directly from sf::Sprite for simple collision detection
        virtual sf::FloatRect getLocalBounds() {
            sf::IntRect rect(0, 0, m_texture.getSize().x, m_texture.getSize().y);
            float width = static_cast<float>(std::abs(rect.width));
            float height = static_cast<float>(std::abs(rect.height));
        
            return sf::FloatRect(0.0f, 0.0f, width, height);
        }
    
        virtual sf::FloatRect getGlobalBounds() {
            return getTransform().transformRect(getLocalBounds());
        }

		virtual sf::Vector2f getCenter() {
			sf::Vector2f pos = getPosition();
			sf::Vector2u size = m_texture.getSize();
			pos.x += size.x / 2;
			pos.y += size.y / 2;

			return pos;
		}

		virtual bool collides(sub::Entity* entity)
		{
			sf::FloatRect rect = entity->getGlobalBounds();
			return getGlobalBounds().intersects(rect);
		}
        
        bool isCollisionEnabled = true;
        int collisionType = 0;
    
    protected:
    
        sf::VertexArray m_vertices;
        sf::Texture m_texture;

		sf::Shader m_shader;
		bool hasShader = false;
    
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            if (!active)
                return;
            
            states.transform *= getTransform();
        
            states.texture = &m_texture;

			if (hasShader)
			{
				states.shader = &m_shader;
			}
        
            target.draw(m_vertices, states);
        }
    };
}

#endif /* defined(__SFML_Test_1__MyEntity__) */
