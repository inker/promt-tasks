#include "stdafx.h"
#include <string>
#include <list>
#include <stack>
#include <iostream>
#include <sstream>
#include <functional>
#include <set>
#include <vector>

void fill_operations_set(std::set<char>& operations);

class ArithmExpr {
	std::string data;
	int calculated_result;
	bool is_calculated;
	std::set<char> operations;

public:
	ArithmExpr() {
		fill_operations_set(operations);
	}
	
	ArithmExpr(const std::string& expr) : is_calculated(false), data(expr) {
		is_calculated = false;
		data = expr;
		fill_operations_set(operations);
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

	int calculate();
	std::list<int> tokenize_and_check(const std::string& expr) const;
	void calculate(std::list<int>& expr, const std::list<int>::iterator& start, std::list<int>::iterator& end);
	void calculate(std::list<int>& expr, const std::list<int>::iterator& start, const std::list<int>::iterator& end, int s1, int s2);
};