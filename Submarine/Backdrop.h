//
//  Backdrop.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/6/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__Backdrop__
#define __SFML_Test_1__Backdrop__

#include <stdio.h>
#include "Entity.h"

namespace sub {
	class Backdrop : public sub::Entity
	{
	public:
		Backdrop();
		~Backdrop();

		void update(float delta);

		bool load(const std::string& texture, float spd, float dir);

		float speed;
		//Either 1 or -1
		int direction;

	private:
		bool canRun;
		float count;
	};
}

#endif /* defined(__SFML_Test_1__Backdrop__) */
