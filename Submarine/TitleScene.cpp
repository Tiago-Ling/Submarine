//
//  TitleScene.cpp
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/7/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#include "TitleScene.h"
#include "GameScene.h"
#include "Fader.h"
#include "Image.h"

//sub::Backdrop bg;
//Tilemap map;

sub::Image logo;

sf::Font titleFont;
sf::Text infoText;
sf::Text creditText;
sf::Text titleHiscore;

sub::Fader aFader;
float lerpTime;
float currentTime;

sf::SoundBuffer titleBuffer;
sf::Sound titleSelect;

sub::TitleScene::~TitleScene()
{

}

bool sub::TitleScene::init(sf::RenderTarget& target)
{
    std::cout << "TitleScene.init()\n";
    
    camera.reset(sf::FloatRect(0, 0, 1024, 600));
    target.setView(camera);

	if (!titleBuffer.loadFromFile("game_start.wav")) {
		std::cout << "select loading failed!\n";
	}
	else {
		titleSelect.setBuffer(titleBuffer);
	}
    
    //TODO: Return false if state initialization fails
	//bg = new sub::Backdrop();
    //if (!bg.load("fundo_ceu.jpg", 0.1f, 1))
    //{
    //    std::cout << "Backdrop texture loading failed!\n";
    //} else {
    //    add(bg);
    //}
    
////    define the level with an array of tile indices
//    const int level[] =
//    {
//        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
//        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
//        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
//        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
//        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
//        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
//        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//    };
//    
//    if (!map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 8))
//    {
//        std::cout << "Tilemap texture loading failed!\n";
//    } else {
//        add(map);
//    }

	if (!logo.load("logo.png")) {
		std::cout << "Logo loading failed!\n";
	}
	else {
		add(logo);
		logo.setPosition(512 - logo.getTexture().getSize().x / 2, 100);
	}

	if (!titleFont.loadFromFile("sansation.ttf")) {
		std::cout << "Font loading failed!\n";
	}

	infoText.setFont(titleFont);
	infoText.setString("Press SPACE to play");
	infoText.setCharacterSize(24);
	infoText.setColor(sf::Color::White);
	infoText.setStyle(sf::Text::Bold);
	infoText.setPosition(390, 600);
	lerpTime = 3.0;

	creditText.setFont(titleFont);
	creditText.setString("Code/GD: Tiago Ling Alexandre - Art: Paulo Frank - 2015 @ PucPR");
	creditText.setCharacterSize(20);
	creditText.setColor(sf::Color::White);
	creditText.setStyle(sf::Text::Bold);
	creditText.setPosition(185, 565);

	titleHiscore.setFont(titleFont);
	int hiscore = sub::Util::loadScore();
	std::string str = "Highscore : " + std::to_string(hiscore);
	titleHiscore.setString(str);
	titleHiscore.setCharacterSize(24);
	titleHiscore.setColor(sf::Color::White);
	titleHiscore.setStyle(sf::Text::Bold);
	titleHiscore.setPosition(410, 10);
	

	if (!aFader.load("vignette.frag", 2.0, sub::FadeType::NONE, target))
	{
		std::cout << "Fader loading failed!\n";
	}
	else {
		//Shader problem: no adding, no updates :/
		aFader.active = false;
		add(aFader);
	}

	setShader(aFader.shader);
	aFader.fade(2, 1, false);

	return true;
}

sub::Scene* sub::TitleScene::handleEvents(sf::Event event, sf::RenderTarget& target)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Space:
                //Put code to change states here.
                std::cout << "Changing from TitleScene to MenuScene\n";
				titleSelect.play();
                return new sub::GameScene(false, 1, 0);
                break;
            default:
                break;
        }
    }
    
    return NULL;
}

void sub::TitleScene::update(float delta, sf::RenderTarget& target)
{
	//TODO: Move this somewhere else (A Tween class?)

	currentTime += delta;
	if (currentTime > lerpTime) {
		currentTime = lerpTime;
	} else {
		float percent = currentTime / lerpTime;
		float newX = infoText.getPosition().x;
		float newY = sub::Util::lerp(600, 400, sub::Util::smoothstep(percent));
		infoText.setPosition(sf::Vector2f(newX, newY));
	}
    

    int size = entities.size();
    for (int i = 0; i < size; i++)
    {
		if (entities[i] && entities[i]->active)
			entities[i]->update(delta);
    }
}

void sub::TitleScene::render(float delta, sf::RenderTarget& target)
{
	int size = entities.size();
	for (int i = 0; i < size; i++)
	{
		target.draw(*entities[i]);
	}

	target.draw(infoText);
	target.draw(creditText);
	target.draw(titleHiscore);
}

bool sub::TitleScene::exit()
{
    std::cout << "TitleScene.exit()\n";
    if (persist)
        return true;

    return false;
}