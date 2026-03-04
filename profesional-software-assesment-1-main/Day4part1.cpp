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
	/*day 4 part 1*/
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


	/*loop through the x axis*/
	for (vector<char> row : wordgrid) {
		for (int i = 0; i + 3 < row.size(); i++) {
			bool ordered = row[i] == 'X' && row[i + 1] == 'M' && row[i + 2] == 'A' && row[i + 3] == 'S';

			bool reversed = row[i] == 'S' && row[i + 1] == 'A' && row[i + 2] == 'M' && row[i + 3] == 'X';

			if (ordered || reversed) {
				totalxmas++;
			}

		}
	}

	//loop through the y axis
	for (int i = 0; i < wordgrid[0].size(); i++) {
		vector<char> thewords;
		for (int j = 0; j + 3 < wordgrid.size(); j++) {
			thewords.push_back(wordgrid[j][i]);
			if (thewords.size() > 4) {
				thewords.erase(thewords.begin());
			}
			bool ordered = wordgrid[j][i] == 'X' && wordgrid[j + 1][i] == 'M' && wordgrid[j + 2][i] == 'A' && wordgrid[j + 3][i] == 'S';
			bool reversed = wordgrid[j][i] == 'S' && wordgrid[j + 1][i] == 'A' && wordgrid[j + 2][i] == 'M' && wordgrid[j + 3][i] == 'X';
			if (ordered || reversed) {
				totalxmas++;
			}
		}
		thewords.clear();
	}

	cout << "day 4 part 1 answer:" << endl;
	cout << totalxmas << endl;
}