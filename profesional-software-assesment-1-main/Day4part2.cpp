#include <iostream>
#include <fstream>
#include <chrono>
#include <regex>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <sstream>

using namespace std;
int main(){
	/*day 4 part 2*/
    ifstream file4("Day4.txt");
	string theword = "XMAS";
	vector<string> words;
	vector< vector<char> > wordgrid;
	string line;
	int totalxmas = 0;


	while (getline(file4, line)) {
		words.push_back(line);
	}

	for (string sentence : words) {
		vector<char> row;
		for (char c : sentence) {
			row.push_back(c);
		}
		wordgrid.push_back(row);
	}

	int totalxmas2 = 0;
	for (int i = 0; i < wordgrid.size() - 1; i++) {
		for (int j = 0; j < wordgrid[i].size() - 1; j++) {
			if (wordgrid[i][j] == 'A' && i >= 1 && j >= 1) {
				char tl = wordgrid[i - 1][j - 1];
				char tr = wordgrid[i - 1][j + 1];
				char bl = wordgrid[i + 1][j - 1];
				char br = wordgrid[i + 1][j + 1];

				bool diag1 = (tl == 'M' && br == 'S') || (tl == 'S' && br == 'M');

				bool diag2 = (tr == 'M' && bl == 'S') || (tr == 'S' && bl == 'M');

				if (diag1 && diag2)
					totalxmas2++;
			}
		}
	}
	cout << "day 4 part 2 answer:" << endl;
	cout << totalxmas2 << endl;
}