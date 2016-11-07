/*
========================================================================
======================================================================
* Name
: 2048.c
* Author
: Aarati ganesh salave (S.Y.Btech in Computer Engineering from CoEP)
* Description : Console version of the game "2048" for GNU/Linux
* Copyright (C) Aarati salave
* ID : aaratisalave@gmail.com
*
* This program is free software; you can redistribute it and/or modify it
* under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2.1 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this program; if not, write to the Free Software Foundation,
* Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
========================================================================
======================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "project.h"


//print the game board
void print(int tiles[SIZE][SIZE]) {
	int c, d;
	printf("\033[H");
	printf("4 - Left, 8 - Up, 6 - Right, 5 - Down  and Press Enter or  Ctrl + Z to Quit\n\n");
	printf("Score : %d pts\n\n", score);
	d = 0;
	printf("****************************\n");
	while(d < SIZE){
		printf("\n");
		c = 0;
		while(c < SIZE) {
			if (tiles[c][d] != 0) {
				char s[8];
				snprintf(s ,8 ,"%u" ,(int)1<<tiles[c][d]);
				int t = 7 - strlen(s);
				printf("%*s%s%*s", t - t/2,"", s, t/2, "");
			} else {
				printf("   -   ");
			}
			c++;
		}
		printf("\n");
		printf("\n");
		d++;
	}
	printf("****************************\n");
	printf("\n");

} 



int searchTarget(int array[SIZE], int a, int stop) {
	int p;
	if (a == 0) { //the position is already on the first, don't evaluate
		return a;
	}
	p = a - 1;
	while (p >= 0) {
		if (array[p] != 0) {
			if (array[p] != array[a]) { // merge is not possible, take next position
				return p + 1;
			}
			return p;
		}
		else { // we should not slide further, return this one
			if (p == stop) {
				return p;
			}
		}
		p--;
	}
	return a;
}
// add the same number 
int combine(int array[SIZE]) {
	int flag = 0;
	int a ,p , stop = 0;
	a = 0;
	while (a < SIZE) {
		if (array[a] != 0) {
			p = searchTarget(array, a, stop);// if target is not original position, then move or merge
			if (p != a) {
					// if target is zero, this is a move
				if (array[p] == 0) {
					array[p] = array[a];
				}
				else if (array[p] == array[a]) {
					// merge (increase power of two)
					array[p]++;
					// increase score
					score += (int)1 << array[p];
					// set stop to avoid double merge
					stop = p + 1;
					}
				array[a] = 0;
				flag = 1;
				}
			}
		a++;		
	}
	return flag;
}
//rotate board instead of sliding tiles
void rotateboard(int tiles[SIZE][SIZE]) {
	int i, j, n = SIZE;
	int tp;
	i = 0;
	while (i < n/2) {
		for (j = i; j < n-i-1; j++) {
			tp = tiles[i][j];
			tiles[i][j] = tiles[j][n-i-1];
			tiles[j][n-i-1] = tiles[n-i-1][n-j-1];
			tiles[n-i-1][n-j-1] = tiles[n-j-1][i];
			tiles[n-j-1][i] = tp;
			}
		i++;
	}
}
//to slide up 
int Up(int tiles[SIZE][SIZE]) {
	int flag = 0;
	int a;
	a = 0;
	while (a < SIZE) {
		flag |= combine(tiles[a]);
		a++;
	}
	return flag;
}
//to slide left
//rotate board once addup then again rotateboard trice
int Left(int tiles[SIZE][SIZE]) { 
	int flag;
	rotateboard(tiles);
	flag = Up(tiles);
	rotateboard(tiles);
	rotateboard(tiles);
	rotateboard(tiles);
	return flag;
}
//to slide up
//rotate board twice addup then again rotateboard twice
int Down(int tiles[SIZE][SIZE]) { 
	int flag;
	rotateboard(tiles);
	rotateboard(tiles);
	flag = Up(tiles);
	rotateboard(tiles); 
	rotateboard(tiles);
	return flag;
}
//to slide right
//rotateboard trice add up again rotate rotateboard once
int Right(int tiles[SIZE][SIZE]) {
	int flag;
	rotateboard(tiles);
	rotateboard(tiles);
	rotateboard(tiles);
	flag = Up(tiles);
	rotateboard(tiles); 
	return flag;
}
//to searchpair of same number
int searchPair(int tiles[SIZE][SIZE]) {
	int flag = 0;
	int a, b;
	a = 0;
	while(a < SIZE) {
		for (b = 0; b < SIZE-1; b++) {
			if (tiles[a][b] == tiles[a][b+1])
				return 1;
			}
		a++;
	}
	return flag;
}
//to count empty tiles 
int Empty(int tiles[SIZE][SIZE]) {
	int a, b;
	int count = 0;
	a = 0;
	while (a < SIZE) {
		for (b = 0; b < SIZE; b++) {
			if (tiles[a][b] == 0) {
				count++;
			}
		}
		a++;
	}
	return count;
}
// check for empty slides
// check for search pair
// check all options of slide
int gameOver(int tiles[SIZE][SIZE]) {
	int ended = 1;
	if (Empty(tiles) > 0)
		return 0;
	if (searchPair(tiles))
		return 0;
	rotateboard(tiles);
	if (searchPair(tiles))
		ended = 0;
	rotateboard(tiles);
	rotateboard(tiles);
	rotateboard(tiles);
	return ended;
}
//after sliding titles add random 2 at random position
void add2(int tiles[SIZE][SIZE]) {
	static int initialized = 0;
	int a, b, c, len = 0, n, list[SIZE*SIZE][2];
	if (!initialized) {
		srand(time(NULL));
		initialized = 1;
	}
	a = 0;
	while (a < SIZE) {
		for (b = 0; b < SIZE; b++) {
			if (tiles[a][b] == 0) {
				list[len][0] = a;
				list[len][1] = b;
				len++;
			}
		}
		a++;	
	}
	if (len > 0) {
		c = rand() % len;
		a = list[c][0];
		b = list[c][1];
		n = (rand() % 10) / 9+1;
		tiles[a][b] = n;
	}
}
//initialize board
void tinit(int tiles[SIZE][SIZE]) {
	int a, b;
	a = 0;
	while (a < SIZE) {
		for (b = 0; b < SIZE; b++) {
			tiles[a][b] = 0;
		}
		a++;
	}
	add2(tiles);
	add2(tiles);
	print(tiles);
	score = 0;
}
int main() {
	int tiles[SIZE][SIZE];
	char c;
	int flag;
	printf("\033[?25l\033[2J");
	tinit(tiles);
	while (1) {
		//printf("\n");
		scanf("%c", &c);
		switch(c) {
			case '4':
			// '4' key
				flag = Left(tiles);
				break;
			case '6':
			// '6' key
				flag = Right(tiles);
				break;
			case '8':
			// '8' key
				flag = Up(tiles);
				break;
			case '5':
			// '5' key
				flag = Down(tiles);
				break;
			default:
				flag = 0;
				break;
			}
			if (flag) {
				print(tiles);
				add2(tiles);
				print(tiles);
				if (gameOver(tiles)) {
					printf("GAME OVER");
					break;
				}
			}	
		}
	printf("\033[?25h\033[m");
	return 0;
}

