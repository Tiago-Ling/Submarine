//
//  GameScene.cpp
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/7/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#include <cmath>
#include "GameScene.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "Tilemap.h"
#include "Fader.h"
#include "Enemy.h"
#include "Util.h"
#include "Player.h"
#include "Backdrop.h"
#include "Spawner.h"

const int NUM_ENEMIES = 50;
const int NUM_LEVELS = 2;

sub::Fader fader;
sub::Enemy enemies[NUM_ENEMIES];
sub::Shot shots[50];
sub::Player player;
sub::Backdrop bgs[3];
sf::Font font;
sf::Text healthLabel;
sf::Text scoreLabel;
std::string wavesLeft;
sf::Text waveLabel;
sub::Spawner spawner;

sf::Music music;
sf::SoundBuffer pShotBuffer;
sf::SoundBuffer eShotBuffer;
sf::SoundBuffer eDmgBuffer;
sf::SoundBuffer pDmgBuffer;
sf::SoundBuffer pDeathBuffer;
sf::SoundBuffer eDeathBuffer;

sf::Sound pDeath;
sf::Sound eDeath;

float radius;
bool isGameOver;

sf::Event ev;

sub::GameScene::GameScene(bool persist, int level, int score) : Scene(persist) {
	this->persist = persist;
	this->level = level;
	this->score = score;
	spawner.init(level);
}

sub::GameScene::~GameScene()
{

}

bool sub::GameScene::init(sf::RenderTarget& target)
{
    std::cout << "GameScene.init()\n";

	radius = 0.75;
	isGameOver = false;
    
    camera.reset(sf::FloatRect(0, 0, 1024, 600));
    target.setView(camera);

	//Audio
	if (!pShotBuffer.loadFromFile("p_shot.wav")) {
		std::cout << "p_shot loading failed!\n";
	}

	if (!eShotBuffer.loadFromFile("e_shot.wav")) {
		std::cout << "e_shot loading failed!\n";
	}

	if (!eDmgBuffer.loadFromFile("e_dmg.wav")) {
		std::cout << "e_dmg loading failed!\n";
	}

	if (!pDmgBuffer.loadFromFile("p_dmg.wav")) {
		std::cout << "p_dmg loading failed!\n";
	}

	if (!pDeathBuffer.loadFromFile("p_death.wav")) {
		std::cout << "p_death loading failed!\n";
	}
	else {
		pDeath.setBuffer(eDeathBuffer);
	}

	if (!eDeathBuffer.loadFromFile("e_death.wav")) {
		std::cout << "e_death loading failed!\n";
	}
	else {
		eDeath.setBuffer(eDeathBuffer);
	}

	if (!music.openFromFile("under_the_veil.ogg")) {
		std::cout << "Music loading failed!\n";
	}
	music.play();
	//End

	if (!font.loadFromFile("sansation.ttf"))
	{
		// error...
		std::cout << "Font loading failed!\n";
	}

	//Player health
	healthLabel.setFont(font); // font is a sf::Font
	std::string str = "Health : " + std::to_string(player.health);
	healthLabel.setString(str);
	healthLabel.setCharacterSize(20); // in pixels, not points!
	healthLabel.setColor(sf::Color::White);
	healthLabel.setStyle(sf::Text::Bold);
	healthLabel.setPosition(10, 10);

	//Player score
	scoreLabel.setFont(font); // font is a sf::Font
	str = "Score : " + std::to_string(score);
	scoreLabel.setString(str);
	scoreLabel.setCharacterSize(20); // in pixels, not points!
	scoreLabel.setColor(sf::Color::White);
	scoreLabel.setStyle(sf::Text::Bold);
	scoreLabel.setPosition(850, 10);
	
	waveLabel.setFont(font); // font is a sf::Font
	wavesLeft = " Level : " + std::to_string(this->level) + "\nWaves : " + std::to_string(spawner.totalWaves - spawner.currentWave);
	waveLabel.setString(wavesLeft);
	waveLabel.setCharacterSize(20); // in pixels, not points!
	waveLabel.setColor(sf::Color::White);
	waveLabel.setStyle(sf::Text::Bold);
	waveLabel.setPosition(450, 10);

	//BGs
	if (!bgs[0].load("bg_0_2.png", 0.0, 1))
	{
		std::cout << "Backdrop texture loading failed!\n";
	}
	else {
		add(bgs[0]);
	}

	//"Speed" -> from 0.0 to 1.0. The lower the value, the faster it goes
	if (!bgs[1].load("bg_1_1.png", 40.0, 1))
	{
		std::cout << "Backdrop texture loading failed!\n";
	}
	else {
		bgs[1].setPosition(0.0, 600.0 - bgs[1].getTexture().getSize().y);
		add(bgs[1]);
	}

	if (!bgs[2].load("bg_2_1.png", 120.0, 1))
	{
		std::cout << "Backdrop texture loading failed!\n";
	}
	else {
		bgs[2].setPosition(0.0, 600.0 - bgs[2].getTexture().getSize().y);
		add(bgs[2]);
	}
    
    if (!fader.load("vignette.frag", 2.0, sub::FadeType::NONE, target))
    {
        std::cout << "Fader loading failed!\n";
    } else {
		fader.active = false;
        add(fader);
    }
    
    setShader(fader.shader);
    
    if (!player.load("sub_red_v2.png"))
    {
        std::cout << "Player loading failed!\n";
    } else {
		player.shotSfx.setBuffer(pShotBuffer);
		player.dmgSfx.setBuffer(pDmgBuffer);
        add(player);
        
        int size = player.totalShots;
        for (int i = 0; i < size; i++) {
            if (shots[i].load("shot.png")) {
                add(shots[i]);
                player.shots.push_back(&shots[i]);
            }
        }
    }

	int size = NUM_ENEMIES;
	for (int i = 0; i < size; i++) {
		if (enemies[i].load("squid.png", sf::Vector2f(75.0, 75.0), 125, 41, 12)) {
			enemies[i].shotSfx.setBuffer(eShotBuffer);
			enemies[i].dmgSfx.setBuffer(eDmgBuffer);
			add(enemies[i]);
			add(enemies[i].bullet);
			spawner.enemies.push_back(&enemies[i]);
		}
	}

	return true;
}

sub::Scene* sub::GameScene::handleEvents(sf::Event event, sf::RenderTarget& target)
{
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
    //        case sf::Keyboard::Escape:
    //            std::cout << "Exiting application";
				//this->destroy = true;
    //            break;
            //case sf::Keyboard::U:
            //    //Put code to change states here.
            //    std::cout << "Changing from GameScene to GameScene\n";
            //    return new sub::TitleScene(false);
            //    break;
            default:
                break;
        }
    }

	//Move this to another place (all scene handling should be re-designed!)
	if (spawner.isLevelFinished) {
		if (level < NUM_LEVELS) {
			level++;
			std::cout << "Moving to level " << level << "!\n";
			return new sub::GameScene(false, level, score);
		}
		else {
			std::cout << "Final level finished!\n";
			return new sub::GameOverScene(false);
		}
	}

	if (isGameOver && fader.isFinished) {
		std::cout << "Game over!\n";
		int hiscore = sub::Util::loadScore();
		if (score > hiscore) {
			sub::Util::saveScore(score);
		}

		return new sub::GameOverScene(false);
	}
    
    return NULL;
}

void sub::GameScene::update(float delta, sf::RenderTarget& target)
{   
	//Updating entities
    int size = entities.size();
    for (int i = 0; i < size; i++)
    {
		//Rudimentary collision (TODO: complete refactor)
		if (entities[i]->active) {
			entities[i]->update(delta);

			if (entities[i]->isCollisionEnabled) {
				for (int j = 0; j < size; j++) {
					if (i == j || entities[i]->collisionType == entities[j]->collisionType)
						continue;

					if (entities[j]->active && entities[j]->isCollisionEnabled) {
						if (entities[i]->collides(entities[j])) {

							//Player x Enemy
							if (entities[i]->collisionType == 111 && entities[j]->collisionType == 777) {
								std::cout << "Player collided at " << i << "!\n";

								//Kill the enemy
								entities[j]->active = false;
								entities[j]->isCollisionEnabled = false;
								entities[j]->setPosition(-500, -500);

								//Play enemy death
								eDeath.play();

								//Update player health
								player.health -= 10;
								std::string str = "Health : " + std::to_string(player.health);
								healthLabel.setString(str);

								if (player.health > 0) {
									player.dmgSfx.play();
								}
								else {
									std::cout << "Player is dead...\n";
									int hiscore = sub::Util::loadScore();
									if (score > hiscore) {
										sub::Util::saveScore(score);
									}
									player.active = false;

									isGameOver = true;
									fader.fade(2.0, 0, false);
									
									pDeath.play();
								}

								break;
							}

							//Player x Enemy Shot
							if (entities[i]->collisionType == 111 && entities[j]->collisionType == 999) {
								
								//Kill the bullet
								entities[j]->active = false;
								entities[j]->isCollisionEnabled = false;
								entities[j]->setPosition(-100, -100);

								//Update player health
								player.health -= 10;
								std::string str = "Health : " + std::to_string(player.health);
								healthLabel.setString(str);

								if (player.health > 0) {
									player.dmgSfx.play();
								}
								else {
									std::cout << "Player is dead...\n";
									int hiscore = sub::Util::loadScore();
									if (score > hiscore) {
										sub::Util::saveScore(score);
									}
									player.active = false;
									isGameOver = true;
									fader.fade(2.0, 0, false);

									pDeath.play();
								}

								break;
							}

							//Player Shot x Enemy
							if (entities[i]->collisionType == 666 && entities[j]->collisionType == 777) {
								//Kill the shot
								entities[i]->active = false;
								entities[i]->isCollisionEnabled = false;
								entities[i]->setPosition(-100, -100);

								//Kill the enemy
								sub::Enemy* enemy = static_cast<sub::Enemy*>(entities[j]);
								enemy->vColor -= 85;
								enemy->health--;
								if (enemy->health <= 0) {
									std::cout << "Enemy destroyed!\n";
									entities[j]->active = false;
									entities[j]->isCollisionEnabled = false;
									entities[j]->setPosition(-500, -500);

									//Play enemy death
									eDeath.play();

									//Update score
									score += 50;
									std::string str = "Score : " + std::to_string(score);
									scoreLabel.setString(str);
								}
								else {
									enemy->dmgSfx.play();

									//Update score
									score += 5;
									std::string str = "Score : " + std::to_string(score);
									scoreLabel.setString(str);
								}

								break;
							}
						}
					}
				}
			}
		}
    }
    
	spawner.update(delta);

	sf::Vector2f pPos = player.getCenter();
	for (int i = 0; i < 50; i++) {
		if (enemies[i].active) {
			enemies[i].playerPosition = pPos;
		}
	}

	wavesLeft = " Level : " + std::to_string(this->level) + "\nWaves : " + std::to_string(spawner.totalWaves - spawner.currentWave);
	waveLabel.setString(wavesLeft);

	if (spawner.isLevelFinished) {
		//TODO: Fix this hack!!!
		handleEvents(ev, target);
	}

	if (fader.isFinished) {
		//TODO: Fix this hack!!!
		handleEvents(ev, target);
	}
}

void sub::GameScene::render(float delta, sf::RenderTarget& target)
{
    int size = entities.size();
    for (int i = 0; i < size; i++)
    {
        target.draw(*entities[i]);
    }

	target.draw(healthLabel);
	target.draw(scoreLabel);
	target.draw(waveLabel);
}

bool sub::GameScene::exit()
{
    std::cout << "GameScene.exit()\n";

	music.stop();

    if (persist)
        return true;
    
    return false;
}
