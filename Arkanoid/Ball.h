#pragma once
#include <SFML/Graphics.hpp>
#include"GameArkanoid.h"
#include"Globals_number.h"
using namespace sf;


class Ball : public GameArkanoid
{
protected:
	float xBall, yBall, temp_X, temp_Y;

public:
	Ball() { xBall = 250, yBall = 440, temp_X = number::six, temp_Y = number::five; };
	~Ball() {};

	void SetBallPos(float a, float b) { s_ball.setPosition(a, b); }
	Sprite GetBall() { return s_ball; }

	void SetBall_X(float i) { xBall = i; }
	void SetBall_Y(float i) { yBall = i; }
	void SetTempX(float i) { temp_X = i; }
	void SetTempY(float i) { temp_Y = i; }

	float GetBall_X() { return xBall; }
	float GetBall_Y() { return yBall; }
	float GetTempX() { return temp_X; }
	float GetTempY() { return temp_Y; }
};
