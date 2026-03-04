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
    /*day 2 part 1*/
	ifstream file2("Day2.txt");
	vector<string> Day2;
	for (int i = 0; i < 1000; i++) {
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
}