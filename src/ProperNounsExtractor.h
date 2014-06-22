#include "stdafx.h"
#include <string>
#include <vector>
#include <regex>
#include <iostream>

class ProperNouns {

public:
	
	std::vector<std::string> words;

	ProperNouns(std::string text) {
		std::regex re("\\b[A-Z]([A-Za-z]|\\d)*");
		std::smatch m;
		std::regex_token_iterator<std::string::iterator> rend, it(text.begin(), text.end(), re);
		words = { it, rend };
	}

};