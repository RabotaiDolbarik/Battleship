#include <iostream>
#include <string>
#include <algorithm>
#include "Player.h"
using std::string;
using std::cout;
using std::cin;
void Player::renderField(char(&f)[SIZE + 2][SIZE + 2])
{
	cout << "   À Á Â Ã Ä Å Æ Ç È Ê       ÎÁÎÇÍÀ×ÅÍÈß:\n";
	for (int i = 1; i < SIZE + 1; i++) {
		if (i != SIZE)
			cout << ' ' << i;
		else
			cout << i;
		for (int j = 1; j < SIZE + 1; j++)
			cout << ' ' << f[i][j];
		if (i == 1)
			cout << "       . — ïóñòàÿ êëåòêà";
		else if (i == 2)
			cout << "       # — êîðàáëü";
		else if (i == 3)
			cout << "       X — ïîïàäàíèå";
		else if (i == 4)
			cout << "       o — ïðîìàõ";
		else if (i == 5)
			cout << "       @ — êëåòêà, ãäå êîðàáëü íå ìîæåò íàõîäèòüñÿ";
		putchar('\n');
	}
	cout << "\n\n";
}
void Player::printFieldRow(const int& row)
{
	if (row != SIZE) cout << ' ' << row;
	else cout << row;
	for (int j = 1; j < SIZE + 1; j++) {
		cout << ' ' << field[row][j];
	}
}
void Player::printHiddenFieldRow(const int& row)
{
	if (row != SIZE) cout << ' ' << row;
	else cout << row;
	for (int j = 1; j < SIZE + 1; j++) {
		cout << ' ' << hidenField[row][j];
	}
}
void Player::createCoords(int& x, int& number)
{
	string alphabet = "ÀÁÂÃÄÅÆÇÈÊ";
	string letter{};
	do {
		x = 0;
		number = -1;
		cout << "ÍÀÏÈØÈÒÅ ×ÅÐÅÇ ÏÐÎÁÅË ÊÎÎÐÄÈÍÀÒÛ ÊËÅÒÊÈ!\n";
		cout << "ÔÎÐÌÀÒ: ÁÓÊÂÀ ×ÈÑËÎ\t";
		cout << "ÏÐÈÌÅÐ: À 1\n";
		cin >> letter >> number;
		if (cin.fail() || letter.size() > 1) { //ïðîâåðÿåò åñëè ââåëè íå ÷èñëî
			cin.clear();
			cin.ignore(10000, '\n');   // î÷èùàåì ÒÎËÜÊÎ êîãäà ðåàëüíî áûë ìóñîð
			cout << "ÎØÈÁÊÀ: ÂÂÅÄÈÒÅ ÁÓÊÂÀ ×ÈÑËÎ\n\n";
			continue;
		}
		int pos = alphabet.find(std::toupper(letter[0])); // ïîçèöèÿ áóêâû
		if (pos == string::npos) { //åñëè íå íàøëè
			cout << "ÍÅÊÎÐÐÅÊÒÍÀß ÁÓÊÂÀ. ÏÎÏÐÎÁÓÉÒÅ ÑÍÎÂÀ!\n\n";
			continue;
		}
		x = pos + 1;
		if (number < 1 || number > 10)
			cout << "ÂÛ ÍÅÊÎÐÐÅÊÒÍÎ ÂÂÅËÈ ÂÒÎÐÓÞ ÊÎÎÐÄÈÍÀÒÓ. ÏÎÏÐÎÁÓÉÒÅ ÑÍÎÂÀ!\n\n";
	} while (x == 0 || number < 1 || number > 10);
}
bool Player::close(int x, int y)
{
	return (field[x - 1][y - 1] == '#' || field[x - 1][y] == '#' || field[x - 1][y + 1] == '#' ||
		field[x][y - 1] == '#' || field[x][y + 1] == '#' || field[x + 1][y - 1] == '#' || field[x + 1][y] == '#' ||
		field[x + 1][y + 1] == '#');
}
void Player::createShip(int len)
{
	string direction{};
	bool flag{ false };
	do {
		cout << "ÑÎÇÄÀÉÒÅ ÊÎÐÀÁËÜ ÄËÈÍÍÎÉ " << len << "!\n";
		int x{ 0 }, y{};
		createCoords(x, y);
		if (len != 1) {
			std::cin.clear();                     // ñáðîñèòü ôëàãè îøèáîê
			std::cin.ignore(10000, '\n');         // óäàëèòü âñ¸ äî ñèìâîëà '\n'
			cout << "ÂÂÅÄÈÒÅ ÍÀÏÐÀÂËÅÍÈÅ ÊÎÐÀÁËß: ÂÂÅÐÕ, ÂÍÈÇ, ÂÏÐÀÂÎ ÈËÈ ÂËÅÂÎ\n";
			cin >> direction;
			std::transform(direction.begin(), direction.end(), direction.begin(), [](char c) {return std::toupper(c);});
		}
		else
			direction = "ÂÏÐÀÂÎ";
		bool near{ true };
		if (direction == "ÂÏÐÀÂÎ" && x <= 10 - len + 1) {
			for (int i = x; i < x + len; i++) {
				if (close(y, i) || field[y][x] == '#') {
					near = false;
					cout << "ÐßÄÎÌ ÅÑÒÜ ÊÎÐÀÁËÜ! ÂÂÅÄÈÒÅ ÄÐÓÃÈÅ ÊÎÎÐÄÈÍÀÒÛ ÈËÈ ÍÀÏÐÀÂËÅÍÈÅ\n";
					break;
				}
			}
			if (near) {
				for (int i = x; i < x + len; i++)
					field[y][i] = '#';
				flag = true;
			}
		}
		else if (direction == "ÂËÅÂÎ" && x >= len) {
			for (int i = x; i > x - len; i--) {
				if (close(y, i) || field[y][x] == '#') {
					near = false;
					cout << "ÐßÄÎÌ ÅÑÒÜ ÊÎÐÀÁËÜ! ÂÂÅÄÈÒÅ ÄÐÓÃÈÅ ÊÎÎÐÄÈÍÀÒÛ ÈËÈ ÍÀÏÐÀÂËÅÍÈÅ\n";
					break;
				}
			}
			if (near) {
				for (int i = x; i > x - len; i--)
					field[y][i] = '#';
				flag = true;
			}
		}
		else if (direction == "ÂÍÈÇ" && y <= 10 - len + 1) {
			for (int j = y; j < y + len; j++) {
				if (close(j, x) || field[y][x] == '#') {
					near = false;
					cout << "ÐßÄÎÌ ÅÑÒÜ ÊÎÐÀÁËÜ! ÂÂÅÄÈÒÅ ÄÐÓÃÈÅ ÊÎÎÐÄÈÍÀÒÛ ÈËÈ ÍÀÏÐÀÂËÅÍÈÅ\n";
					break;
				}
			}
			if (near) {
				for (int j = y; j < y + len; j++)
					field[j][x] = '#';
				flag = true;
			}
		}
		else if (direction == "ÂÂÅÐÕ" && y >= len) {
			for (int j = y; j > y - len; j--) {
				if (close(j, x) || field[y][x] == '#') {
					near = false;
					cout << "ÐßÄÎÌ ÅÑÒÜ ÊÎÐÀÁËÜ! ÂÂÅÄÈÒÅ ÄÐÓÃÈÅ ÊÎÎÐÄÈÍÀÒÛ ÈËÈ ÍÀÏÐÀÂËÅÍÈÅ\n";
					break;
				}
			}
			if (near) {
				for (int j = y; j > y - len; j--)
					field[j][x] = '#';
				flag = true;
			}
		}
		else
			cout << "ÍÀÏÐÀÂËÅÍÈÅ ÂÂÅÄÅÍÎ ÍÅÊÎÐÐÅÊÒÍÎ ÈËÈ ÊÎÐÀÁËÜ ÂÛØÅË ÇÀ ÃÐÀÍÈÖÛ. ÏÎÏÐÎÁÓÉÒÅ ÑÍÎÂÀ\n\n";
	} while (flag == false);
}
void Player::computer_createShip(int len)
{
	string direction{};
	bool flag{ false };
	do {
		int x{ rand() % 10 + 1 }, y{ rand() % 10 + 1 };
		if (len != 1) {
			int direct{ rand() % 4 };
			if (direct == 0)
				direction = "ÂÏÐÀÂÎ";
			else if (direct == 1)
				direction = "ÂËÅÂÎ";
			else if (direct == 2)
				direction = "ÂÂÅÐÕ";
			else
				direction = "ÂÍÈÇ";
		}
		else
			direction = "ÂÏÐÀÂÎ";
		bool near{ true };
		if (direction == "ÂÏÐÀÂÎ" && x <= 10 - len + 1) {
			for (int i = x; i < x + len; i++) {
				if (close(y, i) || field[y][x] == '#') {
					near = false;
					break;
				}
			}
			if (near) {
				for (int i = x; i < x + len; i++)
					field[y][i] = '#';
				flag = true;
			}
		}
		else if (direction == "ÂËÅÂÎ" && x >= len) {
			for (int i = x; i > x - len; i--) {
				if (close(y, i) || field[y][x] == '#') {
					near = false;
					break;
				}
			}
			if (near) {
				for (int i = x; i > x - len; i--)
					field[y][i] = '#';
				flag = true;
			}
		}
		else if (direction == "ÂÍÈÇ" && y <= 10 - len + 1) {
			for (int j = y; j < y + len; j++) {
				if (close(j, x) || field[y][x] == '#') {
					near = false;
					break;
				}
			}
			if (near) {
				for (int j = y; j < y + len; j++)
					field[j][x] = '#';
				flag = true;
			}
		}
		else if (direction == "ÂÂÅÐÕ" && y >= len) {
			for (int j = y; j > y - len; j--) {
				if (close(j, x) || field[y][x] == '#') {
					near = false;
					break;
				}
			}
			if (near) {
				for (int j = y; j > y - len; j--)
					field[j][x] = '#';
				flag = true;
			}
		}
	} while (flag == false);
}
void Player::round(int& row, int& col)
{
	if (field[row - 1][col] == 'X') {
		for (;field[row + 1][col] == 'X'; row++);
		for (; field[row][col] == 'X'; row--) {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (field[row - i][col - j] != 'X')
						hidenField[row - i][col - j] = '@';
				}
			}
		}
	}
	else if (field[row + 1][col] == 'X') {
		for (;field[row - 1][col] == 'X'; row--);
		for (; field[row][col] == 'X'; row++) {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (field[row - i][col - j] != 'X')
						hidenField[row - i][col - j] = '@';
				}
			}
		}
	}
	else if (field[row][col - 1] == 'X') {
		for (;field[row][col + 1] == 'X'; col++);
		for (; field[row][col] == 'X'; col--) {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (field[row - i][col - j] != 'X')
						hidenField[row - i][col - j] = '@';
				}
			}
		}
	}
	else if (field[row][col + 1] == 'X') {
		for (;field[row][col - 1] == 'X'; col--);
		for (; field[row][col] == 'X'; col++) {
			for (int i = -1; i <= 1; i++) {
				for (int j = -1; j <= 1; j++) {
					if (field[row - i][col - j] != 'X')
						hidenField[row - i][col - j] = '@';
				}
			}
		}
	}
	else {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (field[row - i][col - j] != 'X')
					hidenField[row - i][col - j] = '@';
			}
		}
	}
}
bool Player::is_correct(int& row, int& col, int& direct){
	if (field[row][col] == 'o')
	return true;
	if (direct == 1) {
		if (row == 0 || row >= 2 && (field[row - 1][col - 1] == 'X' || field[row - 1][col] == 'X' ||
			field[row - 1][col + 1] == 'X'))
			return true;
		else
			return false;
	}
	if (direct == 2) {
		if (row == 11 || row <= 9 && (field[row + 1][col - 1] == 'X' || field[row + 1][col] == 'X' ||
			field[row + 1][col + 1] == 'X'))
			return true;
		else
			return false;
	}
	if (direct == 3) {
		if (col == 0 || col >= 2 && (field[row - 1][col - 1] == 'X' || field[row][col - 1] == 'X' ||
			field[row + 1][col - 1] == 'X'))
			return true;
		else
			return false;
	}
	else {
		if (col == 11 || col <= 9 && (field[row - 1][col + 1] == 'X' || field[row][col + 1] == 'X' ||
			field[row + 1][col + 1] == 'X'))
			return true;
		else
			return false;
	}
}
void Player::start()
{
	for (int i = 0; i < SIZE + 2; i++) {
		for (int j = 0; j < SIZE + 2; j++) {
			field[i][j] = '.';
			hidenField[i][j] = '.';
		}
	}
	showField();
	createShip(4);
	countShips++;
	showField();
	for (int i = 0; i < 2; i++) {
		createShip(3);
		countShips++;
		showField();
	}
	for (int i = 0; i < 3; i++) {
		createShip(2);
		countShips++;
		showField();
	}
	for (int i = 0; i < 4; i++) {
		createShip(1);
		countShips++;
		showField();
	}
}
void Player::computer_start()
{
	for (int i = 0; i < SIZE + 2; i++) {
		for (int j = 0; j < SIZE + 2; j++) {
			field[i][j] = '.';
			hidenField[i][j] = '.';
		}
	}
	computer_createShip(4);
	countShips++;
	for (int i = 0; i < 2; i++) {
		computer_createShip(3);
		countShips++;
	}
	for (int i = 0; i < 3; i++) {
		computer_createShip(2);
		countShips++;
	}
	for (int i = 0; i < 4; i++) {
		computer_createShip(1);
		countShips++;
	}
}
bool Player::attack(Player& enemy)
{
	cout << "ÂÀØÅ ÏÎËÅ                  ÏÎËÅ ÏÐÎÒÈÂÍÈÊÀ\n";
	cout << "   À Á Â Ã Ä Å Æ Ç È Ê        À Á Â Ã Ä Å Æ Ç È Ê\n";

	for (int i = 1; i < SIZE + 1; i++) {
		// ---- Ñòðîêà ÑÂÎÅÃÎ ïîëÿ ----
		printFieldRow(i);

		// ---- Îòñòóï ìåæäó ïîëÿìè ----
		cout << "     ";

		// ---- Ñòðîêà ×ÓÆÎÃÎ ïîëÿ (ñêðûòîãî) ----
		enemy.printHiddenFieldRow(i);

		// ---- Îáîçíà÷åíèÿ (òîëüêî â ïåðâûõ ñòðîêàõ) ----
		if (i == 1)
			cout << "       . — ïóñòàÿ êëåòêà";
		else if (i == 2)
			cout << "       # — êîðàáëü";
		else if (i == 3)
			cout << "       X — ïîïàäàíèå";
		else if (i == 4)
			cout << "       o — ïðîìàõ";
		else if (i == 5)
			cout << "       @ — êëåòêà, ãäå êîðàáëü íå ìîæåò íàõîäèòüñÿ";

		putchar('\n');
	}
	cout << "ÈÃÐÎÊ, ÄÅËÀÉÒÅ ÂÛÑÒÐÅË!\n";
	int x{ 0 }, y{};
	enemy.createCoords(x, y);
	putchar('\n');
	if (enemy.field[y][x] == '#') {
		enemy.field[y][x] = 'X';
		enemy.hidenField[y][x] = 'X';
		if (enemy.close(y, x) || (y >= 3 && enemy.field[y - 1][x] == 'X' && enemy.field[y - 2][x] == '#') ||
			(y <= 8 && enemy.field[y + 1][x] == 'X' && enemy.field[y + 2][x] == '#') ||
			(x >= 3 && enemy.field[y][x - 1] == 'X' && enemy.field[y][x - 2] == '#') ||
			(x <= 8 && enemy.field[y][x + 1] == 'X' && enemy.field[y][x + 2] == '#') ||
			(y >= 4 && enemy.field[y - 1][x] == 'X' && enemy.field[y - 2][x] == 'X' && enemy.field[y - 3][x] == '#') ||
			(y <= 7 && enemy.field[y + 1][x] == 'X' && enemy.field[y + 2][x] == 'X' && enemy.field[y + 3][x] == '#') ||
			(x >= 4 && enemy.field[y][x - 1] == 'X' && enemy.field[y][x - 2] == 'X' && enemy.field[y][x - 3] == '#') ||
			(x <= 7 && enemy.field[y][x + 1] == 'X' && enemy.field[y][x + 2] == 'X' && enemy.field[y][x + 3] == '#')) {
			cout << "ÏÎÏÀË!\n";
		}
		else {
			enemy.countShips--;
			enemy.round(y, x);
			cout << "ÊÎÐÀÁËÜ ÓÍÈ×ÒÎÆÅÍ!\n";
		}
		if (enemy.getCount() != 0)
			cout << "ÕÎÄÈÒÅ ÑÍÎÂÀ!\n\n";
		return true;
	}
	else {
		if (enemy.hidenField[y][x] == '.')
			enemy.hidenField[y][x] = 'o';
		if (enemy.field[y][x] == '.')
			enemy.field[y][x] = 'o';
		cout << "ÌÈÌÎ!\n";
		enemy.showHiddenField();
		return false;
	}
}
bool Player::computer_attack(int& row, int& col, int& direct)
{
	int x{}, y{};
	if (row != 0 || col != 0) {
		x = row;
		y = col;
	}
	else {
		do {
			x = rand() % 10 + 1;
			y = rand() % 10 + 1;
		} while (field[x][y] != '.' && field[x][y] != '#' || (field[x - 1][y] == 'X' || field[x + 1][y] == 'X' ||
			field[x][y - 1] == 'X' || field[x][y + 1] == 'X' || (field[x - 1][y - 1] == 'X') || (field[x - 1][y + 1] == 'X') ||
			(field[x + 1][y - 1] == 'X') || (field[x + 1][y + 1] == 'X')));
	}
	if (field[x][y] == '#') {
		field[x][y] = 'X';
		if (close(x, y) || (x >= 3 && field[x - 1][y] == 'X' && field[x - 2][y] == '#') ||
			(x <= 8 && field[x + 1][y] == 'X' && field[x + 2][y] == '#') ||
			(y >= 3 && field[x][y - 1] == 'X' && field[x][y - 2] == '#') ||
			(y <= 8 && field[x][y + 1] == 'X' && field[x][y + 2] == '#') ||
			(x >= 4 && field[x - 1][y] == 'X' && field[x - 2][y] == 'X' && field[x - 3][y] == '#') ||
			(x <= 7 && field[x + 1][y] == 'X' && field[x + 2][y] == 'X' && field[x + 3][y] == '#') ||
			(y >= 4 && field[x][y - 1] == 'X' && field[x][y - 2] == 'X' && field[x][y - 3] == '#') ||
			(y <= 7 && field[x][y + 1] == 'X' && field[x][y + 2] == 'X' && field[x][y + 3] == '#')) {
			cout << "ÊÎÌÏÜÞÒÅÐ ÏÎÏÀË ÏÎ ÂÀØÅÌÓ ÊÎÐÀÁËÞ!\n";
			showField();
			cout << "ÊÎÌÏÜÞÒÅÐ ÕÎÄÈÒ ÑÍÎÂÀ!\n\n";
			if (direct == 0)
				direct = rand() % 4 + 1;
			if (direct == 1) {
				row = x - 1;
				col = y;
				if (field[row][col] == '#') {
					return computer_attack(row, col, direct);
				}
				else if (row <= 6 && (field[row][col] == '.' || field[row][col] == 'o') && field[row + 1][col] == 'X' &&
					field[row + 2][col] == 'X' && field[row + 3][col] == 'X') {
					if (is_correct(row, col, direct)) {
						row += 4;
						return computer_attack(row, col, direct);
					}
					else {
						field[row][col] = 'o';
						row += 4;
						return miss(row, col);
					}

				}
				else if (row <= 7 && field[row][col] == '.' && field[row + 1][col] == 'X' && field[row + 2][col] == 'X') {
					if (is_correct(row, col, direct)) {
						row += 3;
						direct = 2;
						return computer_attack(row, col, direct);
					}
					else {
						field[row][col] = 'o';
						row += 3;
						direct = 2;
						return miss(row, col);
					}
				}
				else if (field[row][col] == '.' && row >= 1) {
					if (!is_correct(row, col, direct)) {
						field[row][col] = 'o';
						return miss(row, col);
					}
				}
				else {
					if (is_correct(row, col, direct))
						return computer_attack(row, col, direct);
					else {
						field[row][col] = 'o';
						row += 4;
						return miss(row, col);
					}
				}
			}
			else if (direct == 2) {
				row = x + 1;
				col = y;
				if (field[row][col] == '#') {
					return computer_attack(row, col, direct);
				}
				else if (row >= 5 && field[row][col] == '.' && field[row - 1][col] == 'X' &&
					field[row - 2][col] == 'X' && field[row - 3][col] == 'X') {
					if (is_correct(row, col, direct)) {
						row -= 4;
						return computer_attack(row, col, direct);
					}
					else {
						field[row][col] = 'o';
						row -= 4;
						return miss(row, col);
					}
				}
				else if (row >= 4 && (field[row][col] == '.' || field[row][col] == 'o') && field[row - 1][col] == 'X' &&
					field[row - 2][col] == 'X') {
					if (is_correct(row, col, direct)) {
						row -= 3;
						direct = 1;
						return computer_attack(row, col, direct);
					}
					else {
						field[row][col] = 'o';
						row -= 3;
						direct = 1;
						return miss(row, col);
					}
				}
				else if (field[row][col] == '.' && row <= 10) {
					if (!is_correct(row, col, direct)) {
						field[row][col] = 'o';
						return miss(row, col);
					}
				}
				else {
					if (is_correct(row, col, direct))
						return computer_attack(row, col, direct);
					else {
						field[row][col] = 'o';
						row += 4;
						return miss(row, col);
					}
				}
			}
			else if (direct == 3) {
				col = y - 1;
				row = x;
				if (field[row][col] == '#') {
					return computer_attack(row, col, direct);
				}
				else if (col <= 6 && field[row][col] == '.' && field[row][col + 1] == 'X' &&
					field[row][col + 2] == 'X' && field[row][col + 3] == 'X') {
					if (is_correct(row, col, direct)) {
						col += 4;
						return computer_attack(row, col, direct);
					}
					else {
						field[row][col] = 'o';
						col += 4;
						return miss(row, col);
					}
				}
				else if (col <= 7 && field[row][col] == '.' && field[row][col + 1] == 'X' && field[row][col + 2] == 'X') {
					if (is_correct(row, col, direct)) {
						col += 3;
						direct = 4;
						return computer_attack(row, col, direct);
					}
					else {
						field[row][col] = 'o';
						col += 3;
						direct = 4;
						return miss(row, col);
					}
				}
				else if (field[row][col] == '.' && col >= 1) {
					if (!is_correct(row, col, direct)) {
						field[row][col] = 'o';
						return miss(row, col);
					}
				}
				else {
					if (is_correct(row, col, direct))
						return computer_attack(row, col, direct);
					else {
						field[row][col] = 'o';
						row += 4;
						return miss(row, col);
					}
				}
			}
			else if (direct == 4) {
				col = y + 1;
				row = x;
				direct = 4;
				if (field[row][col] == '#' && col <= 10) {
					return computer_attack(row, col, direct);
				}
				else if (col >= 5 && field[row][col] == '.' && field[row][col - 1] == 'X' &&
					field[row][col - 2] == 'X' && field[row][col - 3] == 'X') {
					if (is_correct(row, col, direct)) {
						col -= 4;
						return computer_attack(row, col, direct);
					}
					else {
						field[row][col] = 'o';
						col -= 4;
						return miss(row, col);
					}
				}
				else if (col >= 4 && field[row][col] == '.' && field[row][col - 1] == 'X' && field[row][col - 2] == 'X') {
					if (is_correct(row, col, direct)) {
						col -= 3;
						direct = 3;
						return computer_attack(row, col, direct);
					}
					else {
						field[row][col] = 'o';
						col -= 3;
						direct = 3;
						return miss(row, col);
					}
				}
				else if (field[row][col] == '.' && col <= 10) {
					if (!is_correct(row, col, direct)) {
						field[row][col] = 'o';
						return miss(row, col);
					}
				}
				else {
					if (is_correct(row, col, direct))
						return computer_attack(row, col, direct);
					else {
						field[row][col] = 'o';
						row += 4;
						return miss(row, col);
					}
				}
			}
		}
		else {
			row = 0;
			col = 0;
			direct = 0;
			countShips--;
			cout << "ÊÎÌÏÜÞÒÅÐ ÓÍÈ×ÒÎÆÈË ÂÀØ ÊÎÐÀÁËÜ!\n";
		}
		showField();
		if (getCount() != 0)
			cout << "ÊÎÌÏÜÞÒÅÐ ÕÎÄÈÒ ÑÍÎÂÀ!\n\n";
		return true;
	}
	else {
		if (row != 0 || col != 0) {
			x = row;
			y = col;
		}
		if (field[x][y] == '.' && x >= 1 && x <= 10 && y >= 1 && y <= 10) {
			if (!((direct == 1 && row >= 2 && (field[row - 1][col - 1] == 'X' || field[row - 1][col] == 'X' ||
				field[row - 1][col + 1] == 'X')) || (direct == 2 && row <= 9 && (field[row + 1][col - 1] == 'X' ||
					field[row + 1][col] == 'X' || field[row + 1][col + 1] == 'X')) ||
				(direct == 3 && col >= 2 && (field[row - 1][col - 1] == 'X' || field[row][col - 1] == 'X' ||
					field[row + 1][col - 1] == 'X')) || (direct == 4 && col <= 9 && (field[row - 1][col + 1] == 'X' ||
						field[row][col + 1] == 'X' || field[row + 1][col + 1] == 'X')))) {
				field[x][y] = 'o';
				return miss(x, y);
			}
		}
		if (direct != 0) {
			if (direct == 1)
				row++;
			else if (direct == 2)
				row--;
			else if (direct == 3)
				col++;
			else
				col--;
		}
		if (row != 0 || col != 0) {
			bool flag = true;
			do {
				direct = rand() % 4 + 1;
				if (direct == 1 && row >= 2 && field[row - 1][col] != 'o') {
					row--;
					return computer_attack(row, col, direct);
				}
				else if (direct == 2 && row <= 9 && field[row + 1][col] != 'o') {
					row++;
					return computer_attack(row, col, direct);
				}
				else if (direct == 3 && col >= 2 && field[row][col - 1] != 'o') {
					col--;
					return computer_attack(row, col, direct);
				}
				else if (direct == 4 && col <= 9 && field[row][col + 1] != 'o') {
					col++;
					return computer_attack(row, col, direct);
				}
			} while (flag);
		}
	}
}
