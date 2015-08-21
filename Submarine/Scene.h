//
//  Scene.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/3/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__Scene__
#define __SFML_Test_1__Scene__

#include <stdio.h>
#include <iostream>
#include <vector>
#include "Entity.h"

namespace sub {
   class Scene {
public:
    Scene(bool persist) {
        this->persist = persist;
    }
    
    ~Scene() {
        //Call the destructor on every member
        entities.clear();
        
        int size = entities.size();
        for (int i = 0; i < size; i++) {
            delete entities[i];
			entities[i] = NULL;
        }
        
		//delete sceneShader;
        //sceneShader = NULL;

        //Swaps objects to a temporary nameless empty vector and when it gets destroyed, deallocates memory for members
        std::vector<Entity *>().swap(entities);
    }
    
	virtual Scene* handleEvents(sf::Event event, sf::RenderTarget& target) { return NULL; }
    virtual void update(float delta, sf::RenderTarget& target) {}
    virtual void render(float delta, sf::RenderTarget& target) {}
	virtual bool init(sf::RenderTarget& target) { return true; }
	virtual bool exit() { return true; }
    
    void add(Entity& entity) {
        entities.push_back(&entity);
    }
    
    void setShader(sf::Shader& shader) {
        sceneShader = &shader;
    }

	sub::Entity* getFirstByCollisionType(int type) {
		int size = entities.size();
		for (int i = 0; i < size; i++) {
			if (entities[i]->collisionType == type)
				return entities[i];
		}

		return nullptr;
	}
       
    sf::Shader *sceneShader;
	bool persist;

	//Setting this to true destroys the scene at the end of the current frame
	bool destroy = false;
    
protected:
    std::vector<Entity *> entities;
    sf::View camera;
};
    
} //namespace sub

#endif /* defined(__SFML_Test_1__Scene__) */
