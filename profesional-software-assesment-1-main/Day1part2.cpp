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
}