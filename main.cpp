#include <iostream>
#include <fstream>
#include <chrono>
#include <cassert>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <sstream>

using namespace std;
using namespace chrono;
const int day2 = 1000;

int main() {
	ifstream file1("Day1.txt");

	vector<int> right, left;
	int x, y;

	while (file1 >> x >> y) {
		right.push_back(x);
		left.push_back(y);
	}


	/*day 1 part 2*/
	long total2 = 0;
	for (int i = 0; i < right.size(); i++) {
		int count = 0;
		for (int j = 0; j < left.size(); j++) {
			if (right[i] == left[j]) {
				count += 1;
			}
		}
		int stuff = right[i] * count;
		total2 += stuff;
	}
	cout << "day 1 part 2 answer:" << endl;
	cout << total2 << endl;

	/*day 1 part 1*/
	sort(right.begin(), right.end());
	sort(left.begin(), left.end());

	long  total = 0;
	for (int i = 0; i < right.size(); i++) {
		total += abs(right[i] - left[i]);
	}
	cout << "day 1 part 1 answer:" << endl;
	cout << total << endl;



	/*day 2 part 1*/
	ifstream file2("Day2.txt");
	vector<string> Day2;
	for (int i = 0; i < day2; i++) {
		string line;
		getline(file2, line);
		Day2.push_back(line);
	}

	int safecount = 0;
	vector<string> unsafelevels;
	for (string line : Day2) {
		//cout << line << endl;
		stringstream ss(line);
		int deviation_count = 0;

		//added level deviation to check for how far off the levels are, or how many levels are off by more than 2
		int level_deviation = 0;
		vector<int> numbers;
		bool growing;
		int prevnum;
		int x;
		while (ss >> x) {
			numbers.push_back(x);
		}

		for (int i = 0; i < numbers.size(); i++) {
			//cout << numbers[i] << endl;
			if (i == 0) {
				prevnum = numbers[i];
			}
			else if (i == 1) {
				//determine if its growing or not
				if (numbers[i] > prevnum) {
					growing = true;
				}
				else {
					growing = false;
				}

				//check if the level difference is more than 3 or less than 1
				int diff = abs(prevnum - numbers[i]);
				if (diff < 1 || diff > 3) deviation_count++;


				prevnum = numbers[i];


			}
			else {
				/*check for the growth in an instance
				it will ensure something breaks the rule of whether something is growing abnormaly*/
				if (growing && prevnum > numbers[i])deviation_count++;
				else if (!growing && prevnum < numbers[i])deviation_count++;


				//check if the level difference is more than 3 or less than 1
				int diff = abs(prevnum - numbers[i]);
				if (diff < 1 || diff > 3) deviation_count++;

				prevnum = numbers[i];
			}
		}
		if (deviation_count == 0) {
			safecount += 1;
		}
		else {
			unsafelevels.push_back(line);
			//after that create another loop outside this loop which loops the deletion of every level as a sort of last chance cleanup
		}
	}
	cout << "day 2 part 1 answer:" << endl;
	cout << safecount << endl;
	cout << unsafelevels.size() << " unsafelevels found" << endl;

	//day 2 part 2
	for (string level : unsafelevels) {
		stringstream ss(level);
		vector<int> numbers;
		vector< vector<int> > modified_levels;
		int safe_deletions = 0;
		int x;
		while (ss >> x) {
			numbers.push_back(x);
		}
		//try removing each number and see if it makes it safe
		for (int i = 0; i < numbers.size(); i++) {
			vector<int> modified_level;
			for (int j = 0; j < numbers.size(); j++) {
				if (j != i) {
					modified_level.push_back(numbers[j]);
				}
			}
			modified_levels.push_back(modified_level);
		}
		//to do: find a way to remove each number without actually removing it, maybe by just skipping it in the loop and seeing if it makes it safe
		for (vector<int> mod_level : modified_levels) {
			int deviation_count = 0;
			bool growing;
			int prevnum;

			for (int i = 0; i < mod_level.size(); i++) {
				if (i == 0) {
					prevnum = mod_level[i];
				}
				else if (i == 1) {
					//determine if its growing or not
					if (mod_level[i] > prevnum) {
						growing = true;
					}
					else {
						growing = false;
					}
					//check if the level difference is more than 3 or less than 1
					int diff = abs(prevnum - mod_level[i]);
					if (diff < 1 || diff > 3) deviation_count++;

					prevnum = mod_level[i];
				}
				else {

					if (growing && prevnum > mod_level[i])deviation_count++;
					else if (!growing && prevnum < mod_level[i])deviation_count++;

					int diff = abs(prevnum - mod_level[i]);
					if (diff < 1 || diff > 3) deviation_count++;

					prevnum = mod_level[i];
				}
			}

			if (deviation_count == 0) {
				safe_deletions += 1;
			}

		}

		if (safe_deletions > 0) {
			safecount += 1;
		}


	}
	cout << "day 2 part 2 answer:" << endl;
	cout << safecount << endl;

	/*day 3 part 1*/
	vector < vector<int> > numbers;
	int total3 = 0;
	ifstream file3("Day3.txt");
	vector<string>Day3;
	string line;

	while (getline(file3, line)) {
		Day3.push_back(line);
	}
	for (string line : Day3) {
		int order = 0;
		string multstuff;
		/*collect the characters*/
		for (char c : line) {
			if (order == 0) {
				if (c == 'm') order = 1;

			}
			else if (order == 1) {
				if (c == 'u') order = 2;
				else order = 0;
			}
			else if (order == 2) {
				if (c == 'l') order = 3;
				else order = 0;
			}
			else if (order == 3) {
				if (c == '(') {
					order = 4;
					multstuff.clear();
				}
				else order = 0;
			}
			else if (order == 4) {
				if (c == ')') {
					bool valid = true;
					int commacount = 0;
					for (char mc : multstuff) {
						if (mc == ',') {
							commacount++;
						}
						else if (!isdigit(mc)) {
							valid = false;
							break;
						}
					}

					if (valid && commacount == 1) {
						//added
						int commaindex = multstuff.find(',');

						string left = multstuff.substr(0, commaindex);
						string right = multstuff.substr(commaindex + 1);


						if (left.size() >= 1 && left.size() <= 3 && right.size() >= 1 && right.size() <= 3) {
							replace(multstuff.begin(), multstuff.end(), ',', ' ');
							int a = stoi(left);
							int b = stoi(right);
							total3 += a * b;

						}

						//added ab



					}

					multstuff.clear();
					order = 0;

				}
				else if (isdigit(c) || c == ',') {
					multstuff += c;
				}
				else {
					order = 0;
					multstuff.clear();
				}

			}
			else {
				order = 0;
			}
		}


		//if (numbers.size() == 2) {
		//	cout << numbers[0] * numbers[1] << endl;
		//}
		//else if (numbers.size() > 2){
		//	cout << "error: more than 2 numbers found in line" << endl;
		//}
		//else {
		//	cout << "error: less than 2 numbers found in line" << endl;
		//}

	}

	cout << "day 3 part 1 answer:" << endl;
	cout << total3 << endl;
	//day 3 part 2
	total3 = 0;
	bool mulEnabled = true;

	line = "";

	for (string line : Day3) {

		int orderMul = 0;
		int orderDo = 0;
		int orderDont = 0;
		string multstuff;

		for (char c : line) {


			if (orderDo == 0 && c == 'd') orderDo = 1;
			else if (orderDo == 1 && c == 'o') orderDo = 2;
			else if (orderDo == 2 && c == '(') orderDo = 3;
			else if (orderDo == 3 && c == ')') {
				mulEnabled = true;
				orderDo = 0;
			}
			else orderDo = 0;


			if (orderDont == 0 && c == 'd') orderDont = 1;
			else if (orderDont == 1 && c == 'o') orderDont = 2;
			else if (orderDont == 2 && c == 'n') orderDont = 3;
			else if (orderDont == 3 && c == '\'') orderDont = 4;
			else if (orderDont == 4 && c == 't') orderDont = 5;
			else if (orderDont == 5 && c == '(') orderDont = 6;
			else if (orderDont == 6 && c == ')') {
				mulEnabled = false;
				orderDont = 0;
			}
			else orderDont = 0;


			if (orderMul == 0) {
				if (c == 'm') orderMul = 1;
			}
			else if (orderMul == 1) {
				if (c == 'u') orderMul = 2;
				else orderMul = 0;
			}
			else if (orderMul == 2) {
				if (c == 'l') orderMul = 3;
				else orderMul = 0;
			}
			else if (orderMul == 3) {
				if (c == '(') {
					orderMul = 4;
					multstuff.clear();
				}
				else orderMul = 0;
			}
			else if (orderMul == 4) {

				if (c == ')') {

					if (mulEnabled) {

						bool valid = true;
						int commacount = 0;

						for (char mc : multstuff) {
							if (mc == ',') commacount++;
							else if (!isdigit(mc)) {
								valid = false;
								break;
							}
						}

						if (valid && commacount == 1) {

							int commaindex = multstuff.find(',');

							string left = multstuff.substr(0, commaindex);
							string right = multstuff.substr(commaindex + 1);

							if (left.size() >= 1 && left.size() <= 3 &&
								right.size() >= 1 && right.size() <= 3)
							{
								int a = stoi(left);
								int b = stoi(right);

								total3 += a * b;
							}
						}
					}

					multstuff.clear();
					orderMul = 0;
				}
				else if (isdigit(c) || c == ',') {
					multstuff += c;
				}
				else {
					orderMul = 0;
					multstuff.clear();
				}
			}
		}
	}

	cout << "day 3 part 2 answer:\n";
	cout << total3 << endl;





	/*day 4 part 1*/
	ifstream file4("Day4.txt");
	string theword = "XMAS";
	vector<string> words;
	vector< vector<char> > wordgrid;
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


	//loop through the diagonals
	for (int i = 0; i < wordgrid.size(); i++) {
		for (int j = 0; j < wordgrid[i].size(); j++) {
			if (i + 3 < wordgrid.size() && j + 3 < wordgrid[i].size()) {
				bool ordered = wordgrid[i][j] == 'X' && wordgrid[i + 1][j + 1] == 'M' && wordgrid[i + 2][j + 2] == 'A' && wordgrid[i + 3][j + 3] == 'S';
				bool reversed = wordgrid[i][j] == 'S' && wordgrid[i + 1][j + 1] == 'A' && wordgrid[i + 2][j + 2] == 'M' && wordgrid[i + 3][j + 3] == 'X';
				if (ordered || reversed) {
					totalxmas++;
				}
			}
			if (i - 3 >= 0 && j + 3 < wordgrid[i].size()) {
				bool ordered = wordgrid[i][j] == 'X' && wordgrid[i - 1][j + 1] == 'M' && wordgrid[i - 2][j + 2] == 'A' && wordgrid[i - 3][j + 3] == 'S';
				bool reversed = wordgrid[i][j] == 'S' && wordgrid[i - 1][j + 1] == 'A' && wordgrid[i - 2][j + 2] == 'M' && wordgrid[i - 3][j + 3] == 'X';
				if (ordered || reversed) {
					totalxmas++;
				}
			}
		}
	}

	cout << "day 4 part 1 answer:" << endl;
	cout << totalxmas << endl;

	/*day 4 part 2*/
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


	/*day 5 part 1*/
	/*i got this from somewhere else*/
	ifstream file5("Day5.txt");
	string line5;
	unordered_map<int8_t, unordered_set<int8_t>> p;
	while (getline(file5, line5) && (line5 != ""))
		p[stoi(line5.substr(0, 2))].insert(stoi(line5.substr(3, 2)));
	int part1(0), part2(0);
	while (getline(file5, line5)) {
		vector<int8_t> ordered;
		for (int i = 0; i < line5.length(); i += 3) ordered.push_back(stoi(line5.substr(i, 2)));
		auto unOrdered(ordered);
		sort(ordered.begin(), ordered.end(),
			[&p](int8_t l, int8_t r) { return p[l].find(r) != p[l].end(); });
		if (unOrdered == ordered)
			part1 += ordered[ordered.size() / 2];
		else
			part2 += ordered[ordered.size() / 2];
	}
	
	cout << "Part 1" << part1 << endl;
	cout << "Part 2" << part2 << endl;
	return 0;
}
