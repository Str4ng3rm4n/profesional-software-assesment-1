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
	/*day 3 part 1*/
	ifstream file3("Day3.txt");
	string Day3;
	string line;

	while (getline(file3, line)) {
		Day3 += line ;
	}

    //day 3 part 2
	regex pattern2(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
	int total3 = 0;
	bool mulEnabled = true;

	sregex_iterator begin(Day3.begin(), Day3.end(), pattern2);
	sregex_iterator end2;

	for (auto i = begin; i != end2; ++i) {
		smatch match = *i;
		if (match[0] == "do()") {
			mulEnabled = true;
		}
		else if (match[0] == "don't()") {
			mulEnabled = false;
		}
		if (mulEnabled && match[1] != "") {
			int num1 = stoi(match[1]);
			int num2 = stoi(match[2]);
			total3 += num1 * num2;
		}
	}

	cout << "day 3 part 2 answer:" << endl;
	cout << total3 << endl;
}