#pragma once
class Unit {
public:
	char name[18] = "�A����";
	char job[18] = "���m";
	int hp = 30;
	int mp = 12;
	int maxhp = 30;
	int maxmp = 12;
	int atk = 7;
	int def = 3;
	int x;
	int y;
	int steps = 0;
	void Move(int* Obstacle, int* Coordinate, int n);
	void Attack(char* enemy_name, int* enemy_hp, int* enemy_def, int* damage);
	void Move_AI();
	void Status_Write(char* monster_name, int* hp, int* mp, int* maxhp, int* maxmp, int* atk, int* def);
	void Victory(char* monster_name);
};
//�ړ�//
void Unit::Move(int* Obstacle, int* Coordinate, int n) {
	if (*Obstacle != 1) {
		*Coordinate += n;
		steps += 1;
		if (steps >= 5) {
			if (hp < maxhp)
				hp += 1;
			steps = 0;
		}
	}
	if (*Obstacle == 2) {
		Floor += 1;
		reset = true;
		dungeon_maker = true;
	}
}
//�U��//
void Unit::Attack(char* enemy_name, int* enemy_hp, int* enemy_def, int* damage) {
	cout << endl << name << "�̍U��!" << endl;
	*damage = atk / 2 - *enemy_def / 4;
	*damage += (int)(rand() * (*damage / 5.0 + 1.0) / (1.0 + RAND_MAX));
	*enemy_hp -= *damage;
	cout << enemy_name << "��" << *damage << "�̃_���[�W!" << endl;
}
//�G�̈ړ�//
void Unit::Move_AI() {
	other = (int)(rand() * 4.0 / (1.0 + RAND_MAX));
	switch (other) {
	case 0:
		if (labyrinth[y][x + 1] == 0)
			x += 1;
		break;
	case 1:
		if (labyrinth[y][x - 1] == 0)
			x -= 1;
		break;
	case 2:
		if (labyrinth[y + 1][x] == 0)
			y += 1;
		break;
	case 3:
		if (labyrinth[y - 1][x] == 0)
			y -= 1;
		break;
	}
}
//�X�e�[�^�X�������ݗp//
void Unit::Status_Write(char* monster_name, int* monster_hp, int* monster_mp, int* monster_maxhp, int* monster_maxmp, int* monster_atk, int* monster_def) {
	strcpy_s(name, monster_name);
	hp = *monster_hp;
	mp = *monster_mp;
	maxhp = *monster_maxhp;
	maxmp = *monster_maxmp;
	atk = *monster_atk;
	def = *monster_def;
}
//�������ꍇ�̏���//
void Unit::Victory(char* monster_name) {
	cout << monster_name << "���E�����I";
}