#include "Spawner.h"

#include <iostream>
#include <fstream>
#include <string>

const int NUM_ENEMIES = 100;
const int NUM_SLOTS = 6;

sub::Spawner::Spawner()
{

}

void sub::Spawner::init(int level)
{
	//enemiesToSpawn = NUM_ENEMIES;
	//spawnInterval = 1.5;
	//spawnIntervalCounter = 0.0;

	//wave_delay_times = {5, 5, 4, 4, 4, 4, 3, 3,};

	isLevelFinished = false;

	std::string filename = "level_" + std::to_string(level) + ".txt";
	std::cout << "Loading data file : " << filename << std::endl;
	std::ifstream file(filename);
	std::string str;
	while (std::getline(file, str))
	{
		data.push_back(str);
	}

	for (int i = 0; i < NUM_SLOTS; i++)
	{
		slots.push_back(0);
	}

	currentWave = 0;
	totalWaves = static_cast<int>(data.size());

	spawnIntervalCounter = 0.0;
	delayCounter = 0.0;
	isWaveInCourse = false;
	active = true;
}


sub::Spawner::~Spawner()
{

}

void sub::Spawner::spawn()
{
	if (currentWave > totalWaves - 1) {
		std::cout << "All waves finished, deactivating spawner!" << std::endl;
		active = false;
		isLevelFinished = true;
		return;
	}

	std::cout << "Starting wave" << currentWave << "!" << std::endl;
	std::string str = data[currentWave];
	std::string delimiter = ",";

	size_t pos = 0;
	std::string token;

	int count = 0;
	while ((pos = str.find(delimiter)) != std::string::npos) {

		token = str.substr(0, pos);

		//Slots variables
		std::string sDelimiter = "-";
		size_t sPos = 0;
		std::string subToken;
		int sCounter = 0;

		switch (count) {
		case 0: //Number of enemies per wave (note: this will be multiplied by the slots)
			enemiesToSpawn = atoi(token.c_str());
			std::cout << "Enemies to Spawn  : " << enemiesToSpawn << std::endl;
			break;
		case 1: //Rate of spawning, or how much time between each enemy
			spawnInterval = atof(token.c_str());
			std::cout << "Spawn Interval : " << spawnInterval << std::endl;
			break;
		case 2: //Slots representing each position to spawn (0 = no enemy; 1 = squid; 2 = other enemy
			std::cout << "Slot types : " << token << std::endl;
			//slots.resize(6);
			while ((sPos = token.find(sDelimiter)) != std::string::npos) {
				subToken = token.substr(0, sPos);
				slots[sCounter] = atoi(subToken.c_str());
				//std::cout << "Slot  : " << slots[sCounter] << std::endl;
				token.erase(0, sPos + sDelimiter.length());

				sCounter++;
			}
			break;
		case 3: //Delay time to next wave
			delayCounter = 0.0;
			delayToNextWave = atof(token.c_str());
			std::cout << "Delay Until Next Wave : " << delayToNextWave << std::endl;
			break;
		default:
			break;
		}

		str.erase(0, pos + delimiter.length());

		count++;
	}

	isWaveInCourse = true;
}

void sub::Spawner::update(float delta)
{
	if (!active)
		return;

	if (!isWaveInCourse) {
		if (delayCounter < delayToNextWave) {
			delayCounter += delta;
			return;
		}
		else {
			delayCounter = 0;
			spawn();
			return;
		}
	}

	if (enemiesToSpawn > 0) {
		if (spawnIntervalCounter < spawnInterval) {
			spawnIntervalCounter += delta;
			return;
		}
		else {
			//Spawn one enemy for each slot
			for (int i = 0; i < NUM_SLOTS; i++) {

				//slots[i] = 0 -> no enemy;
				if (slots[i] > 0) {
					for (int j = 0; j < NUM_ENEMIES; j++) {
						if (enemies[j]->active == false) {
							std::cout << "Spawning enemy at " << j << "\n";
							//speedY = 0, good for squid movement
							//speedX = 0, good for smooth sine wave

							sf::Vector2f enemySize = static_cast<sf::Vector2f>(enemies[j]->getTexture().getSize());
							sf::Vector2f position, spd, amp, dir;
							float angle = 0;
							switch (i) {
							case 0: //Vertical bottom
								position = sf::Vector2f(30, -enemySize.y);
								spd = sf::Vector2f(0, 2);
								amp = sf::Vector2f(0, 3);
								dir = sf::Vector2f(0, 1);
								angle = 270;
								break;
							case 1: //Vertical bottom
								position = sf::Vector2f(826 - enemySize.x / 2, -enemySize.y);
								spd = sf::Vector2f(0, 2);
								amp = sf::Vector2f(0, 3);
								dir = sf::Vector2f(0, 1);
								angle = 270;
								break;
							case 2: //Horizontal Left
								position = sf::Vector2f(1024, 150);
								spd = sf::Vector2f(0, 2);
								amp = sf::Vector2f(2, 2);
								dir = sf::Vector2f(-1, 0);
								angle = 0;
								break;
							case 3: //Horizontal left
								position = sf::Vector2f(1024, 480);
								spd = sf::Vector2f(2, 1);
								amp = sf::Vector2f(4, 1);
								dir = sf::Vector2f(-1, 0);
								angle = 0;
								break;
							case 4: //Vertical Top
								position = sf::Vector2f(826, 600);
								spd = sf::Vector2f(0, 2);
								amp = sf::Vector2f(0, 3);
								dir = sf::Vector2f(0, -1);
								angle = 90;
								break;
							case 5: //Vertical Top
								position = sf::Vector2f(198, 600);
								spd = sf::Vector2f(0, 2);
								amp = sf::Vector2f(0, 3);
								dir = sf::Vector2f(0, -1);
								angle = 90;
								break;
							default:
								break;
							}

							enemies[j]->activate(spd, amp, position, dir, angle, 4);

							spawnIntervalCounter = 0.0;
							enemiesToSpawn--;

							break;
						}
					}
				}
			}
		}
	}
	else {
		//Check if there is a next wave
		if (currentWave < totalWaves - 1)
			currentWave++;
		else
			active = false;

		isWaveInCourse = false;
	}
}