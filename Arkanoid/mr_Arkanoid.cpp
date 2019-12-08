#include <SFML/Graphics.hpp>
#include<iostream>
#include <windows.h>
#include"Globals_number.h"
#include"GameArkanoid.h"
#include"Ball.h"
#include"Line.h"
#include"Level.h"

using namespace sf;

RenderWindow WindowGame(VideoMode(WIDTH_X, HEIGHT_Y), "Arkanoid", Style::Close);

//Singalton
GameArkanoid* GameArkanoid::arkanoid = nullptr;
GameArkanoid* GameArkanoid::GetGame()
{
	if (arkanoid == nullptr)
		return arkanoid = new GameArkanoid();
	else
		return arkanoid;
}

int main()
{
	ContextSettings settings;//зглажування фігур/ відеокарта або драйвер повинні підтримувать
	WindowGame.setFramerateLimit(60);

	bool beginPlay = false, MenuBool = true, MenuSetting = false, Win = false;
	int tempWin = 0;

	Level myLevel;
	Ball myBall;
	Line myLine;//Ракетка
	GameArkanoid *myGameArkanoid;
	myGameArkanoid = GameArkanoid::GetGame();

	myLevel.SetSettingBlock();//block
	myLevel.SetSettingBlock2();//block2
	myLevel.SetSettingLife();//life

	myLine.SetRaketkaPos(myLine.GetPosRaket_X(), HEIGHT_Y - 20);//ставим ракетку і мяч по центру
	myBall.SetBallPos(myBall.GetBall_X(), myBall.GetBall_Y());


	while (WindowGame.isOpen())//Begin Play :)
	{
		Event event;
		while (WindowGame.pollEvent(event))
			if (event.type == Event::Closed)
				WindowGame.close();


		Vector2i positionMouse = Mouse::getPosition(WindowGame);

		if (positionMouse.x < 0)//крайні положення ракеткі ліво
		{
			myLine.SetRaketkaPos(0, HEIGHT_Y - 20);
			myBall.SetBallPos(40, HEIGHT_Y - 33);
		}

		if (positionMouse.x > WIDTH_X - 20)//крайні положення ракеткі право
		{
			myLine.SetRaketkaPos(550, HEIGHT_Y - 20);
			myBall.SetBallPos(590, HEIGHT_Y - 33);
		}

		if (positionMouse.x - 40 > 0 && positionMouse.x + 45 < WIDTH_X)
			myLine.SetRaketkaPos((float)(positionMouse.x) - 40, HEIGHT_Y - 20);//40 - це серидина ракеткі	

		if (beginPlay == false && (positionMouse.x - 40 > 0 && positionMouse.x + 45 < WIDTH_X))//рухаєм шарік разом з ракеткой
		{
			myBall.SetBallPos((float)(positionMouse.x), HEIGHT_Y - 33);
			myBall.SetBall_X((float)positionMouse.x);
			myBall.SetBall_Y(HEIGHT_Y - 33);
		}

		if (Mouse::isButtonPressed(Mouse::Right))//старт ігри
			beginPlay = true;

		if (beginPlay == true && LifeArcad > 0)//шарік в Грі
		{
			if (FloatRect(myBall.GetBall_X(), myBall.GetBall_Y(), 15.0, 15.0).intersects(myLine.GetRaketka().getGlobalBounds())) myBall.SetTempY(-(float)(rand() % 6 + 3));
			if (myBall.GetBall_X() < 0 || myBall.GetBall_X() > WIDTH_X) myBall.SetTempX(-myBall.GetTempX());
			if (myBall.GetBall_Y() < 45)  myBall.SetTempY(-myBall.GetTempY());

			//Первіряєм чи збігаються голобальні кординати рамкі спрайта блока з глоб. кор. рамкі мячіка
			for (int i = 0; i < counter; i++)
			{
				if (myLevel.GetBlock2(i).getGlobalBounds().intersects(myBall.GetBall().getGlobalBounds()) && i < number::five)
				{
					myBall.SetTempY(-myBall.GetTempY());
					myLevel.SetBlock2(i);
					break;
				}

				if (myLevel.GetBlock(i).getGlobalBounds().intersects(myBall.GetBall().getGlobalBounds()))
				{
					myBall.SetTempY(-myBall.GetTempY());
					myLevel.SetBlock(i);
					break;
				}
			}
			myBall.SetBall_X(myBall.GetBall_X() + myBall.GetTempX());
			myBall.SetBall_Y(myBall.GetBall_Y() + myBall.GetTempY());

			myBall.SetBallPos(myBall.GetBall_X(), myBall.GetBall_Y());

			for (int i = 0; i < counter; i++)
			{
				if (myLevel.GetCountBlock(i) == -100)
					tempWin++;

				if (tempWin == counter)//збили всі блокі. Ура!!!
				{
					beginPlay = false;
					inLevel++;
					//Гра з 3-ох рівнів, ВИГРАШ
					if (inLevel == number::three)
					{
						Win = true;
						inLevel = 0;
					}
					myLevel.SetSettingBlock();//block
					myLevel.SetSettingBlock2();//block2
				}
			}
			tempWin = 0;


			if (myBall.GetBall_Y() > HEIGHT_Y)//бивша бага з жизннями(виправлена). Можлива інша реалізація
				LifeArcad--;

		}////beginPlay == true //шарік в Грі


		if (myBall.GetBall_Y() > HEIGHT_Y)//шарік ниже ракеткі, відновлюєв стартові положення 
			beginPlay = false;


		WindowGame.clear();
		if (MenuBool == false && MenuSetting == false && Win == false)//Ігрові елементи
		{
			WindowGame.draw(myGameArkanoid->GetPole());
			WindowGame.draw(myLine.GetRaketka());
			WindowGame.draw(myBall.GetBall());
			for (int i = 0; i < counter; i++)
				WindowGame.draw(myLevel.GetBlock(i));

			for (int i = 0; i < number::five; i++)
				WindowGame.draw(myLevel.GetBlock2(i));

			for (int i = 0; i < LifeArcad; i++)
				WindowGame.draw(myLevel.GetLife(i));
		}

		//Меню
		if (MenuBool == true)
		{
			WindowGame.draw(myGameArkanoid->GetMenuArc());
			myGameArkanoid->SetMenu(0, 0, 135, 185);
			myGameArkanoid->SetMenuPos(260, 250);
			WindowGame.draw(myGameArkanoid->GetMenu());
			//New Game
			if ((positionMouse.x > 260 && positionMouse.x < 393) && (positionMouse.y > 250 && positionMouse.y < 309))
			{
				myGameArkanoid->SetMenuBack(137, 0, 135, 60);
				myGameArkanoid->SetMenuBackPos(260, 250);
				WindowGame.draw(myGameArkanoid->GetMenuBack());
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					MenuBool = false;
					myLevel.SetSettingBlock();//розтавляєм блоки. для відновля після Game Over
					myLevel.SetSettingBlock2();
					myLevel.SetSettingLife();
				}


			}
			//Seting
			if ((positionMouse.x > 260 && positionMouse.x < 393) && (positionMouse.y > 313 && positionMouse.y < 371))
			{
				myGameArkanoid->SetMenuBack(137, 62, 135, 60);
				myGameArkanoid->SetMenuBackPos(260, 313);
				WindowGame.draw(myGameArkanoid->GetMenuBack());
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					MenuBool = false;
					MenuSetting = true;
				}

			}
			//Exit
			if ((positionMouse.x > 260 && positionMouse.x < 393) && (positionMouse.y > 374 && positionMouse.y < 433))
			{
				myGameArkanoid->SetMenuBack(137, 124, 135, 60);
				myGameArkanoid->SetMenuBackPos(260, 374);
				WindowGame.draw(myGameArkanoid->GetMenuBack());
				if (Mouse::isButtonPressed(Mouse::Left))
					WindowGame.close();
			}

		}
		//Seting
		if (MenuSetting == true)
		{
			WindowGame.draw(myGameArkanoid->GetSetting());
			//Back
			if ((positionMouse.x > 0 && positionMouse.x < 135) && (positionMouse.y > 0 && positionMouse.y < 60))
			{
				myGameArkanoid->SetMenuBack(137, 186, 135, 60);
				myGameArkanoid->SetMenuBackPos(0, 0);
				WindowGame.draw(myGameArkanoid->GetMenuBack());

				if (Mouse::isButtonPressed(Mouse::Left))
				{
					MenuBool = true;
					MenuSetting = false;
				}

			}
			else
			{
				myGameArkanoid->SetMenuBack(0, 186, 135, 60);
				myGameArkanoid->SetMenuBackPos(0, 0);
				WindowGame.draw(myGameArkanoid->GetMenuBack());
			}

		}

		if (Win == true)
		{
			myGameArkanoid->SetMenuBack(0, 313, 235, 360);
			myGameArkanoid->SetMenuBackPos(180, 200);
			WindowGame.draw(myGameArkanoid->GetMenuBack());
			WindowGame.display();
			Sleep(3000);
			Win = false;
			MenuBool = true;
		}

		if (LifeArcad == 0)
		{
			myBall.GetBall().setPosition(0, 700);
			//Game Over
			if ((positionMouse.x > 260 && positionMouse.x < 393) && (positionMouse.y > 150 && positionMouse.y < 210))
			{
				myGameArkanoid->SetMenuBack(137, 248, 135, 60);
				myGameArkanoid->SetMenuBackPos(260, 150);
				WindowGame.draw(myGameArkanoid->GetMenuBack());

				if (Mouse::isButtonPressed(Mouse::Left))
				{
					MenuBool = true;
					LifeArcad = number::three;
					inLevel = 0;
				}

			}
			else
			{
				myGameArkanoid->SetMenuBack(0, 248, 135, 60);
				myGameArkanoid->SetMenuBackPos(260, 150);
				WindowGame.draw(myGameArkanoid->GetMenuBack());
			}

		}

		WindowGame.display();
	}

	return 0;
}
