#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>

#define kbhit _kbhit
#define getch _getch

#define Width 50 //콘솔창 가로 길이
#define Height 30 //콘솔창 세로 길이

#define _Width 30 // 게임화면 가로 길이 
#define _Height 20 // 게임화면 세로 길이

int mino[6][3][3] = {
	{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, // I
	{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}, // O
	{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, // T
	{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, // L
	{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, // J
	{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, // S
	{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}}, // Z
};

void gotoxy(int x, int y) { //커서 이동 함수 
   COORD pos = {x, y};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD getxy() {
    COORD Cur;
    CONSOLE_SCREEN_BUFFER_INFO a;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&a);
    Cur.X = a.dwCursorPosition.X;
    Cur.Y = a.dwCursorPosition.Y;
    return Cur;
}

void Console_Size(int w, int h) { //콘솔 사이즈 설정
   char temp[50];
   sprintf(temp, "Mode con cols=%d lines=%d", w, h);
   system(temp);
}

void CursorView(char show) { //커서숨기기 0이면 숨김, 1이면 보임
   HANDLE hConsole;
   CONSOLE_CURSOR_INFO ConsoleCursor;

   hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

   ConsoleCursor.bVisible = show;
   ConsoleCursor.dwSize = 1;

   SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void DesignStartScreen(void) { //시작화면 설정
   system("cls");
   for (int i = 1; i <= Height; i++) {
      for (int j = 1; j <= Width; j++) {
         if (i == 1 || i == Height)
            printf("=");
         else if (j == 1 || j == Width)
            printf("|");
         else
            printf(" ");
      }
   }
}
void DesignGameScreen(void) { //게임화면 설정
   system("cls");
   for (int i = 1; i <= _Height; i++) {
      for (int j = 1; j <= _Width; j++) {
         if (i == 1 || i == _Height)
            printf("=");
         else if (j == 1 || j == 11 || j == _Width)
            printf("|");
         else
            printf(" ");
      }
   }
}

void Main_Start() {
   DesignStartScreen();
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
   gotoxy(Width / 2 - 5, Height / 2);
   printf("My Tetris");
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
   gotoxy(Width / 2 - 8, Height / 2 + 4);
   //인트로-

   while(1) {
      printf("아무 키나 누르세요!");
      Sleep(500);
      if (kbhit()) break;
      gotoxy(Width / 2 - 8, Height / 2 + 4);
      printf("                   ");
      Sleep(500);
      gotoxy(Width / 2 - 8, Height / 2 + 4);
   }
}

int Main_Menu() {
   DesignStartScreen();
   gotoxy(Width / 2 - 5, Height / 2 - 6);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
   printf("If You Can");
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

   gotoxy(Width / 2 - 4, Height / 2);
   printf("게임 시작");
   gotoxy(Width / 2 - 5, Height / 2 + 2);
   printf("플레이 방법");
   gotoxy(Width / 2 - 3, Height / 2 + 4);
   printf("제작자");
   gotoxy(Width / 2 - 4, Height / 2 + 6);
   printf("게임 종료");
   gotoxy(Width / 2 + 8, Height / 2);
   printf("◀");
   Sleep(100);
   
   int return_n = 0;
   while (1) { //키보드 움직임
      int key;
      if (kbhit()) {
         key = getch();
         if (key == 224 || key == 0) {
            key = getch();
            switch (key) {
            case 72: //상
               gotoxy(Width / 2 + 8, Height / 2 + return_n);
               printf("  ");
               return_n -= 2;
               if (return_n < 0) return_n = 6;
               gotoxy(Width / 2 + 8, Height / 2 + return_n);
               printf("◀");
               break;
            case 80: //하
               gotoxy(Width / 2 + 8, Height / 2 + return_n);
               printf("  ");
               return_n += 2;
               if (return_n > 6) return_n = 0;
               gotoxy(Width / 2 + 8, Height / 2 + return_n);
               printf("◀");
               break;
            default:
               break;
            }
         }
         else
            if (key == 13)//엔터
               return return_n/2 + 1;
      }
   }
}

void print_mino(int _x, int _y, int mino[3][3]) {
	int x = _x;
	int y = _y;
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (mino[i][j] == 1)
				printf("%c", '#');
			else
				printf("%c", ' ');
		}
		gotoxy(x, y+1);
	}
	gotoxy(_x, _y);
}

void selector(int* order) {
	for (int i = 0; i < 7; i++) {
		int temp = rand()%7+1;
		for (int j = 0; j < 7 && order[j] != temp; j++);
		if (j < 7) i--;
		else order[i] = temp;
	}
}

int Main_Game() {
	Console_Size(_Width, _Height);
	DesignGameScreen();
	
	int return_n = 0;
	int order[7] = {-1,};
	
	
	while(1) {
		int x = 6;
		int y = 1;
		selector(order);
		for (int i = 0; i < 7; i++) {
			print_mino(x, y++, mino[order[i]])
			Sleep(500);
			
			
			if (kbhit()) {
        	int temp = getch();
        	if (temp == 27) // ESC 
        		break;
    	}
		
		}
		
      	
   }
   
   
	Console_Size(Width, Height);
	return return_n;
}

void Main_Control() {
   DesignStartScreen();
   gotoxy(Width/2 - 4, Height/2 - 4);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
   printf("min49590");
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
   
   while(1) {
      if (kbhit()) {
         int temp = getch();
         if (temp == 27) // ESC 
            break;
      }
      gotoxy(Width/2 - 6, Height/2 + 8);
      printf("ESC: 뒤로가기");
      Sleep(500);
      if (kbhit()) {
         int temp = getch();
         if (temp == 27) // ESC
            break;
      }
      gotoxy(Width/2 - 6, Height/2 + 8);
      printf("            ");
      Sleep(500);
   }
}

void Main_Developer() {
   DesignStartScreen();
   gotoxy(Width/2 - 4, Height/2 - 4);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
   printf("min49590");
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
   
   while(1) {
      if (kbhit()) {
         int temp = getch();
         if (temp == 27) // ESC 
            break;
      }
      gotoxy(Width/2 - 6, Height/2 + 8);
      printf("ESC: 뒤로가기");
      Sleep(500);
      if (kbhit()) {
         int temp = getch();
         if (temp == 27) // ESC
            break;
      }
      gotoxy(Width/2 - 6, Height/2 + 8);
      printf("            ");
      Sleep(500);
   }
}

void Main_End() {
   DesignStartScreen();
   
   for (int i = 3; i >= 0; i--) {
      if (i < 3)
         Sleep(1000);
      gotoxy(Width/2 - 12, Height/2);
      printf("게임이 %d 초 후 종료됩니다.", i);
   }
   Sleep(100);
   system("cls");
}

int main(void) { // main
   SetConsoleTitle("My Tetris");
   Console_Size(Width, Height);
   CursorView(0);
   srand(time(NULL));
   
   Main_Start();
   int return_n = 0;
   while(1) {
      return_n = Main_Menu();
      if (return_n == 4) { // 게잉 종료 
         Main_End();
         break;
      }
      else if (return_n == 3) { // 게임 개발자 
         Main_Developer();
      }
      else if (return_n == 2) { // 게임 방법 
         Main_Control();
      }
      else if (return_n == 1) { // 게임 
         if (Main_Game() == 1) { // 게임 내에서 게임 종료 
            Main_End();
            break;
         }
      }
   }
   
   return 0;
}
