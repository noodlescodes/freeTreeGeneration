#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>

using namespace std;

const int INFINITY = INT_MAX;
int k;
vector<int> L;
vector<int> W;
int p;
int q;
int h1;
int h2;
int r;
int c;
int n;

void set_params(int n) {
	k = (n >> 1) + 1; // floor(n/2) + 1

	// Calculate L
	for(int i = 1; i <= k; i++) {
		L.push_back(i);
	}
	for(int i = 2; i <= (n - k + 1); i++) {
		L.push_back(i);
	}

	// Calculate W
	for(int i = 0; i <= (k - 1); i++) {
		W.push_back(i);
	}
	W.push_back(1);
	for(int i = k + 1; i <= (n - 1); i++) {
		W.push_back(i);
	}

	p = n;
	if(n == 4) {
		p = 3;
	}

	q = n - 1;

	h1 = k;

	h2 = n;

	r = k;

	if((n % 2) == 0) {
		c = n + 1;
	}
	else {
		c = INFINITY;
	}
}

uint nextTree() {
	bool fixit = false;
	bool needr;
	bool needc;
	bool needh2;
	int oldp;
	int delta;
	int oldlq;
	int oldwq;

	if(c == n + 1 || p == h2 && (L[h1 - 1] == L[h2 - 1] + 1 && n - h2 > r - h1 || L[h1 - 1] && n - h2 + 1 < r - h1)) {
		if(L[r - 1] > 3) {
			p = r;
			q = W[r - 1];
			if(h1 == r) {
				h1 = h1 - 1;
			}
			fixit = true;
		}
		else {
			p = r;
			r = r - 1;
			q = 2;
		}
	}
	needr = false;
	needc = false;
	needh2 = false;
	
	if(p <= h1) {
		h1 = p - 1;
	}
	if(p <= r) {
		needr = true;
	}
	else if(p <= h2) {
		needh2 = true;
	}
	else if(L[h2 - 1] == (L[h1 - 1] - 1) && (n - h2) == (r - h1)) {
		if(p <= c) {
			needc = true;
		}
	}
	else {
		c = INFINITY;
	}

	oldp = p;
	delta = q - p;
	oldlq = L[q - 1];
	oldwq = W[q - 1];
	p = INFINITY;

	for(int i = oldp; i <= n; i++) {
		L[i - 1] = L[i + delta - 1];
		if(L[i - 1] == 2) {
			W[i - 1] = 1;
		}
		else {
			p = i;
			if(L[i - 1] == oldlq) {
				q = oldwq;
			}
			else {
				q = W[i + delta - 1] - delta;
			}
			W[i - 1] = q;
		}
		if(needr && (L[i - 1] == 2)) {
			needr = false;
			needh2 = true;
			r = i - 1;
		}
		if(needh2 && (L[i - 1] <= L[i - 1 - 1]) && (i > (r + 1))) {
			needh2 = false;
			h2 = i - 1;
			if((L[h2 - 1] == (L[h1 - 1] - 1)) && ((n - h2) == (r - h1))) {
				needc = true;
			}
			else {
				c = INFINITY;
			}
		}
		if(needc) {
			if(L[i - 1] != (L[h1 - h2 + i - 1] - 1)) {
				needc = false;
				c = i;
			}
			else {
				c = i + 1;
			}
		}
	}
	if(fixit) {
		r = n - h1 + 1;
		for(int i = r + 1; i <= n; i++) {
			L[i - 1] = i - r + 1;
			W[i - 1] = i - 1;
		}
		W[r + 1 - 1] = 1;
		h2 = n;
		p = n;
		q = p - 1;
		c = INFINITY;
	}
	else {
		if(p == INFINITY) {
			if(L[oldp - 1 - 1] != 2) {
				p = oldp - 1;
			}
			else {
				p = oldp - 2;
			}
			q = W[p - 1];
		}
		if(needh2) {
			h2 = n;
			if((L[h2 - 1] == L[h1 - 1] - 1) && (h1 == r)) {
				c = n + 1;
			}
			else {
				c = INFINITY;
			}
		}
	}

	return q;
}

void printVector(vector<int> v) {
	cout << "[";
	for(uint i = 0; i < v.size() - 1; i++) {
		cout << v[i] << ",";
	}
	cout << v[v.size() - 1] << "]" << endl;
}

int main(int argc, char *argv[]) {
	vector<vector<int> > trees;
        n = atoi(argv[1]);
	set_params(n);

	trees.push_back(L);

	while(q != 0) {
		nextTree();
		//printVector(L);
		trees.push_back(L);
	}

	//for(uint i = 0; i < trees.size(); i++) {
	//	printVector(trees[i]);
	//}
}
