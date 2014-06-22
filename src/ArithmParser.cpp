#include "stdafx.h"
#include "ArithmParser.h"

using namespace std;

void fill_operations_map(map<char, function<int(int, int)>>& operations) {
	operations['+'] = [](int a, int b) { return a + b; };
	operations['-'] = [](int a, int b) { return a - b; };
	operations['*'] = [](int a, int b) { return a * b; };
	operations['/'] = [](int a, int b) { return a / b; };
}

int ArithmExpr::calculate() {
	list<int> expr = tokenize_and_check(data);
	stack<list<int>::iterator> st;
	for (auto it = expr.begin(); it != expr.end(); ++it) {
		int token = *it;
		if (token == INT_MIN) {
			st.push(it);
		} else if (token == INT_MIN + 1) {
			calculate(expr, st.top(), it);
			st.pop();
		}
	}
	return expr.front();
}

list<int> ArithmExpr::tokenize_and_check(const string& expr) const {
	list<int> tokens;
	tokens.push_back(INT_MIN);
	stringstream ss;
	int state = 0;
	int num = 0;
	int brackets = 0;
	for (const char& c : expr) {
		if (c == ' ') continue;
		if ((state & 1) && operations.count(c)) {
			if (state == 1 || state == 3) {
				ss >> num;
				ss = stringstream();
				tokens.push_back(state == 3 ? -num : num);
			}
			tokens.push_back(INT_MIN - 40 + c);
			state = 2;
		} else if (c == '(') {
			if (state == 3) {
				tokens.push_back(-1);
				tokens.push_back(INT_MIN + 2);
			}
			tokens.push_back(INT_MIN);
			++brackets;
			state = 0;
		} else if (c == ')') {
			if (state == 1 || state == 3) {
				ss >> num;
				ss = stringstream();
				tokens.push_back(state == 3 ? -num : num);
			}
			tokens.push_back(INT_MIN + 1);
			--brackets;
			state = 5;
		} else {
			if (c == '-') state = 3;
			else {
				ss << c;
				if (state != 3) state = 1;
			}
		}
	}
	try {
		if (brackets) throw runtime_error("Brackets do not match.");
	} catch (exception& e) {
		cout << e.what();
		if (brackets > 0) {
			while (brackets--) tokens.push_back(INT_MIN + 1);
			cout << " Additional brackets were appended" << endl;
		} else terminate();
	}
	if (state < 4) {
		ss >> num;
		tokens.push_back(state == 3 ? -num : num);
	}
	tokens.push_back(INT_MIN + 1);
	return tokens;
}

void ArithmExpr::calculate(list<int>& expr, const list<int>::iterator& start, list<int>::iterator& end) {
	calculate(expr, start, end, INT_MIN + 2, INT_MIN + 7);
	calculate(expr, start, end, INT_MIN + 3, INT_MIN + 5);
	expr.erase(start);
	expr.erase(end--);
}

void ArithmExpr::calculate(list<int>& expr, const list<int>::iterator& start, const list<int>::iterator& end, int s1, int s2) {
	for (auto it = start; it != end; ++it) {
		int token = *it;
		if (token == s1 || token == s2) {
			auto first_it = prev(it);
			int res = operations[40 - INT_MIN + token](*first_it, *++it);
			expr.erase(first_it, ++it);
			expr.insert(it--, res);
		}
	}
}