#include <iostream>
#include <conio.h>
using namespace std;

bool main_flag = true;

void printBoard(char a[10]) {
    cout << a[7] << " " << a[8] << " " << a[9] << endl <<
        a[4] << " " << a[5] << " " << a[6] << endl <<
        a[1] << " " << a[2] << " " << a[3] << endl;
}

void playerMove(char a[10], char playerSymbol) {
    int move;
    cout << " Игрок " << (playerSymbol == 'x' ? "1" : "2") << " ваш ход: " << endl;
    move = _getch() - '0';
    if (move == -21) { 
        main_flag = false;
        return;
    }
    while (a[move] != '-') {
        cout << "Недопустимый ход. Попробуйте еще раз: ";
        move = _getch() - '0';
    }
    a[move] = playerSymbol;
    printBoard(a);
}

bool checkWin(char a[10], char playerSymbol) {
    int winConditions[8][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {1, 5, 9}, {3, 5, 7}, {1, 4, 7}, {2, 5, 8}, {3, 6, 9} };
    for (int i = 0; i < 8; i++) {
        if (a[winConditions[i][0]] == playerSymbol && a[winConditions[i][1]] == playerSymbol && a[winConditions[i][2]] == playerSymbol) {
            cout << "Игрок " << (playerSymbol == 'x' ? "1" : "2") << " выиграл!!";
            main_flag = false;
            return true;
        }
    }
    return false;
}

int main() {
    setlocale(LC_ALL, "ru");

    char a[10] = { '-', '-','-','-','-','-','-','-','-', '-' };
    cout << "7 8 9" << endl << "4 5 6" << endl << "1 2 3" << endl << endl;

    while (main_flag) {
        printBoard(a);

        for (int i = 0; i < 9; i++) {
            playerMove(a, i % 2 == 0 ? 'x' : 'o');
            if (!main_flag) {
                cout << "Игра прервана";
                return 0;
            }
            if (checkWin(a, i % 2 == 0 ? 'x' : 'o')) {
                return 0;
            }
        }

        cout << "Ничья";
    }
}
