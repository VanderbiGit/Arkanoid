#pragma once
#include"Globals_number.h"
#include <SFML/Graphics.hpp>
using namespace sf;


class GameArkanoid
{
protected:
	Image i_life, i_block, i_block2, i_ball, i_pole, i_raketka, i_menu, i_menuBack, i_setting, i_menuArc;
	Texture t_life, t_block, t_block2, t_ball, t_pole, t_raketka, t_menu, t_menuBack, t_setting, t_menuArc;
	Sprite s_block[25], s_block2[number::five], s_life[number::three], s_ball, s_pole, s_raketka, s_menu, s_menuBack, s_setting, s_menuArc;

	static GameArkanoid* arkanoid;
	GameArkanoid()
	{
		i_life.loadFromFile("images/Ball.png");
		i_block.loadFromFile("images/Blok1.png");
		i_block2.loadFromFile("images/Blok2.png");
		i_ball.loadFromFile("images/Ball.png");
		i_pole.loadFromFile("images/PoleGame.png");
		i_raketka.loadFromFile("images/Raketka.png");
		i_menu.loadFromFile("images/menu.png");
		i_menuBack.loadFromFile("images/menu.png");
		i_setting.loadFromFile("images/setting.png");
		i_menuArc.loadFromFile("images/menuA.png");

		t_life.loadFromImage(i_life);
		t_block.loadFromImage(i_block);
		t_block2.loadFromImage(i_block2);
		t_ball.loadFromImage(i_ball);
		t_pole.loadFromImage(i_pole);
		t_raketka.loadFromImage(i_raketka);
		t_menu.loadFromImage(i_menu);
		t_menuBack.loadFromImage(i_menuBack);
		t_setting.loadFromImage(i_setting);
		t_menuArc.loadFromImage(i_menuArc);

		s_ball.setTexture(t_ball);
		s_pole.setTexture(t_pole);
		s_raketka.setTexture(t_raketka);
		s_menu.setTexture(t_menu);
		s_menuBack.setTexture(t_menuBack);
		s_setting.setTexture(t_setting);
		s_menuArc.setTexture(t_menuArc);
	};

public:

	static GameArkanoid* GetGame();
	~GameArkanoid() {};

	void SetMenu(int a, int b, int c, int d) { s_menu.setTextureRect(IntRect(a, b, c, d)); };
	void SetMenuPos(float a, float b) { s_menu.setPosition(a, b); };
	void SetMenuBack(int a, int b, int c, int d) { s_menuBack.setTextureRect(IntRect(a, b, c, d)); };
	void SetMenuBackPos(float a, float b) { s_menuBack.setPosition(a, b); };

	Sprite GetPole() { return s_pole; };
	Sprite GetMenu() { return s_menu; };
	Sprite GetMenuBack() { return s_menuBack; };
	Sprite GetSetting() { return s_setting; };
	Sprite GetMenuArc() { return s_menuArc; };
};