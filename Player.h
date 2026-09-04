#ifndef _PLAYER_H_
#define _PLAYER_H_

using std::cout;
enum { SIZE = 10 };
class Player
{
	char field[SIZE + 2][SIZE + 2]{};
	char hidenField[SIZE + 2][SIZE + 2]{};
	int countShips{ 0 };
	void renderField(char(&f)[SIZE + 2][SIZE + 2]);
	void printFieldRow(const int& row);
	void printHiddenFieldRow(const int& row);

	void createCoords(int& x, int& number);
	bool close(int x, int y);

	void createShip(int len);
	void computer_createShip(int len);

	void round(int& row, int& col);
	bool is_correct(int& row, int& col, int& direct);
	bool miss(int& row, int& col) {
		cout << "ÊÎÌÏÜÞÒÅÐ ÂÛÑÒÐÅËÈË ÌÈÌÎ!\n";
		showField();
		return false;
	}
public:
	int getCount() {return countShips;}
	void showField() {return renderField(field);}
	void showHiddenField() {return renderField(hidenField);}

	void start();
	void computer_start();

	bool attack(Player& enemy);
	bool computer_attack(int& row, int& col, int& direct);
};
#endif
