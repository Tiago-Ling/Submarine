#include "Game.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "GameOverScene.h"

int main(int, char const**)
{
    sf::RenderWindow theWindow(sf::VideoMode(1024, 600), "Submarine");
    sf::RenderTexture theTexture;
    theTexture.create(1024, 600, false);

	sub::TitleScene theScene(false);
	sub::Game theGame(theWindow, theTexture, theScene);
    
	theGame.execute();
	
	return 0;
}
