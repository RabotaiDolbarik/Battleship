#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include "Player.h" 
using std::cout;
using std::cin;
using std::string;
void clearConsole() { // очистка консоли в зависимости от ОС
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}
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
				Player* computer{new Player};
				Player* person{new Player};
				computer->computer_start();
				cout << "КОМПЬЮТЕР РАССТАВИЛ ВСЕ КОРАБЛИ!\n\n";
				person->start();
				cout << "ВЫ УСПЕШНО РАССТАВИЛИ ВСЕ КОРАБЛИ! НАЖМИТЕ ENTER, ЧТОБЫ ПРОДОЛЖИТЬ\n";
				cin.ignore(10000, '\n'); // пропустить "хвост" предыдущего ввода
				cin.get();    // подождать нажатия Enter
				clearConsole();
				int turn{ 1 }; // чей ход
				int row{ 0 }, col{ 0 }, direction{ 0 }, count{1};
				while (computer->getCount() != 0 && person->getCount() != 0) {
					if (turn % 2 != 0) {
						cout << "КОМПЬЮТЕР ХОДИТ!\n\n";
						if (!person->computer_attack(row, col, direction))
							turn++;
					}
					else {
						cout << "ИГРОК, ВАШ ХОД!\n\n";
 						if (!person->attack(*computer))
							turn++;
					}
				}
				if (computer->getCount() == 0)
					cout << "ВЫ ПОБЕДИЛИ!\n";
				else
					cout << "ВЫ ПРОИГРАЛИ!\n";
				cout << "ПОЛЕ КОМПЬЮТЕРА\n";
				computer->showField();
				cout << "\n\nВАШЕ ПОЛЕ\n";
				person->showField();
				delete computer;
				delete person;
				break;
			}
		case 2: {
			Player* number1{new Player};
			Player* number2{new Player};
			cout << "ИГРОК №1, РАСПОЛОЖИТЕ СВОИ КОРАБЛИ!\n\n";
			number1->start();
			cout << "ИГРОК №1 ЗАКОНЧИЛ РАССТАНОВКУ. НАЖМИТЕ ENTER И ПЕРЕДАЙТЕ УПРАВЛЕНИЕ ИГРОКУ №2\n";
			cin.ignore(10000, '\n'); // пропустить "хвост" предыдущего ввода
			cin.get();    // подождать нажатия Enter
			clearConsole(); // очистка консоли 
			cout << "ИГРОК №2, РАСПОЛОЖИТЕ СВОИ КОРАБЛИ!\n\n";
			number2->start();
			cout << "ИГРОК №2 ЗАКОНЧИЛ РАССТАНОВКУ. НАЖМИТЕ ENTER И ПЕРЕДАЙТЕ УПРАВЛЕНИЕ ИГРОКУ №1\n";
			cin.ignore(10000, '\n'); // пропустить "хвост" предыдущего ввода
			cin.get();    // подождать нажатия Enter
			clearConsole();
			int turn{ 1 }; // чей ход
			while (number1->getCount() != 0 && number2->getCount() != 0) {
				if (turn % 2 != 0) {
					cout << "ИГРОК №1, ВАШ ХОД!\n\n";
					if (!number1->attack(*number2)) {
						turn++;
						cout << "ИГРОК №1 ВЫСТРЕЛИЛ МИМО. НАЖМИТЕ ENTER И ПЕРЕДАЙТЕ УПРАВЛЕНИЕ ИГРОКУ №2\n";
						cin.ignore(10000, '\n'); // пропустить "хвост" предыдущего ввода
						cin.get();    // подождать нажатия Enter
						clearConsole(); // очистка консоли 
						cout << "ИГРОК №2, НАЖМИТЕ ENTER, ЧТОБЫ НАЧАТЬ СТРЕЛЬБУ!\n";
						cin.get();    // подождать нажатия Enter
					}
				}
				else {
					cout << "ИГРОК №2, ВАШ ХОД!\n\n";
					if (!number2->attack(*number1)) {
						turn++;
						cout << "ИГРОК №2 ВЫСТРЕЛИЛ МИМО. НАЖМИТЕ ENTER И НЕ ПОДСМАТРИВАЯ ПЕРЕДАЙТЕ УПРАВЛЕНИЕ ИГРОКУ №1\n";
						cin.ignore(10000, '\n'); // пропустить "хвост" предыдущего ввода
						cin.get();    // подождать нажатия Enter
						clearConsole(); // очистка консоли 
						cout << "ИГРОК №1, НАЖМИТЕ ENTER, ЧТОБЫ НАЧАТЬ СТРЕЛЬБУ!\n";
						cin.get();    // подождать нажатия Enter
					}
				}
			}
			if (number1->getCount() == 0)
				cout << "ИГРОК №2 ПОБЕДИЛ!\n";
			else
				cout << "ИГРОК №1 ПОБЕДИЛ!\n";
			cout << "ПОЛЕ ИГРОКА №1\n";
			number1->showField();
			cout << "\n\nПОЛЕ ИГРОКА №2\n";
			number2->showField();
			delete number1;
			delete number2;
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
