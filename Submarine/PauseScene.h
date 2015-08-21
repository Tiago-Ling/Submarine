#ifndef __SFML_Test_1__PauseScene__
#define __SFML_Test_1__PauseScene__

#include <stdio.h>
#include "Scene.h"

namespace sub {
	class PauseScene : public sub::Scene
	{
	public:
		PauseScene(bool persist) : Scene(persist) {
			this->persist = persist;
		}
		~PauseScene();

		Scene* handleEvents(sf::Event event, sf::RenderTarget& target);
		void update(float delta, sf::RenderTarget& target);
		void render(float delta, sf::RenderTarget& target);
		bool init(sf::RenderTarget& target);
		bool exit();
	};
}
#endif

