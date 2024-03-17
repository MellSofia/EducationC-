#include <iostream>
#include <chrono>
#include<cstdarg>
using namespace std;
void kr(char a[10]) {
    cout << a[1] << " " << a[2] << " " << a[3] << endl <<
        a[4] << " " << a[5] << " " << a[6] << endl
        << a[7] << " " << a[8] << " " << a[9] << endl;
}
void p1(char a[10]) {
    int b;
    cout << " Игрок 1 На какое место ставить ваш знак: ";
    cin >> b;
    while (a[b] != '-') { cin >> b; }
    a[b] = 'x';
    kr(a);
}
void p2(char a[10]) {
    int c;
    cout << " Игрок 2 На какое место ставить ваш знак: ";
    cin >> c;
    while (a[c] != '-') { cin >> c; }
    a[c] = 'o';
    kr(a);
}
int win1(char a[10], int k) {
    if ((a[1] == 'x') && (a[2] == 'x') && (a[3] == 'x')) { cout << "1 player Winn!!"; k = 1; return 1; }
    if ((a[4] == 'x') && (a[5] == 'x') && (a[6] == 'x')) { cout << "1 player Winn!!"; k = 1; return 1; }
    if ((a[7] == 'x') && (a[8] == 'x') && (a[9] == 'x')) { cout << "1 player Winn!!"; k = 1; return 1; }
    if ((a[1] == 'x') && (a[5] == 'x') && (a[9] == 'x')) { cout << "1 player Winn!!"; k = 1; return 1; }
    if ((a[3] == 'x') && (a[5] == 'x') && (a[7] == 'x')) { cout << "1 player Winn!!"; k = 1; return 1; }
    if ((a[1] == 'x') && (a[4] == 'x') && (a[7] == 'x')) { cout << "1 player Winn!!"; k = 1; return 1; }
    if ((a[2] == 'x') && (a[5] == 'x') && (a[8] == 'x')) { cout << "1 player Winn!!"; k = 1; return 1; }
    if ((a[3] == 'x') && (a[6] == 'x') && (a[9] == 'x')) { cout << "1 player Winn!!"; k = 1; return 1; }
    else k = 1;
}
int win2(char a[10], int k) {
    if ((a[1] == 'o') && (a[2] == 'o') && (a[3] == 'o')) { cout << "2 player Winn!!"; k = 1; return 1; }
    if ((a[4] == 'o') && (a[5] == 'o') && (a[6] == 'o')) { cout << "2 player Winn!!"; k = 1; return 1; }
    if ((a[7] == 'o') && (a[8] == 'o') && (a[9] == 'o')) { cout << "2 player Winn!!"; k = 1; return 1; }
    if ((a[1] == 'o') && (a[5] == 'o') && (a[9] == 'o')) { cout << "2 player Winn!!"; k = 1; return 1; }
    if ((a[3] == 'o') && (a[5] == 'o') && (a[7] == 'o')) { cout << "2 player Winn!!"; k = 1; return 1; }
    if ((a[1] == 'o') && (a[4] == 'o') && (a[7] == 'o')) { cout << "2 player Winn!!"; k = 1; return 1; }
    if ((a[2] == 'o') && (a[5] == 'o') && (a[8] == 'o')) { cout << "2 player Winn!!"; k = 1; return 1; }
    if ((a[3] == 'o') && (a[6] == 'o') && (a[9] == 'o')) { cout << "2 player Winn!!"; k = 1; return 1; }
    else k = 0;
}
int main() {
    char a[10] = { '-', '-','-','-','-','-','-','-','-', '-' };
    int k = 0; int z = 0;
    cout << "1 2 3" << endl << "4 5 6" << endl << "7 8 9" << endl << endl;
    kr(a);
    p1(a);  //1
    win1(a, k);
    p2(a);  //2
    win2(a, k);
    p1(a);  //3
    win1(a, k);
    p2(a);  //4
    win2(a, k);
    p1(a);  //5
    if (win1(a, k) == 1) { return 0; }
    p2(a);  //6
    if (win2(a, k) == 1) { return 0; }
    p1(a);  //7
    if (win1(a, k) == 1) { return 0; }
    p2(a);  //8
    if (win2(a, k) == 1) { return 0; }
    p1(a);  //9
    if (win1(a, k) == 1) { return 0; }
    if (k == 0) cout << "Nichia";
}