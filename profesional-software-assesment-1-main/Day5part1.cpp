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
	/*day 5 part 1*/
	
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
}