#include "stdafx.h"
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <cctype>

class ProperNouns {

public:
	
	std::vector<std::string> words;

	ProperNouns(std::string text) {
		bool proper = false;
		bool prev_non_alnum = true;
		std::string word;
		for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
			char c = *it;
			if (std::isalnum(c)) {
				if (proper) {
					word += c;
				} else if (prev_non_alnum && c >= 'A' && c < 'Z') {
					word += c;
					proper = true;
				}
				prev_non_alnum = false;
			} else {
				if (proper) {
					proper = false;
					words.push_back(word);
					word.clear();
				}
				prev_non_alnum = true;
			}

		}
	}

};