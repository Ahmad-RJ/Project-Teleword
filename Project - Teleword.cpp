#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <chrono>
using namespace std;
void printgrid(char array1[][15], int colorgrid[][15]) {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (colorgrid[i][j] == 0) {
				SetConsoleTextAttribute(h, 7);
				cout << array1[i][j] << " ";
			}
			if (colorgrid[i][j] == 1) {
				SetConsoleTextAttribute(h, 6);
				cout << array1[i][j] << " ";
			}
			if (colorgrid[i][j] == 2) {
				SetConsoleTextAttribute(h, 9);
				cout << array1[i][j] << " ";
			}
			if (colorgrid[i][j] > 2) {
				SetConsoleTextAttribute(h, 4);
				cout << array1[i][j] << " ";
			}
		}
		SetConsoleTextAttribute(h, 7);
		cout << endl;
	}
}
int largestnumcheck(int array[]) {
	int temp = 0, marker = 0;
	for (int x = 0; x < 15; x++) {
		if (array[x] > temp) {
			temp = array[x];
			marker = x;
		}
	}
	return marker;
}
int getwordlengthfunc(char word[]) {
	int length = 0;
	while (word[length] != '\0') {
		length++;
	}
	return length;
}
int checkscatter(int colorgrid[][15]) {
	int scatter = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			if (colorgrid[i][j] == 0) {
				scatter++;
				break;
			}
		}
	}
	return scatter;
}
int lower2upper(char array2[]) {
	int ascii = 0, i = 0;
	for (i = 0; array2[i] != '.'; i++) {
		ascii = array2[i];
		if (ascii > 96 && ascii < 123) {
			ascii = array2[i];
			ascii -= 32;
			array2[i] = ascii;
		}
	}
	return i;
}
void printtelewordfunc(int colorgrid[][15], char array1[][15]) {
	cout << "Teleword: ";
	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++) {
			if (colorgrid[x][y] == 0) {
				cout << array1[x][y];
			}
		}
	}
	cout << endl;
}
int wordseparator(int counter, char array2[], char word[], int& nextwordstart, int& max, int& min, int& sum, int& count) {
	int temp = nextwordstart, wordsepcheck = 0, temp1 = 0;
	if (nextwordstart > 1) {
		temp = nextwordstart + 1;
	}
	while (nextwordstart <= counter) {
		if (array2[temp] == ',' || array2[temp] == '.') {
			word[wordsepcheck] = '\0';
			break;
		}
		word[wordsepcheck] = array2[temp];
		wordsepcheck++;
		temp++;
	}
	nextwordstart = temp;
	while (word[temp1] != '\0') {
		temp1++;
	}
	if (temp1 > max) {
		max = temp1;
	}
	if (temp1 < min) {
		min = temp1;
	}
	sum = sum + temp1;
	count++;
	return wordsepcheck;
}
int diagonal_left_down(int colorgrid[][15], char array1[][15], char word[], int row, int column, int lengthofword, char lol, int hrow[], int hcol[]) {
	int n = 2, counter = 2, found = 0;
	for (n = 2; n <= lengthofword; n++) {
		if (word[n] == array1[row + n][column - n]) {
			counter++;
		}
	}
	if (counter == lengthofword) {
		colorgrid[row][column]++;
		colorgrid[row + 1][column - 1]++;
		found = 1;
		for (n = 2; n < lengthofword; n++) {
			colorgrid[row + n][column - n]++;
		}
		if (lol == 't' || lol == 'T') {
			printgrid(array1, colorgrid);
			cout << endl;
		}
		for (int x = 0; x < lengthofword; x++) {
			hrow[x + row]++;
		}
		for (int x = 0; x < lengthofword; x++) {
			hcol[column - x]++;
		}
	}
	return found;
}
int vertical_up(int colorgrid[][15], char array1[][15], char word[], int row, int column, int lengthofword, char lol, int hrow[], int hcol[]) {
	int n = 2, counter = 2, found = 0;
	for (n = 2; n <= lengthofword; n++) {
		if (word[n] == array1[row - n][column]) {
			counter++;
		}
	}
	if (counter == lengthofword) {
		colorgrid[row][column]++;
		colorgrid[row - 1][column]++;
		found = 1;
		for (n = 2; n < lengthofword; n++) {
			colorgrid[row - n][column]++;
		}
		if (lol == 't' || lol == 'T') {
			printgrid(array1, colorgrid);
			cout << endl;
		}
		for (int x = 0; x < lengthofword; x++) {
			hrow[row - x]++;
		}
		hcol[column]++;
	}
	return found;
}
int vertical_down(int colorgrid[][15], char array1[][15], char word[], int row, int column, int lengthofword, char lol, int hrow[], int hcol[]) {
	int n = 2, counter = 2, found = 0;
	for (n = 2; n <= lengthofword; n++) {
		if (word[n] == array1[row + n][column]) {
			counter++;
		}
	}
	if (counter == lengthofword) {
		colorgrid[row][column]++;
		colorgrid[row + 1][column]++;
		found = 1;
		for (n = 2; n < lengthofword; n++) {
			colorgrid[row + n][column]++;
		}
		if (lol == 't' || lol == 'T') {
			printgrid(array1, colorgrid);
			cout << endl;
		}
		for (int x = 0; x < lengthofword; x++) {
			hrow[x + row]++;
		}
		hcol[column]++;
	}
	return found;
}
int horizontal_right_left(int colorgrid[][15], char array1[][15], char word[], int row, int column, int lengthofword, char lol, int hrow[], int hcol[]) {
	int n = 2, counter = 2, found = 0;
	for (n = 2; n <= lengthofword; n++) {
		if (word[n] == array1[row][column - n]) {
			counter++;
		}
	}
	if (counter == lengthofword) {
		colorgrid[row][column]++;
		colorgrid[row][column - 1]++;
		found = 1;
		for (n = 2; n < lengthofword; n++) {
			colorgrid[row][column - n]++;
		}
		if (lol == 't' || lol == 'T') {
			printgrid(array1, colorgrid);
			cout << endl;
		}
		hrow[row]++;
		for (int x = 0; x < lengthofword; x++) {
			hcol[column - x]++;
		}
	}
	return found;
}
int horizontal_left_right(int colorgrid[][15], char array1[][15], char word[], int row, int column, int lengthofword, char lol, int hrow[], int hcol[]) {
	int n = 2, counter = 2, found = 0;
	for (n = 2; n <= lengthofword; n++) {
		if (word[n] == array1[row][column + n]) {
			counter++;
		}
	}
	if (counter == lengthofword) {
		colorgrid[row][column]++;
		colorgrid[row][column + 1]++;
		found = 1;
		for (n = 2; n < lengthofword; n++) {
			colorgrid[row][column + n]++;
		}
		if (lol == 't' || lol == 'T') {
			printgrid(array1, colorgrid);
			cout << endl;
		}
		hrow[row]++;
		for (int x = 0; x < lengthofword; x++) {
			hcol[column + x]++;
		}
	}
	return found;
}
int diagonal_left_up(int colorgrid[][15], char array1[][15], char word[], int row, int column, int lengthofword, char lol, int hrow[], int hcol[]) {
	int n = 2, counter = 2, found = 0;
	for (n = 2; n <= lengthofword; n++) {
		if (word[n] == array1[row - n][column - n]) {
			counter++;
		}
	}
	if (counter == lengthofword) {
		colorgrid[row][column]++;
		colorgrid[row - 1][column - 1]++;
		found = 1;
		for (n = 2; n < lengthofword; n++) {
			colorgrid[row - n][column - n]++;
		}
		if (lol == 't' || lol == 'T') {
			printgrid(array1, colorgrid);
			cout << endl;
		}
		for (int x = 0; x < lengthofword; x++) {
			hrow[row - x]++;
		}
		for (int x = 0; x < lengthofword; x++) {
			hcol[column - x]++;
		}
	}
	return found;
}
int diagonal_right_up(int colorgrid[][15], char array1[][15], char word[], int row, int column, int lengthofword, char lol, int hrow[], int hcol[]) {
	int n = 2, counter = 2, found = 0;
	for (n = 2; n <= lengthofword; n++) {
		if (word[n] == array1[row - n][column + n]) {
			counter++;
		}
	}
	if (counter == lengthofword) {
		colorgrid[row][column]++;
		colorgrid[row - 1][column + 1]++;
		found = 1;
		for (n = 2; n < lengthofword; n++) {
			colorgrid[row - n][column + n]++;
		}
		if (lol == 't' || lol == 'T') {
			printgrid(array1, colorgrid);
			cout << endl;
		}
		for (int x = 0; x < lengthofword; x++) {
			hrow[row - x]++;
		}
		for (int x = 0; x < lengthofword; x++) {
			hcol[column + x]++;
		}
	}
	return found;
}
int diagonal_right_down(int colorgrid[][15], char array1[][15], char word[], int row, int column, int lengthofword, char lol, int hrow[], int hcol[]) {
	int n = 2, counter = 2, found = 0;
	for (n = 2; n <= lengthofword; n++) {
		if (word[n] == array1[row + n][column + n]) {
			counter++;
		}
	}
	if (counter == lengthofword) {
		colorgrid[row][column]++;
		colorgrid[row + 1][column + 1]++;
		found = 1;
		for (n = 2; n < lengthofword; n++) {
			colorgrid[row + n][column + n]++;
		}
		if (lol == 't' || lol == 'T') {
			printgrid(array1, colorgrid);
			cout << endl;
		}
		for (int x = 0; x < lengthofword; x++) {
			hrow[x + row]++;
		}
		for (int x = 0; x < lengthofword; x++) {
			hcol[column + x]++;
		}
	}
	return found;
}
int main() {
	int wordsepcheck, nextwordstart = 0, haha = 0, hor_lr = 0, hor_rl = 0, ver_d = 0, ver_u = 0, dia_lu = 0, dia_ld = 0, dia_ru = 0, dia_rd = 0;
	char pressbutton, array1[15][15], input, array2[500], word[15];
	int max = 0, min = 100, sum = 0, count = 0, line = 1, ascii = 0, counter = 0, colorgrid[15][15], numofwords = 1, hrow[15], hcol[15];
	for (int x = 0; x < 15; x++) {
		hrow[x] = 0;
		hcol[x] = 0;
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			colorgrid[i][j] = 0;
		}
	}
	ifstream doc1;
	doc1.open("teleword_1.txt");
	if (doc1.is_open()) {
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				doc1 >> input;
				if (input == ' ') {
					j--;
					continue;
				}
				array1[i][j] = input;
				cout << array1[i][j] << " ";
			}
			cout << endl;
			line++;
		}
		cout << endl;
		for (int i = 0; i < 500 && line >= 15; i++) {
			doc1 >> array2[i];
			if (array2[i] == '.') {
				break;
			}
			cout << array2[i];
			if (array2[i] == ',') {
				cout << " ";
			}
		}
		cout << "." << endl << endl;
	}
	counter = lower2upper(array2);
	for (int i = 0; array2[i] != '\0'; i++) {
		if (array2[i] == ',') {
			numofwords++;
		}
	}
	cout << "1. Press 'T' to Solve Puzzle Step by Step." << endl << "2. Press 'S' to Solve the Puzzle at Once." << endl << "3. Press 'X' for Statistics of the Puzzle." << endl;
	cin >> pressbutton;
	if (pressbutton == 't' || pressbutton == 'T') {
		system("cls");
		printgrid(array1, colorgrid);
		_getch();
		system("cls");
	}
	auto start = std::chrono::steady_clock::now();
	for (int p = 0; p < numofwords; p++) {
		wordsepcheck = wordseparator(counter, array2, word, nextwordstart, max, min, sum, count);
		int lengthofword = getwordlengthfunc(word);
		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				if (word[0] == array1[i][j]) {
					if (word[1] == array1[i][j + 1]) {
						haha = horizontal_left_right(colorgrid, array1, word, i, j, lengthofword, pressbutton, hrow, hcol);
						if (haha == 1) {
							i = 15;
							j = 15;
							haha = 0;
							hor_lr++;
						}
					}
					if (word[1] == array1[i][j - 1]) {
						haha = horizontal_right_left(colorgrid, array1, word, i, j, lengthofword, pressbutton, hrow, hcol);
						if (haha == 1) {
							i = 15;
							j = 15;
							haha = 0;
							hor_rl++;
						}
					}
					if (word[1] == array1[i + 1][j]) {
						haha = vertical_down(colorgrid, array1, word, i, j, lengthofword, pressbutton, hrow, hcol);
						if (haha == 1) {
							i = 15;
							j = 15;
							haha = 0;
							ver_d++;
						}
					}
					if (word[1] == array1[i - 1][j]) {
						haha = vertical_up(colorgrid, array1, word, i, j, lengthofword, pressbutton, hrow, hcol);
						if (haha == 1) {
							i = 15;
							j = 15;
							haha = 0;
							ver_u++;
						}
					}
					if (word[1] == array1[i - 1][j - 1]) {
						haha = diagonal_left_up(colorgrid, array1, word, i, j, lengthofword, pressbutton, hrow, hcol);
						if (haha == 1) {
							i = 15;
							j = 15;
							haha = 0;
							dia_lu++;
						}
					}
					if (j > 0 && i < 14) {
						if (word[1] == array1[i + 1][j - 1]) {
							haha = diagonal_left_down(colorgrid, array1, word, i, j, lengthofword, pressbutton, hrow, hcol);
							if (haha == 1) {
								i = 15;
								j = 15;
								haha = 0;
								dia_ld++;
							}
						}
					}
					if (word[1] == array1[i - 1][j + 1]) {
						haha = diagonal_right_up(colorgrid, array1, word, i, j, lengthofword, pressbutton, hrow, hcol);
						if (haha == 1) {
							i = 15;
							j = 15;
							haha = 0;
							dia_ru++;
						}
					}
					if (word[1] == array1[i + 1][j + 1]) {
						haha = diagonal_right_down(colorgrid, array1, word, i, j, lengthofword, pressbutton, hrow, hcol);
						if (haha == 1) {
							i = 15;
							j = 15;
							haha = 0;
							dia_rd++;
						}
					}
				}
			}
		}
		if (pressbutton == 't' || pressbutton == 'T') {
			_getch();
		}
		if (p < numofwords - 1 && (pressbutton == 't' || pressbutton == 'T')) {
			system("cls");
		}
	}
	if (pressbutton == 's' || pressbutton == 'S') {
		cout << endl;
		printgrid(array1, colorgrid);
		cout << endl;
	}
	if ((pressbutton == 's' || pressbutton == 't') || (pressbutton == 'S' || pressbutton == 'S')) {
		printtelewordfunc(colorgrid, array1);
	}
	auto end = std::chrono::steady_clock::now();
	if (pressbutton == 'x' || pressbutton == 'X') {
		cout << endl;
		printgrid(array1, colorgrid);
		cout << endl;
		printtelewordfunc(colorgrid, array1);
		cout << endl;
		double timetaken = double(std::chrono::duration_cast <std::chrono::microseconds> (end - start).count());
		cout << "Teleword Scatter: " << checkscatter(colorgrid) << endl;
		cout << "Time Taken: " << timetaken << " Micro-seconds" << endl;
		cout << "Longest Word Length: " << max << endl;
		cout << "Shortest Word Length: " << min << endl;
		cout << "Average Word Length: " << sum / count << endl;
		cout << "Word Distribution: Horizontal: " << hor_lr + hor_rl << " (" << hor_lr << ", " << hor_rl << ")";
		cout << ", Vertical: " << ver_d + ver_u << " (" << ver_d << ", " << ver_u << ")";
		cout << ", Diagonal: " << dia_lu + dia_ld + dia_rd + dia_ru << " (" << dia_rd + dia_ru << ", " << dia_lu + dia_ld << ")" << endl;
		cout << "Heaviest Row: " << largestnumcheck(hrow) << endl;
		cout << "Heaviest Column: " << largestnumcheck(hcol) << endl;
	}
	return 0;
}