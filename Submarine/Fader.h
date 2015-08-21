//
//  Fader.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/7/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__Fader__
#define __SFML_Test_1__Fader__

#include <stdio.h>
#include "Entity.h"

namespace sub {
    
    enum FadeType { FADE_IN, FADE_OUT, NONE };
    
    class Fader : public sub::Entity
    {
    public:
        Fader();
        ~Fader();
        
        void update(float delta);
        
        bool load(const std::string& vignette, float duration, sub::FadeType t, sf::RenderTarget& target);

		void adjustVignette(float radius, float softness, float opacity);
		//type : 0 = fade out; 1 = fade in
		void fade(float time, int type, bool endLevel);
        
        sf::Shader shader;

		bool isFinished;
        
    private:
        FadeType type;
        float total;
        float current;
        
        float radius;
        float softness;
        float opacity;

		float startRadius, startSoftness, startOpacity;
		float targetRadius, targetSoftness, targetOpacity;

        
    protected:
//        void draw(sf::RenderTarget& target, sf::RenderStates states);
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
//            states.transform *= getTransform();
            
//            states.texture = &m_texture;
            
//            states.shader = &shader;
            
//            target.draw(m_vertices, states);
        }
        
    };
}

#endif /* defined(__SFML_Test_1__Fader__) */
