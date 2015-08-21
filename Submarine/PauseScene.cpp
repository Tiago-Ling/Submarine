#include "PauseScene.h"
#include "GameScene.h"
#include "Fader.h"

sf::Font pauseFont;
sf::Text pauseText;

bool sub::PauseScene::init(sf::RenderTarget& target)
{
	std::cout << "TitleScene.init()\n";

	camera.reset(sf::FloatRect(0, 0, 1024, 600));
	target.setView(camera);

	if (!pauseFont.loadFromFile("sansation.ttf"))
	{
		std::cout << "Font loading failed!\n";
	}

	pauseText.setFont(pauseFont);
	pauseText.setString("Pause!");
	pauseText.setCharacterSize(24);
	pauseText.setColor(sf::Color::White);
	pauseText.setStyle(sf::Text::Bold || sf::Text::Underlined);

	pauseText.setPosition(480, 280);

	return true;
}

sub::Scene* sub::PauseScene::handleEvents(sf::Event event, sf::RenderTarget& target)
{
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Escape:
			//Put code to change states here.
			std::cout << "Changing from PauseScene to GameScene\n";
			destroy = true;
			break;
		default:
			break;
		}
	}

	return NULL;
}

void sub::PauseScene::update(float delta, sf::RenderTarget& target)
{
	//TODO: Move this 
	int size = entities.size();
	for (int i = 0; i < size; i++)
	{
		entities[i]->update(delta);
	}
}

void sub::PauseScene::render(float delta, sf::RenderTarget& target)
{
	int size = entities.size();
	for (int i = 0; i < size; i++)
	{
		target.draw(*entities[i]);
	}

	target.draw(pauseText);
}

bool sub::PauseScene::exit()
{
	std::cout << "PauseScene.exit()\n";
	if (persist)
		return true;

	return false;
}

sub::PauseScene::~PauseScene()
{
}
