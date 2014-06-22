// PromtTasks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WordGenerator.h"
#include "ArithmParser.h"
#include "ProperNounsExtractor.h"
#include <assert.h>

using namespace std;

void task1() {
	srand(time(0));
	WordGenerator wg = { "prefix.txt", "suffix.txt", "alphabet.txt" };
	int n = -1;
	cout << "Input the number of words to generate: ";
	for (;;) {
		cin >> n;
		if (n < 0) cout << "The number should be positive. Try again: ";
		else break;
	}
	wg.generate_words("result.txt", n);
}

void task2() {
	cout << endl;
	assert(ArithmExpr("(5") == 5);
	assert(ArithmExpr("(((-1") == -1);
	assert(ArithmExpr("0") == 0);
	assert(ArithmExpr("2+2") == 4);
	assert(ArithmExpr("3 + -2 * 4") == -5);
	assert(ArithmExpr("-23*45+(-55+36)-5*-8+18*0*(-5)") == -1014);
	assert(ArithmExpr("-(-35+(2*(-65)+22*(-6))*(65-70*(33-22))*(75-50)+3)") == -4617718);
	assert(ArithmExpr("-23*45+(-55+36)-5*-(-35+(2*(-65)+22*(-6))*(65-70*(33-22))*(75-50)+3)*-8+18*0*(-5)") == -184709774);
	assert(ArithmExpr("-23*45+(-55+36)-5*(56*(-4*1*(3*12)))-(-35+(2*(-65)+22*(-6))*(65-70*(33-22))*(75-50)+3)*-8+18*0*(-5)") == 36981010);
	cin.clear();
	cin.ignore(cin.rdbuf()->in_avail());
	for(;;) {
		cout << "Input the arithmetic expression to calculate or type \"exit\" to exit.:" << endl;
		string str;
		getline(cin, str);
		if (str == "exit") break;
		ArithmExpr ae = str;
		cout << " = " << ae << endl;
	}
}

void task3() {
	ProperNouns pn = "This is just a text container Some Proper Nouns. And this is Another one. And the Next One.";
}

int _tmain(int argc, _TCHAR* argv[]) {
	task1();
	task2();

	return 0;
}

