#include "pch.h"
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include "WinConsoleTools.h"

typedef struct {
	int x;
	int y;
} coord;

void printAtPos(coord pos, char c, char **map) // tlac a ulozenie do mapy na urcitu poziciu 
{
	setCursorPosition(pos.x, pos.y);
	putchar(c);
	map[pos.y][pos.x] = c;
}

void generateFood(coord* food, int w, int h, char **map) // vygenerovanie jedla na nahodnu poziciu mimo hada
{
	do
	{
		food->y = rand() % h;
		food->x = rand() % w;
	} while (map[food->y][food->x] != ' ');
	printAtPos(*food, '*', map);
}


void gameOver(int *game, int score)
{
	Sleep(1000);
	*game = 0;
	system("cls");
	printf("GAME OVER\n\nScore: %d\n\n", score);
	getchar();
}

void updateTitle(unsigned int score)
{
	wchar_t title[20];
	swprintf(title, 20, L"HAD | Score: %d", score);
	SetConsoleTitle(title);
}

unsigned int newGame(int width, int height, char **map, int speed)
{
	int game = 1, paused = 0;
	int len = 1;
	coord food;
	int dirX = 0, dirY = 0;
	unsigned int score = 0;

	coord cur, prev;
	coord *snake = (coord*)malloc(sizeof(coord));

	updateTitle(score);

	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			setCursorPosition(j, i);
			putchar(map[i][j]);
		}
	}

	// vygenerovanie pociatocnej pozicie hlavy hada
	srand((unsigned)time(NULL));
	do
	{
		snake[0].y = rand() % height;
		snake[0].x = rand() % width;
	} while (map[snake[0].y][snake[0].x] == 'X');

	// vygenerovanie pociatocneho smeru - x/y je nahodne, +/- sa urci podla toho, ktora stena je dalej
	if (rand() % 2)
		dirX = (snake[0].x < width / 2) ? 1 : -1;
	else
		dirY = (snake[0].y < height / 2) ? 1 : -1;

	printAtPos(snake[0], 'o', map);
	generateFood(&food, width, height, map);

	while (game)
	{
		if (_kbhit())
		{
			char input = _getwch();
			if (input == -32 || input == 0 || input == 0xE0)
				input = _getwch();

			switch (input)
			{
			case 'w':
			case 'W':
			case 72:
				if (dirY != 1)
					dirY = -1;
				dirX = 0;
				break;
			case 's':
			case 'S':
			case 80:
				if (dirY != -1)
					dirY = 1;
				dirX = 0;
				break;
			case 'a':
			case 'A':
			case 75:
				dirY = 0;
				if (dirX != 1)
					dirX = -1;
				break;
			case 'd':
			case 'D':
			case 77:
				dirY = 0;
				if (dirX != -1)
					dirX = 1;
				break;
			case 27:
			case 'p':
				SetConsoleTitle(L"HAD | PAUZA");
				_getwch();
				updateTitle(score);
				break;
			}
		}

		prev = snake[0]; // ulozenie predchodzej pozicie hlavy

		// kontrola, ci je pred hadom prekazka
		if ((snake[0].x + dirX > width - 1 || snake[0].x + dirX < 0 || snake[0].y + dirY > height - 1 || snake[0].y + dirY < 0) || map[snake[0].y + dirY][snake[0].x + dirX] == 'o' || map[snake[0].y + dirY][snake[0].x + dirX] == 'X')
		{
			gameOver(&game, score);
			return score;
		}
		else // pohyb hlavy hada
		{
			printAtPos(snake[0], ' ', map);
			snake[0].y += dirY;
			snake[0].x += dirX;
			printAtPos(snake[0], 'o', map);
		}

		for (int i = 1; i < len; ++i) // pohyb chvosta (presunutie kazdeho clanku na predchodziu poziciu predchodzieho clanku)
		{
			cur = snake[i];
			printAtPos(snake[i], ' ', map);
			snake[i] = prev;
			printAtPos(snake[i], 'o', map);
			prev = cur;
		}

		if (snake[0].y == food.y && snake[0].x == food.x) // zjedenie jedla
		{
			score += 5;
			updateTitle(score);

			snake = (coord*)realloc(snake, ++len * sizeof(coord));
			snake[len - 1] = prev;

			generateFood(&food, width, height, map);
		}

		if (len < 3) // pociatocny narast na tri clanky
		{
			snake = (coord*)realloc(snake, ++len * sizeof(coord));
			snake[len - 1] = prev;
		}
		else // delay
			Sleep(350 / speed);
	}

	return score;
}