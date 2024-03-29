// had-test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#include "WinConsoleTools.h"
#include "Matrix.h"
#include "Game.h"

#define HEIGHT 40
#define WIDTH 70
#define MAX_NAME_LENGTH 20
#define MAX_SPEED 10

int main()
{
	SetConsoleTitle(L"HAD");
	hideCursor();

	char **map;
	int m, n; // rozmery hracieho pola

	FILE *mapFile;
	fopen_s(&mapFile, "map.txt", "r");

	if (mapFile != NULL)
	{
		char c; 
		n = -2, m = 0; // spocitanie rozmerov
		while ((c = getc(mapFile)) != '\n') // spocitanie sirky (znaky v prvom riadku -2 znaky ohranicenia)
		{
			++n;
		}
		while ((c = getc(mapFile)) != EOF) // spocitanie vysky (pocet \n - netreba odcitavat riadky ohranicenia - jeden \n uz bol precitany, v poslednom riadku \n nie je)
		{	
			if (c == '\n')
				++m;
		}
		if (m > 20 && n > 20) // rozmery musia byt aspon 20x20
		{					  // nacitanie mapy
			map = createMatrix(m, n);
			setConsoleSize(n, m);
			fseek(mapFile, 0, SEEK_SET); // vratenie na zaciatok suboru
			int i = -1; // vyska - prvy riadok sa do vysky nepocita
			int j = 0;  // sirka
			while ((c = getc(mapFile)) != EOF)
			{
				if (c != '#') // znaky ohranicenia su ignorovane
				{
					if (c == '\n')
					{
						++i;
						j = 0;
					}
					else
					{
						map[i][j++] = c;
					}
				}
			}
			printf("Bola nacitana mapa zo suboru map.txt\n");
		}
		else
		{
			m = HEIGHT;
			n = WIDTH;
			setConsoleSize(n, m);
			map = createMatrix(m, n);
			initMatrix(map, m, n);
			printf("Subor map.txt je neplatny. Mapa nebola nacitana.\n");
		}
		fclose(mapFile);
	}
	else
	{
		m = HEIGHT;
		n = WIDTH;
		setConsoleSize(n, m);
		map = createMatrix(m, n);
		initMatrix(map, m, n);
	}

	struct player {
		char name[MAX_NAME_LENGTH];
		unsigned int score;
	};

	FILE *hsFile;
	fopen_s(&hsFile, "highscores.txt", "r");
	struct player topPlayers[10];
	for (int i = 0; i < 10; ++i)
		topPlayers[i].score = 0;

	if (hsFile != NULL) // precitanie skore zo suboru
	{
		int i = 0;
		while (!feof(hsFile) && i < 10)
		{
			char buffer[MAX_NAME_LENGTH];
			fscanf_s(hsFile, "%s", buffer, 3);
			fscanf_s(hsFile, "%s", buffer, MAX_NAME_LENGTH);
			fscanf_s(hsFile, "%u", &topPlayers[i].score);
			strcpy_s(topPlayers[i++].name, buffer);
		}
		fclose(hsFile);
	}
	
	int playing = 1;
	while (playing)
	{
		unsigned int score;
		int speed;
		char name[MAX_NAME_LENGTH];

		printf("Meno hraca: ");
		scanf_s("%s", name, MAX_NAME_LENGTH);
		do
		{
			printf("Rychlost (1-%d): ", MAX_SPEED);
			scanf_s("%d", &speed);
		} while (speed > MAX_SPEED || speed < 1);
		for (int i = 3; i >= 0; --i)
		{
			if (i == 0)
				printf("GO!");
			else
				printf("%d...", i);
			Sleep(250);
		}
		system("cls");

		// spustenie hry
		score = newGame(n, m, map, speed);

		// zaradenie skore do tabulky; nulove skore su ignorovane
		for (int i = 0; i < 10; ++i)
		{
			if (score > topPlayers[i].score) // aktualne skore sa vlozi na vhodnu poziciu, mensie skore sa posunu o jednu poziciu dolu
			{
				struct player prev = topPlayers[i];
				topPlayers[i].score = score;
				strcpy_s(topPlayers[i].name, name);
				for (int j = i + 1; j < 10 && prev.score != 0; ++j)
				{
					struct player tmp = topPlayers[j];
					topPlayers[j] = prev;
					prev = tmp;
				}
				break;
			}
		}

		// zapisanie skore do suboru
		if (topPlayers[0].score != 0)
		{
			fopen_s(&hsFile, "highscores.txt", "w");
			for (int i = 0; i < 10 && topPlayers[i].score != 0; ++i)
			{
				fprintf(hsFile, "%2d. %*s %5u\n", i + 1, -MAX_NAME_LENGTH, topPlayers[i].name, topPlayers[i].score);
				printf("%2d. %*s %5u\n", i + 1, -MAX_NAME_LENGTH, topPlayers[i].name, topPlayers[i].score);
			}
			fclose(hsFile);
		}

		printf("\nHrat znova? y/N: ");
		playing = (tolower(getchar()) == 'y') ? 1 : 0;
		system("cls");
	}
}
