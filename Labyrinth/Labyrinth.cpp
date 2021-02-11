#include <iostream>
#include <stdio.h>
#include <conio.h>
#include<stdlib.h>
#include <string>
#include <time.h>
using namespace std;
#define WIDTH 21//幅さ//
#define HEIGHT 21//長さ//
int labyrinth[WIDTH][HEIGHT];//迷宮データを収める二次元配列//
int other, other_2nd;//雑用//
int player_x = 2, player_y = 18;//プレイヤーの初期位置//
int damage;//ダメージの計算//
int Floor = 1;//今のいるフロア//
int Event = 0;//0:移動中　1:戦闘中//
int command = 0;//コマンド入力用//
int turn = 0;//戦闘中　1:主人公のターン 2:魔物のターン//
int monster_number;//魔物の番号//
bool reset = true;//魔物のリセット//
bool position = false;
bool dungeon_maker = true;//迷宮の自動生成とリセット//
int z;
//魔物のデータベース//
struct status {
	char name[16];
	int maxhp;
	int hp;
	int maxmp;
	int mp;
	int atk;
	int def;
};
struct status monster[2]{
"ドロ状な生物",9,9,0,0,12,1,
"大きな蝙蝠",12,12,0,0,15,3
};
#include "Unit.h"
Unit Monster[8];
#include "Dungeon.h"
int main() {
	srand((unsigned int)time(0));
	rand();
	Unit Player;
	Dungeon Labyrinth;
	if (reset) {
		for (other = 0; other < 8; other++) {
			other_2nd = (int)(rand() * 2.0 / (1.0 + RAND_MAX));
			Monster[other].Status_Write(monster[other_2nd].name, &monster[other_2nd].hp, &monster[other_2nd].mp, &monster[other_2nd].maxhp, &monster[other_2nd].maxmp, &monster[other_2nd].atk, &monster[other_2nd].def);
			Monster[other].x = (int)(rand() * 21.0 / (1.0 + RAND_MAX));
			Monster[other].y = (int)(rand() * 21.0 / (1.0 + RAND_MAX));
			while (labyrinth[Monster[other].y][Monster[other].x] != 0 && position == true) {
				for (other_2nd = 0; other_2nd < 8; other_2nd++) {
					if ((Monster[other].x == Monster[other_2nd].x || Monster[other].y == Monster[other_2nd].y) && other != other_2nd)
						position = true;
				}
				Monster[other].x = (int)(rand() * 21.0 / (1.0 + RAND_MAX));
				Monster[other].y = (int)(rand() * 21.0 / (1.0 + RAND_MAX));
			}
		}
		reset = false;
	}
	do {
		system("cls");
		printf("----%s----\n職業:%s\nHP:%3d/%3d\nMP:%3d/%3d\n\n", Player.name, Player.job, Player.hp, Player.maxhp, Player.mp, Player.maxmp);
		printf("謎の地下迷宮B%dF\n", Floor);
		//迷宮生成//
		Labyrinth.Making();
		//迷宮の描画部分//
		Labyrinth.ShowMap();
		cout << endl << endl << "事件：";
		switch (Event) {
		case 0:
			cout << endl << Player.name << "はダンジョンに彷徨っている" << endl << endl;
			cout << "[W][S][A][D]:上下左右の移動";
			switch (_getch()) {
			case 'w':
				Player.Move(&labyrinth[player_y - 1][player_x], &player_y, -1);
				break;
			case 's':
				Player.Move(&labyrinth[player_y + 1][player_x], &player_y, 1);
				break;
			case 'a':
				Player.Move(&labyrinth[player_y][player_x - 1], &player_x, -1);
				break;
			case 'd':
				Player.Move(&labyrinth[player_y][player_x + 1], &player_x, +1);
				break;
			}
			if (player_y == Monster[0].y && player_x == Monster[0].x)
				Event = 1;
			if (Event == 0) {
				for (other_2nd = 0; other_2nd < 8; other_2nd++) {
					Monster[other_2nd].Move_AI();
				}
			}
			for (other = 0; other < 8; other++) {
				if (player_y == Monster[other].y && player_x == Monster[other].x) {
					Event = 1;
					monster_number = other;
				}
			}
			break;
		case 1:
			cout << endl << "魔物に遭遇した" << endl;
			cout << endl << "敵：" << Monster[monster_number].name << endl;
			if (turn == 0) {
				cout << "[1]攻撃" << endl;
				switch (_getch()) {
				case '1':
					command = 1;
					turn = 1;
					break;
					break;
				}
			}
			else if (turn == 1) {
				switch (command) {
				case 1:
					Player.Attack(Monster[monster_number].name, &Monster[monster_number].hp, &Monster[monster_number].mp, &damage);
					if (_getch())
						turn = 2;
					break;
				}
			}
			else if (turn == 2 && Monster[monster_number].hp > 0) {
				Monster[monster_number].Attack(Player.name, &Player.hp, &Player.mp, &damage);
				if (_getch())
					turn = 0;
			}
			if (Monster[monster_number].hp <= 0) {
				Player.Victory(Monster[monster_number].name);
				Monster[monster_number].x = 22;
				Monster[monster_number].y = 22;
				if (_getch())
					Event = 0;
				turn = 0;
			}
		}
	} while (Floor < 21);
	cout << endl << "YOU WIN";
	cin >> z;
}