#pragma once

#include "Entity.h"

namespace sub {
	class Image : public sub::Entity
	{
	public:
		Image();
		~Image();

		void update(float delta);

		bool load(const std::string& texture);
	};
}

