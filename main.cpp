#include"head.h"
int main(void)
{
	int velocity;
	bool wall;

	velocity = get_velocity();
	wall = havewall();
	GameInit();
	while (1) //��Ϸ��ѭ����ͨ������ˢ��ʵ�ֶ�̬��
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