#include "stdafx.h"
#include "WordGenerator.h"

using namespace std;

WordGenerator::WordGenerator(const string& prefixes_file, const string& suffixes_file, const string& alphabet_file) {
	parse_file(prefixes_file, prefixes);
	parse_file(suffixes_file, suffixes);
	parse_file(alphabet_file, alphabet);
}

string WordGenerator::generate_word() const {
	return generate_affixes(PREFIX, 0, 3) + generate_root(1, 5) + generate_affixes(SUFFIX, 0, 2);
}

void WordGenerator::generate_words(const string& output_file, size_t number_of_words) const {
	ofstream ofs(output_file);
	if (ofs.is_open()) {
		while (number_of_words-- > 0) {
			ofs << generate_word() << endl;
		}
		ofs.close();
	}
}

template <typename T>
void WordGenerator::parse_file(const string& path, set<T>& container) {
	T s;
	ifstream ifs(path);
	if (ifs.is_open()) {
		while (ifs >> s) {
			container.insert(s);
		}
		ifs.close();
	}
}

string WordGenerator::generate_root(size_t min_length, size_t max_length) const {
	if (max_length < min_length) swap(min_length, max_length);
	int length = min_length + (rand() % (max_length - min_length + 1));
	string root;
	root.resize(length);
	for (auto& c : root) {
		c = *next(alphabet.begin(), rand() % alphabet.size());
	}
	return root;
}

string WordGenerator::generate_affixes(affix_type type, size_t min, size_t max) const {
	auto& affix_set = (type == PREFIX ? prefixes : suffixes);
	if (max < min) swap(min, max);
	int length = min + (rand() % (max - min + 1));;
	string affixes;
	for (int i = 0; i < length; ++i) {
		affixes += *next(affix_set.begin(), rand() % affix_set.size());
	}
	return affixes;
}
