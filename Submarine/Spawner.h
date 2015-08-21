#pragma once

#include "SFML\Graphics.hpp"
#include "Enemy.h"

namespace sub {
	class Spawner
	{
	public:
		Spawner();
		~Spawner();

		void init(int level);
		void update(float delta);
		void spawn();

		int currentWave;
		int totalWaves;

		bool isLevelFinished;

		//int* wave_times[5] = {3, 3, 3};
		//int** waves;

		//std::vector<int> wave_delay_times;
		//int wave_delay_times[5] = {5, 5, 4, 4, 3};

		std::vector<std::string> data;

		std::vector<sub::Enemy *> enemies;

		bool active;
	private:

		//Used when spawning
		std::vector<int> slots;
		
		int waveEnemiesSpawned;
		int enemiesToSpawn;

		float spawnInterval;
		float spawnIntervalCounter;

		float delayToNextWave;
		float delayCounter;

		bool isWaveInCourse;
	};
}

