#pragma once
#include "Scene.h"

namespace sub {
	class GameOverScene : public sub::Scene
	{
	public:
		GameOverScene(bool persist) : Scene(persist) {
			this->persist = persist;
		}
		~GameOverScene();

		Scene* handleEvents(sf::Event event, sf::RenderTarget& target);
		void update(float delta, sf::RenderTarget& target);
		void render(float delta, sf::RenderTarget& target);
		bool init(sf::RenderTarget& target);
		bool exit();
	};
}

