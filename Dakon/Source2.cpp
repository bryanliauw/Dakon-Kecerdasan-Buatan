#include<iostream>
#include<Windows.h>
using namespace std;

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class catur {
protected:
	int jalan[16];
	int player;
	int keep;
public:
	catur() {
		for (int i = 0; i < 16; i++)
		{
			jalan[i] = 7;
		}
		jalan[7] = 0;
		jalan[15] = 0;
		//player = 1; //INI
	}
	void set_player(int ply) {
		player = ply;
	}
	int get_player() {
		return player;
	}
	int get_value(int index) {
		return jalan[index];
	}
	void draw(int player, int temp = 0) {
		system("cls");
		//-----------// update gambar
		HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hstdout, 9);
		if (player == 1)
		{
			gotoxy(52, 4); cout << "Giliran AI";
		}
		else
		{
			gotoxy(50, 4); cout << "Giliran Player";
		}
		SetConsoleTextAttribute(hstdout, 11);
		int a = 8, b = 9, c = 30;
		gotoxy(54, 5); cout << "*DAKON*";
		SetConsoleTextAttribute(hstdout, 12);
		gotoxy(c, b++); cout << "------";
		gotoxy(c, b++); cout << "|";
		gotoxy(c, b); cout << "------";
		b = 9;
		gotoxy(79, b++); cout << "------";
		gotoxy(79, b++); cout << "     |";
		gotoxy(79, b); cout << "------";
		for (int i = 0; i < 2; i++) {
			gotoxy(36, a++);
			cout << "-";
			for (int j = 0; j < 7; j++) {
				cout << "------";
			}
			gotoxy(36, a++);
			cout << "|";
			for (int k = 0; k < 7; k++) {
				cout << "     |";
			}
		}
		gotoxy(36, a++);
		cout << "-";
		for (int l = 0; l < 7; l++) {
			cout << "------";
		}
		SetConsoleTextAttribute(hstdout, 15);
		//-----------// update biji
		SetConsoleTextAttribute(hstdout, 10);
		gotoxy(27, 6);
		if (temp == 0)
		{
			cout << "Biji : " << temp << endl;
		}
		else
		{
			cout << "Biji : " << temp << endl;
		}
		//----------// update angka
		int d = 74, e = 38, co = 0, co1 = 8;
		for (int i = 0; i < 16; i++)
		{
			if (i == 15) {
				gotoxy(32, 10);
				cout << jalan[i] << endl;
			}
			else if (i == 7) {
				gotoxy(80, 10);
				cout << jalan[i] << endl;
			}
			else {
				if (i > 7)
				{
					SetConsoleTextAttribute(hstdout, 8);
					gotoxy(d + 1, 13);
					cout << co1++;
					SetConsoleTextAttribute(hstdout, 15);
					gotoxy(d, 11);
					cout << jalan[i] << endl;
					d -= 6;
				}
				else
				{
					SetConsoleTextAttribute(hstdout, 8);
					gotoxy(e + 1, 7);
					cout << co++;
					SetConsoleTextAttribute(hstdout, 15);
					gotoxy(e, 9);
					cout << jalan[i] << endl;
					e += 6;
				}
			}
		}
		system("pause");
	}
	void reset() {
		for (int i = 0; i < 16; i++)
		{
			jalan[i] = 7;
		}
		jalan[7] = 0;
		jalan[15] = 0;
	}
	int get_lumbung1() {
		return jalan[7];
	}
	int get_lumbung2() {
		return jalan[15];
	}
	bool play() {
		if (jalan[7] + jalan[15] == 7 * 14) {
			return false;
		}
		return true;
	}
	// lek berhenti di lumbung sendiri bisa pilih lagi (V)
	// lek berhenti di jalan kosong ganti player 
	// lek plih satu hrs tetep jalan, dan bisa menembak (V)
	bool check(int plr) {
		if (plr == 1) {
			int x = 0;
			for (int i = 0; i < 7; i++)
			{
				if (get_value(i) == 0) {
					x++;
				}
			}
			if (x == 7) {
				return true;
			}
		}
		if (plr == 2) {
			int x = 0;
			for (int i = 8; i < 15; i++)
			{
				if (get_value(i) == 0) {
					x++;
				}
			}
			if (x == 7) {
				return true;
			}
		}
		return false;
	}
	void run(int player, int index, int AI = 0) {
		int sl = 5;
		if (player == 1 && (index >= 0 && index <= 6) && get_value(index) != 0) { //AI
			int temp = get_value(index);
			jalan[index] = 0; //diambil
			while (temp > 0)
			{
				if (index == 14) {
					index = -1;
				}
				if (index != 15) {
					index++;
					jalan[index] += 1;
					temp--;
					if (AI != 1) {
						draw(player, temp);
						Sleep(sl);
					}
				}
				if (temp == 0 && jalan[index] > 1 && index != 7 && index != 15) {
					temp = jalan[index];
					if (AI != 1) {
						draw(player, temp);
						Sleep(sl);
					}
					jalan[index] = 0;
				}
			}
			if (get_value(index) == 1 && (index >= 0 && index <= 6) && jalan[14 - index] != 0) { //AI tembak
				jalan[7] += jalan[index] + jalan[14 - index];
				jalan[index] = 0;
				jalan[14 - index] = 0;
				if (AI != 1) {
					draw(player, temp);
					Sleep(sl);
				}
				set_player(2);
			}
			else if (get_value(index) == 1 && (index >= 0 && index <= 6) && jalan[14 - index] == 0) {
				set_player(2);
			}
			else if (index == 7) { //berhenti lumbung AI
				set_player(1);
			}
			else if (get_value(index) == 1 && (index >= 8 && index <= 15)) { //berhenti jalan player
				set_player(2);
			}
		}
		else if (player == 2 && (index >= 8 && index <= 14) && get_value(index) != 0) { //Player
			int temp = get_value(index);
			jalan[index] = 0; //diambil
			while (temp > 0)
			{
				if (index == 15) {
					index = -1;
				}
				if (index != 6) {
					index++;
					jalan[index] += 1;
					temp--;
					if (AI != 1) {
						draw(player, temp);
						Sleep(sl);
					}
				}
				if (index == 6) {
					index = 7;
				}
				if (temp == 0 && jalan[index] > 1 && index != 15 && index != 7) {
					temp = jalan[index];
					if (AI != 1) {
						draw(player, temp);
						Sleep(sl);
					}
					jalan[index] = 0;
				}
			}
			if (get_value(index) == 1 && (index >= 8 && index <= 14) && jalan[14 - index] != 0) { //Player tembak
				jalan[15] += jalan[index] + jalan[14 - index];
				jalan[index] = 0;
				jalan[14 - index] = 0;
				if (AI != 1) {
					draw(player, temp);
					Sleep(sl);
				}
				set_player(1);
			}
			else if (get_value(index) == 1 && (index >= 8 && index <= 14) && jalan[14 - index] == 0) {
				set_player(1);
			}
			else if (index == 15) { //berhenti lumbung Player
				set_player(2);
			}
			else if (get_value(index) == 1 && (index >= 0 && index <= 6)) { //berhenti jalan AI
				set_player(1);
			}
		}
	}
	void copy(catur ctr) {
		for (int i = 0; i < 16; i++)
		{
			jalan[i] = ctr.jalan[i];
		}
	}
};

class data_prun {
protected:
	catur ctr;
public:
	data_prun() {

	}
	int run_data() {
		catur save, save1, save2, save3, save4, save5, save6;
		int op;

		save6.copy(ctr);
		int keep_e = -10000, data5 = 10000, e_s = 0, e_l = 6;
		while (ctr.get_value(e_s) == 0) { e_s++; }
		while (ctr.get_value(e_l) == 0) { e_l--; }
		for (int e = e_s; e < e_l + 1; e++) //AI
		{
			if (ctr.get_value(e) != 0)
			{
				ctr.run(1, e, 1);
				save5.copy(ctr);

				int keep_f = 10000, data4 = -10000, f_s = 8, f_l = 14;
				while (ctr.get_value(f_s) == 0) { f_s++; }
				while (ctr.get_value(f_l) == 0) { f_l--; }
				if (f_l == 0) {
					op = e_l;
					return op;
				}
				for (int f = f_s; f < f_l + 1; f++) //PLAYER
				{
					if (ctr.get_value(f) != 0)
					{
						ctr.run(2, f, 1);
						save4.copy(ctr);

						int keep_g = -10000, data3 = 10000, g_s = 0, g_l = 6;
						while (ctr.get_value(g_s) == 0) { g_s++; }
						while (ctr.get_value(g_l) == 0) { g_l--; }
						for (int g = g_s; g < g_l + 1; g++) //AI
						{
							if (ctr.get_value(g) != 0)
							{
								ctr.run(1, g, 1);
								save3.copy(ctr);

								int keep_h = 10000, data2 = -10000, h_s = 8, h_l = 14;
								while (ctr.get_value(h_s) == 0) { h_s++; }
								while (ctr.get_value(h_l) == 0) { h_l--; }
								for (int h = h_s; h < h_l + 1; h++) //PLAYER
								{
									if (ctr.get_value(h) != 0)
									{
										ctr.run(2, h, 1);
										save2.copy(ctr);

										int keep_i = -10000, data1 = 10000, i_s = 0, i_l = 6;
										while (ctr.get_value(i_s) == 0) { i_s++; }
										while (ctr.get_value(i_l) == 0) { i_l--; }
										for (int i = i_s; i < i_l + 1; i++) //AI
										{
											if (ctr.get_value(i) != 0)
											{
												ctr.run(1, i, 1);
												save1.copy(ctr);

												int keep_j = 10000, j_s = 8, j_l = 14;
												while (ctr.get_value(j_s) == 0) { j_s++; }
												while (ctr.get_value(j_l) == 0) { j_l--; }
												for (int j = j_s; j < j_l + 1; j++) //PLAYER
												{
													if (ctr.get_value(j) != 0)
													{
														ctr.run(2, j, 1);
														{
															int lumbung = ctr.get_lumbung1() - ctr.get_lumbung2();
															if (i == i_s) {
																data1 = min(data1, lumbung);
															}
															else if (i != i_s) {
																if (lumbung <= data1) {
																	j = 15; //break
																}
																else {
																	if (keep_j > lumbung) {
																		keep_j = lumbung;
																	}
																}
																if (j == j_l) {
																	data1 = keep_j;
																}
															}
														}
													}
													ctr.copy(save1);
												}
												if (h == h_s) {
													data2 = max(data2, data1);
												}
												else if (h != h_s) {
													if (data1 >= data2) {
														i = 7;
													}
													else {
														if (keep_i < data1) {
															keep_i = data1;
														}
													}
													if (i == i_l) {
														data2 = keep_i;
													}
												}
											}
											ctr.copy(save2);
										}
										if (g == g_s) {
											data3 = min(data3, data2);
										}
										else if (g != g_s) {
											if (data2 <= data3) {
												h = 15;
											}
											else {
												if (keep_h > data2) {
													keep_h = data2;
												}
											}
											if (h == h_l) {
												data3 = keep_h;
											}
										}
									}
									ctr.copy(save3);
								}
								if (f == f_s) {
									data4 = max(data4, data3);
								}
								else if (f != f_s) {
									if (data3 >= data4) {
										g = 7;
									}
									else {
										if (keep_g < data3) {
											keep_g = data3;
										}
									}
									if (g == g_l) {
										data4 = keep_g;
									}
								}
							}
							ctr.copy(save4);
						}
						if (e == e_s) {
							data5 = min(data5, data4);
							op = e;
						}
						else if (e != e_s) {
							if (data4 <= data5) {
								f = 15;
							}
							else {
								if (keep_f > data4) {
									keep_f = data4;
									op = e;
								}
							}
							if (f == f_l) {
								data5 = keep_f;
							}
						}
					}
					ctr.copy(save5);
				}
			}
			ctr.copy(save6);
		}
		cout << data5 << endl;
		system("pause");
		return op;
	}
	void play() {
		int input;
		ctr.draw(1);
		cout << run_data() << endl;
		ctr.run(1, run_data());
		while (ctr.play())
		{
			if (ctr.check(1)) {
				ctr.draw(2);
				cout << "Input Index: ";
				cin >> input;
				ctr.run(2, input);
			}
			else if (ctr.check(2)) {
				ctr.draw(1);
				cout << run_data() << endl;
				ctr.run(1, run_data());
			}
			else if (ctr.get_player() == 1)
			{ //AI
				ctr.draw(1);
				cout << run_data() << endl;
				ctr.run(1, run_data());
			}
			else
			{ //Player
				ctr.draw(2);
				cout << "Input Index: ";
				cin >> input;
				ctr.run(2, input);
			}
		}
	}
};

int main() {
	data_prun d;
	d.play();
	return 0;
}