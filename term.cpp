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
int keep_moving = 0; // 한칸씩 이동

void removeCursor(void);   //커서 지우는 함수
void showCursor(void);     //커서 드러내는 함수
void gotoxy(int x, int y);     //x,y축으로 이동
void textcolor(int fg_color, int bg_color);     //텍스트와 텍스트배경 컬러
void cls(int bg_color, int text_color);     //배경 색 설정
void draw_box2(int x1, int y1, int x2, int y2);     //화면박스
void draw_box2_fill(int x1, int y1, int x2, int y2, int color);   //화면 박스 색채우기
void clean(void);     //화면 박스들 뺴고 다 지우는 함수
void road(void);      //도로
void road2(void);     //도로2
void background_intro(void);     //배경 구름
void print_gamename(void);   //우측 상단 게임이름이랑 제작자
void howtoplay(void);
void intro(void);            //인트로 car 
void show_hp(int hp);        //남은 체력 표시
void information(int n);   //중요하지 않은 정보(꾸미기용)
void car(int x);          //3x4 사이즈의 차
void player(unsigned char ch, int D);    //플레이어 방향키로 움직이게하는 코드
void putcar(int x, int y);     //차를 그리고
void erasecar(int x, int y);     //지우고
int check(int carx, int cary, int objectx, int objecty);   //충돌처리
void object(int x, int y);   // 장애물
void putobj(int x, int y);
void eraseobj(int x, int y);
void item1(int x, int y);    // 하트 아이템
void putitem1(int x, int y);
void eraseitem1(int x, int y);
void item2(int x, int y);   //점수 뻥튀기 아이템
void putitem2(int x, int y);
void eraseitem2(int x, int y);
void item3(int x, int y);    //속도 감소 아이템
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
	//  <초기화면>
	removeCursor(); // 커서를 안보이게 한다
	cls(GREEN2, BLACK);
	background_intro();
	textcolor(BLACK, GREEN2);
	draw_box2(0, 0, 79, 28);
	draw_box2(81, 0, 106, 28);
	draw_box2(83, 1, 104, 4);  // 게임이름과 제작자(나) 프린트
	print_gamename();
	draw_box2(83, 5, 104, 9);  // 플레이어 이름칸
	draw_box2(83, 10, 104, 14);  //스코어 표기칸
	draw_box2(83, 15, 104, 19); //남은 체력 수치화(숫자 or 체력바)
	show_hp(hp);
	draw_box2(83, 20, 104, 27);  //차의 속도와 각종 정보들 information 함수
	draw_box2(108, 1, 126, 12);
	howtoplay();
	information(D);
	intro();

	gotoxy(26, 17);
	printf("player의 이름을 입력하세요.");
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


	//  <인트로 끝> 
	clean();  //다지워버리는 함수 
	//인트로를 지우기 위해서 다 지워버리고 새로 박스와 게임 틀 작성
	cls(GREEN2, BLACK);
	textcolor(BLACK, GREEN2);
	draw_box2(0, 0, 79, 28);
	draw_box2(81, 0, 106, 28);
	draw_box2(83, 1, 104, 4);     // 게임이름과 제작자(나) 프린트
	print_gamename();
	draw_box2(83, 5, 104, 9);     // 플레이어 이름칸
	gotoxy(85, 6);
	printf("player :");
	gotoxy(86, 8);
	printf("%s", name);
	draw_box2(83, 10, 104, 14);   //스코어 표기칸
	show_hp(hp);
	draw_box2(83, 15, 104, 19);   //남은 체력 수치화(숫자 or 체력바)
	draw_box2(83, 20, 104, 27);   //차의 속도와 각종 정보들? information 함수
	information(D);
	draw_box2(108, 1, 126, 12);
	howtoplay();
	putcar(40, 22);

	while (1) {
		road();
		road2();
		if (hp <= 0)  //hp가 0이하가 되면 게임 오버
		{
			clean();
			gotoxy(40, 15);
			printf("game over!");
			gotoxy(36, 17);
			printf("%s score is %d!", name, score - 3);
			gotoxy(36, 19);
			//끝
			gotoxy(32, 21);
			printf("종료하려면 ESC를 입력하세요!");
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

		//점수
		gotoxy(85, 11);
		printf("score : %d", score);
		score += 3;



		//장애물
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

		// 일정 주기마다 장애물의 랜덤 개수 설정
		if (end > 28)
		{
			objNum = 4 + rand() % 5;
			end = 0;
			// 개수만큼 장애물의 x값을 랜덤을 지정
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


		// 장애물 위치 업데이트
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

		// 내려오는 주기 맞춰주는 변수
		end++;


		// 각 장애물에 대한 충돌처리
		for (int i = 0; i < objNum; i++) {
			if (check(carX, carY, objects[i].x, objects[i].y) == 1) {
				eraseobj(objects[i].x, objects[i].y);
				show_hp(--hp);
			}
		}

		// 아이템1 충돌처리
		for (int i = 0; i < item1Num; i++) {
			if (check(carX, carY, items1[i].x, items1[i].y) == 1) {
				if (hp <= 4) { //hp가 5일땐 더 채워지지 않음.
					show_hp(++hp);  //에너지 회복 아이템
					eraseitem1(items1[i].x, items1[i].y);
				}
			}
		}

		// 아이템2 충돌처리
		for (int i = 0; i < item2Num; i++) {
			if (check(carX, carY, items2[i].x, items2[i].y) == 1) {
				score += 500;  //점수 추가 아이템
				eraseitem2(items2[i].x, items2[i].y);
			}
		}

		// 아이템3 충돌처리 
		for (int i = 0; i < item3Num; i++) {
			if (check(carX, carY, items3[i].x, items3[i].y) == 1) {
				D += 1;  //거꾸로 가게하는 방해 아이템
				eraseitem3(items3[i].x, items3[i].y);
			}
		}
		if (kbhit() == 1) {  // 키보드가 눌려져 있으면
			ch = getch();      // key 값을 읽는다
			if (ch == 27)      // 입력된 키가 ESC이면 TRUE
				break;
			if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
				ch = getch();
				// Player는 방향키로 움직인다.
				switch (ch) {
				case LEFT:
				case RIGHT:
					player(ch, D);
					break;
				default:       // 특수키 이지만 방향키가 아닌 경우
					player(0, D);
				}
			}
			else {
				player(0, D);
			}
		}


		if (end >= 23 && carX >= 9 && carY >= 17)  //장애물에 부딪히면 모양이 망가지는데 다시 그려서 생성
			putcar(carX, carY);

		//점수
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

void removeCursor(void) {  // 커서를 안보이게 한다

	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void showCursor(void) { // 커서를 보이게 한다
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void gotoxy(int x, int y) //내가 원하는 위치로 커서 이동
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);// WIN32API 함수입니다. 이건 알필요 없어요
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
	for (x = x1; x <= x2; x += 2) { // 한글은 2칸씩 차지한다.
		gotoxy(x, y1);
		printf("%s", "─"); // ㅂ 누르고 한자키 누르고 선택
		gotoxy(x, y2);
		printf("%s", "─");
	}
	for (y = y1; y <= y2; y++) {
		gotoxy(x1, y);
		printf("%s", "│");
		gotoxy(x2, y);
		printf("%s", "│");
	}
	gotoxy(x1, y1); printf("┌");
	gotoxy(x1, y2); printf("└");
	gotoxy(x2, y1); printf("┐");
	gotoxy(x2, y2); printf("┘");
}

void draw_box2_fill(int x1, int y1, int x2, int y2, int color)
{
	int x, y;

	textcolor(BLACK, WHITE);
	for (x = x1; x <= x2; x += 2) { // 한글은 2칸씩 차지한다.
		gotoxy(x, y1);
		printf("%s", "─"); // ㅂ 누르고 한자키 누르고 선택
		gotoxy(x, y2);
		printf("%s", "─");
	}
	for (y = y1; y <= y2; y++) {
		gotoxy(x1, y);
		printf("%s", "│");
		gotoxy(x2, y);
		printf("%s", "│");
	}
	gotoxy(x1, y1); printf("┌");
	gotoxy(x1, y2); printf("└");
	gotoxy(x2, y1); printf("┐");
	gotoxy(x2, y2); printf("┘");
	//getch();
	for (y = y1 + 1; y < y2; y++) {
		for (x = x1 + 2; x < x2; x++) {
			textcolor(color, color);
			gotoxy(x, y);
			printf(" ");
		}
	}

}

void clean(void) //화면 싹 날리는 함수
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

void road(void)  //가운데 길 표현
{
	int y;
	for (y = 1; y <= 27; y++) {
		gotoxy(12, y);
		printf("%s", "│");
		gotoxy(70, y);
		printf("%s", "│");
	}
}
void road2(void)  //가운데 길 표현2
{
	int y;
	for (y = 1; y <= 27; y++) {
		gotoxy(13, y);
		printf("%s", "│");
		gotoxy(71, y);
		printf("%s", "│");
	}
}

void background_intro(void)  //스테이지 1 초원 배경
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
	textcolor(15, 15);  //구름
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
	printf(" ← :왼쪽 이동");
	gotoxy(109, 3);
	printf(" → :오른쪽 이동");
	gotoxy(109, 5);
	printf("  *방해를 하는*");
	gotoxy(110, 6);
	textcolor(0, 4);
	printf("X: 장애물");
	gotoxy(110, 7);
	textcolor(0, 14);
	printf("D: 반대로 주행");
	textcolor(0, 10);
	gotoxy(109, 9);
	printf("  *도움이 되는*");
	gotoxy(110, 10);
	textcolor(0, 9);
	printf("S: 500점 추가");
	gotoxy(110, 11);
	textcolor(0, 13);
	printf("@: 에너지 1 회복");
	textcolor(0, 10);

}

void print_gamename(void)
{
	gotoxy(85, 2);
	printf("S1mple Car Racing");
	gotoxy(85, 3);
	printf("제작자 : movinggun");
}

void intro(void)  //CAR 인트로 , press start any key 
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
	printf("88￣￣88'");
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

void show_hp(int hp)  //hp는 전역변수로 초기값은 5, 장애물과 부딪힐시 --hp; 통해서 하트 한 개 감소
{
	int i, j;
	gotoxy(85, 16);
	printf("ENERGY");
	gotoxy(85, 18);
	for (i = hp; i > 0; i--) {
		printf("♥ ");
	}
	for (j = 5 - hp; j > 0; j--) {
		printf("♡ ");
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
		printf(" 시스템 이상 없음.");
	else {
		gotoxy(85, 25);
		textcolor(0, 4);
		printf(" 핸들이 고장났어 !");
	}
	textcolor(0, 10);
}

void car(int x)
{
	int y = 22;
	gotoxy(x, y);
	printf(" ▣");
	gotoxy(x - 1, y + 1);
	printf("◐■◑");
	gotoxy(x, y + 2);
	printf(" ▥");
	gotoxy(x - 1, y + 3);
	printf("◐■◑");
}

void putcar(int x, int y)
{
	gotoxy(x + 1, y);
	printf("▣");
	gotoxy(x - 1, y + 1);
	printf("◐■◑");
	gotoxy(x + 1, y + 2);
	printf("▥");
	gotoxy(x - 1, y + 3);
	printf("◐■◑");
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

void player(unsigned char ch, int D)  //D가 짝수면 정상주행 홀수면 반대로 주행
{
	static int oldx = 40, oldy = 22, newx = 40, newy = 22;
	int move_flag = 0;
	static int called = 0;
	static unsigned char last_ch = 0;

	if (called == 0) { // 최초 위치
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
				newx = oldx - 2;    //한칸씩 움직임
				if (newx < 12) {  //도로를 넘어가면 움직이지 못하고 체력이 하나 까임.
					show_hp(--hp);
					newx = oldx;
				}
			}

			move_flag = 1;
			break;
		case RIGHT:
			if (oldx < 78) {
				newx = oldx + 2;    //한칸씩움직임
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
				newx = oldx - 2;    //한칸씩 움직임
				if (newx < 12) {  //도로를 넘어가면 움직이지 못하고 체력이 하나 까임.
					show_hp(--hp);
					newx = oldx;
				}
			}

			move_flag = 1;
			break;
		case LEFT:
			if (oldx < 78) {
				newx = oldx + 2;    //한칸씩움직임
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
		erasecar(oldx, oldy); // 마지막 위치의 * 를 지우고
		putcar(newx, newy); // 새로운 위치에서 * 를 표시한다.
		oldx = newx; // 마지막 위치를 기억한다.
		oldy = newy;
		carX = newx;
		carY = newy;
	}
}


int check(int carx, int cary, int objectx, int objecty)  //충돌처리
{

	if (objectx >= carx - 1 && objectx <= carx + 4 && cary == objecty)
	{
		return 1;  //충돌 했을 때 1 return
	}

	return 0;  //충돌하지 않는 경우
}

void object(int x, int y)    //장애물 떨어지게
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

void putobj(int x, int y)   //장애물 생성
{
	gotoxy(x, y);
	putchar('X');
}

void eraseobj(int x, int y)    //장애물 지우기
{
	gotoxy(x, y);
	putchar(BLANK);
}


void item1(int x, int y)    //하트 아이템
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

void item2(int x, int y)   //점수 뻥튀기 아이템
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


void item3(int x, int y)   //방향키 거꾸로하기
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
