#pragma once
#include <SFML/Graphics.hpp>
#include"GameArkanoid.h"
#include"Globals_number.h"
using namespace sf;

class Line :public GameArkanoid
{
protected:
	float xRaketka;

public:
	Line() { xRaketka = 210; };
	~Line() {};

	Sprite GetRaketka() { return s_raketka; }
	float GetPosRaket_X() { return xRaketka; }

	void SetRaketka(int a, int b, int c, int d) { s_raketka.setTextureRect(IntRect(a, b, c, d)); }
	void SetRaketkaPos(float a, float b) { s_raketka.setPosition(a, b); }


};