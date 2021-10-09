#include "head.h"
//�ṹ���ö�ٶ���
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

//��������
char get_first(void)
{
	char ch;

	//����ǰ��հף�ͬʱʹ�س�����Ӧ
	while (isspace(ch = getchar()))
		continue;
	//��ʱch==��һ���ǿհ���ĸ
	//����ʣ�໺����
	while (getchar() != '\n')
		continue;

	return ch;
}
char get_choice(void)//��ӡ�˵�����ȡ��ȷ��ѡ��
{
	char choice;

	printf("ѡ���Ѷȣ�������ĸ��[Enter]��:\n");
	printf("a)��          b)����\n");
	printf("c)����          d)����\n");
	printf("e)�����˰�      q)ү������\n");
	//��֤��ȡ��ȷ��ѡ��
	choice = get_first();
	while (!('a' <= choice && choice <= 'e') && choice != 'q')
	{
		printf("���벻��!\n");
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
		default: printf("��ô�Ͷ����˸�%c?,����һ��\n", ch);
		}
}
bool havewall(void) //����ײǽ����
{
	bool have;
	char choice;

	printf("\n�Ƿ�ѡ��߽磿\n");
	printf("a) ��   b) ��\n");

	choice = get_first();
	while (choice != 'a' && choice != 'b')
	{
		puts("���벻��\n");
		choice = get_first();
	}

	if (choice == 'a')
		return true;
	else
		return false;
}
void GameInit(void)
{
	//������ʱ�����������
	srand((unsigned)time(NULL));
	//��ʼ����
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
	//��ʼ��ʳ��
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.point.x = rand() % (WIN_WIDTH - 1) / 10 * 10;
	food.point.y = rand() % (WIN_HEIGHT - 1) / 10 * 10;
	//���س�ʼ����
	initgraph(WIN_WIDTH, WIN_HEIGHT, SHOWCONSOLE);
	outtextxy(100, 70, "��ӭ���������С��ߣ�");
	outtextxy(100, 100, "�ο�csdn@С��������");
	outtextxy(100, 130, "�������bug�������룬�����Ѷ�ѡ�񣬲����");
	outtextxy(100, 160, "���ӵ�ͼ�߽�ѡ��պ��(lan)��(de)ȥ����ͼ");
	outtextxy(100, 190, "лл֧��");
	Sleep(2000);//���ִ���
}
void GameDraw(void)
{
	int i;
	char temp[100];//Ϊ��ʵ�ֶ�̬�仯����Ҫ������
	//����ϴε�ҳ��
	cleardevice();
	//����ɫ����
	setbkcolor(RGB(105, 160, 141));
	//����
	setlinecolor(BLACK);
	setfillcolor(YELLOW);
	for (i = 0; i < snake.length; i++)
		fillrectangle(snake.coor[i].x, snake.coor[i].y,
			snake.coor[i].x + snake.size, snake.coor[i].y + snake.size);
	//��ʳ��
	setfillcolor(food.color);//֮ǰ�õ�RGBǶ��rand������ÿ�η���color������һ��
	fillellipse(food.point.x, food.point.y,
		food.point.x + 10, food.point.y + 10);
	//��ʾ����
	sprintf(temp, "��ķ���:%d", snake.score);
	outtextxy(20, 20, temp);
}
void GameOver(void)
{
	outtextxy(150, 150, "��Ϸ����");
	Sleep(2000);
	exit(0);
}
void SnakeMove(bool havewall) //���Լ�һ��boolȥ����ײǽ�ж�
{
	int i;
	//�ƶ����壬ֱ�Ӹ�ֵ�ṹ�Ϳ�����
	for (i = snake.length - 1; i > 0; i--)
		snake.coor[i] = snake.coor[i - 1];
	//�ƶ���ͷ
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
	default:printf("���������⣿��ô���");
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
		//������food
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