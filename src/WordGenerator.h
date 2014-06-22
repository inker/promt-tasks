#include "stdafx.h"
#include <string>
#include <set>
#include <fstream>
#include <iostream>
#include <ctime>

class WordGenerator {
	std::set<std::string> prefixes;
	std::set<std::string> suffixes;
	std::set<char> alphabet;
	static enum affix_type {
		PREFIX, SUFFIX
	};
public:
	WordGenerator(const std::string& prefixes_file, const std::string& suffixes_file, const std::string& alphabet_file);
	std::string generate_word() const;
	void generate_words(const std::string& output_file, size_t number_of_words) const;
private:
	template <typename T>
	void parse_file(const std::string& path, std::set<T>& container);
	std::string generate_root(size_t min_length, size_t max_length) const;
	std::string generate_affixes(affix_type, size_t min, size_t max) const;
};