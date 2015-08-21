#include "GameOverScene.h"
#include "Image.h"
#include "TitleScene.h"
#include "Fader.h"

sf::Font goFont;
sf::Text goText;
sub::Image gameOver;
sub::Fader goFader;

bool sub::GameOverScene::init(sf::RenderTarget& target)
{
	std::cout << "TitleScene.init()\n";

	camera.reset(sf::FloatRect(0, 0, 1024, 600));
	target.setView(camera);

	if (!gameOver.load("game_over.png")) {
		std::cout << "Game Over loading failed!\n";
	}
	else {
		add(gameOver);
		gameOver.setPosition(512 - gameOver.getTexture().getSize().x / 2, 100);
	}

	if (!goFont.loadFromFile("sansation.ttf"))
	{
		std::cout << "Font loading failed!\n";
	}

	goText.setFont(goFont);
	
	int hiscore = sub::Util::loadScore();
	std::string str = "     Your Score : " + std::to_string(hiscore) + "\nPress SPACE to go to title";
	goText.setString(str);
	goText.setCharacterSize(24);
	goText.setColor(sf::Color::White);
	goText.setStyle(sf::Text::Bold);
	goText.setPosition(340, 400);

	if (!goFader.load("vignette.frag", 2.0, sub::FadeType::NONE, target))
	{
		std::cout << "Fader loading failed!\n";
	}
	else {
		//Shader problem: no adding, no updates :/
		goFader.active = false;
		add(goFader);
	}

	setShader(goFader.shader);
	goFader.fade(2, 1, false);

	return true;
}

sub::Scene* sub::GameOverScene::handleEvents(sf::Event event, sf::RenderTarget& target)
{
	if (event.type == sf::Event::KeyPressed) {
		switch (event.key.code) {
		case sf::Keyboard::Space:
			return new sub::TitleScene(false);
			break;
			break;
		default:
			break;
		}
	}

	return NULL;
}

void sub::GameOverScene::update(float delta, sf::RenderTarget& target)
{
	//TODO: Move this 
	int size = entities.size();
	for (int i = 0; i < size; i++)
	{
		entities[i]->update(delta);
	}
}

void sub::GameOverScene::render(float delta, sf::RenderTarget& target)
{
	int size = entities.size();
	for (int i = 0; i < size; i++)
	{
		target.draw(*entities[i]);
	}

	target.draw(goText);
}

bool sub::GameOverScene::exit()
{
	if (persist)
		return true;

	return false;
}

sub::GameOverScene::~GameOverScene()
{
}
