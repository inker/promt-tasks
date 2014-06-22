#include "stdafx.h"
#include <string>
#include <list>
#include <stack>
#include <iostream>
#include <sstream>
#include <functional>
#include <map>
#include <vector>

void fill_operations_map(std::map<char, std::function<int(int, int)>>& operations) {
	operations['+'] = [](int a, int b) { return a + b; };
	operations['-'] = [](int a, int b) { return a - b; };
	operations['*'] = [](int a, int b) { return a * b; };
	operations['/'] = [](int a, int b) { return a / b; };
}

class ArithmExpr {
	std::string data;
	int calculated_result;
	bool is_calculated;
	std::map<char, std::function<int(int, int)>> operations;

public:
	ArithmExpr() : ArithmExpr(std::string()) {}
	
	ArithmExpr(const std::string& expr) : is_calculated(false), data(expr) {
		fill_operations_map(operations);
	}

	ArithmExpr& operator=(const char* expr) {
		data = expr;
		return *this;
	}

	operator int() {
		if (!is_calculated) {
			calculated_result = calculate();
			is_calculated = true;
		}
		return calculated_result;
	}

private:

	int calculate() {
		std::list<int> expr = tokenize_and_check(data);
		std::stack<std::list<int>::iterator> st;
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

	std::list<int> tokenize_and_check(const std::string& expr) const {
		std::list<int> tokens;
		tokens.push_back(INT_MIN);
		std::stringstream ss;
		int state = 0;
		int num = 0;
		int brackets = 0;
		for (const char& c : expr) {
			if (c == ' ') continue;
			if ((state & 1) && operations.count(c)) {
				if (state == 1 || state == 3) {
					ss >> num;
					ss = std::stringstream();
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
					ss = std::stringstream();
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
			if (brackets) throw std::runtime_error("Brackets do not match.");
		} catch (std::exception& e) {
			std::cout << e.what();
			if (brackets > 0) {
				while (brackets--) tokens.push_back(INT_MIN + 1);
				std::cout << " Additional brackets were appended" << std::endl;
			} else std::terminate();
		}
		if (state < 4) {
			ss >> num;
			tokens.push_back(state == 3 ? -num : num);
		}
		tokens.push_back(INT_MIN + 1);
		return tokens;
	}

	void calculate(std::list<int>& expr, const std::list<int>::iterator& start, std::list<int>::iterator& end) {
		calculate_by_order(expr, start, end, INT_MIN + 2, INT_MIN + 7);
		calculate_by_order(expr, start, end, INT_MIN + 3, INT_MIN + 5);
		expr.erase(start);
		expr.erase(end--);
	}

	void calculate_by_order(std::list<int>& expr, const std::list<int>::iterator& start, const std::list<int>::iterator& end, int s1, int s2) {
		for (auto it = start; it != end; ++it) {
			int token = *it;
			if (token == s1 || token == s2) {
				auto first_it = std::prev(it);
				int res = operations[40 - INT_MIN + token](*first_it, *++it);
				expr.erase(first_it, ++it);
				expr.insert(it--, res);
			}
		}
	}
};