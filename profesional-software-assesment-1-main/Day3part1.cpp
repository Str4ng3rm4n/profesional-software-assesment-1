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
	int total3 = 0;
	ifstream file3("Day3.txt");
	regex pattern1(R"(mul\((\d{1,3}),(\d{1,3})\))");
	string Day3;
	string line;

	while (getline(file3, line)) {
		Day3 += line ;
	}
	sregex_iterator begin(Day3.begin(), Day3.end(), pattern1);
	sregex_iterator end;

	for (auto i = begin; i != end; ++i) {
		smatch match = *i;
		int num1 = stoi(match[1]);
		int num2 = stoi(match[2]);
		total3 += num1 * num2;
	}
	cout << "day 3 part 1 answer:" << endl;
	cout << total3 << endl;
}