//
//  Util.h
//  SFML_Test_1
//
//  Created by Tiago Ling Alexandre on 7/8/15.
//  Copyright (c) 2015 Coffee Games. All rights reserved.
//

#ifndef __SFML_Test_1__Util__
#define __SFML_Test_1__Util__

#include <stdio.h>
#include <cmath>
#include <fstream>
#include <SFML/Graphics.hpp>

namespace sub {
    
    static const double PI = 3.14159265358979323846;
    static const double ONE_DEGREE = 180.0 / PI;
    
    class Util
    {
    public:
		//Very simple random range for integers
        static int randomRange(int min, int max)
        {
            int n = max - min + 1;
            int remainder = RAND_MAX % n;
            int x;
            do {
                x = rand();
            } while (x >= RAND_MAX - remainder);
            
            return min + x % n;
        }
        
        //a = initial, b = final, f = factor (0 - 1)
        static float lerp(float a, float b, float f)
        {
            return a + f * (b - a);
        }

		static float smoothstep(float t)
		{
			return t * t * t * (t * (6.0 * t - 15.0) + 10.0);
		}
        
		//Adapted to use sf::Vector2f from Professor Vinicius Mendonça's lib
        static sf::Vector2f newBySizeAngle(float size, float radians)
        {
            return sf::Vector2f(cos(radians) * size, sin(radians) * size);
        }
        
        inline static float toRadians(float angdeg)
        {
            return static_cast<float>(angdeg / ONE_DEGREE);
        }

		inline static float sizeSqr(sf::Vector2f& vec)
		{
			return vec.x * vec.x + vec.y * vec.y;
		}

		inline static float size(sf::Vector2f& vec)
		{
			return sqrtf(sizeSqr(vec));
		}

		inline static sf::Vector2f& normalize(sf::Vector2f& vec) {
			float s = sizeSqr(vec);

			if (s != 0) {
				float ss = sqrtf(s);
				vec.x = vec.x / ss;
				vec.y = vec.y / ss;
			}

			return vec;
		}

		inline static float dot(const sf::Vector2f& a, const sf::Vector2f& b)
		{
			return a.x * b.x + a.y * b.y;
		}
		//End

		//current = direction; target = target.position - current.position
		inline static float lookAt(sf::Vector2f current, sf::Vector2f target) {
			current = normalize(current);
			target = normalize(target);
			return acos(dot(current, target));
		}

		inline static void saveScore(int score) {
			std::ofstream file;
			file.open("highscore.txt");
			file << score;
			file.close();
		}

		inline static int loadScore() {
			std::string filename = "highscore.txt";
			//std::cout << "Loading data file : " << filename << std::endl;
			std::ifstream file(filename);
			std::string score;
			std::getline(file, score);

			return atoi(score.c_str());
		}
    };
}

#endif /* defined(__SFML_Test_1__Util__) */
