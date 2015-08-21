//
//  Updatable.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/9/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__Updatable__
#define __SFML_Test_1__Updatable__

#include <stdio.h>

class Scene;

namespace sub {
    class Updatable {
    public:
        virtual void update(float delta, const Scene* scene) {}
        
        bool active = true;
    };
}

#endif /* defined(__SFML_Test_1__Updatable__) */
