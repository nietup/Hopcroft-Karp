// Karp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

class Matcher {
public:
	Matcher(int, vector<int>*);
	~Matcher();

	int * Match();
	void InitMatch();
	bool CorrectMatches();

private:
	int n, matchedNo;
	int * matchLeft;
	int * matchRight;
	vector<int> * edges;
};

Matcher::Matcher(int _n, vector<int> * _e) : n(_n), matchedNo(0) {
	edges = new vector<int>[n];
	edges = _e;
}

Matcher::~Matcher() {
	delete edges;
}

int * Matcher::Match() {
	InitMatch();
	while (CorrectMatches());
	return matchLeft;
}

void Matcher::InitMatch() {
	matchLeft = new int[n];
	matchRight = new int[n];
	bool * matched = new bool[n];
	for (int i = 0; i < n; i++) {
		matchLeft[i] = matchRight[i] = -1;
		matched[i] = false;
	}
	for (int i = 0; i < n; i++) {
		int clean = -1;
		int j = 0;
		for (auto e : edges[i]) {
			if (!matched[e]) {
				matchLeft[i] = e;
				matchRight[e] = i;
				matched[e] = true;
				matchedNo++;
				clean = j;
				break;
			}
			j++;
		}
		if (-1 != clean)
			edges[i].erase(edges[i].begin() + j);
	}
	delete matched;
}

bool Matcher::CorrectMatches() {
	if (n == matchedNo)
		return false;

	int currentLeft = -1;
	int currentRight;
	for (int i = 0; i < n; i++)
		if (-1 == matchLeft[i]) {
			currentLeft = i;
			break;
		}
	if (-1 == currentLeft)
		return false;

	vector<int> alternatingPath;
	alternatingPath.push_back(currentLeft);

	while (true) {
		int esize = edges[currentLeft].size();
		if (esize) {
			//loop in ap check
			//check if there is a vertex on the right size that is:
			// connected with current left vertex (== is in edges[currentLeft])
			// not yed added to alternating path  (== is not in alternatingPath)
			int notAPVertex = -1;
			for (auto & p : edges[currentLeft]) {
				for (auto & q : alternatingPath)
					if (q == p) break;
				notAPVertex = p;
				break;
			}

			//failure
			if (-1 == notAPVertex) {
				//-1 = matching NOT YET found
				//-2 = matching impossible
				matchLeft[alternatingPath[0]] = -2;
				return true;
			}

			//success
			if (0 <= notAPVertex) {
				currentRight = edges[currentLeft][notAPVertex];
				alternatingPath.push_back(currentRight);
			}
		}
		else {
			matchLeft[alternatingPath[0]] = -2;
			
			return true;
		}

		if (-1 != matchRight[currentRight]) {
			currentLeft = matchRight[currentRight];
			alternatingPath.push_back(currentLeft);
		}
		else {
			int size = alternatingPath.size();
			for (int i = 0; i < size; i += 2) {
				matchLeft[alternatingPath[i]] = alternatingPath[i + 1];
				matchRight[alternatingPath[i + 1]] = alternatingPath[i];
			}
			matchedNo++;

			return true;
		}
	}
}

int main() {
	/*const int n = 5;
	vector<int> edges[n];
	edges[0].push_back(0);
	edges[0].push_back(2);
	edges[1].push_back(3);
	edges[1].push_back(4);
	edges[2].push_back(1);
	edges[2].push_back(2);
	edges[3].push_back(2);
	edges[3].push_back(3);
	edges[4].push_back(2);*/


	/*const int n = 3;
	vector<int> edges[n];
	edges[0].push_back(0);
	edges[0].push_back(1);
	edges[1].push_back(0);
	edges[2].push_back(1);
	edges[2].push_back(2);*/

	/*const int n = 5;
	vector<int> edges[n];
	edges[0].push_back(0);
	edges[0].push_back(1);
	edges[1].push_back(0);
	edges[2].push_back(1);
	edges[2].push_back(4);
	edges[3].push_back(2);
	edges[3].push_back(3);
	edges[3].push_back(4);
	edges[4].push_back(2);*/

	/*const int n = 6;
	vector<int> edges[n];
	edges[0].push_back(0);
	edges[0].push_back(1);
	edges[1].push_back(0);
	edges[2].push_back(1);
	edges[2].push_back(2);
	edges[2].push_back(3);
	edges[3].push_back(1);
	edges[3].push_back(2);
	edges[4].push_back(2);
	edges[4].push_back(3);
	edges[5].push_back(2);
	edges[5].push_back(3);*/

	const int n = 3;
	vector<int> edges[n];
	edges[0].push_back(0);
	edges[0].push_back(1);
	edges[0].push_back(2);
	edges[1].push_back(0);
	edges[2].push_back(0);
	edges[2].push_back(1);


	Matcher mat(n, edges);
	int * match = mat.Match();

	cout << "Found match: ";
	for (int i = 0; i < n; i++)
		cout << match[i] << " ";

	cin.get();
	return 0;
}
