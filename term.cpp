#include "car.h"

typedef struct Object
{
	int x, y;
}Object;

typedef struct Item1
{
	int x, y;
}Item1;   //

typedef struct Item2
{
	int x, y;
}Item2;   //

typedef struct Item3
{
	int x, y;
}Item3;   //


int hp = 5;
int keep_moving = 0; // ��ĭ�� �̵�

void removeCursor(void);   //Ŀ�� ����� �Լ�
void showCursor(void);     //Ŀ�� �巯���� �Լ�
void gotoxy(int x, int y);     //x,y������ �̵�
void textcolor(int fg_color, int bg_color);     //�ؽ�Ʈ�� �ؽ�Ʈ��� �÷�
void cls(int bg_color, int text_color);     //��� �� ����
void draw_box2(int x1, int y1, int x2, int y2);     //ȭ��ڽ�
void draw_box2_fill(int x1, int y1, int x2, int y2, int color);   //ȭ�� �ڽ� ��ä���
void clean(void);     //ȭ�� �ڽ��� ���� �� ����� �Լ�
void road(void);      //����
void road2(void);     //����2
void background_intro(void);     //��� ����
void print_gamename(void);   //���� ��� �����̸��̶� ������
void howtoplay(void);
void intro(void);            //��Ʈ�� car 
void show_hp(int hp);        //���� ü�� ǥ��
void information(int n);   //�߿����� ���� ����(�ٹ̱��)
void car(int x);          //3x4 �������� ��
void player(unsigned char ch, int D);    //�÷��̾� ����Ű�� �����̰��ϴ� �ڵ�
void putcar(int x, int y);     //���� �׸���
void erasecar(int x, int y);     //�����
int check(int carx, int cary, int objectx, int objecty);   //�浹ó��
void object(int x, int y);   // ��ֹ�
void putobj(int x, int y);
void eraseobj(int x, int y);
void item1(int x, int y);    // ��Ʈ ������
void putitem1(int x, int y);
void eraseitem1(int x, int y);
void item2(int x, int y);   //���� ��Ƣ�� ������
void putitem2(int x, int y);
void eraseitem2(int x, int y);
void item3(int x, int y);    //�ӵ� ���� ������
void putitem3(int x, int y);
void eraseitem3(int x, int y);


int objectX = 12, objectY = 1;
int carX = 0, carY = 0;
int item1X = 12, item1y = 1;   //
int item2X = 12, item2y = 1;   //
int item3X = 12, item3y = 1;   //
void main()
{
	system("mode con cols=150 lines=40");

	int i, x, y, r;
	unsigned char ch;
	int score = 0;
	char name[50];
	int D = 0;
	srand(time(NULL));
	//  <�ʱ�ȭ��>
	removeCursor(); // Ŀ���� �Ⱥ��̰� �Ѵ�
	cls(GREEN2, BLACK);
	background_intro();
	textcolor(BLACK, GREEN2);
	draw_box2(0, 0, 79, 28);
	draw_box2(81, 0, 106, 28);
	draw_box2(83, 1, 104, 4);  // �����̸��� ������(��) ����Ʈ
	print_gamename();
	draw_box2(83, 5, 104, 9);  // �÷��̾� �̸�ĭ
	draw_box2(83, 10, 104, 14);  //���ھ� ǥ��ĭ
	draw_box2(83, 15, 104, 19); //���� ü�� ��ġȭ(���� or ü�¹�)
	show_hp(hp);
	draw_box2(83, 20, 104, 27);  //���� �ӵ��� ���� ������ information �Լ�
	draw_box2(108, 1, 126, 12);
	howtoplay();
	information(D);
	intro();

	gotoxy(26, 17);
	printf("player�� �̸��� �Է��ϼ���.");
	textcolor(0, 9);
	gotoxy(37, 18);
	textcolor(0, 10);
	showCursor();
	scanf("%s", name);
	removeCursor();
	gotoxy(85, 6);
	printf("player :");
	gotoxy(86, 8);
	printf("%s", name);


	//  <��Ʈ�� ��> 
	clean();  //������������ �Լ� 
	//��Ʈ�θ� ����� ���ؼ� �� ���������� ���� �ڽ��� ���� Ʋ �ۼ�
	cls(GREEN2, BLACK);
	textcolor(BLACK, GREEN2);
	draw_box2(0, 0, 79, 28);
	draw_box2(81, 0, 106, 28);
	draw_box2(83, 1, 104, 4);     // �����̸��� ������(��) ����Ʈ
	print_gamename();
	draw_box2(83, 5, 104, 9);     // �÷��̾� �̸�ĭ
	gotoxy(85, 6);
	printf("player :");
	gotoxy(86, 8);
	printf("%s", name);
	draw_box2(83, 10, 104, 14);   //���ھ� ǥ��ĭ
	show_hp(hp);
	draw_box2(83, 15, 104, 19);   //���� ü�� ��ġȭ(���� or ü�¹�)
	draw_box2(83, 20, 104, 27);   //���� �ӵ��� ���� ������? information �Լ�
	information(D);
	draw_box2(108, 1, 126, 12);
	howtoplay();
	putcar(40, 22);

	while (1) {
		road();
		road2();
		if (hp <= 0)  //hp�� 0���ϰ� �Ǹ� ���� ����
		{
			clean();
			gotoxy(40, 15);
			printf("game over!");
			gotoxy(36, 17);
			printf("%s score is %d!", name, score - 3);
			gotoxy(36, 19);
			//��
			gotoxy(32, 21);
			printf("�����Ϸ��� ESC�� �Է��ϼ���!");
			while (1) {
				if (kbhit() == 1) {
					ch = getch();
					if (ch == ESC) {
						gotoxy(2, 30);
						break;
					}
				}
			}
			break;
		}
		information(D);

		//����
		gotoxy(85, 11);
		printf("score : %d", score);
		score += 3;



		//��ֹ�
		Object objects[10];
		Item1 items1[3];  //
		Item2 items2[3];  //
		Item3 items3[5];  //

		int tmp = 12;
		static int objNum = 1;
		static int end = 29;

		static int item1Num = 0;  //
		static int item2Num = 0;  //
		static int item3Num = 0;  //

		// ���� �ֱ⸶�� ��ֹ��� ���� ���� ����
		if (end > 28)
		{
			objNum = 4 + rand() % 5;
			end = 0;
			// ������ŭ ��ֹ��� x���� ������ ����
			for (int i = 0; i < objNum; i++) {
				tmp = 14 + rand() % 56;
				objects[i].x = tmp;
				objects[i].y = 1;
			}
		}

		if (end == 8) //
		{
			item1Num = rand() % 2;
			for (int i = 0; i < item1Num; i++) {
				tmp = 14 + rand() % 56;
				items1[i].x = tmp;
				items1[i].y = 1;
			}
		}//
		if (end == 22) //
		{
			item2Num = rand() % 2;
			for (int i = 0; i < item2Num; i++) {
				tmp = 14 + rand() % 56;
				items2[i].x = tmp;
				items2[i].y = 1;
			}
		}//
		if (end == 15) //
		{
			item3Num = 1 + rand() % 4;
			for (int i = 0; i < item3Num; i++) {
				tmp = 14 + rand() % 56;
				items3[i].x = tmp;
				items3[i].y = 1;
			}
		}//


		// ��ֹ� ��ġ ������Ʈ
		for (int i = 0; i < objNum; i++) {
			object(objects[i].x, objects[i].y);
			objects[i].y++;
		}

		for (int i = 0; i < item1Num; i++) {  //
			item1(items1[i].x, items1[i].y);
			items1[i].y++;
		} //

		for (int i = 0; i < item2Num; i++) {  //
			item2(items2[i].x, items2[i].y);
			items2[i].y++;
		} //

		for (int i = 0; i < item3Num; i++) {  //
			item3(items3[i].x, items3[i].y);
			items3[i].y++;
		} //

		// �������� �ֱ� �����ִ� ����
		end++;


		// �� ��ֹ��� ���� �浹ó��
		for (int i = 0; i < objNum; i++) {
			if (check(carX, carY, objects[i].x, objects[i].y) == 1) {
				eraseobj(objects[i].x, objects[i].y);
				show_hp(--hp);
			}
		}

		// ������1 �浹ó��
		for (int i = 0; i < item1Num; i++) {
			if (check(carX, carY, items1[i].x, items1[i].y) == 1) {
				if (hp <= 4) { //hp�� 5�϶� �� ä������ ����.
					show_hp(++hp);  //������ ȸ�� ������
					eraseitem1(items1[i].x, items1[i].y);
				}
			}
		}

		// ������2 �浹ó��
		for (int i = 0; i < item2Num; i++) {
			if (check(carX, carY, items2[i].x, items2[i].y) == 1) {
				score += 500;  //���� �߰� ������
				eraseitem2(items2[i].x, items2[i].y);
			}
		}

		// ������3 �浹ó�� 
		for (int i = 0; i < item3Num; i++) {
			if (check(carX, carY, items3[i].x, items3[i].y) == 1) {
				D += 1;  //�Ųٷ� �����ϴ� ���� ������
				eraseitem3(items3[i].x, items3[i].y);
			}
		}
		if (kbhit() == 1) {  // Ű���尡 ������ ������
			ch = getch();      // key ���� �д´�
			if (ch == 27)      // �Էµ� Ű�� ESC�̸� TRUE
				break;
			if (ch == SPECIAL1 || ch == SPECIAL2) { // ���� Ư��Ű
				ch = getch();
				// Player�� ����Ű�� �����δ�.
				switch (ch) {
				case LEFT:
				case RIGHT:
					player(ch, D);
					break;
				default:       // Ư��Ű ������ ����Ű�� �ƴ� ���
					player(0, D);
				}
			}
			else {
				player(0, D);
			}
		}


		if (end >= 23 && carX >= 9 && carY >= 17)  //��ֹ��� �ε����� ����� �������µ� �ٽ� �׷��� ����
			putcar(carX, carY);

		//����
		if (score < 500)
			Sleep(70);
		else if (score < 1500)
			Sleep(55);
		else if (score < 3000)
			Sleep(45);
		else
			Sleep(35);
	}
}

void removeCursor(void) {  // Ŀ���� �Ⱥ��̰� �Ѵ�

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void showCursor(void) { // Ŀ���� ���̰� �Ѵ�
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void gotoxy(int x, int y) //���� ���ϴ� ��ġ�� Ŀ�� �̵�
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API �Լ��Դϴ�. �̰� ���ʿ� �����
}

void textcolor(int fg_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}

void cls(int bg_color, int text_color)
{
	char cmd[100];
	system("cls");
	sprintf(cmd, "COLOR %x%x", bg_color, text_color);
	system(cmd);

}

void draw_box2(int x1, int y1, int x2, int y2)
{
	int x, y;
	//int len = strlen(ch);
	for (x = x1; x <= x2; x += 2) { // �ѱ��� 2ĭ�� �����Ѵ�.
		gotoxy(x, y1);
		printf("%s", "��"); // �� ������ ����Ű ������ ����
		gotoxy(x, y2);
		printf("%s", "��");
	}
	for (y = y1; y <= y2; y++) {
		gotoxy(x1, y);
		printf("%s", "��");
		gotoxy(x2, y);
		printf("%s", "��");
	}
	gotoxy(x1, y1); printf("��");
	gotoxy(x1, y2); printf("��");
	gotoxy(x2, y1); printf("��");
	gotoxy(x2, y2); printf("��");
}

void draw_box2_fill(int x1, int y1, int x2, int y2, int color)
{
	int x, y;

	textcolor(BLACK, WHITE);
	for (x = x1; x <= x2; x += 2) { // �ѱ��� 2ĭ�� �����Ѵ�.
		gotoxy(x, y1);
		printf("%s", "��"); // �� ������ ����Ű ������ ����
		gotoxy(x, y2);
		printf("%s", "��");
	}
	for (y = y1; y <= y2; y++) {
		gotoxy(x1, y);
		printf("%s", "��");
		gotoxy(x2, y);
		printf("%s", "��");
	}
	gotoxy(x1, y1); printf("��");
	gotoxy(x1, y2); printf("��");
	gotoxy(x2, y1); printf("��");
	gotoxy(x2, y2); printf("��");
	//getch();
	for (y = y1 + 1; y < y2; y++) {
		for (x = x1 + 2; x < x2; x++) {
			textcolor(color, color);
			gotoxy(x, y);
			printf(" ");
		}
	}

}

void clean(void) //ȭ�� �� ������ �Լ�
{
	int i, j;
	textcolor(0, 2);
	for (i = 1; i < 79; i++) {
		for (j = 1; j < 28; j++)
		{
			gotoxy(i, j);
			printf(" ");
		}
	}
}

void road(void)  //��� �� ǥ��
{
	int y;
	for (y = 1; y <= 27; y++) {
		gotoxy(12, y);
		printf("%s", "��");
		gotoxy(70, y);
		printf("%s", "��");
	}
}
void road2(void)  //��� �� ǥ��2
{
	int y;
	for (y = 1; y <= 27; y++) {
		gotoxy(13, y);
		printf("%s", "��");
		gotoxy(71, y);
		printf("%s", "��");
	}
}

void background_intro(void)  //�������� 1 �ʿ� ���
{
	int i, j;
	gotoxy(0, 1);
	textcolor(9, 9);
	for (i = 1; i < 80; i++) {
		for (j = 1; j < 13; j++) {
			gotoxy(i, j);
			printf(" ");
		}
	}
	textcolor(15, 15);  //����
	for (i = 25; i < 30; i++) {
		gotoxy(i, 3);
		printf(" ");
	}
	for (i = 23; i < 33; i++) {
		gotoxy(i, 4);
		printf(" ");
	}
	for (i = 21; i < 34; i++) {
		gotoxy(i, 5);
		printf(" ");
	}
	for (i = 65; i < 68; i++) {
		gotoxy(i, 2);
		printf(" ");
	}
	for (i = 64; i < 69; i++) {
		gotoxy(i, 3);
		printf(" ");
	}
	for (i = 62; i < 70; i++) {
		gotoxy(i, 4);
		printf(" ");
	}
}

void howtoplay(void)  // draw_box2(108, 1, 126 11);
{
	gotoxy(109, 2);
	printf(" �� :���� �̵�");
	gotoxy(109, 3);
	printf(" �� :������ �̵�");
	gotoxy(109, 5);
	printf("  *���ظ� �ϴ�*");
	gotoxy(110, 6);
	textcolor(0, 4);
	printf("X: ��ֹ�");
	gotoxy(110, 7);
	textcolor(0, 14);
	printf("D: �ݴ�� ����");
	textcolor(0, 10);
	gotoxy(109, 9);
	printf("  *������ �Ǵ�*");
	gotoxy(110, 10);
	textcolor(0, 9);
	printf("S: 500�� �߰�");
	gotoxy(110, 11);
	textcolor(0, 13);
	printf("@: ������ 1 ȸ��");
	textcolor(0, 10);

}

void print_gamename(void)
{
	gotoxy(85, 2);
	printf("S1mple Car Racing");
	gotoxy(85, 3);
	printf("������ : movinggun");
}

void intro(void)  //CAR ��Ʈ�� , press start any key 
{
	char ch;
	textcolor(0, 9);
	gotoxy(24, 7);
	printf("..");
	gotoxy(20, 8);
	printf(".ad8PP8ba.");
	gotoxy(19, 9);
	printf("d8r");
	gotoxy(18, 10);
	printf("o8");
	gotoxy(18, 11);
	printf("88");
	gotoxy(18, 12);
	printf("a8");
	textcolor(0, 10);
	gotoxy(19, 13);
	printf("b8q");
	gotoxy(20, 14);
	printf("*aY8bbbp9'");
	gotoxy(23, 15);
	printf("\'\"\"");

	textcolor(0, 9);
	gotoxy(37, 8);
	printf(".db.");
	gotoxy(36, 9);
	printf("d8  8b");
	gotoxy(35, 10);
	printf("d8    8b");
	gotoxy(34, 11);
	printf("d88888888b");
	gotoxy(33, 12);
	printf("d8        8b");
	textcolor(0, 10);
	gotoxy(32, 13);
	printf("d8          8b");
	gotoxy(31, 14);
	printf("d8            8b");

	textcolor(0, 9);
	gotoxy(49, 8);
	printf("8888888ba");
	gotoxy(49, 9);
	printf("88     \"8b");
	gotoxy(49, 10);
	printf("88     \,8P");
	gotoxy(49, 11);
	printf("88aaaa8P'");
	gotoxy(49, 12);
	printf("88����88'");
	textcolor(0, 10);
	gotoxy(49, 13);
	printf("88    '8b");
	gotoxy(49, 14);
	printf("88     '8b.");

	while (1)
	{
		if (kbhit() == 1) {
			ch = getch();
			break;
		}
		gotoxy(32, 21);
		textcolor(5, 14);
		printf(" PRESS ANY KEY! ");
		Sleep(500);
		gotoxy(32, 21);
		textcolor(9, 12);
		printf(" PRESS ANY KEY! ");
		Sleep(500);
	}
	textcolor(BLACK, GREEN2);
}

void show_hp(int hp)  //hp�� ���������� �ʱⰪ�� 5, ��ֹ��� �ε����� --hp; ���ؼ� ��Ʈ �� �� ����
{
	int i, j;
	gotoxy(85, 16);
	printf("ENERGY");
	gotoxy(85, 18);
	for (i = hp; i > 0; i--) {
		printf("�� ");
	}
	for (j = 5 - hp; j > 0; j--) {
		printf("�� ");
	}
}

void information(int n)  //
{
	gotoxy(88, 21);
	printf("- CAR info -");
	gotoxy(85, 22);
	printf("Model:Tesla model S");
	gotoxy(85, 23);
	printf("Max speed : 322km");
	gotoxy(85, 24);
	printf("remaining fuel: 85%");
	gotoxy(85, 25);
	if (n % 2 == 0)
		printf(" �ý��� �̻� ����.");
	else {
		gotoxy(85, 25);
		textcolor(0, 4);
		printf(" �ڵ��� ���峵�� !");
	}
	textcolor(0, 10);
}

void car(int x)
{
	int y = 22;
	gotoxy(x, y);
	printf(" ��");
	gotoxy(x - 1, y + 1);
	printf("�ġ��");
	gotoxy(x, y + 2);
	printf(" ��");
	gotoxy(x - 1, y + 3);
	printf("�ġ��");
}

void putcar(int x, int y)
{
	gotoxy(x + 1, y);
	printf("��");
	gotoxy(x - 1, y + 1);
	printf("�ġ��");
	gotoxy(x + 1, y + 2);
	printf("��");
	gotoxy(x - 1, y + 3);
	printf("�ġ��");
}

void erasecar(int x, int y)
{
	gotoxy(x + 1, y);
	printf("  ");
	gotoxy(x - 1, y + 1);
	printf("    ");
	gotoxy(x, y + 1);
	printf("  ");
	gotoxy(x + 1, y + 1);
	printf("    ");
	gotoxy(x + 1, y + 2);
	printf("  ");
	gotoxy(x - 1, y + 3);
	printf("    ");
	gotoxy(x, y + 3);
	printf("  ");
	gotoxy(x + 1, y + 3);
	printf("    ");
}

void player(unsigned char ch, int D)  //D�� ¦���� �������� Ȧ���� �ݴ�� ����
{
	static int oldx = 40, oldy = 22, newx = 40, newy = 22;
	int move_flag = 0;
	static int called = 0;
	static unsigned char last_ch = 0;

	if (called == 0) { // ���� ��ġ
		removeCursor();
		putcar(oldx, oldy);
		called = 1;
	}
	if (keep_moving && ch == 0)
		ch = last_ch;
	last_ch = ch;



	if (D % 2 == 0) {
		switch (ch) {
		case LEFT:
			if (oldx > 0) {
				newx = oldx - 2;    //��ĭ�� ������
				if (newx < 12) {  //���θ� �Ѿ�� �������� ���ϰ� ü���� �ϳ� ����.
					show_hp(--hp);
					newx = oldx;
				}
			}

			move_flag = 1;
			break;
		case RIGHT:
			if (oldx < 78) {
				newx = oldx + 2;    //��ĭ��������
				if (newx > 69) {
					show_hp(--hp);
					newx = oldx;
				}
			}

			move_flag = 1;
			break;
		}
	}
	else {
		switch (ch) {
		case RIGHT:
			if (oldx > 0) {
				newx = oldx - 2;    //��ĭ�� ������
				if (newx < 12) {  //���θ� �Ѿ�� �������� ���ϰ� ü���� �ϳ� ����.
					show_hp(--hp);
					newx = oldx;
				}
			}

			move_flag = 1;
			break;
		case LEFT:
			if (oldx < 78) {
				newx = oldx + 2;    //��ĭ��������
				if (newx > 69) {
					show_hp(--hp);
					newx = oldx;
				}
			}

			move_flag = 1;
			break;
		}
	}



	if (move_flag) {
		erasecar(oldx, oldy); // ������ ��ġ�� * �� �����
		putcar(newx, newy); // ���ο� ��ġ���� * �� ǥ���Ѵ�.
		oldx = newx; // ������ ��ġ�� ����Ѵ�.
		oldy = newy;
		carX = newx;
		carY = newy;
	}
}


int check(int carx, int cary, int objectx, int objecty)  //�浹ó��
{

	if (objectx >= carx - 1 && objectx <= carx + 4 && cary == objecty)
	{
		return 1;  //�浹 ���� �� 1 return
	}

	return 0;  //�浹���� �ʴ� ���
}

void object(int x, int y)    //��ֹ� ��������
{
	if (y < 27) {
		textcolor(0, 4);
		putobj(x, y + 1);
		textcolor(0, 10);
		eraseobj(x, y);
	}
	else
		eraseobj(x, y - 2);

}

void putobj(int x, int y)   //��ֹ� ����
{
	gotoxy(x, y);
	putchar('X');
}

void eraseobj(int x, int y)    //��ֹ� �����
{
	gotoxy(x, y);
	putchar(BLANK);
}


void item1(int x, int y)    //��Ʈ ������
{
	if (y < 27) {
		textcolor(0, 13);
		putitem1(x, y + 1);
		textcolor(0, 10);
		eraseitem1(x, y);
	}
	else
		eraseitem1(x, y - 2);
}

void putitem1(int x, int y)
{
	gotoxy(x, y);
	putchar('@');
}

void eraseitem1(int x, int y)
{
	gotoxy(x, y);
	putchar(BLANK);
}

void item2(int x, int y)   //���� ��Ƣ�� ������
{
	if (y < 27) {
		textcolor(0, 9);
		putitem2(x, y + 1);
		textcolor(0, 10);
		eraseitem2(x, y);
	}
	else
		eraseitem2(x, y - 2);
}

void putitem2(int x, int y)
{
	gotoxy(x, y);
	putchar('S');
}

void eraseitem2(int x, int y)
{
	gotoxy(x, y);
	putchar(BLANK);
}


void item3(int x, int y)   //����Ű �Ųٷ��ϱ�
{
	if (y < 27) {
		textcolor(0, 14);
		putitem3(x, y + 1);
		textcolor(0, 10);
		eraseitem3(x, y);
	}
	else
		eraseitem3(x, y - 2);
}

void putitem3(int x, int y)
{
	gotoxy(x, y);
	putchar('D');
}

void eraseitem3(int x, int y)
{
	gotoxy(x, y);
	putchar(BLANK);
}
