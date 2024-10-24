#include <bits/stdc++.h>
#include <windows.h>
#include <fstream>
#include <conio.h>
#define END Timer += double(clock() - startTime) / (double) CLOCKS_PER_SEC;
#define EXITEND Timer += double(clock() - st) / (double) CLOCKS_PER_SEC;
using namespace std;

char x, y;
double Timer = 0;
bool GameStatus = false, SaveCheck = false, ExitInMove = false, Gameover = false;
int CheckColor = 0, Turn = 1, TurnCheck = 0;
long long int NumOfGames = 0;
string ExitCheck, Fix, Enter, Moves, NorL;
int coordinates[3][3];

struct {
    string name = "Player_1";
    char symbol = 'X';
    long double score = 0;
    int Number_Of_GamePieces = 14;
} Player_1;

struct {
    string name = "Player_2";
    char symbol = 'O';
    long double score = 0;
    int Number_Of_GamePieces = 14;
} Player_2;

char** HexGrid = new char* [9];

void Form_HexGrid () {
    for (int i = 0; i < 9; i++) {
        if (i < 5)
            HexGrid[i] = new char[(5 + i)];
        else
            HexGrid[i] = new char[8 - (i % 5)];
    }
    for (int i = 0; i < 9; i++) {
        int row;
        if (i < 5)
            row = (5 + i);
        else
            row = (8 - (i % 5));
        if (i == 0 or i == 1) {
            for (int j = 0; j < row; j++)
                HexGrid[i][j] = 'X';
        }
        else if (i == 2) {
            for (int j = 0; j < row; j++) {
                if (j >= 2 and j <= 4)
                    HexGrid[i][j] = 'X';
                else
                    HexGrid[i][j] = '#';
            }
        }
        else if (i == 6) {
            for (int j = 0; j < row; j++) {
                if (j >= 2 and j <= 4)
                    HexGrid[i][j] = 'O';
                else
                    HexGrid[i][j] = '#';
            }
        }
        else if (i == 7 or i == 8) {
            for (int j = 0; j < row; j++)
                HexGrid[i][j] = 'O';
        }
        else
            for (int j = 0; j < row; j++)
                HexGrid[i][j] = '#';
    }
}

char** TempHex = new char* [9];

void Form_Temp() {
    for (int i = 0; i < 9; i++) {
        if (i < 5)
            TempHex[i] = new char[(5 + i)];
        else
            TempHex[i] = new char[8 - (i % 5)];
    }
    for (int i = 0; i < 9; i++) {
        int row;
        if (i < 5)
            row = (5 + i);
        else
            row = (8 - (i % 5));
        for (int j = 0; j < row; j++)
            TempHex[i][j] = HexGrid[i][j];
    }
}

string space (int spaces) {
    string temp = "";
    for (int i = 0; i < spaces; i++)
        temp += " ";
    return temp;
}

void Print (char** MyTemp) {
    cout << "---------------------" << '\n';
    for (int i = 0; i < 9; i++) {
        int row;
        int temp;
        if (i < 5) {
            row = (5 + (i % 5));
            temp = (9 - 5 - (i % 5));
        }
        else {
            row = (8 - (i % 5));
            temp = ((i % 5) + 1);
        }
        string spaces = space (temp);
        cout << i << " - ";
        cout << spaces;
        for (int j = 0; j < row; j++)
            cout << MyTemp[i][j] << " ";
        cout << '\n';
    }
    cout << "---------------------" << '\n';
}

void PrintChart () {
    Player_1.score = ((100 / (14 - Player_1.Number_Of_GamePieces + 1)) + ((14 - Player_2.Number_Of_GamePieces) * 10));
    Player_2.score = ((100 / (14 - Player_2.Number_Of_GamePieces + 1)) + ((14 - Player_1.Number_Of_GamePieces) * 10));
    cout << "|===== Abalone =====" << '\n';
    cout << "| S ----------------" << '\n';
    cout << "| C | 1 : " << Player_1.name << " : " << Player_1.score << '\n';
    cout << "| O ----------------" << "      Time : " << "{ " << Timer << " s }" << '\n';
    cout << "| R | 2 : " << Player_2.name << " : " << Player_2.score << '\n';
    cout << "| E ----------------" << '\n' << '\n';
    if (Turn == 1)
        cout << "  { Player " << Turn << " Turn }" << '\n' << '\n';
    else
        cout << "  { Player " << Turn << " Turn }" << '\n' << '\n';
    Print(HexGrid);
    cout << '\n';
}

bool Right () {
    if (Moves == "1") {
        int X = x - '0';
        int Y = y - '0';
        if (X < 5) {
            if ((Y + 1) > (X + 5 - 1))
                return false;
        }
        else {
            if ((Y + 1) > (8 - (X % 5) - 1))
                return false;
        }
        if (HexGrid[X][Y + 1] == '#') {
            TempHex[X][Y + 1] = 'D';
            return true;
        }
        else
            return false;
    }
    else if (Moves == "2") {
        int X = coordinates[0][0];
        int Y = coordinates[0][1];
        if (X < 5) {
            if ((Y + 1) > (X + 5 - 1))
                return false;
        }
        else {
            if ((Y + 1) > (8 - (X % 5) - 1))
                return false;
        }
        if (X == coordinates[1][0] and (Y + 1) == coordinates[1][1])
            return true;
        else
            return false;
    }
}

bool To_Right () {
    bool ToRightCheckone = false;
    bool ToRightChecktwo = false;
    int X = coordinates[0][0];
    int Y = coordinates[0][1];
    if (X < 5) {
        if ((Y + 1) > (X + 5 - 1))
            return false;
    }
    else {
        if ((Y + 1) > (8 - (X % 5) - 1))
            return false;
    }
    if (HexGrid[X][Y + 1] == '#')
        ToRightCheckone = true;
    else
        return false;
    X = coordinates[1][0];
    Y = coordinates[1][1];
    if (X < 5) {
        if ((Y + 1) > (X + 5 - 1))
            return false;
    }
    else {
        if ((Y + 1) > (8 - (X % 5) - 1))
            return false;
    }
    if (HexGrid[X][Y + 1] == '#')
        ToRightChecktwo = true;
    else
        return false;
    if (ToRightCheckone == true and ToRightChecktwo == true) {
        return true;
    }
}

bool To_Right3 () {
    bool ToRightCheckone = false;
    bool ToRightChecktwo = false;
    bool ToRightCheckthree = false;
    int X = coordinates[0][0];
    int Y = coordinates[0][1];
    if (X < 5) {
        if ((Y + 1) > (X + 5 - 1))
            return false;
    }
    else {
        if ((Y + 1) > (8 - (X % 5) - 1))
            return false;
    }
    if (HexGrid[X][Y + 1] == '#')
        ToRightCheckone = true;
    else
        return false;
    X = coordinates[1][0];
    Y = coordinates[1][1];
    if (X < 5) {
        if ((Y + 1) > (X + 5 - 1))
            return false;
    }
    else {
        if ((Y + 1) > (8 - (X % 5) - 1))
            return false;
    }
    if (HexGrid[X][Y + 1] == '#')
        ToRightChecktwo = true;
    else
        return false;
    X = coordinates[2][0];
    Y = coordinates[2][1];
    if (X < 5) {
        if ((Y + 1) > (X + 5 - 1))
            return false;
    }
    else {
        if ((Y + 1) > (8 - (X % 5) - 1))
            return false;
    }
    if (HexGrid[X][Y + 1] == '#')
        ToRightChecktwo = true;
    else
        return false;
    if (ToRightCheckone == true and ToRightChecktwo == true and ToRightCheckthree == true) {
        return true;
    }
}

void By_Right (int i, int j) { 
    char tttptpt = HexGrid[i][j + 1];
    HexGrid[i][j + 1] = HexGrid[i][j];
    HexGrid[i][j] = tttptpt;
}

bool Right_3 (int i, int j, int ii, int jj) {
    if (i < 5) {
        if ((j + 1) > (i + 5 - 1))
            return false;
    }
    else {
        if ((j + 1) > (8 - (i % 5) - 1))
            return false;
    }
    if (i == ii and (j + 1) == jj)
        return true;
    else
        return false;
}

bool Left () {
    if (Moves == "1") {
        int X = x - '0';
        int Y = y - '0';
        if ((Y - 1) < 0)
            return false;
        if (HexGrid[X][Y - 1] == '#') {
            TempHex[X][Y - 1] = 'A';
            return true;
        }
        else
            return false;
    }
    else if (Moves == "2") {
        int X = coordinates[0][0];
        int Y = coordinates[0][1];
        if ((Y - 1) < 0)
            return false;
        if (X == coordinates[1][0] and (Y - 1) == coordinates[1][1])
            return true;
        else
            return false;
    }
}

bool To_Left () {
    bool ToRightCheckone = false;
    bool ToRightChecktwo = false;
    int X = coordinates[0][0];
    int Y = coordinates[0][1];
    if ((Y - 1) < 0)
        return false;
    if (HexGrid[X][Y - 1] == '#')
        ToRightCheckone = true;
    else
        return false;
    X = coordinates[1][0];
    Y = coordinates[1][1];
    if ((Y - 1) < 0)
        return false;
    if (HexGrid[X][Y - 1] == '#')
        ToRightChecktwo = true;
    else
        return false;
    if (ToRightCheckone == true and ToRightChecktwo == true) {
        return true;
    }
}

bool To_Left3 () {
    bool ToRightCheckone = false;
    bool ToRightChecktwo = false;
    bool ToRightCheckthree = false;
    int X = coordinates[0][0];
    int Y = coordinates[0][1];
    if ((Y - 1) < 0)
        return false;
    if (HexGrid[X][Y - 1] == '#')
        ToRightCheckone = true;
    else
        return false;
    X = coordinates[1][0];
    Y = coordinates[1][1];
    if ((Y - 1) < 0)
        return false;
    if (HexGrid[X][Y - 1] == '#')
        ToRightChecktwo = true;
    else
        return false;
    X = coordinates[2][0];
    Y = coordinates[2][1];
    if ((Y - 1) < 0)
        return false;
    if (HexGrid[X][Y - 1] == '#')
        ToRightChecktwo = true;
    else
        return false;
    if (ToRightCheckone == true and ToRightChecktwo == true and ToRightCheckthree == true) {
        return true;
    }
}

void By_Left (int i, int j) {
    char tttptpt = HexGrid[i][j - 1];
    HexGrid[i][j - 1] = HexGrid[i][j];
    HexGrid[i][j] = tttptpt;
}

bool Left_3 (int i, int j, int ii, int jj) {
    if ((j - 1) < 0)
        return false;
    if (i == ii and (j - 1) == jj)
        return true;
    else
        return false;
}

bool UpRight () {
    if (Moves == "1") {
        int X = x - '0';
        int Y = y - '0';
        if ((X - 1) < 0)
            return false;
        if (X < 5) {
            if (Y > (X - 1 + 5 - 1))
                return false;
            if (HexGrid[X - 1][Y] == '#') {
                TempHex[X - 1][Y] = 'E';
                return true;
            }
            else
                return false;
        }
        else {
            if (HexGrid[X - 1][Y + 1] == '#') {
                TempHex[X - 1][Y + 1] = 'E';
                return true;
            }
            else
                return false;        
        }
    }
    else if (Moves == "2") {
        int X = coordinates[0][0];
        int Y = coordinates[0][1];
        if ((X - 1) < 0)
            return false;
        if (X < 5) {
            if (Y > (X - 1 + 5 - 1))
                return false;
            if ((X - 1) == coordinates[1][0] and (Y) == coordinates[1][1]) 
                return true;
            else
                return false;
        }
        else {
            if (X - 1 == coordinates[1][0] and (Y + 1) == coordinates[1][1]) 
                return true;
            else
                return false;        
        }
    }
}

bool To_UpRight () {
    bool ToRightCheckone_1 = false;
    bool ToRightChecktwo_1 = false;
    bool ToRightCheckone_2 = false;
    bool ToRightChecktwo_2 = false;
    int X = coordinates[0][0];
    int Y = coordinates[0][1];
    if ((X - 1) < 0)
            return false;
    if (X < 5) {
        if (Y > (X - 1 + 5 - 1))
            return false;
        if (HexGrid[X - 1][Y] == '#')
            ToRightCheckone_1 = true;
        else
            return false;
    }
    else {
        if (HexGrid[X - 1][Y + 1] == '#')
            ToRightCheckone_2 = true;
        else
            return false;        
    }
    X = coordinates[1][0];
    Y = coordinates[1][1];
    if ((X - 1) < 0)
            return false;
    if (X < 5) {
        if (Y > (X - 1 + 5 - 1))
            return false;
        if (HexGrid[X - 1][Y] == '#')
            ToRightChecktwo_1 = true;
        else
            return false;
    }
    else {
        if (HexGrid[X - 1][Y + 1] == '#')
            ToRightChecktwo_2 = true;
        else
            return false;        
    }
    if (ToRightChecktwo_1 == true and ToRightCheckone_1 == true) {
        return true;
    }
    else if (ToRightChecktwo_2 == true and ToRightCheckone_2 == true) {
        return true;
    }
}

bool To_UpRight3 () {
    bool ToRightCheckone_1 = false;
    bool ToRightChecktwo_1 = false;
    bool ToRightCheckthree_1 = false;
    bool ToRightCheckone_2 = false;
    bool ToRightChecktwo_2 = false;
    bool ToRightCheckthree_2 = false;
    int X = coordinates[0][0];
    int Y = coordinates[0][1];
    if ((X - 1) < 0)
            return false;
    if (X < 5) {
        if (Y > (X - 1 + 5 - 1))
            return false;
        if (HexGrid[X - 1][Y] == '#')
            ToRightCheckone_1 = true;
        else
            return false;
    }
    else {
        if (HexGrid[X - 1][Y + 1] == '#')
            ToRightCheckone_2 = true;
        else
            return false;        
    }
    X = coordinates[1][0];
    Y = coordinates[1][1];
    if ((X - 1) < 0)
            return false;
    if (X < 5) {
        if (Y > (X - 1 + 5 - 1))
            return false;
        if (HexGrid[X - 1][Y] == '#')
            ToRightChecktwo_1 = true;
        else
            return false;
    }
    else {
        if (HexGrid[X - 1][Y + 1] == '#')
            ToRightChecktwo_2 = true;
        else
            return false;        
    }
    X = coordinates[2][0];
    Y = coordinates[2][1];
    if ((X - 1) < 0)
            return false;
    if (X < 5) {
        if (Y > (X - 1 + 5 - 1))
            return false;
        if (HexGrid[X - 1][Y] == '#')
            ToRightCheckthree_1 = true;
        else
            return false;
    }
    else {
        if (HexGrid[X - 1][Y + 1] == '#')
            ToRightCheckthree_2 = true;
        else
            return false;        
    }
    if (ToRightChecktwo_1 == true and ToRightCheckone_1 == true) {
        return true;
    }
    else if (ToRightChecktwo_2 == true and ToRightCheckone_2 == true) {
        return true;
    }
}

void By_UpRight (int i, int j) {
    if (i < 5) {
        char tttptpt = HexGrid[i - 1][j];
        HexGrid[i - 1][j] = HexGrid[i][j];
        HexGrid[i][j] = tttptpt;
    }
    else {
        char tttptpt = HexGrid[i - 1][j + 1];
        HexGrid[i - 1][j + 1] = HexGrid[i][j];
        HexGrid[i][j] = tttptpt;
    }
}

bool UpRight_3 (int i, int j, int ii, int jj) {
    if ((i - 1) < 0)
        return false;
    if (i < 5) {
        if (j > (i - 1 + 5 - 1))
            return false;
        if ((i - 1) == ii and (j) == jj) 
            return true;
        else
            return false;
    }
    else {
        if (i - 1 == ii and (j + 1) == jj) 
            return true;
        else
            return false;        
    }
}

bool UpLeft () {
    if (Moves ==  "1") {
        int X = x - '0';
        int Y = y - '0';
        if ((X - 1) < 0)
            return false;
        if (X < 5) {
            if ((Y - 1) < 0)
                return false;
            if (HexGrid[X - 1][Y - 1] == '#') {
                TempHex[X - 1][Y - 1] = 'Q';
                return true;
            }
            else
                return false;
        }
        else {
            if (HexGrid[X - 1][Y] == '#') {
                TempHex[X - 1][Y] = 'Q';
                return true;
            }
            else
                return false;
        }
    }
    else if (Moves == "2") {
        int X = coordinates[0][0];
        int Y = coordinates[0][1];
        if ((X - 1) < 0)
            return false;
        if (X < 5) {
            if ((Y - 1) < 0)
                return false;
            if ((X - 1) == coordinates[1][0] and (Y - 1) == coordinates[1][1])
                return true;
            else
                return false;
        }
        else {
            if ((X - 1) == coordinates[1][0] and (Y) == coordinates[1][1])
                return true;
            else
                return false;
        }
    }
}

bool To_UpLeft () {
    bool ToRightCheckone_1 = false;
    bool ToRightChecktwo_1 = false;
    bool ToRightCheckone_2 = false;
    bool ToRightChecktwo_2 = false;
    int X = coordinates[0][0];
    int Y = coordinates[0][1];
    if ((X - 1) < 0)
        return false;
    if (X < 5) {
        if ((Y - 1) < 0)
            return false;
        if (HexGrid[X - 1][Y - 1] == '#')
            ToRightCheckone_1 = true;
        else
            return false;
    }
    else {
        if (HexGrid[X - 1][Y] == '#')
            ToRightCheckone_2 = true;
        else
            return false;
    }
    X = coordinates[1][0];
    Y = coordinates[1][1];
    if ((X - 1) < 0)
        return false;
    if (X < 5) {
        if ((Y - 1) < 0)
            return false;
        if (HexGrid[X - 1][Y - 1] == '#')
            ToRightChecktwo_1 = true;
        else
            return false;
    }
    else {
        if (HexGrid[X - 1][Y] == '#')
            ToRightChecktwo_2 = true;
        else
            return false;
    }
    if (ToRightChecktwo_1 == true and ToRightCheckone_1 == true) {
        return true;
    }
    else if (ToRightChecktwo_2 == true and ToRightCheckone_2 == true) {
        return true;
    }
}

void By_UpLeft (int i, int j) {
    if (i < 5) {
        char tttptpt = HexGrid[i - 1][j - 1];
        HexGrid[i - 1][j - 1] = HexGrid[i][j];
        HexGrid[i][j] = tttptpt;
    }
    else {
        char tttptpt = HexGrid[i - 1][j];
        HexGrid[i - 1][j] = HexGrid[i][j];
        HexGrid[i][j] = tttptpt;
    }
}

bool UpLeft_3 (int i, int j, int ii, int jj) {
    if ((i - 1) < 0)
        return false;
    if (i < 5) {
        if ((j - 1) < 0)
            return false;
        if ((i - 1) == ii and (j - 1) == jj)
            return true;
        else
            return false;
    }
    else {
        if ((i - 1) == ii and (j) == jj)
            return true;
        else
            return false;
    }
}

bool DownRight () {
    if (Moves == "1") {
        int X = x - '0';
        int Y = y - '0';
        if ((X + 1) > 8)
            return false;
        if (X < 4) {
            if (HexGrid[X + 1][Y + 1] == '#') {
                TempHex[X + 1][Y + 1] = 'C';
                return true;
            }
            else
                return false;
        }
        else {
            if ((Y + 1) > (8 - ((X + 1) % 5)))
                return false;
            if (HexGrid[X + 1][Y] == '#') {
                TempHex[X + 1][Y] = 'C';
                return true;
            }
            else
                return false;
        }
    }
    else if (Moves == "2") {
        int X = coordinates[0][0];
        int Y = coordinates[0][1];
        if ((X + 1) > 8)
            return false;
        if (X < 4) {
            if ((X + 1) == coordinates[1][0] and (Y + 1) == coordinates[1][1])
                return true;
            else
                return false;
        }
        else {
            if ((Y + 1) > (8 - ((X + 1) % 5)))
                return false;
            if ((X + 1) == coordinates[1][0] and (Y) == coordinates[1][1])
                return true;
            else
                return false;
        }
    }
}

bool To_DownRight () {
    bool ToRightCheckone_1 = false;
    bool ToRightChecktwo_1 = false;
    bool ToRightCheckone_2 = false;
    bool ToRightChecktwo_2 = false;
    int X = coordinates[0][0];
    int Y = coordinates[0][1];
    if ((X + 1) > 8)
        return false;
    if (X < 4) {
        if (HexGrid[X + 1][Y + 1] == '#')
            ToRightCheckone_1 = true;
        else
            return false;
    }
    else {
        if ((Y + 1) > (8 - ((X + 1) % 5)))
            return false;
        if (HexGrid[X + 1][Y] == '#')
            ToRightCheckone_2 = true;
        else
            return false;
    }
    X = coordinates[1][0];
    Y = coordinates[1][1];
    if ((X + 1) > 8)
        return false;
    if (X < 4) {
        if (HexGrid[X + 1][Y + 1] == '#')
            ToRightChecktwo_1 = true;
        else
            return false;
    }
    else {
        if ((Y + 1) > (8 - ((X + 1) % 5)))
            return false;
        if (HexGrid[X + 1][Y] == '#')
            ToRightChecktwo_2 = true;
        else
            return false;
    }
    if (ToRightChecktwo_1 == true and ToRightCheckone_1 == true) {
        return true;
    }
    else if (ToRightChecktwo_2 == true and ToRightCheckone_2 == true) {
        return true;
    }
}

void By_DownRight (int i, int j) {
    if (i < 4) {
        char tttptpt = HexGrid[i + 1][j + 1];
        HexGrid[i + 1][j + 1] = HexGrid[i][j];
        HexGrid[i][j] = tttptpt;
    }
    else {
        char tttptpt = HexGrid[i + 1][j];
        HexGrid[i + 1][j] = HexGrid[i][j];
        HexGrid[i][j] = tttptpt;
    }
}

bool DownRight_3 (int i, int j, int ii, int jj) {
    if ((i + 1) > 8)
        return false;
    if (i < 4) {
        if ((i + 1) == ii and (j + 1) == jj)
            return true;
        else
            return false;
    }
    else {
        if ((j + 1) > (8 - ((i + 1) % 5)))
            return false;
        if ((i + 1) == ii and (j) == jj)
            return true;
        else
            return false;
    }
}

bool DownLeft () {
    if (Moves == "1") {
        int X = x - '0';
        int Y = y - '0';
        if ((X + 1) > 8)
            return false;
        if (X < 4) {
            if (HexGrid[X + 1][Y] == '#') {
                TempHex[X + 1][Y] = 'Z';
                return true;
            }
            else
                return false;
        }
        else {
            if ((Y - 1) < 0)
                return false;
            if (HexGrid[X + 1][Y - 1] == '#') {
                TempHex[X + 1][Y - 1] = 'Z';
                return true;
            }
            else
                return false;
        }
    }
    else if (Moves == "2") {
        int X = coordinates[0][0];
        int Y = coordinates[0][1];
        if ((X + 1) > 8)
            return false;
        if (X < 4) {
            if ((X + 1) == coordinates[1][0] and (Y) == coordinates[1][1])
                return true;
            else
                return false;
        }
        else {
            if ((Y - 1) < 0)
                return false;
            if ((X + 1) == coordinates[1][0] and (Y - 1) == coordinates[1][1])
                return true;
            else
                return false;
        }
    }
}

bool To_DownLeft () {
    bool ToRightCheckone_1 = false;
    bool ToRightChecktwo_1 = false;
    bool ToRightCheckone_2 = false;
    bool ToRightChecktwo_2 = false;
    int X = coordinates[0][0];
    int Y = coordinates[0][1];
    if ((X + 1) > 8)
        return false;
    if (X < 4) {
        if (HexGrid[X + 1][Y] == '#')
            ToRightCheckone_1 = true;
        else
            return false;
    }
    else {
        if ((Y - 1) < 0)
            return false;
        if (HexGrid[X + 1][Y - 1] == '#')
            ToRightCheckone_2 = true;
        else
            return false;
    }
    X = coordinates[1][0];
    Y = coordinates[1][1];
    if ((X + 1) > 8)
        return false;
    if (X < 4) {
        if (HexGrid[X + 1][Y] == '#')
            ToRightChecktwo_1 = true;
        else
            return false;
    }
    else {
        if ((Y - 1) < 0)
            return false;
        if (HexGrid[X + 1][Y - 1] == '#')
            ToRightChecktwo_2 = true;
        else
            return false;
    }
    if (ToRightChecktwo_1 == true and ToRightCheckone_1 == true) {
        return true;
    }
    else if (ToRightChecktwo_2 == true and ToRightCheckone_2 == true) {
        return true;
    }
}

void By_DownLeft (int i, int j) {
    if (i < 4) {
        char tttptpt = HexGrid[i + 1][j];
        HexGrid[i + 1][j] = HexGrid[i][j];
        HexGrid[i][j] = tttptpt;
    }
    else {
        char tttptpt = HexGrid[i + 1][j - 1];
        HexGrid[i + 1][j - 1] = HexGrid[i][j];
        HexGrid[i][j] = tttptpt;
    }
}

bool DownLeft_3 (int i, int j, int ii, int jj) {
    if ((i + 1) > 8)
        return false;
    if (i < 4) {
        if ((i + 1) == ii and (j) == jj)
            return true;
        else
            return false;
    }
    else {
        if ((j - 1) < 0)
            return false;
        if ((i + 1) == ii and (j - 1) == jj)
            return true;
        else
            return false;
    }
}

bool Push_Right () {
    int X = coordinates[1][0];
    int Y = coordinates[1][1];
    if (X < 5) {
        if ((Y + 1) > (X + 5 - 1))
            return false;
    }
    else { 
        if ((Y + 1) > (8 - (X % 5) - 1))
            return false;
    }
    bool Out = false;
    if (X < 5) { 
        if ((Y + 2) > (X + 5 - 1))
            Out = true;
    }
    else { 
        if ((Y + 2) > (8 - (X % 5) - 1))
            Out = true;
    }
    bool Out2 = false;
    if (X < 5) { 
        if ((Y + 3) > (X + 5 - 1))
            Out2 = true;
    }
    else { 
        if ((Y + 3) > (8 - (X % 5) - 1))
            Out2 = true;
    }
    bool Out3 = false;
    if (X < 5) { 
        if ((Y + 4) > (X + 5 - 1))
            Out3 = true;
    }
    else { 
        if ((Y + 4) > (8 - (X % 5) - 1))
            Out3 = true;
    }
    if (Turn == 1) {
        if (HexGrid[X][Y + 1] == Player_2.symbol and Out == true) {
            Player_2.Number_Of_GamePieces--;
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == '#' and Out == false) {
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_2.symbol and Out == false and HexGrid[X][Y + 2] == '#') {
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_1.symbol and Out == false and HexGrid[X][Y + 2] == '#') {
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_1.symbol and Out == false and HexGrid[X][Y + 2] == Player_2.symbol and Out2 == true) {
            Player_2.Number_Of_GamePieces--;
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_1.symbol and Out == false and HexGrid[X][Y + 2] == Player_2.symbol and Out2 == false and HexGrid[X][Y + 3] == '#') {
            HexGrid[X][Y + 3] = HexGrid[X][Y + 2];
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_1.symbol and Out == false and HexGrid[X][Y + 2] == Player_2.symbol and Out2 == false and HexGrid[X][Y + 3] == Player_2.symbol and Out3 == true) {
            Player_2.Number_Of_GamePieces--;
            HexGrid[X][Y + 3] = HexGrid[X][Y + 2];
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_1.symbol and Out == false and HexGrid[X][Y + 2] == Player_2.symbol and Out2 == false and HexGrid[X][Y + 3] == Player_2.symbol and Out3 == false and HexGrid[X][Y + 4] == '#') {
            HexGrid[X][Y + 4] = HexGrid[X][Y + 3];
            HexGrid[X][Y + 3] = HexGrid[X][Y + 2];
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        return false;
    }
    else if (Turn == 2) {
        if (HexGrid[X][Y + 1] == Player_1.symbol and Out == true) {
            Player_1.Number_Of_GamePieces--;
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == '#' and Out == false) {
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_1.symbol and Out == false and HexGrid[X][Y + 2] == '#') {
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_2.symbol and Out == false and HexGrid[X][Y + 2] == '#') {
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_2.symbol and Out == false and HexGrid[X][Y + 2] == Player_1.symbol and Out2 == true) {
            Player_1.Number_Of_GamePieces--;
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_2.symbol and Out == false and HexGrid[X][Y + 2] == Player_1.symbol and Out2 == false and HexGrid[X][Y + 3] == '#') {
            HexGrid[X][Y + 3] = HexGrid[X][Y + 2];
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_2.symbol and Out == false and HexGrid[X][Y + 2] == Player_1.symbol and Out2 == false and HexGrid[X][Y + 3] == Player_2.symbol and Out3 == true) {
            Player_1.Number_Of_GamePieces--;
            HexGrid[X][Y + 3] = HexGrid[X][Y + 2];
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y + 1] == Player_2.symbol and Out == false and HexGrid[X][Y + 2] == Player_1.symbol and Out2 == false and HexGrid[X][Y + 3] == Player_1.symbol and Out3 == false and HexGrid[X][Y + 4] == '#') {
            HexGrid[X][Y + 4] = HexGrid[X][Y + 3];
            HexGrid[X][Y + 3] = HexGrid[X][Y + 2];
            HexGrid[X][Y + 2] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = '#';
            return true;
        }
        return false;
    }
}

bool Push_Left () {
    int X = coordinates[1][0];
    int Y = coordinates[1][1];
    if ((Y - 1) < 0)
        return false;
    bool Out = false;
    if ((Y - 2) < 0)
        Out = true;
    bool Out2 = false;
    if ((Y - 3) < 0)
        Out2 = true;
    bool Out3 = false;
    if ((Y - 4) < 0)
        Out3 = true;
    if (Turn == 1) {
        if (HexGrid[X][Y - 1] == Player_2.symbol and Out == true) {
            Player_2.Number_Of_GamePieces--;
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == '#' and Out == false) {
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_2.symbol and Out == false and HexGrid[X][Y - 2] == '#') {
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_1.symbol and Out == false and HexGrid[X][Y - 2] == '#') {
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_1.symbol and Out == false and HexGrid[X][Y - 2] == Player_2.symbol and Out2 == true) {
            Player_2.Number_Of_GamePieces--;
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_1.symbol and Out == false and HexGrid[X][Y - 2] == Player_2.symbol and Out2 == false and HexGrid[X][Y - 3] == '#') {
            HexGrid[X][Y - 3] = HexGrid[X][Y - 2];
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_1.symbol and Out == false and HexGrid[X][Y - 2] == Player_2.symbol and Out2 == false and HexGrid[X][Y - 3] == Player_2.symbol and Out3 == true) {
            Player_2.Number_Of_GamePieces--;
            HexGrid[X][Y - 3] = HexGrid[X][Y - 2];
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_1.symbol and Out == false and HexGrid[X][Y - 2] == Player_2.symbol and Out2 == false and HexGrid[X][Y - 3] == Player_2.symbol and Out3 == false and HexGrid[X][Y - 4] == '#') {
            HexGrid[X][Y - 4] = HexGrid[X][Y - 3];
            HexGrid[X][Y - 3] = HexGrid[X][Y - 2];
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        return false;
    }
    else if (Turn == 2) {
        if (HexGrid[X][Y - 1] == Player_1.symbol and Out == true) {
            Player_1.Number_Of_GamePieces--;
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == '#' and Out == false) {
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_1.symbol and Out == false and HexGrid[X][Y - 2] == '#') {
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_2.symbol and Out == false and HexGrid[X][Y - 2] == '#') {
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_2.symbol and Out == false and HexGrid[X][Y - 2] == Player_1.symbol and Out2 == true) {
            Player_1.Number_Of_GamePieces--;
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_2.symbol and Out == false and HexGrid[X][Y - 2] == Player_1.symbol and Out2 == false and HexGrid[X][Y - 3] == '#') {
            HexGrid[X][Y - 3] = HexGrid[X][Y - 2];
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_2.symbol and Out == false and HexGrid[X][Y - 2] == Player_1.symbol and Out2 == false and HexGrid[X][Y - 3] == Player_1.symbol and Out3 == true) {
            Player_1.Number_Of_GamePieces--;
            HexGrid[X][Y - 3] = HexGrid[X][Y - 2];
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        else if (HexGrid[X][Y - 1] == Player_2.symbol and Out == false and HexGrid[X][Y - 2] == Player_1.symbol and Out2 == false and HexGrid[X][Y - 3] == Player_1.symbol and Out3 == false and HexGrid[X][Y - 4] == '#') {
            HexGrid[X][Y - 4] = HexGrid[X][Y - 3];
            HexGrid[X][Y - 3] = HexGrid[X][Y - 2];
            HexGrid[X][Y - 2] = HexGrid[X][Y - 1];
            HexGrid[X][Y - 1] = HexGrid[X][Y];
            HexGrid[X][Y] = HexGrid[X][Y + 1];
            HexGrid[X][Y + 1] = '#';
            return true;
        }
        return false;
    }
}

bool Push_UpRight () {
    int X = coordinates[1][0];
    int Y = coordinates[1][1];
    if ((X - 1) < 0)
        return false;
    if (X < 5) { 
        if (Y > (X - 1 + 5 - 1))
            return false;
    }
    bool Out = false; 
    if ((X - 2) < 0)
        Out = true;
    if (X < 5) { 
        if (Y > (X - 2 + 5 - 1)) 
            Out = true;
    }
    else {
        if (Y + 1 > (X - 2 + 5 - 1)) 
            Out = true;
    }
    bool Out2 = false; 
    if ((X - 3) < 0)
        Out2 = true;
    if (X < 5) { 
        if (Y > (X - 3 + 5 - 1))
            Out2 = true;
    }
    else {
        if (Y + 1 > (X - 3 + 5 - 1))
            Out2 = true;
    }
    bool Out3 = false; 
    if ((X - 4) < 0) 
        Out3 = true;
    if (X < 5) { 
        if (Y > (X - 4 + 5 - 1)) 
            Out3 = true;
    }
    else {
        if (Y + 1 > (X - 4 + 5 - 1))
            Out3 = true;
    }
    if (Turn == 1) {
        if (X < 5) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and Out == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                if (X + 1 < 5) {
                    HexGrid[X][Y] = HexGrid[X + 1][Y];
                    HexGrid[X + 1][Y] = '#';
                    return true;
                }
                else {
                    HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                    HexGrid[X + 1][Y - 1] = '#';
                    return true;
                }
            }
        }
        else {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and Out == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y] == '#') {
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y] == '#') {
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X > 4) {
            if (HexGrid[X - 1][Y + 1] == '#') {
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X < 4) {
            if ((HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == '#') or (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == '#')) {
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if ((HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == '#') or (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == '#')) {
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 5) {
            if ((HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 1] == '#') or (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 1] == '#')) {
                HexGrid[X - 2][Y + 1] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X > 5) {
            if ((HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 2] == '#') or (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 2] == '#')) {
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }   
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }   
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 1] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 2][Y + 1] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }   
        }
        if (X > 5) {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 2] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }   
        }
        if (X == 3) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and HexGrid[X - 3][Y] == '#') {
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and HexGrid[X - 3][Y] == '#') {
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 1] == Player_2.symbol and HexGrid[X - 3][Y + 1] == '#') {
                HexGrid[X - 3][Y + 1] = HexGrid[X - 2][Y + 1];
                HexGrid[X - 2][Y + 1] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 2] == Player_2.symbol and HexGrid[X - 3][Y + 2] == '#') {
                HexGrid[X - 3][Y + 2] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 2] == Player_2.symbol and HexGrid[X - 3][Y + 3] == '#') {
                HexGrid[X - 3][Y + 3] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and HexGrid[X - 3][Y] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and HexGrid[X - 3][Y] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 1] == Player_2.symbol and HexGrid[X - 3][Y + 1] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 3][Y + 1] = HexGrid[X - 2][Y + 1];
                HexGrid[X - 2][Y + 1] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 2] == Player_2.symbol and HexGrid[X - 3][Y + 2] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 3][Y + 2] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 2] == Player_2.symbol and HexGrid[X - 3][Y + 3] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 3][Y + 3] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and HexGrid[X - 3][Y] == Player_2.symbol and HexGrid[X - 4][Y] == '#') {
                HexGrid[X - 4][Y] = HexGrid[X - 3][Y];
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 1] == Player_2.symbol and HexGrid[X - 3][Y + 1] == Player_2.symbol and HexGrid[X - 4][Y + 1] == '#') {
                HexGrid[X - 4][Y + 1] = HexGrid[X - 3][Y + 1];
                HexGrid[X - 3][Y + 1] = HexGrid[X - 2][Y + 1];
                HexGrid[X - 2][Y + 1] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 2] == Player_2.symbol and HexGrid[X - 3][Y + 2] == Player_2.symbol and HexGrid[X - 4][Y + 2] == '#') {
                HexGrid[X - 4][Y + 2] = HexGrid[X - 3][Y + 2];
                HexGrid[X - 3][Y + 2] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 2] == Player_2.symbol and HexGrid[X - 3][Y + 3] == Player_2.symbol and HexGrid[X - 4][Y + 3] == '#') {
                HexGrid[X - 4][Y + 3] = HexGrid[X - 3][Y + 3];
                HexGrid[X - 3][Y + 3] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        return false;
    }
    else if (Turn == 2) {
        if (X < 5) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and Out == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                if (X + 1 < 5) {
                    HexGrid[X][Y] = HexGrid[X + 1][Y];
                    HexGrid[X + 1][Y] = '#';
                    return true;
                }
                else {
                    HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                    HexGrid[X + 1][Y - 1] = '#';
                    return true;
                }
            }
        }
        else {
            if (HexGrid[X - 1][Y + 1] == Player_1.symbol and Out == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y] == '#') {
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y] == '#') {
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X > 4) {
            if (HexGrid[X - 1][Y + 1] == '#') {
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X < 4) {
            if ((HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == '#') or (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == '#')) {
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if ((HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == '#') or (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == '#')) {
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 5) {
            if ((HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 1] == '#') or (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 1] == '#')) {
                HexGrid[X - 2][Y + 1] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X > 5) {
            if ((HexGrid[X - 1][Y + 1] == Player_1.symbol and HexGrid[X - 2][Y + 2] == '#') or (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 2] == '#')) {
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }   
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }   
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 1] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 2][Y + 1] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }   
        }
        if (X > 5) {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 2] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }   
        }
        if (X == 3) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and HexGrid[X - 3][Y] == '#') {
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and HexGrid[X - 3][Y] == '#') {
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 1] == Player_1.symbol and HexGrid[X - 3][Y + 1] == '#') {
                HexGrid[X - 3][Y + 1] = HexGrid[X - 2][Y + 1];
                HexGrid[X - 2][Y + 1] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 2] == Player_1.symbol and HexGrid[X - 3][Y + 2] == '#') {
                HexGrid[X - 3][Y + 2] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 2] == Player_1.symbol and HexGrid[X - 3][Y + 3] == '#') {
                HexGrid[X - 3][Y + 3] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and HexGrid[X - 3][Y] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and HexGrid[X - 3][Y] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 1] == Player_1.symbol and HexGrid[X - 3][Y + 1] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 3][Y + 1] = HexGrid[X - 2][Y + 1];
                HexGrid[X - 2][Y + 1] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 2] == Player_1.symbol and HexGrid[X - 3][Y + 2] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 3][Y + 2] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 2] == Player_1.symbol and HexGrid[X - 3][Y + 3] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 3][Y + 3] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and HexGrid[X - 3][Y] == Player_1.symbol and HexGrid[X - 4][Y] == '#') {
                HexGrid[X - 4][Y] = HexGrid[X - 3][Y];
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 1] == Player_1.symbol and HexGrid[X - 3][Y + 1] == Player_1.symbol and HexGrid[X - 4][Y + 1] == '#') {
                HexGrid[X - 4][Y + 1] = HexGrid[X - 3][Y + 1];
                HexGrid[X - 3][Y + 1] = HexGrid[X - 2][Y + 1];
                HexGrid[X - 2][Y + 1] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 2] == Player_1.symbol and HexGrid[X - 3][Y + 2] == Player_1.symbol and HexGrid[X - 4][Y + 2] == '#') {
                HexGrid[X - 4][Y + 2] = HexGrid[X - 3][Y + 2];
                HexGrid[X - 3][Y + 2] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y + 1] == Player_2.symbol and HexGrid[X - 2][Y + 2] == Player_1.symbol and HexGrid[X - 3][Y + 3] == Player_1.symbol and HexGrid[X - 4][Y + 3] == '#') {
                HexGrid[X - 4][Y + 3] = HexGrid[X - 3][Y + 3];
                HexGrid[X - 3][Y + 3] = HexGrid[X - 2][Y + 2];
                HexGrid[X - 2][Y + 2] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = '#';
                return true;
            }
        }
        return false;
    }
}

bool Push_DownLeft () {
    int X = coordinates[1][0];
    int Y = coordinates[1][1];
    if ((X + 1) > 8)
        return false;
    if (X > 3) {
        if ((Y - 1) < 0)
            return false;
    }
    bool Out = false; 
    if ((X + 2) > 8)
        Out = true;
    if (X > 3) {
        if ((Y - 2) < 0)
            Out = true;
    }
    if (X == 3){
        if ((Y - 1) < 0)
            Out = true;
    }
    bool Out2 = false; 
    if ((X + 3) > 8)
        Out2 = true;
    if (X > 3) {
        if ((Y - 3) < 0)
            Out2 = true;
    }
    if (X == 2){
        if ((Y - 1) < 0)
            Out2 = true;
    }
    bool Out3 = false; 
    if ((X + 4) > 8)
        Out3 = true;
    if (X > 3) {
        if ((Y - 4) < 0)
            Out3 = true;
    }
    if (X == 1){
        if ((Y - 1) < 0)
            Out3 = true;
    }
    if (Turn == 1) {
        if (X < 4) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and Out == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                if (X - 1 < 4) {
                    HexGrid[X][Y] = HexGrid[X - 1][Y];
                    HexGrid[X - 1][Y] = '#';
                    return true;
                }
                else {
                    HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                    HexGrid[X - 1][Y + 1] = '#';
                    return true;
                }
            }
        }
        else {
            if (HexGrid[X + 1][Y - 1] == Player_2.symbol and Out == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X + 1][Y] == '#') {
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y - 1] == '#') {
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X > 4) {
            if (HexGrid[X + 1][Y - 1] == '#') {
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }
        }
        if (X > 4) {
            if ((HexGrid[X + 1][Y - 1] == Player_2.symbol and HexGrid[X + 2][Y - 2] == '#') or (HexGrid[X + 1][Y - 1] == Player_1.symbol and HexGrid[X + 2][Y -  2] == '#')) {
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if ((HexGrid[X + 1][Y - 1] == Player_2.symbol and HexGrid[X + 2][Y - 2] == '#') or (HexGrid[X + 1][Y - 1] == Player_1.symbol and HexGrid[X + 2][Y -  2] == '#')) {
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 3) {
            if ((HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y - 1] == '#') or (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y - 1] == '#')) {
                HexGrid[X + 2][Y - 1] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X < 3) {
            if ((HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y] == '#') or (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y] == '#')) {
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 2) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }   
        }
        if (X == 3) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y - 1] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 2][Y - 1] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }   
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y - 1] == Player_1.symbol and HexGrid[X + 2][Y - 2] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }   
        }
        if (X > 4) {
            if (HexGrid[X + 1][Y - 1] == Player_1.symbol and HexGrid[X + 2][Y - 2] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }   
        }
        if (X == 1) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y] == Player_2.symbol and HexGrid[X + 3][Y] == '#') {
                HexGrid[X + 3][Y] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 2) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y] == Player_2.symbol and HexGrid[X + 3][Y - 1] == '#') {
                HexGrid[X + 3][Y - 1] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 3) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y - 1] == Player_2.symbol and HexGrid[X + 3][Y - 2] == '#') {
                HexGrid[X + 3][Y - 2] = HexGrid[X + 2][Y - 1];
                HexGrid[X + 2][Y - 1] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y - 1] == Player_1.symbol and HexGrid[X + 2][Y - 2] == Player_2.symbol and HexGrid[X + 3][Y - 3] == '#') {
                HexGrid[X + 3][Y - 3] = HexGrid[X + 2][Y - 2];
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X + 1][Y - 1] == Player_1.symbol and HexGrid[X + 2][Y - 2] == Player_2.symbol and HexGrid[X + 3][Y - 3] == '#') {
                HexGrid[X + 3][Y - 3] = HexGrid[X + 2][Y - 2];
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 1) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y] == Player_2.symbol and HexGrid[X + 3][Y] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 3][Y] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 2) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y] == Player_2.symbol and HexGrid[X + 3][Y - 1] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 3][Y - 1] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 3) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y - 1] == Player_2.symbol and HexGrid[X + 3][Y - 2] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 3][Y - 2] = HexGrid[X + 2][Y - 1];
                HexGrid[X + 2][Y - 1] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y - 1] == Player_1.symbol and HexGrid[X + 2][Y - 2] == Player_2.symbol and HexGrid[X + 3][Y - 3] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 3][Y - 3] = HexGrid[X + 2][Y - 2];
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X + 1][Y - 1] == Player_1.symbol and HexGrid[X + 2][Y - 2] == Player_2.symbol and HexGrid[X + 3][Y - 3] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 3][Y - 3] = HexGrid[X + 2][Y - 2];
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 1) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y] == Player_2.symbol and HexGrid[X + 3][Y] == Player_2.symbol and HexGrid[X + 4][Y - 1] == '#') {
                HexGrid[X + 4][Y - 1] = HexGrid[X + 3][Y];
                HexGrid[X + 3][Y] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 2) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y] == Player_2.symbol and HexGrid[X + 3][Y - 1] == Player_2.symbol and HexGrid[X + 4][Y - 2] == '#') {
                HexGrid[X + 4][Y - 2] = HexGrid[X + 3][Y - 1];
                HexGrid[X + 3][Y - 1] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 3) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y - 1] == Player_2.symbol and HexGrid[X + 3][Y - 2] == Player_2.symbol and HexGrid[X + 4][Y - 3] == '#') {
                HexGrid[X + 4][Y - 3] = HexGrid[X + 3][Y - 2];
                HexGrid[X + 3][Y - 2] = HexGrid[X + 2][Y - 1];
                HexGrid[X + 2][Y - 1] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y - 1] == Player_1.symbol and HexGrid[X + 2][Y - 2] == Player_2.symbol and HexGrid[X + 3][Y - 3] == Player_2.symbol and HexGrid[X + 4][Y - 4] == '#') {
                HexGrid[X + 4][Y - 4] = HexGrid[X + 3][Y - 3];
                HexGrid[X + 3][Y - 3] = HexGrid[X + 2][Y - 2];
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        return false;
    }
    else if (Turn == 2) {
        if (X < 4) {
            if (HexGrid[X + 1][Y] == Player_1.symbol and Out == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                if (X - 1 < 4) {
                    HexGrid[X][Y] = HexGrid[X - 1][Y];
                    HexGrid[X - 1][Y] = '#';
                    return true;
                }
                else {
                    HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                    HexGrid[X - 1][Y + 1] = '#';
                    return true;
                }
            }
        }
        else {
            if (HexGrid[X + 1][Y - 1] == Player_1.symbol and Out == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X + 1][Y] == '#') {
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y - 1] == '#') {
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X > 4) {
            if (HexGrid[X + 1][Y - 1] == '#') {
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }
        }
        if (X > 4) {
            if ((HexGrid[X + 1][Y - 1] == Player_1.symbol and HexGrid[X + 2][Y - 2] == '#') or (HexGrid[X + 1][Y - 1] == Player_2.symbol and HexGrid[X + 2][Y -  2] == '#')) {
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if ((HexGrid[X + 1][Y - 1] == Player_1.symbol and HexGrid[X + 2][Y - 2] == '#') or (HexGrid[X + 1][Y - 1] == Player_2.symbol and HexGrid[X + 2][Y -  2] == '#')) {
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 3) {
            if ((HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y - 1] == '#') or (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y - 1] == '#')) {
                HexGrid[X + 2][Y - 1] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X < 3) {
            if ((HexGrid[X + 1][Y] == Player_1.symbol and HexGrid[X + 2][Y] == '#') or (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y] == '#')) {
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 2) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }   
        }
        if (X == 3) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y - 1] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 2][Y - 1] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }   
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y - 1] == Player_2.symbol and HexGrid[X + 2][Y - 2] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }   
        }
        if (X > 4) {
            if (HexGrid[X + 1][Y - 1] == Player_2.symbol and HexGrid[X + 2][Y - 2] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }   
        }
        if (X == 1) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y] == Player_1.symbol and HexGrid[X + 3][Y] == '#') {
                HexGrid[X + 3][Y] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 2) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y] == Player_1.symbol and HexGrid[X + 3][Y - 1] == '#') {
                HexGrid[X + 3][Y - 1] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 3) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y - 1] == Player_1.symbol and HexGrid[X + 3][Y - 2] == '#') {
                HexGrid[X + 3][Y - 2] = HexGrid[X + 2][Y - 1];
                HexGrid[X + 2][Y - 1] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y - 1] == Player_2.symbol and HexGrid[X + 2][Y - 2] == Player_1.symbol and HexGrid[X + 3][Y - 3] == '#') {
                HexGrid[X + 3][Y - 3] = HexGrid[X + 2][Y - 2];
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X + 1][Y - 1] == Player_2.symbol and HexGrid[X + 2][Y - 2] == Player_1.symbol and HexGrid[X + 3][Y - 3] == '#') {
                HexGrid[X + 3][Y - 3] = HexGrid[X + 2][Y - 2];
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 1) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y] == Player_1.symbol and HexGrid[X + 3][Y] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 3][Y] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 2) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y] == Player_1.symbol and HexGrid[X + 3][Y - 1] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 3][Y - 1] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 3) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y - 1] == Player_1.symbol and HexGrid[X + 3][Y - 2] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 3][Y - 2] = HexGrid[X + 2][Y - 1];
                HexGrid[X + 2][Y - 1] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y - 1] == Player_2.symbol and HexGrid[X + 2][Y - 2] == Player_1.symbol and HexGrid[X + 3][Y - 3] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 3][Y - 3] = HexGrid[X + 2][Y - 2];
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X + 1][Y - 1] == Player_2.symbol and HexGrid[X + 2][Y - 2] == Player_1.symbol and HexGrid[X + 3][Y - 3] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 3][Y - 3] = HexGrid[X + 2][Y - 2];
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
                HexGrid[X - 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 1) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y] == Player_1.symbol and HexGrid[X + 3][Y] == Player_1.symbol and HexGrid[X + 4][Y - 1] == '#') {
                HexGrid[X + 4][Y - 1] = HexGrid[X + 3][Y];
                HexGrid[X + 3][Y] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 2) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y] == Player_1.symbol and HexGrid[X + 3][Y - 1] == Player_1.symbol and HexGrid[X + 4][Y - 2] == '#') {
                HexGrid[X + 4][Y - 2] = HexGrid[X + 3][Y - 1];
                HexGrid[X + 3][Y - 1] = HexGrid[X + 2][Y];
                HexGrid[X + 2][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 3) {
            if (HexGrid[X + 1][Y] == Player_2.symbol and HexGrid[X + 2][Y - 1] == Player_1.symbol and HexGrid[X + 3][Y - 2] == Player_1.symbol and HexGrid[X + 4][Y - 3] == '#') {
                HexGrid[X + 4][Y - 3] = HexGrid[X + 3][Y - 2];
                HexGrid[X + 3][Y - 2] = HexGrid[X + 2][Y - 1];
                HexGrid[X + 2][Y - 1] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y - 1] == Player_2.symbol and HexGrid[X + 2][Y - 2] == Player_1.symbol and HexGrid[X + 3][Y - 3] == Player_1.symbol and HexGrid[X + 4][Y - 4] == '#') {
                HexGrid[X + 4][Y - 4] = HexGrid[X + 3][Y - 3];
                HexGrid[X + 3][Y - 3] = HexGrid[X + 2][Y - 2];
                HexGrid[X + 2][Y - 2] = HexGrid[X + 1][Y - 1];
                HexGrid[X + 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        return false;
    }
}

bool Push_UpLeft () {
    int X = coordinates[1][0];
    int Y = coordinates[1][1];
    if ((X - 1) < 0)
        return false;
    if (X < 5) {
        if ((Y - 1) < 0)
            return false;
    }
    bool Out = false; 
    if ((X - 2) < 0)
        Out = true;
    if (X < 5) {
        if ((Y - 2) < 0)
            Out = true;
    }
    else {
        if ((Y - 1) < 0)
            Out = true;
    }

    bool Out2 = false;
    if ((X - 3) < 0)
        Out2 = true;
    if (X < 5) {
        if ((Y - 3) < 0)
            Out2 = true;
    }
    else {
        if ((Y - 2) < 0)
            Out2 = true;
    }

    bool Out3 = false; 
    if ((X - 4) < 0)
        Out3 = true;
    if (X < 5) {
        if ((Y - 4) < 0)
            Out3 = true;
    }
    else {
        if ((Y - 3) < 0)
            Out3 = true;
    }

    if (Turn == 1) {
        if (X < 5) {
            if (HexGrid[X - 1][Y - 1] == Player_2.symbol and Out == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                if (X + 1 < 5) {
                    HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                    HexGrid[X + 1][Y + 1] = '#';
                    return true;
                }
                else {
                    HexGrid[X][Y] = HexGrid[X + 1][Y];
                    HexGrid[X + 1][Y] = '#';
                    return true;
                }
            }
        }
        else {
            if (HexGrid[X - 1][Y] == Player_2.symbol and Out == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y - 1] == '#') {
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                HexGrid[X + 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y - 1] == '#') {
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X > 4) {
            if (HexGrid[X - 1][Y] == '#') {
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X < 4) {
            if ((HexGrid[X - 1][Y - 1] == Player_2.symbol and HexGrid[X - 2][Y - 2] == '#') or (HexGrid[X - 1][Y - 1] == Player_1.symbol and HexGrid[X - 2][Y - 2] == '#')) {
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                HexGrid[X + 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if ((HexGrid[X - 1][Y - 1] == Player_2.symbol and HexGrid[X - 2][Y - 2] == '#') or (HexGrid[X - 1][Y - 1] == Player_1.symbol and HexGrid[X - 2][Y - 2] == '#')) {
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if ((HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y - 1] == '#') or (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y - 1] == '#')) {
                HexGrid[X - 2][Y - 1] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X > 5) {
            if ((HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == '#') or (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == '#')) {
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y - 1] == Player_1.symbol and HexGrid[X - 2][Y - 2] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                HexGrid[X + 1][Y + 1] = '#';
                return true;
            }   
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y - 1] == Player_1.symbol and HexGrid[X - 2][Y - 2] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }   
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y - 1] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 2][Y - 1] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }   
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and Out2 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }   
        }
        if (X == 3) {
            if (HexGrid[X - 1][Y - 1] == Player_1.symbol and HexGrid[X - 2][Y - 2] == Player_2.symbol and HexGrid[X - 3][Y - 3] == '#') {
                HexGrid[X - 3][Y - 3] = HexGrid[X - 2][Y - 2];
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                HexGrid[X + 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y - 1] == Player_1.symbol and HexGrid[X - 2][Y - 2] == Player_2.symbol and HexGrid[X - 3][Y - 3] == '#') {
                HexGrid[X - 3][Y - 3] = HexGrid[X - 2][Y - 2];
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y - 1] == Player_2.symbol and HexGrid[X - 3][Y - 2] == '#') {
                HexGrid[X - 3][Y - 2] = HexGrid[X - 2][Y - 1];
                HexGrid[X - 2][Y - 1] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and HexGrid[X - 3][Y - 1] == '#') {
                HexGrid[X - 3][Y - 1] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and HexGrid[X - 3][Y] == '#') {
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y - 1] == Player_1.symbol and HexGrid[X - 2][Y - 2] == Player_2.symbol and HexGrid[X - 3][Y - 3] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 3][Y - 3] = HexGrid[X - 2][Y - 2];
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                HexGrid[X + 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y - 1] == Player_1.symbol and HexGrid[X - 2][Y - 2] == Player_2.symbol and HexGrid[X - 3][Y - 3] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 3][Y - 3] = HexGrid[X - 2][Y - 2];
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y - 1] == Player_2.symbol and HexGrid[X - 3][Y - 2] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 3][Y - 2] = HexGrid[X - 2][Y - 1];
                HexGrid[X - 2][Y - 1] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and HexGrid[X - 3][Y - 1] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 3][Y - 1] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and HexGrid[X - 3][Y] == Player_2.symbol and Out3 == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y - 1] == Player_1.symbol and HexGrid[X - 2][Y - 2] == Player_2.symbol and HexGrid[X - 3][Y - 3] == Player_2.symbol and HexGrid[X - 4][Y - 4] == '#') {
                HexGrid[X - 4][Y - 4] = HexGrid[X - 3][Y - 3];
                HexGrid[X - 3][Y - 3] = HexGrid[X - 2][Y - 2];
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y - 1] == Player_2.symbol and HexGrid[X - 3][Y - 2] == Player_2.symbol and HexGrid[X - 4][Y - 3] == '#') {
                HexGrid[X - 4][Y - 3] = HexGrid[X - 3][Y - 2];
                HexGrid[X - 3][Y - 2] = HexGrid[X - 2][Y - 1];
                HexGrid[X - 2][Y - 1] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and HexGrid[X - 3][Y - 1] == Player_2.symbol and HexGrid[X - 4][Y - 2] == '#') {
                HexGrid[X - 4][Y - 2] = HexGrid[X - 3][Y - 1];
                HexGrid[X - 3][Y - 1] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == Player_2.symbol and HexGrid[X - 3][Y] == Player_2.symbol and HexGrid[X - 4][Y - 1] == '#') {
                HexGrid[X - 4][Y - 1] = HexGrid[X - 3][Y];
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        return false;
    }
    else if (Turn == 2) {
        if (X < 5) {
            if (HexGrid[X - 1][Y - 1] == Player_1.symbol and Out == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                if (X + 1 < 5) {
                    HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                    HexGrid[X + 1][Y + 1] = '#';
                    return true;
                }
                else {
                    HexGrid[X][Y] = HexGrid[X + 1][Y];
                    HexGrid[X + 1][Y] = '#';
                    return true;
                }
            }
        }
        else {
            if (HexGrid[X - 1][Y] == Player_1.symbol and Out == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y - 1] == '#') {
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                HexGrid[X + 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y - 1] == '#') {
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X > 4) {
            if (HexGrid[X - 1][Y] == '#') {
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X < 4) {
            if ((HexGrid[X - 1][Y - 1] == Player_1.symbol and HexGrid[X - 2][Y - 2] == '#') or (HexGrid[X - 1][Y - 1] == Player_2.symbol and HexGrid[X - 2][Y - 2] == '#')) {
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                HexGrid[X + 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if ((HexGrid[X - 1][Y - 1] == Player_1.symbol and HexGrid[X - 2][Y - 2] == '#') or (HexGrid[X - 1][Y - 1] == Player_2.symbol and HexGrid[X - 2][Y - 2] == '#')) {
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if ((HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y - 1] == '#') or (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y - 1] == '#')) {
                HexGrid[X - 2][Y - 1] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X > 5) {
            if ((HexGrid[X - 1][Y] == Player_1.symbol and HexGrid[X - 2][Y] == '#') or (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == '#')) {
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y - 1] == Player_2.symbol and HexGrid[X - 2][Y - 2] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                HexGrid[X + 1][Y + 1] = '#';
                return true;
            }   
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y - 1] == Player_2.symbol and HexGrid[X - 2][Y - 2] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }   
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y - 1] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 2][Y - 1] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }   
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and Out2 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }   
        }
        if (X == 3) {
            if (HexGrid[X - 1][Y - 1] == Player_2.symbol and HexGrid[X - 2][Y - 2] == Player_1.symbol and HexGrid[X - 3][Y - 3] == '#') {
                HexGrid[X - 3][Y - 3] = HexGrid[X - 2][Y - 2];
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                HexGrid[X + 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y - 1] == Player_2.symbol and HexGrid[X - 2][Y - 2] == Player_1.symbol and HexGrid[X - 3][Y - 3] == '#') {
                HexGrid[X - 3][Y - 3] = HexGrid[X - 2][Y - 2];
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y - 1] == Player_1.symbol and HexGrid[X - 3][Y - 2] == '#') {
                HexGrid[X - 3][Y - 2] = HexGrid[X - 2][Y - 1];
                HexGrid[X - 2][Y - 1] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and HexGrid[X - 3][Y - 1] == '#') {
                HexGrid[X - 3][Y - 1] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and HexGrid[X - 3][Y] == '#') {
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X - 1][Y - 1] == Player_2.symbol and HexGrid[X - 2][Y - 2] == Player_1.symbol and HexGrid[X - 3][Y - 3] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 3][Y - 3] = HexGrid[X - 2][Y - 2];
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
                HexGrid[X + 1][Y + 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y - 1] == Player_2.symbol and HexGrid[X - 2][Y - 2] == Player_1.symbol and HexGrid[X - 3][Y - 3] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 3][Y - 3] = HexGrid[X - 2][Y - 2];
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y - 1] == Player_1.symbol and HexGrid[X - 3][Y - 2] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 3][Y - 2] = HexGrid[X - 2][Y - 1];
                HexGrid[X - 2][Y - 1] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and HexGrid[X - 3][Y - 1] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 3][Y - 1] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and HexGrid[X - 3][Y] == Player_1.symbol and Out3 == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X - 1][Y - 1] == Player_2.symbol and HexGrid[X - 2][Y - 2] == Player_1.symbol and HexGrid[X - 3][Y - 3] == Player_1.symbol and HexGrid[X - 4][Y - 4] == '#') {
                HexGrid[X - 4][Y - 4] = HexGrid[X - 3][Y - 3];
                HexGrid[X - 3][Y - 3] = HexGrid[X - 2][Y - 2];
                HexGrid[X - 2][Y - 2] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 5) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y - 1] == Player_1.symbol and HexGrid[X - 3][Y - 2] == Player_1.symbol and HexGrid[X - 4][Y - 3] == '#') {
                HexGrid[X - 4][Y - 3] = HexGrid[X - 3][Y - 2];
                HexGrid[X - 3][Y - 2] = HexGrid[X - 2][Y - 1];
                HexGrid[X - 2][Y - 1] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 6) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and HexGrid[X - 3][Y - 1] == Player_1.symbol and HexGrid[X - 4][Y - 2] == '#') {
                HexGrid[X - 4][Y - 2] = HexGrid[X - 3][Y - 1];
                HexGrid[X - 3][Y - 1] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
        if (X == 7) {
            if (HexGrid[X - 1][Y] == Player_2.symbol and HexGrid[X - 2][Y] == Player_1.symbol and HexGrid[X - 3][Y] == Player_1.symbol and HexGrid[X - 4][Y - 1] == '#') {
                HexGrid[X - 4][Y - 1] = HexGrid[X - 3][Y];
                HexGrid[X - 3][Y] = HexGrid[X - 2][Y];
                HexGrid[X - 2][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X + 1][Y];
                HexGrid[X + 1][Y] = '#';
                return true;
            }
        }
    }
}

bool Push_DownRight () {
    int X = coordinates[1][0];
    int Y = coordinates[1][1];
    if ((X + 1) > 8)
        return false;
    if (X > 3) { 
        if ((Y + 1) > (8 - ((X + 1) % 5)))
            return false;   
    }
    bool Out = false; 
    if ((X + 2) > 8)
        Out = true;
    if (X > 3) { 
        if ((Y + 1) > (8 - ((X + 2) % 5)))
            Out = true; 
    }
    if (X == 3) {
        if ((Y + 2) > (X + 1 + 5 - 1))
            Out = true;  
    }
    bool Out2 = false; 
    if ((X + 3) > 8)
        Out2 = true;
    if (X > 3) { 
        if ((Y + 1) > (8 - ((X + 3) % 5)))
            Out2 = true; 
    }
    if (X == 2) {
        if ((Y + 3) > (X + 2 + 5 - 1))
            Out2 = true;
    }
    bool Out3 = false; 
    if ((X + 4) > 8)
        Out3 = true;
    if (X > 3) { 
        if ((Y + 1) > (8 - ((X + 4) % 5)))
            Out3 = true; 
    }
    if (X == 1) {
        if ((Y + 4) > (X + 3 + 5 - 1))
            Out3 = true;   
    }
    if (Turn == 1) {
        if (X < 4) {
            if (HexGrid[X + 1][Y + 1] == Player_2.symbol and Out == true) {
                Player_2.Number_Of_GamePieces--;
                HexGrid[X + 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = '#';
                return true;
            }
        }
        else {
            Player_2.Number_Of_GamePieces--;
            HexGrid[X + 1][Y] = HexGrid[X][Y];
            if (X - 1 < 4) {
                HexGrid[X][Y] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = '#';
                return true;
            }
            else {
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X + 1][Y + 1] == '#') {
                HexGrid[X + 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y] == '#') {
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = '#';
                return true;
            }
        }
        if (X > 4) {
            if (HexGrid[X + 1][Y] == '#') {
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }  
        //----
        //----
        //----
    }
    else if (Turn == 2) {
        if (X < 4) {
            if (HexGrid[X + 1][Y + 1] == Player_1.symbol and Out == true) {
                Player_1.Number_Of_GamePieces--;
                HexGrid[X + 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = '#';
                return true;
            }
        }
        else {
            Player_1.Number_Of_GamePieces--;
            HexGrid[X + 1][Y] = HexGrid[X][Y];
            if (X - 1 < 4) {
                HexGrid[X][Y] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = '#';
                return true;
            }
            else {
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }
        if (X < 4) {
            if (HexGrid[X + 1][Y + 1] == '#') {
                HexGrid[X + 1][Y + 1] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = '#';
                return true;
            }
        }
        if (X == 4) {
            if (HexGrid[X + 1][Y] == '#') {
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y - 1];
                HexGrid[X - 1][Y - 1] = '#';
                return true;
            }
        }
        if (X > 4) {
            if (HexGrid[X + 1][Y] == '#') {
                HexGrid[X + 1][Y] = HexGrid[X][Y];
                HexGrid[X][Y] = HexGrid[X - 1][Y];
                HexGrid[X - 1][Y] = '#';
                return true;
            }
        }  
        //----
        //----
        //----
    }
}

void D_Move () {
    int X = x - '0';
    int Y = y - '0';
    char PieceTmp;
    PieceTmp = HexGrid[X][Y];
    HexGrid[X][Y] = HexGrid[X][Y + 1];
    HexGrid[X][Y + 1] = PieceTmp;
}
void A_Move () {
    int X = x - '0';
    int Y = y - '0';
    char PieceTmp;
    PieceTmp = HexGrid[X][Y];
    HexGrid[X][Y] = HexGrid[X][Y - 1];
    HexGrid[X][Y - 1] = PieceTmp;
}
void E_Move () {
    int X = x - '0';
    int Y = y - '0';
    char PieceTmp = HexGrid[X][Y];
    if (X < 5) {
        HexGrid[X][Y] = HexGrid[X - 1][Y];
        HexGrid[X - 1][Y] = PieceTmp;
    }
    else {
        HexGrid[X][Y] = HexGrid[X - 1][Y + 1];
        HexGrid[X - 1][Y + 1] = PieceTmp;
    }
}
void Q_Move () {
    int X = x - '0';
    int Y = y - '0';
    char PieceTmp = HexGrid[X][Y];
    if (X < 5) {
        HexGrid[X][Y] = HexGrid[X - 1][Y - 1];
        HexGrid[X - 1][Y - 1] = PieceTmp;
    }
    else {
        HexGrid[X][Y] = HexGrid[X - 1][Y];
        HexGrid[X - 1][Y] = PieceTmp;
    }
}
void C_Move () {
    int X = x - '0';
    int Y = y - '0';
    char PieceTmp = HexGrid[X][Y];
    if (X < 4) {
        HexGrid[X][Y] = HexGrid[X + 1][Y + 1];
        HexGrid[X + 1][Y + 1] = PieceTmp;
    }
    else {
        HexGrid[X][Y] = HexGrid[X + 1][Y];
        HexGrid[X + 1][Y] = PieceTmp;
    }
}
void Z_Move () {
    int X = x - '0';
    int Y = y - '0';
    char PieceTmp = HexGrid[X][Y];
    if (X < 4) {
        HexGrid[X][Y] = HexGrid[X + 1][Y];
        HexGrid[X + 1][Y] = PieceTmp;
    }
    else {
        HexGrid[X][Y] = HexGrid[X + 1][Y - 1];
        HexGrid[X + 1][Y - 1] = PieceTmp;
    }
}

void Game () {
    
    while (true) {

        if (Player_1.Number_Of_GamePieces <= 8) {
            system("Cls");
            cout << Player_1.name <<" WON :)";
            Sleep(600);
            system("Cls");
            Sleep(600);
            cout << Player_1.name <<" WON :)";
            Sleep(600);
            system("Cls");
            Sleep(600);
            cout << Player_1.name <<" WON :)";
            Sleep(2000);
            Gameover = true;
            break;
        }
        else if (Player_2.Number_Of_GamePieces <= 8) {
            system("Cls");
            cout << Player_2.name <<" WON :)";
            Sleep(600);
            system("Cls");
            Sleep(600);
            cout << Player_2.name <<" WON :)";
            Sleep(600);
            system("Cls");
            Sleep(600);
            cout << Player_2.name <<" WON :)";
            Sleep(2000);
            Gameover = true;
            break;
        }

        clock_t startTime = clock();

        system ("Cls");
        if (TurnCheck % 2 == 0)
            Turn = 1;
        else
            Turn = 2;
        PrintChart ();

        clock_t st = clock(); 

        cout << "Enter number of coords you want to move (1 or 2 or 3) [0 : EXIT]: ";
        cin >> Moves;
        if (Moves == "0") {
            EXITEND
            break;
        }
        if (Moves == "1") { 
            while (true) {
                system ("Cls");
                PrintChart ();
                while (true) {
                    system ("Cls");
                    PrintChart ();
                    cout << "Enter your coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                    cout << "Coord  : ";
                    cout << "( ";
                    x = _getch();
                    if (x == 0x08) {
                        ExitInMove = true;
                        break;
                    }
                    if (x != '0' and x != '1' and x != '2' and x != '3' and
                        x != '4' and x != '5' and x != '6' and x != '7' and x != '8') {
                        cout << '\n' << '\n';
                        cout << "X is not in range! " << "\a" << '\n';
                        cout << '\n';
                        Sleep(1500);
                        continue;
                    }
                    cout << x << " , ";
                    break;
                }
                if (ExitInMove == true) {
                    ExitInMove = false;
                    break;
                }
                while (true) {
                    system ("Cls");
                    PrintChart ();
                    cout << "Enter your coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                    cout << "Coord  : ";
                    cout << "( " << x << " , ";
                    y = _getch();
                    if (y == 0x08) {
                        ExitInMove = true;
                        break;
                    }
                    if (y != '0' and y != '1' and y != '2' and y != '3' and
                        y != '4' and y != '5' and y != '6' and y != '7' and y != '8') {
                        cout << '\n' << '\n';
                        cout << "Y is not in range! " << "\a" << '\n';
                        cout << '\n';
                        Sleep(1500);
                        continue;
                    }
                    cout << y << " ) ";
                    break;
                }
                if (ExitInMove == true) {
                    ExitInMove = false;
                    break;
                }
                if (HexGrid[x - '0'][y - '0'] == '#') {
                    cout << " is empty! ";
                    Sleep(2000);
                    continue;
                }
                if (Turn == 1) {
                    if (HexGrid[x - '0'][y - '0'] != Player_1.symbol) {
                        cout << " is not your piece!";
                        Sleep(2000);
                        continue;
                    }
                }
                else if (Turn == 2) {
                    if (HexGrid[x - '0'][y - '0'] != Player_2.symbol) {
                        cout << " is not your piece!";
                        Sleep(2000);
                        continue;
                    }
                }

                Form_Temp ();

                bool r = Right();     
                bool l = Left();       
                bool ur = UpRight();   
                bool ul = UpLeft();    
                bool dr = DownRight(); 
                bool dl = DownLeft();  

                if (r == false and l == false and ur == false and
                    ul == false and dr == false and dl == false) {
                    cout << "You can not move this piece! ";
                    Sleep(2000);
                    continue;
                }

                system ("Cls");
                while (true) {
                    system ("Cls");
                    Print (TempHex);
                    cout << '\n';
                    cout << "Enter your option [BACKSPACE : EXIT] : ";
                    char Option;
                    Option = _getch();
                    if (Option == 0x08) {
                        ExitInMove = true;
                        break;
                    }
                    if (r == true and Option == 'D') {
                        D_Move();
                        break;
                    }
                    else if (l == true and Option == 'A') {
                        A_Move();
                        break;
                    }
                    else if (ur == true and Option == 'E') {
                        E_Move();
                        break;
                    }
                    else if (ul == true and Option == 'Q') {
                        Q_Move();
                        break;
                    }
                    else if (dr == true and Option == 'C') {
                        C_Move();
                        break;
                    }
                    else if (dl == true and Option == 'Z') {
                        Z_Move();
                        break;
                    }
                    else {
                        system ("Cls");
                        cout << "Enter a valid option! ";
                        Sleep(1500);   
                        continue;
                    }
                }
                if (ExitInMove == true) {
                    ExitInMove = false;
                    continue;
                }

                TurnCheck++;
                break;
            }
        }
        else if (Moves == "2") { 
            while (true) {    
                while (true) {
                    system ("Cls");
                    PrintChart ();
                    while (true) {
                        system ("Cls");
                        PrintChart ();
                        cout << "Enter your FIRST coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                        cout << "FIRST Coord  : ";
                        cout << "( ";
                        x = _getch();
                        if (x == 0x08) {
                            ExitInMove = true;
                            break;
                        }
                        if (x != '0' and x != '1' and x != '2' and x != '3' and
                            x != '4' and x != '5' and x != '6' and x != '7' and x != '8') {
                            cout << '\n' << '\n';
                            cout << "X is not in range! " << "\a" << '\n';
                            cout << '\n';
                            Sleep(1500);
                            continue;
                        }
                        cout << x << " , ";
                        break;
                    }
                    if (ExitInMove == true)
                        break;
                    while (true) {
                        system ("Cls");
                        PrintChart ();
                        cout << "Enter your FIRST coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                        cout << "FIRST Coord  : ";
                        cout << "( " << x << " , ";
                        y = _getch();
                        if (y == 0x08) {
                            ExitInMove = true;
                            break;
                        }
                        if (y != '0' and y != '1' and y != '2' and y != '3' and
                            y != '4' and y != '5' and y != '6' and y != '7' and y != '8') {
                            cout << '\n' << '\n';
                            cout << "Y is not in range! " << "\a" << '\n';
                            cout << '\n';
                            Sleep(1500);
                            continue;
                        }
                        cout << y << " ) ";
                        break;
                    }
                    if (ExitInMove == true) 
                        break;
                    if (HexGrid[x - '0'][y - '0'] == '#') {
                        cout << " is empty! ";
                        Sleep(2000);
                        continue;
                    }
                    if (Turn == 1) {
                        if (HexGrid[x - '0'][y - '0'] != Player_1.symbol) {
                            cout << " is not your piece!";
                            Sleep(2000);
                            continue;
                        }
                    }
                    else if (Turn == 2) {
                        if (HexGrid[x - '0'][y - '0'] != Player_2.symbol) {
                            cout << " is not your piece!";
                            Sleep(2000);
                            continue;
                        }
                    }
                    if (ExitInMove == true) {
                        break;
                    }
                    coordinates[0][0] = x - '0';
                    coordinates[0][1] = y - '0';
                    break;
                }
                if (ExitInMove == true) {
                    ExitInMove = false;    
                    break;
                }
                while (true) {
                    system ("Cls");
                    PrintChart ();
                    while (true) {
                        system ("Cls");
                        PrintChart ();
                        cout << "Enter your SECOND coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                        cout << "FIRST Coord  : " << "( " << coordinates[0][0] << " , " << coordinates[0][1] << " )" << '\n'; 
                        cout << "SECOND Coord : ";
                        cout << "( ";
                        x = _getch();
                        if (x == 0x08) {
                            ExitInMove = true;
                            break;
                        }
                        if (x != '0' and x != '1' and x != '2' and x != '3' and
                            x != '4' and x != '5' and x != '6' and x != '7' and x != '8') {
                            cout << '\n' << '\n';
                            cout << "X is not in range! " << "\a" << '\n';
                            cout << '\n';
                            Sleep(1500);
                            continue;
                        }
                        cout << x << " , ";
                        break;
                    }
                    if (ExitInMove == true)
                        break;
                    while (true) {
                        system ("Cls");
                        PrintChart ();
                        cout << "Enter your SECOND coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                        cout << "FIRST Coord  : " << "( " << coordinates[0][0] << " , " << coordinates[0][1] << " )" << '\n'; 
                        cout << "SECOND Coord : ";
                        cout << "( " << x << " , ";
                        y = _getch();
                        if (y == 0x08) {
                            ExitInMove = true;
                            break;
                        }
                        if (y != '0' and y != '1' and y != '2' and y != '3' and
                            y != '4' and y != '5' and y != '6' and y != '7' and y != '8') {
                            cout << '\n' << '\n';
                            cout << "Y is not in range! " << "\a" << '\n';
                            cout << '\n';
                            Sleep(1500);
                            continue;
                        }
                        cout << y << " ) ";
                        break;
                    }
                    if (ExitInMove == true) 
                        break;
                    if (HexGrid[x - '0'][y - '0'] == '#') {
                        cout << " is empty! ";
                        Sleep(2000);
                        continue;
                    }
                    if (Turn == 1) {
                        if (HexGrid[x - '0'][y - '0'] != Player_1.symbol) {
                            cout << " is not your piece!";
                            Sleep(2000);
                            continue;
                        }
                    }
                    else if (Turn == 2) {
                        if (HexGrid[x - '0'][y - '0'] != Player_2.symbol) {
                            cout << " is not your piece!";
                            Sleep(2000);
                            continue;
                        }
                    }
                    if (ExitInMove == true)
                        break;
                    coordinates[1][0] = x - '0';
                    coordinates[1][1] = y - '0';
                    break;
                }
                if (ExitInMove == true) {
                    ExitInMove = false;    
                    break;
                }

                if (coordinates[0][0] == coordinates[1][0] and coordinates[0][1] == coordinates[1][1]) {
                    cout << '\n' << "Same pieces! ";
                    Sleep(1500);
                    continue;
                }

                bool r = Right(); 
                bool l = Left();      
                bool ur = UpRight();   
                bool ul = UpLeft();    
                bool dr = DownRight();
                bool dl = DownLeft();  

                if (r == false and l == false and ur == false and
                    ul == false and dr == false and dl == false) {
                    cout << "These 2 pieces are not next to each other! ";
                    Sleep(2000);
                    continue;
                }

                cout << '\n';
                cout << "Enter Q , A , Z , E , D , C [BACKSPACE : EXIT] : ";

                char news = _getch();

                if (news == 0x08)
                    continue;
                if (news != 'Q' and news != 'A' and news != 'Z' and news != 'E' and news != 'D' and news != 'C') {
                    cout << "Enter a valid input! ";
                    continue;
                }
                if (r == true or l == true) {
                    if (r == true and news == 'D') {
                        if (Push_Right() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }
                    else if (l == true and news == 'D') {
                        int tttptpt = coordinates[0][0];
                        coordinates[0][0] = coordinates[1][0];
                        coordinates[1][0] = tttptpt;
                        tttptpt = coordinates[0][1];
                        coordinates[0][1] = coordinates[1][1];
                        coordinates[1][1] = tttptpt;
                        if (Push_Right() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }
                    else if (r == true and news == 'A') {
                        int tttptpt = coordinates[0][0];
                        coordinates[0][0] = coordinates[1][0];
                        coordinates[1][0] = tttptpt;
                        tttptpt = coordinates[0][1];
                        coordinates[0][1] = coordinates[1][1];
                        coordinates[1][1] = tttptpt;
                        if (Push_Left() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }
                    else if (l == true and news == 'A') {
                        if (Push_Left() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }

                    dl = To_DownLeft();
                    dr = To_DownRight();
                    ul = To_UpLeft();
                    ur = To_UpRight();

                    if (dl == true and news == 'Z') {
                        By_DownLeft(coordinates[0][0], coordinates[0][1]);
                        By_DownLeft(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else if (dr == true and news == 'C') {
                        By_DownRight(coordinates[0][0], coordinates[0][1]);
                        By_DownRight(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else if (ul == true and news == 'Q') {
                        By_UpLeft(coordinates[0][0], coordinates[0][1]);
                        By_UpLeft(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else if (ur == true and news == 'E') {
                        By_UpRight(coordinates[0][0], coordinates[0][1]);
                        By_UpRight(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else {
                        cout << "You cant move these pieces!";
                        Sleep(2000);
                        continue;
                    }
                }
                else if (ur == true or dl == true) {
                    if (ur == true and news == 'E') {
                        if (Push_UpRight() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }
                    else if (dl == true and news == 'E') {
                        int tttptpt = coordinates[0][0];
                        coordinates[0][0] = coordinates[1][0];
                        coordinates[1][0] = tttptpt;
                        tttptpt = coordinates[0][1];
                        coordinates[0][1] = coordinates[1][1];
                        coordinates[1][1] = tttptpt;
                        if (Push_UpRight() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }
                    else if (ur == true and news == 'Z') {
                        int tttptpt = coordinates[0][0];
                        coordinates[0][0] = coordinates[1][0];
                        coordinates[1][0] = tttptpt;
                        tttptpt = coordinates[0][1];
                        coordinates[0][1] = coordinates[1][1];
                        coordinates[1][1] = tttptpt;
                        if (Push_DownLeft() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }
                    else if (dl == true and news == 'Z') {
                        if (Push_DownLeft() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }

                    ul = To_UpLeft();
                    dr = To_DownRight();
                    l = To_Left();
                    r = To_Right();

                    if (l == true and news == 'A') {
                        By_Left(coordinates[0][0], coordinates[0][1]);
                        By_Left(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else if (dr == true and news == 'C') {
                        By_DownRight(coordinates[0][0], coordinates[0][1]);
                        By_DownRight(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else if (ul == true and news == 'Q') {
                        By_UpLeft(coordinates[0][0], coordinates[0][1]);
                        By_UpLeft(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else if (r == true and news == 'D') {
                        By_Right(coordinates[0][0], coordinates[0][1]);
                        By_Right(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else {
                        cout << "You cant move these pieces!";
                        Sleep(2000);
                        continue;
                    }
                }
                else if (ul == true or dr == true) {
                    if (ul == true and news == 'Q') {
                        if (Push_UpLeft() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }
                    else if (dr == true and news == 'Q') {
                        int tttptpt = coordinates[0][0];
                        coordinates[0][0] = coordinates[1][0];
                        coordinates[1][0] = tttptpt;
                        tttptpt = coordinates[0][1];
                        coordinates[0][1] = coordinates[1][1];
                        coordinates[1][1] = tttptpt;
                        if (Push_UpLeft() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }
                    else if (ul == true and news == 'C') {
                        int tttptpt = coordinates[0][0];
                        coordinates[0][0] = coordinates[1][0];
                        coordinates[1][0] = tttptpt;
                        tttptpt = coordinates[0][1];
                        coordinates[0][1] = coordinates[1][1];
                        coordinates[1][1] = tttptpt;
                        if (Push_DownRight() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }
                    else if (dr == true and news == 'C') {
                        if (Push_DownRight() == false) {
                            cout << "You cant move these pieces!";
                            Sleep(1700);
                            continue;
                        }
                        TurnCheck++;
                        break;
                    }

                    l = To_Left();
                    r = To_Right();
                    dl = To_DownLeft();
                    ur = To_UpRight();

                    if (l == true and news == 'A') {
                        By_Left(coordinates[0][0], coordinates[0][1]);
                        By_Left(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else if (dl == true and news == 'Z') {
                        By_DownLeft(coordinates[0][0], coordinates[0][1]);
                        By_DownLeft(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else if (ur == true and news == 'E') {
                        By_UpRight(coordinates[0][0], coordinates[0][1]);
                        By_UpRight(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else if (r == true and news == 'D') {
                        By_Right(coordinates[0][0], coordinates[0][1]);
                        By_Right(coordinates[1][0], coordinates[1][1]);
                        TurnCheck++;
                        break;
                    }
                    else {
                        cout << "You cant move these pieces!";
                        Sleep(2000);
                        continue;
                    }
                }

                TurnCheck++;
                break;
            }
        }
        else if (Moves == "3") {
            while (true) {   
                while (true) {
                    system ("Cls");
                    PrintChart ();
                    while (true) {
                        system ("Cls");
                        PrintChart ();
                        cout << "Enter your FIRST coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                        cout << "FIRST Coord  : ";
                        cout << "( ";
                        x = _getch();
                        if (x == 0x08) {
                            ExitInMove = true;
                            break;
                        }
                        if (x != '0' and x != '1' and x != '2' and x != '3' and
                            x != '4' and x != '5' and x != '6' and x != '7' and x != '8') {
                            cout << '\n' << '\n';
                            cout << "X is not in range! " << "\a" << '\n';
                            cout << '\n';
                            Sleep(1500);
                            continue;
                        }
                        cout << x << " , ";
                        break;
                    }
                    if (ExitInMove == true)
                        break;
                    while (true) {
                        system ("Cls");
                        PrintChart ();
                        cout << "Enter your FIRST coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                        cout << "FIRST Coord  : ";
                        cout << "( " << x << " , ";
                        y = _getch();
                        if (y == 0x08) {
                            ExitInMove = true;
                            break;
                        }
                        if (y != '0' and y != '1' and y != '2' and y != '3' and
                            y != '4' and y != '5' and y != '6' and y != '7' and y != '8') {
                            cout << '\n' << '\n';
                            cout << "Y is not in range! " << "\a" << '\n';
                            cout << '\n';
                            Sleep(1500);
                            continue;
                        }
                        cout << y << " ) ";
                        break;
                    }
                    if (ExitInMove == true) 
                        break;
                    if (HexGrid[x - '0'][y - '0'] == '#') {
                        cout << " is empty! ";
                        Sleep(2000);
                        continue;
                    }
                    if (Turn == 1) {
                        if (HexGrid[x - '0'][y - '0'] != Player_1.symbol) {
                            cout << " is not your piece!";
                            Sleep(2000);
                            continue;
                        }
                    }
                    else if (Turn == 2) {
                        if (HexGrid[x - '0'][y - '0'] != Player_2.symbol) {
                            cout << " is not your piece!";
                            Sleep(2000);
                            continue;
                        }
                    }
                    if (ExitInMove == true) {
                        break;
                    }
                    coordinates[0][0] = x - '0';
                    coordinates[0][1] = y - '0';
                    break;
                }
                if (ExitInMove == true) {
                    ExitInMove = false;    
                    break;
                }
                while (true) {
                    system ("Cls");
                    PrintChart ();
                    while (true) {
                        system ("Cls");
                        PrintChart ();
                        cout << "Enter your SECOND coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                        cout << "FIRST Coord  : " << "( " << coordinates[0][0] << " , " << coordinates[0][1] << " )" << '\n'; 
                        cout << "SECOND Coord : ";
                        cout << "( ";
                        x = _getch();
                        if (x == 0x08) {
                            ExitInMove = true;
                            break;
                        }
                        if (x != '0' and x != '1' and x != '2' and x != '3' and
                            x != '4' and x != '5' and x != '6' and x != '7' and x != '8') {
                            cout << '\n' << '\n';
                            cout << "X is not in range! " << "\a" << '\n';
                            cout << '\n';
                            Sleep(1500);
                            continue;
                        }
                        cout << x << " , ";
                        break;
                    }
                    if (ExitInMove == true)
                        break;
                    while (true) {
                        system ("Cls");
                        PrintChart ();
                        cout << "Enter your SECOND coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                        cout << "FIRST Coord  : " << "( " << coordinates[0][0] << " , " << coordinates[0][1] << " )" << '\n'; 
                        cout << "SECOND Coord : ";
                        cout << "( " << x << " , ";
                        y = _getch();
                        if (y == 0x08) {
                            ExitInMove = true;
                            break;
                        }
                        if (y != '0' and y != '1' and y != '2' and y != '3' and
                            y != '4' and y != '5' and y != '6' and y != '7' and y != '8') {
                            cout << '\n' << '\n';
                            cout << "Y is not in range! " << "\a" << '\n';
                            cout << '\n';
                            Sleep(1500);
                            continue;
                        }
                        cout << y << " ) ";
                        break;
                    }
                    if (ExitInMove == true) 
                        break;
                    if (HexGrid[x - '0'][y - '0'] == '#') {
                        cout << " is empty! ";
                        Sleep(2000);
                        continue;
                    }
                    if (Turn == 1) {
                        if (HexGrid[x - '0'][y - '0'] != Player_1.symbol) {
                            cout << " is not your piece!";
                            Sleep(2000);
                            continue;
                        }
                    }
                    else if (Turn == 2) {
                        if (HexGrid[x - '0'][y - '0'] != Player_2.symbol) {
                            cout << " is not your piece!";
                            Sleep(2000);
                            continue;
                        }
                    }
                    if (ExitInMove == true)
                        break;
                    coordinates[1][0] = x - '0';
                    coordinates[1][1] = y - '0';
                    break;
                }
                if (ExitInMove == true) {
                    ExitInMove = false;    
                    break;
                }
                while (true) {
                    system ("Cls");
                    PrintChart ();
                    while (true) {
                        system ("Cls");
                        PrintChart ();
                        cout << "Enter your THIRD coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                        cout << "FIRST Coord  : " << "( " << coordinates[0][0] << " , " << coordinates[0][1] << " )" << '\n'; 
                        cout << "SECOND Coord : " << "( " << coordinates[1][0] << " , " << coordinates[1][1] << " )" << '\n';
                        cout << "THIRD Coord  : " << "( ";
                        x = _getch();
                        if (x == 0x08) {
                            ExitInMove = true;
                            break;
                        }
                        if (x != '0' and x != '1' and x != '2' and x != '3' and
                            x != '4' and x != '5' and x != '6' and x != '7' and x != '8') {
                            cout << '\n' << '\n';
                            cout << "X is not in range! " << "\a" << '\n';
                            cout << '\n';
                            Sleep(1500);
                            continue;
                        }
                        cout << x << " , ";
                        break;
                    }
                    if (ExitInMove == true)
                        break;
                    while (true) {
                        system ("Cls");
                        PrintChart ();
                        cout << "Enter your THIRD coord (first x and second y) [BACKSPACE : EXIT]: " << '\n';
                        cout << "FIRST Coord  : " << "( " << coordinates[0][0] << " , " << coordinates[0][1] << " )" << '\n'; 
                        cout << "SECOND Coord : " << "( " << coordinates[1][0] << " , " << coordinates[1][1] << " )" << '\n';
                        cout << "THIRD Coord  : " << "( " << x << " , ";
                        y = _getch();
                        if (y == 0x08) {
                            ExitInMove = true;
                            break;
                        }
                        if (y != '0' and y != '1' and y != '2' and y != '3' and
                            y != '4' and y != '5' and y != '6' and y != '7' and y != '8') {
                            cout << '\n' << '\n';
                            cout << "Y is not in range! " << "\a" << '\n';
                            cout << '\n';
                            Sleep(1500);
                            continue;
                        }
                        cout << y << " ) ";
                        break;
                    }
                    if (ExitInMove == true) 
                        break;
                    if (HexGrid[x - '0'][y - '0'] == '#') {
                        cout << " is empty! ";
                        Sleep(2000);
                        continue;
                    }
                    if (Turn == 1) {
                        if (HexGrid[x - '0'][y - '0'] != Player_1.symbol) {
                            cout << " is not your piece!";
                            Sleep(2000);
                            continue;
                        }
                    }
                    else if (Turn == 2) {
                        if (HexGrid[x - '0'][y - '0'] != Player_2.symbol) {
                            cout << " is not your piece!";
                            Sleep(2000);
                            continue;
                        }
                    }
                    if (ExitInMove == true)
                        break;
                    coordinates[2][0] = x - '0';
                    coordinates[2][1] = y - '0';

                    break;
                }
            }

            /*
            if (Left_3(coordinates[0][0], coordinates[0][1], coordinates[1][0], coordinates[1][1]) == true or
            Right_3(coordinates[0][0], coordinates[0][1], coordinates[1][0], coordinates[1][1]) == true or
            UpLeft_3(coordinates[0][0], coordinates[0][1], coordinates[1][0], coordinates[1][1]) == true or
            UpRight_3(coordinates[0][0], coordinates[0][1], coordinates[1][0], coordinates[1][1]) == true or
            DownLeft_3(coordinates[0][0], coordinates[0][1], coordinates[1][0], coordinates[1][1]) == true or
            DownRight_3(coordinates[0][0], coordinates[0][1], coordinates[1][0], coordinates[1][1]) == true) {
            }
            */

        }
        else {
            cout << '\n';
            cout << "Enter a valid number! " << "\a" << '\n';
            cout << '\n';
            Sleep(1000);
            continue;
        }
        END
    }
}

int main() {

    while (GameStatus != true) {

        system ("Cls");

        cout << "|=======Abalone=======|" << '\n'; 
        cout << "|- [0] : Play Game   -|" << '\n';
        cout << "|- [1] : Scoreboard  -|" << '\n';
        cout << "|- [2] : Text color  -|" << '\n';
        cout << "|- [3] : Save game   -|" << '\n';
        cout << "|- [4] : Exit        -|" << '\n';
        cout << "|=====================|" << '\n';

        cout << " Choose your option :";
        cin >> Enter;
        getline(cin, Fix);
        system ("Cls");

        if (Enter == "0") { 

            cout << "[0] : New game" << '\n';
            cout << "[1] : Load game" << '\n';
            cout << "Enter your option : ";

            cin >> NorL;
            getline(cin, Fix);

            if (NorL == "0") { 
                system ("Cls");
                Form_HexGrid();

                cout << "Enter player 1 name (X) : ";
                getline(cin, Player_1.name);
                cout << '\n' << '\n';
                cout << "Enter player 2 name (O) : ";
                getline(cin, Player_2.name);
                cout << '\n' << '\n';
                system ("Cls");

                long long int Player1_Name_len = Player_1.name.length();
                long long int Player2_Name_len = Player_2.name.length();
                long long int K = 0, q1 = 0, q2 = 0;
                q1 = Player1_Name_len;
                q2 = Player2_Name_len;
                while (q1 >= 0) {
                    if (Player_1.name[q1] == ' ' or int(Player_1.name[q1]) == 13)
                        K++;
                    q1--;
                }
                if (K == Player1_Name_len)
                    Player_1.name = "Player 1";
                K = 0;
                while (q2 >= 0) {
                    if (Player_2.name[q2] == ' ' or int(Player_2.name[q2]) == 13)
                        K++;
                    q2--;
                }
                if (K == Player2_Name_len)
                    Player_2.name = "Player 2";

                SaveCheck = true;
                Gameover = false;
                Player_1.score = 0;
                Player_2.score = 0;
                Player_1.Number_Of_GamePieces = 14;
                Player_2.Number_Of_GamePieces = 14;
                Timer = 0;
                Turn = 1;

                Game();
            }
            else if (NorL == "1") { 
                ifstream Save ("Game_Save.txt");
                if (Save.peek() == EOF) {
                    cout << '\n';
                    cout << "You dont have any save for game!";
                    Sleep(2000);
                    continue;
                }
                Gameover = false;
                SaveCheck = true;
                string Line;
                getline(Save, Line);
                Player_1.name = Line;
                getline(Save, Line);
                Player_2.name = Line;
                getline(Save, Line);
                Player_1.Number_Of_GamePieces = stoi(Line);
                getline(Save, Line);
                Player_2.Number_Of_GamePieces = stoi(Line);
                getline(Save, Line);
                Player_1.score = stoi(Line);
                getline(Save, Line);
                Player_2.score = stoi(Line);
                getline(Save, Line);
                Turn = stoi(Line);
                getline(Save, Line);
                Timer = stod(Line);
                getline(Save, Line);
                Form_HexGrid();
                int LineWalk = 0;
                for (int i = 0; i < 9; i++) {
                    int row;
                    if (i < 5)
                        row = (5 + i);
                    else
                        row = (9 - (i % 5) - 1);
                    for (int j = 0; j < row; j++) {
                        HexGrid[i][j] = Line[LineWalk];
                        LineWalk++;
                    }
                }
                system ("Cls");

                Game();
                continue;
            }
            else {
                cout << '\n';
                cout << "Enter a valid number! " << "\a" << '\n';
                cout << '\n';
                Sleep(1500);
                continue;
            }
        }
        else if (Enter == "1") {
            cout << "#-----------------#" << '\n';
            cout << "| " << Player_1.name << " : " << Player_1.score << '\n';
            cout << "|------------------" << '\n';
            cout << "| " << Player_2.name << " : " << Player_2.score << '\n';
            cout << "#-----------------#" << '\n' << '\n';
            cout << "Press any key to continue..." << '\n';
            if (_getch() == true)
                continue;
        }
        else if (Enter == "2") { 
            if (CheckColor % 2 == 0)
                system("Color 0A");
            else
                system("color 7");
            CheckColor++;
            cout << '\n';
        }
        else if (Enter == "3") { 
            if (Gameover == true) {
                system("Cls");
                cout << "This game is over, you cant save it! Start a new game. ";
                Sleep(2000);
                continue;
            }
            if (SaveCheck == true) {
                ofstream Save ("Game_Save.txt");

                Save << Player_1.name << '\n'; // 1
                Save << Player_2.name << '\n'; // 2

                Save << Player_1.Number_Of_GamePieces << '\n'; // 3
                Save << Player_2.Number_Of_GamePieces << '\n'; // 4

                Save << Player_1.score << '\n'; // 5
                Save << Player_2.score << '\n'; // 6

                Save << Turn << '\n'; // 7

                Save << Timer << '\n'; // 8

                for (int i = 0; i < 9; i++) {
                    int row;
                    if (i < 5)
                        row = (5 + i);
                    else
                        row = (9 - (i % 5) - 1);
                    for (int j = 0; j < row; j++)
                        Save << HexGrid[i][j]; // 9
                }
                cout << "Saved!";
                Sleep(1500);
            }
            else {
                cout << "First start a game! " << '\n';
                Sleep(2000);
            }
        }
        else if (Enter == "4") { 
            while (true) {
                system ("Cls");
                cout << "-------------------------";
                cout << " Are you sure for exit? (YES or NO) ";
                cout << "-------------------------";
                cout << '\n';
                cin >> ExitCheck;
                if (ExitCheck == "YES") {
                    system("color 7");
                    exit(0);
                }
                else if (ExitCheck == "NO") {
                    system ("Cls");
                    cout << '\n';
                    cout << "          OK! " << '\n';
                    cout << '\n';
                    Sleep (1000);
                    break;
                }
                else {
                    cout << '\n';
                    cout << "Enter a valid option! (Check uppercase & lowercase letters) " << "\a" << '\n';
                    cout << '\n';
                    Sleep (2000);
                    continue;
                }
            }
        }
        else {
            cout << '\n';
            cout << "Enter a valid number! " << "\a" << '\n';
            cout << '\n';
            Sleep(1500);
        }
    }

    getch();
    return 0;
}
