#include "stdafx.h"
#include <string>
#include <vector>
#include <regex>
#include <iostream>

class ProperNouns {
	std::vector<std::string> words;

public:
	ProperNouns(std::string text) {
		std::regex re("\\b[A-Z]([A-Za-z]|\\d)\\b");
		std::smatch m;
		std::regex_token_iterator<std::string::iterator> rend, it(text.begin(), text.end(), re);
		words = { it, rend };
		for (auto& o : words) {
			std::cout << o << std::endl;
		}
	}
};