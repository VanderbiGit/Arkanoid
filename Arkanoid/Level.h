#pragma once
#include <SFML/Graphics.hpp>
#include"GameArkanoid.h"
#include"Globals_number.h"
using namespace sf;

class Level :public GameArkanoid
{
private:
	int arrLevel[3][50], arrLevel1_1[3][10], x, y;
	int temp;
public:
	Level() {};
	~Level() {};

	Sprite SetSettingBlock()
	{
		counter = 0;
		temp = 0;
		int arrLevel[3][50] =
		{
			{ 1,1,1,2,1,3,1,4,1,5, 2,1,2,2,2,3,2,4,2,5, 3,1,3,2,3,3,3,4,3,5, 4,1,4,2,4,3,4,4,4,5, 5,1,5,2,5,3,5,4,5,5 },
			{ 1,1,1,2,1,3,1,4,1,5, -100,1,-100,2,2,3,2,4,2,5, -100,1,-100,2,-100,3,3,4,3,5, -100,1,-100,2,4,3,4,4,4,5, 5,1,5,2,5,3,5,4,5,5 },
			{ 1,1,1,2,1,3,1,4,1,5, -100,1,-100,2,-100,3,-100,4,-100,5, 3,1,3,2,3,3,3,4,3,5, -100,1,-100,2,-100,3,-100,4,-100,5, 5,1,5,2,5,3,5,4,5,5 }
		};

		for (int i = 1; i <= number::five; i++)
			for (int j = 1; j <= number::five; j++)
			{
				s_block[counter].setTexture(t_block);
				if ((float)arrLevel[inLevel][temp] != -100)
					s_block[counter].setPosition((float)arrLevel[inLevel][temp] * 100 - 25, (float)arrLevel[inLevel][temp + 1] * 30 + 45);
				else
					s_block[counter].setPosition(-100, 0);
				temp += 2;
				counter++;
			}
		return s_block[number::five * 5];
	}

	Sprite SetSettingBlock2()
	{
		temp = 0;
		int arrLevel1_1[3][10] = { { 1,1,2,1,3,1,4,1,5,1 } ,{ 1,1,5,1,1,2,5,2,3,5 },{ 1,3,3,3,3,2,3,1,5,3 } };
		for (int j = 1; j <= number::five; j++)
		{
			s_block2[j - 1].setTexture(t_block2);
			s_block2[j - 1].setPosition((float)arrLevel1_1[inLevel][temp] * 100 - 25, (float)arrLevel1_1[inLevel][temp + 1] * 30 + 45);
			temp += 2;
		}
		return s_block2[number::five];
	}

	Sprite SetSettingLife()
	{
		for (int j = 1; j <= number::three; j++)
		{
			s_life[j - 1].setTexture(t_life);
			s_life[j - 1].setPosition((float)j * 30 + 50, 12);
		}
		return s_life[number::three];
	}

	Sprite GetBlock(int i) { return s_block[i]; }
	Sprite GetBlock2(int i) { return s_block2[i]; }
	Sprite GetLife(int i) { return s_life[i]; }

	void SetBlock(int i) { s_block[i].setPosition(-100, 0); }
	void SetBlock2(int i) { s_block2[i].setPosition(-100, 0); }
	void SetLife(int i) { s_life[i].setPosition(-100, 0); }
	float GetCountBlock(int i) { return s_block[i].getGlobalBounds().left; }

};