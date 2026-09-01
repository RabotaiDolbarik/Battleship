#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstdlib>
#include <time.h>
using std::cout;
using std::cin;
using std::string;
enum {SIZE = 10};
void clearConsole() { // очистка консоли в зависимости от ОС
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
struct player
{
private:
	char field[SIZE + 2][SIZE + 2];
	char hidenField[SIZE + 2][SIZE + 2];
	int countShips;
	void renderField(char(&f)[SIZE + 2][SIZE + 2]) {
		cout << "   А Б В Г Д Е Ж З И К       ОБОЗНАЧЕНИЯ:\n";
		for (int i = 1; i < SIZE + 1; i++) {
			if (i != SIZE)
				cout << ' ' << i;
			else
				cout << i;
			for (int j = 1; j < SIZE + 1; j++)
				cout << ' ' << f[i][j];
			if (i == 1)
				cout << "       . — пустая клетка";
			else if (i == 2)
				cout << "       # — корабль";
			else if (i == 3)
				cout << "       X — попадание";
			else if (i == 4)
				cout << "       o — промах";
			else if (i == 5)
				cout << "       @ — клетка, где корабль не может находиться";
			putchar('\n');
		}
		putchar('\n');
	}
	void printFieldRow(const int& row) {
		if (row != SIZE) cout << ' ' << row;
		else cout << row;
		for (int j = 1; j < SIZE + 1; j++) {
			cout << ' ' << field[row][j];
		}
	}

	void printHiddenFieldRow(const int& row) {
		if (row != SIZE) cout << ' ' << row;
		else cout << row;
		for (int j = 1; j < SIZE + 1; j++) {
			cout << ' ' << hidenField[row][j];
		}
	}
	void createCoords(int& x, int& number)
	{
		string alphabet = "АБВГДЕЖЗИК";
		string letter{};
		do {
			x = 0;
			number = -1;
			cout << "НАПИШИТЕ ЧЕРЕЗ ПРОБЕЛ КООРДИНАТЫ КЛЕТКИ!\n";
			cout << "ФОРМАТ: БУКВА ЧИСЛО\t";
			cout << "ПРИМЕР: А 1\n";
			cin >> letter >> number;
			if (cin.fail() || letter.size() > 1) { //проверяет если ввели не число
				cin.clear();
				cin.ignore(10000, '\n');   // очищаем ТОЛЬКО когда реально был мусор
				cout << "ОШИБКА: ВВЕДИТЕ БУКВА ЧИСЛО\n\n";
				continue;
			}
			int pos = alphabet.find(std::toupper(letter[0])); // позиция буквы
			if (pos == string::npos) { //если не нашли
				cout << "НЕКОРРЕКТНАЯ БУКВА. ПОПРОБУЙТЕ СНОВА!\n\n";
				continue;
			}
			x = pos + 1;
			if (number < 1 || number > 10)
				cout << "ВЫ НЕКОРРЕКТНО ВВЕЛИ ВТОРУЮ КООРДИНАТУ. ПОПРОБУЙТЕ СНОВА!\n\n";
		} while (x == 0 || number < 1 || number > 10);
	}
	bool close(int x, int y) {
		return (field[x - 1][y - 1] == '#' || field[x - 1][y] == '#' || field[x - 1][y + 1] == '#' ||
			field[x][y - 1] == '#' || field[x][y + 1] == '#' || field[x + 1][y - 1] == '#' || field[x + 1][y] == '#' ||
			field[x + 1][y + 1] == '#');
	}
	void createShip(int len)
	{
		string direction{};
		bool flag{ false };
		do {
			cout << "СОЗДАЙТЕ КОРАБЛЬ ДЛИННОЙ " << len << "!\n";
			int x{ 0 }, y{};
			createCoords(x, y);
			if (len != 1) {
				std::cin.clear();                     // сбросить флаги ошибок
				std::cin.ignore(10000, '\n');         // удалить всё до символа '\n'
				cout << "ВВЕДИТЕ НАПРАВЛЕНИЕ КОРАБЛЯ: ВВЕРХ, ВНИЗ, ВПРАВО ИЛИ ВЛЕВО\n";
				cin >> direction;
				std::transform(direction.begin(), direction.end(), direction.begin(), [](char c) {return std::toupper(c);});
			}
			else
				direction = "ВПРАВО";
			bool near{ true };
			if (direction == "ВПРАВО" && x <= 10 - len + 1) {
				for (int i = x; i < x + len; i++) {
					if (close(y, i) || field[y][x] == '#') {
						near = false;
						cout << "РЯДОМ ЕСТЬ КОРАБЛЬ! ВВЕДИТЕ ДРУГИЕ КООРДИНАТЫ ИЛИ НАПРАВЛЕНИЕ\n";
						break;
					}
				}
				if (near) {
					for (int i = x; i < x + len; i++)
						field[y][i] = '#';
					flag = true;
				}
			}
			else if (direction == "ВЛЕВО" && x >= len) {
				for (int i = x; i > x - len; i--) {
					if (close(y, i) || field[y][x] == '#') {
						near = false;
						cout << "РЯДОМ ЕСТЬ КОРАБЛЬ! ВВЕДИТЕ ДРУГИЕ КООРДИНАТЫ ИЛИ НАПРАВЛЕНИЕ\n";
						break;
					}
				}
				if (near) {
					for (int i = x; i > x - len; i--)
						field[y][i] = '#';
					flag = true;
				}
			}
			else if (direction == "ВНИЗ" && y <= 10 - len + 1) {
				for (int j = y; j < y + len; j++) {
					if (close(j, x) || field[y][x] == '#') {
						near = false;
						cout << "РЯДОМ ЕСТЬ КОРАБЛЬ! ВВЕДИТЕ ДРУГИЕ КООРДИНАТЫ ИЛИ НАПРАВЛЕНИЕ\n";
						break;
					}
				}
				if (near) {
					for (int j = y; j < y + len; j++)
						field[j][x] = '#';
					flag = true;
				}
			}
			else if (direction == "ВВЕРХ" && y >= len) {
				for (int j = y; j > y - len; j--) {
					if (close(j, x) || field[y][x] == '#') {
						near = false;
						cout << "РЯДОМ ЕСТЬ КОРАБЛЬ! ВВЕДИТЕ ДРУГИЕ КООРДИНАТЫ ИЛИ НАПРАВЛЕНИЕ\n";
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
				cout << "НАПРАВЛЕНИЕ ВВЕДЕНО НЕКОРРЕКТНО ИЛИ КОРАБЛЬ ВЫШЕЛ ЗА ГРАНИЦЫ. ПОПРОБУЙТЕ СНОВА\n\n";
		} while (flag == false);
	}
	bool miss(int& row, int& col) {
		cout << "КОМПЬЮТЕР ВЫСТРЕЛИЛ МИМО!\n";
		showField();
		return false;
	}
	void computer_createShip(int len)
	{
		string direction{};
		bool flag{ false };
		do {
			int x{ rand() % 10 + 1 }, y{ rand() % 10 + 1 };
			if (len != 1) {
				int direct{ rand() % 4 };
				if (direct == 0)
					direction = "ВПРАВО";
				else if (direct == 1)
					direction = "ВЛЕВО";
				else if (direct == 2)
					direction = "ВВЕРХ";
				else
					direction = "ВНИЗ";
			}
			else
				direction = "ВПРАВО";
			bool near{ true };
			if (direction == "ВПРАВО" && x <= 10 - len + 1) {
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
			else if (direction == "ВЛЕВО" && x >= len) {
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
			else if (direction == "ВНИЗ" && y <= 10 - len + 1) {
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
			else if (direction == "ВВЕРХ" && y >= len) {
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
	void round(int& row, int& col) {
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
	bool is_correct(int& row, int& col, int& direct) {
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
public:
	int getCount() {
		return countShips;
	}
	void showField() {
		return renderField(field);
	}
	void showHiddenField() {
		return renderField(hidenField);
	}
	void start()
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
	void computer_start() {
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
	bool attack(player& enemy) {
		cout << "ВАШЕ ПОЛЕ                  ПОЛЕ ПРОТИВНИКА\n";
		cout << "   А Б В Г Д Е Ж З И К        А Б В Г Д Е Ж З И К\n";

		for (int i = 1; i < SIZE + 1; i++) {
			// ---- Строка СВОЕГО поля ----
			printFieldRow(i);

			// ---- Отступ между полями ----
			cout << "     ";

			// ---- Строка ЧУЖОГО поля (скрытого) ----
			enemy.printHiddenFieldRow(i);

			// ---- Обозначения (только в первых строках) ----
			if (i == 1)
				cout << "       . — пустая клетка";
			else if (i == 2)
				cout << "       # — корабль";
			else if (i == 3)
				cout << "       X — попадание";
			else if (i == 4)
				cout << "       o — промах";
			else if (i == 5)
				cout << "       @ — клетка, где корабль не может находиться";

			putchar('\n');
		}
		cout << "ИГРОК, ДЕЛАЙТЕ ВЫСТРЕЛ!\n";
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
				cout << "ПОПАЛ!\n";
			}
			else {
				enemy.countShips--;
				enemy.round(y, x);
				cout << "КОРАБЛЬ УНИЧТОЖЕН!\n";
			}
			if (enemy.getCount() != 0)
				cout << "ХОДИТЕ СНОВА!\n\n";
			return true;
		}
		else {
			if (enemy.hidenField[y][x] == '.')
				enemy.hidenField[y][x] = 'o';
			if (enemy.field[y][x] == '.')
				enemy.field[y][x] = 'o';
			cout << "МИМО!\n";
			enemy.showHiddenField();
			return false;
		}
	}
	bool computer_attack(int& row, int& col, int& direct) {
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
			if (close(x, y) || (x >= 3 && field[x-1][y] == 'X' && field[x - 2][y] == '#') || 
				(x <= 8 && field[x+1][y] == 'X' && field[x + 2][y] == '#') ||
				(y >= 3 && field[x][y-1] == 'X' && field[x][y-2] == '#' ) || 
				(y <= 8 && field[x][y+1] == 'X' && field[x][y+2] == '#') || 
				(x >= 4 && field[x - 1][y] == 'X' && field[x - 2][y] == 'X' && field[x-3][y] == '#') ||
				(x <= 7 && field[x + 1][y] == 'X' && field[x + 2][y] == 'X' && field[x+3][y] == '#') ||
				(y >= 4 && field[x][y-1] == 'X' && field[x][y-2] == 'X' && field[x][y - 3] == '#') ||
				(y <= 7 && field[x][y + 1] == 'X' && field[x][y + 2] == 'X' && field[x][y + 3] == '#')) {
				cout << "КОМПЬЮТЕР ПОПАЛ ПО ВАШЕМУ КОРАБЛЮ!\n";
				showField();
				cout << "КОМПЬЮТЕР ХОДИТ СНОВА!\n\n";
				if (direct == 0)
					direct = rand() % 4 + 1;
				if (direct == 1) {
					row = x - 1;
					col = y;
					if (field[row][col] == '#') {
						return computer_attack(row, col, direct);
					}
					else if (row <= 6 && (field[row][col] == '.' || field[row][col] == 'o')&& field[row + 1][col] == 'X' &&
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
					else if (row <= 7 && field[row][col] == '.' && field[row + 1][col] == 'X' &&  field[row + 2][col] == 'X') {
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
					else if (row >= 4 && (field[row][col] == '.' || field[row][col] == 'o')&& field[row - 1][col] == 'X' &&
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
						field[row][col+2] == 'X' && field[row][col + 3] == 'X') {
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
					else if (col <= 7 && field[row][col] == '.' && field[row][col + 1] == 'X' && field[row][col+2] == 'X') {
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
				else if (direct == 4){
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
				cout << "КОМПЬЮТЕР УНИЧТОЖИЛ ВАШ КОРАБЛЬ!\n";
			}
			showField();
			if (getCount() != 0)
				cout << "КОМПЬЮТЕР ХОДИТ СНОВА!\n\n";
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
					direct = rand() % 4 + 1 ;
					if (direct == 1 && row >= 2 && field[row - 1][col] != 'o') {
						row--;
						return computer_attack(row, col, direct);
					}
					else if (direct == 2 && row <= 9 && field[row + 1][col] != 'o') {
						row ++;
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
};
int main() 
{
	system("chcp 1251 > nul"); //для кодировки
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	int playersCount{}; //количество игроков
	do {
		cout << "ВВЕДИТЕ КОЛИЧЕСТВО ИГРОКОВ\n";
		cin >> playersCount;
		if (cin.fail()) { //проверяет если ввели не число
			cin.clear(); //После ошибки cin находится в состоянии fail. 
			//И пока это состояние не сбросить, последующие операции ввода нормально работать не будут.
			cin.ignore(10000, '\n'); //пропустить максимум 10000 символов, пока не встретится '\n'
			cout << "ОШИБКА: ВВЕДИТЕ ЧИСЛО 1 ИЛИ 2\n\n";
			continue;
		}
		switch (playersCount)
		{
		case 1:{
				player computer{};
				player person{};
				computer.computer_start();
				cout << "КОМПЬЮТЕР РАССТАВИЛ ВСЕ КОРАБЛИ!\n\n";
				person.start();
				cout << "ВЫ УСПЕШНО РАССТАВИЛИ ВСЕ КОРАБЛИ! НАЖМИТЕ ENTER, ЧТОБЫ ПРОДОЛЖИТЬ\n";
				cin.ignore(10000, '\n'); // пропустить "хвост" предыдущего ввода
				cin.get();    // подождать нажатия Enter
				clearConsole();
				int turn{ 1 }; // чей ход
				int row{ 0 }, col{ 0 }, direction{ 0 }, count{1};
				while (computer.getCount() != 0 && person.getCount() != 0) {
					if (turn % 2 != 0) {
						cout << "КОМПЬЮТЕР ХОДИТ!\n\n";
						if (!person.computer_attack(row, col, direction))
							turn++;
					}
					else {
						cout << "ИГРОК, ВАШ ХОД!\n\n";
 						if (!person.attack(computer))
							turn++;
					}
				}
				if (computer.getCount() == 0)
					cout << "ВЫ ПОБЕДИЛИ!\n";
				else
					cout << "ВЫ ПРОИГРАЛИ!\n";
				cout << "ПОЛЕ КОМПЬЮТЕРА\n";
				computer.showField();
				cout << "\n\nВАШЕ ПОЛЕ\n";
				person.showField();
				break;
			}
		case 2: {
			player number1{};
			player number2{};
			cout << "ИГРОК №1, РАСПОЛОЖИТЕ СВОИ КОРАБЛИ!\n\n";
			number1.start();
			cout << "ИГРОК №1 ЗАКОНЧИЛ РАССТАНОВКУ. НАЖМИТЕ ENTER И ПЕРЕДАЙТЕ УПРАВЛЕНИЕ ИГРОКУ №2\n";
			cin.ignore(10000, '\n'); // пропустить "хвост" предыдущего ввода
			cin.get();    // подождать нажатия Enter
			clearConsole(); // очистка консоли 
			cout << "ИГРОК №2, РАСПОЛОЖИТЕ СВОИ КОРАБЛИ!\n\n";
			number2.start();
			cout << "ИГРОК №2 ЗАКОНЧИЛ РАССТАНОВКУ. НАЖМИТЕ ENTER И ПЕРЕДАЙТЕ УПРАВЛЕНИЕ ИГРОКУ №1\n";
			cin.ignore(10000, '\n'); // пропустить "хвост" предыдущего ввода
			cin.get();    // подождать нажатия Enter
			clearConsole();
			int turn{ 1 }; // чей ход
			while (number1.getCount() != 0 && number2.getCount() != 0) {
				if (turn % 2 != 0) {
					cout << "ИГРОК №1, ВАШ ХОД!\n\n";
					if (!number1.attack(number2)) {
						turn++;
						cout << "ИГРОК №1 ВЫСТРЕЛИЛ МИМО. НАЖМИТЕ ENTER И НЕ ПОДСМАТРИВАЯ ПЕРЕДАЙТЕ УПРАВЛЕНИЕ ИГРОКУ №2\n";
						cin.ignore(10000, '\n'); // пропустить "хвост" предыдущего ввода
						cin.get();    // подождать нажатия Enter
						clearConsole(); // очистка консоли 
					}
				}
				else {
					cout << "ИГРОК №2, ВАШ ХОД!\n\n";
					if (!number2.attack(number1)) {
						turn++;
						cout << "ИГРОК №2 ВЫСТРЕЛИЛ МИМО. НАЖМИТЕ ENTER И НЕ ПОДСМАТРИВАЯ ПЕРЕДАЙТЕ УПРАВЛЕНИЕ ИГРОКУ №1\n";
						cin.ignore(10000, '\n'); // пропустить "хвост" предыдущего ввода
						cin.get();    // подождать нажатия Enter
						clearConsole(); // очистка консоли 
					}
				}
			}
			if (number1.getCount() == 0)
				cout << "ИГРОК №2 ПОБЕДИЛ!\n";
			else
				cout << "ИГРОК №1 ПОБЕДИЛ!\n";
			cout << "ПОЛЕ ИГРОКА №1\n";
			number1.showField(); 
			cout << "\n\nПОЛЕ ИГРОКА №2\n";
			number2.showField();
			break;
		}
		default:
			cout << "ERROR: НЕ СУЩЕСТВУЕТ РЕЖИМА ИГРЫ НА ТАКОЕ КОЛИЧЕСТВО ЧЕЛОВЕК\n";
			cout << "ПОПРОБУЙТЕ СНОВА\n\n";
			break;
		}
	} while (playersCount != 1 && playersCount != 2);
	return 0;
}
