#pragma once
class Dungeon {
public:
	bool change = true;
	bool setting = true;
	int map_x = 0, map_y = 0;//–À‹{•`‰æ—p//
	int news = 3;//ª:0 «:1 ©:2 ¨:3//
	int dm_x = 1, dm_y = 1;
	int complexity = 4000;
	int miss = 0;
	void Making();
	void ShowMap();
};
void Dungeon::Making() {
	if (dungeon_maker) {
		//–À‹{‰Šú‰»//
		for (other = 0; other < WIDTH; other++)
			for (other_2nd = 0; other_2nd < HEIGHT; other_2nd++)
				labyrinth[other][other_2nd] = 1;
		int dm_x = (int)(rand() * ((WIDTH - 1) / 2) / (1.0 + RAND_MAX)) * 2 + 1, dm_y = (int)(rand() * ((HEIGHT - 1) / 2) / (1.0 + RAND_MAX)) * 2 + 1;
		player_x = dm_x;
		player_y = dm_y;
		for (other = 0; other < complexity; other++) {
			while (change == true) {
				news = (int)(rand() * 4.0 / (1.0 + RAND_MAX));
				switch (news) {
				case 0:
					if (labyrinth[dm_x][dm_y - 2] == 0 || dm_y - 2 <= 0)
						change = true;
					else {
						change = false;
						miss = 0;
					}
					if (labyrinth[dm_x][dm_y - 1] == 0 && dm_y - 2 >= 0) {
						change = false;
						other -= 1;
						miss += 1;
					}
					break;
				case 1:
					if (labyrinth[dm_x][dm_y + 2] == 0 || dm_y + 2 >= HEIGHT - 1)
						change = true;
					else {
						change = false;
						miss = 0;
					}
					if (labyrinth[dm_x][dm_y + 1] == 0 && dm_y + 2 <= HEIGHT - 1) {
						change = false;
						other -= 1;
						miss += 1;
					}
					break;
				case 2:
					if (labyrinth[dm_x - 2][dm_y] == 0 || dm_x - 2 <= 0)
						change = true;
					else {
						change = false;
						miss = 0;
					}
					if (labyrinth[dm_x - 1][dm_y] == 0 && dm_x - 2 >= 0) {
						change = false;
						other -= 1;
						miss += 1;
					}
					break;
				case 3:
					if (labyrinth[dm_x + 2][dm_y] == 0 || dm_x + 2 >= WIDTH - 1)
						change = true;
					else {
						change = false;
						miss = 0;
					}
					if (labyrinth[dm_x + 1][dm_y] == 0 && dm_x + 2 <= WIDTH - 1) {
						change = false;
						other -= 1;
						miss += 1;
					}
					break;
				}
			}
			for (other_2nd = 0; other_2nd < 2; other_2nd++) {
				if (labyrinth[dm_x][dm_y] == 1)
					labyrinth[dm_x][dm_y] = 0;
				switch (news) {
				case 0:
					dm_y -= 1;
					break;
				case 1:
					dm_y += 1;
					break;
				case 2:
					dm_x -= 1;
					break;
				case 3:
					dm_x += 1;
					break;
				}
			}
			change = true;
			if (other == complexity - 1 || miss >= 399999) {
				labyrinth[dm_x][dm_y] = 2;
				other = complexity;
				dungeon_maker = false;
			}
		}
	}
}
//–À‹{‚Ì•\¦//
void Dungeon::ShowMap() {
	for (map_y = player_y - 2; map_y <= player_y + 2; map_y++) {
		cout << endl;
		for (map_x = player_x - 2; map_x <= player_x + 2; map_x++) {
			for (other = 0; other < 8; other++)
				if (map_x == Monster[other].x && map_y == Monster[other].y)
					other_2nd = 1;
			if (map_x == player_x && map_y == player_y)
				cout << "P";
			else if (map_y < 0 || map_y >= HEIGHT || map_x < 0 || map_x >= WIDTH)
				cout << "#";
			else if (other_2nd == 1)
				cout << "M";
			else {
				switch (labyrinth[map_y][map_x]) {
				case 0:
					cout << " ";
					break;
				case 1:
					cout << "#";
					break;
				case 2:
					cout << "G";
					break;
				}
			}
			other_2nd = 0;
		}
	}
}

