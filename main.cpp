#include"head.h"
int main(void)
{
	int velocity;
	bool wall;

	velocity = get_velocity();
	wall = havewall();
	GameInit();
	while (1) //游戏主循环，通过不断刷新实现动态化
	{
		GameDraw();
		SnakeMove(wall);
		GetKeyState();
		EatFood();
		DontEatSelf();
		Sleep(velocity);
	}

	return 0;
}