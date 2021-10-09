#include "head.h"
//结构体和枚举定义
enum {
	UP,
	DOWN,
	LEFT,
	RIGHT
};
struct {
	int dir;
	int size;
	int length;
	int score;
	POINT coor[MAX_SNAKE];
}snake;
struct {
	POINT point;
	DWORD color;
}food;

//函数定义
char get_first(void)
{
	char ch;

	//清理前面空白，同时使回车无响应
	while (isspace(ch = getchar()))
		continue;
	//此时ch==第一个非空白字母
	//处理剩余缓冲区
	while (getchar() != '\n')
		continue;

	return ch;
}
char get_choice(void)//打印菜单并获取正确的选项
{
	char choice;

	printf("选择难度，输入字母后按[Enter]键:\n");
	printf("a)简单          b)适中\n");
	printf("c)困难          d)地狱\n");
	printf("e)老年人版      q)爷不玩了\n");
	//保证获取正确的选项
	choice = get_first();
	while (!('a' <= choice && choice <= 'e') && choice != 'q')
	{
		printf("输入不对!\n");
		choice = get_first();
	}

	return choice;
}
int get_velocity(void)
{
	char ch;
	if (ch = get_choice())
		switch (ch)
		{
		case 'a': return 100;
		case 'b': return 70;
		case 'c': return 50;
		case 'd': return 40;
		case 'e': return 150;
		case 'q': exit(0);
		default: printf("怎么就读出了个%c?,重启一下\n", ch);
		}
}
bool havewall(void) //增加撞墙机制
{
	bool have;
	char choice;

	printf("\n是否选择边界？\n");
	printf("a) 是   b) 否\n");

	choice = get_first();
	while (choice != 'a' && choice != 'b')
	{
		puts("输入不对\n");
		choice = get_first();
	}

	if (choice == 'a')
		return true;
	else
		return false;
}
void GameInit(void)
{
	//先整个时间随机数种子
	srand((unsigned)time(NULL));
	//初始化蛇
	snake.dir = RIGHT;
	snake.length = 3;
	snake.score = 0;
	snake.size = 10;
	snake.coor[2].x = 0;
	snake.coor[2].y = 0;
	snake.coor[1].x = 0;
	snake.coor[1].y = 0 + 1 * snake.size;
	snake.coor[0].x = 0;
	snake.coor[0].y = 0 + 2 * snake.size;
	//初始化食物
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.point.x = rand() % (WIN_WIDTH - 1) / 10 * 10;
	food.point.y = rand() % (WIN_HEIGHT - 1) / 10 * 10;
	//加载初始窗口
	initgraph(WIN_WIDTH, WIN_HEIGHT, SHOWCONSOLE);
	outtextxy(100, 70, "欢迎来尝试这个小玩具！");
	outtextxy(100, 100, "参考csdn@小鸡在啄米");
	outtextxy(100, 130, "修正诸多bug，简洁代码，增加难度选择，并打包");
	outtextxy(100, 160, "增加地图边界选项，日后可(lan)能(de)去做地图");
	outtextxy(100, 190, "谢谢支持");
	Sleep(2000);//保持窗口
}
void GameDraw(void)
{
	int i;
	char temp[100];//为了实现动态变化，需要用数组
	//清除上次的页面
	cleardevice();
	//背景色设置
	setbkcolor(RGB(105, 160, 141));
	//画蛇
	setlinecolor(BLACK);
	setfillcolor(YELLOW);
	for (i = 0; i < snake.length; i++)
		fillrectangle(snake.coor[i].x, snake.coor[i].y,
			snake.coor[i].x + snake.size, snake.coor[i].y + snake.size);
	//画食物
	setfillcolor(food.color);//之前用的RGB嵌套rand函数，每次访问color都调用一次
	fillellipse(food.point.x, food.point.y,
		food.point.x + 10, food.point.y + 10);
	//显示分数
	sprintf(temp, "你的分数:%d", snake.score);
	outtextxy(20, 20, temp);
}
void GameOver(void)
{
	outtextxy(150, 150, "游戏结束");
	Sleep(2000);
	exit(0);
}
void SnakeMove(bool havewall) //可以加一个bool去控制撞墙判断
{
	int i;
	//移动身体，直接赋值结构就可以了
	for (i = snake.length - 1; i > 0; i--)
		snake.coor[i] = snake.coor[i - 1];
	//移动蛇头
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y -= snake.size;
		if (snake.coor[0].y < 0)
		{
			if (havewall)
				GameOver();
			snake.coor[0].y = WIN_HEIGHT - snake.size;
		}
		break;
	case LEFT:
		snake.coor[0].x -= snake.size;
		if (snake.coor[0].x < 0)
		{
			if (havewall)
				GameOver();
			snake.coor[0].x = WIN_WIDTH - snake.size;
		}
		break;
	case RIGHT:
		snake.coor[0].x += snake.size;
		if (snake.coor[0].x >= WIN_WIDTH)
		{
			if (havewall)
				GameOver();
			snake.coor[0].x = 0;
		}
		break;
	case DOWN:
		snake.coor[0].y += snake.size;
		if (snake.coor[0].y >= WIN_HEIGHT)
		{
			if (havewall)
				GameOver();
			snake.coor[0].y = 0;
		}
		break;
	default:printf("方向有问题？怎么搞的");
	}
}
void GetKeyState(void)
{
	if (GetAsyncKeyState(VK_UP) && snake.dir != DOWN)
		snake.dir = UP;
	if (GetAsyncKeyState(VK_DOWN) && snake.dir != UP)
		snake.dir = DOWN;
	if (GetAsyncKeyState(VK_LEFT) && snake.dir != RIGHT)
		snake.dir = LEFT;
	if (GetAsyncKeyState(VK_RIGHT) && snake.dir != LEFT)
		snake.dir = RIGHT;
}
void EatFood(void)
{
	if (snake.coor[0].x == food.point.x
		&& snake.coor[0].y == food.point.y)
	{
		snake.length++;
		snake.score += 1;
		//构造新food
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.point.x = rand() % (WIN_WIDTH - 1) / 10 * 10;
		food.point.y = rand() % (WIN_HEIGHT - 1) / 10 * 10;
	}
}
void DontEatSelf(void)
{
	int i;

	for (i = 4; i < snake.length; i++)
		if (snake.coor[0].x == snake.coor[i].x
			&& snake.coor[0].y == snake.coor[i].y)
		{
			GameOver();
		}
}