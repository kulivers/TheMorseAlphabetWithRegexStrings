// TheMorseAlphabetWithRegexStrings.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include <cctype>
#include <vector>
#include <regex>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
using namespace std;
#pragma comment(lib, "msvcrtd.lib")

map <char, string> morze = {
	{ 'a', ".-" },
	{ 'b', "-..." },
	{ 'w', ".--" },
	{ 'g', "--." },
	{ 'd', "-.." },
	{ 'e', "." },
	{ 'v', "...-" },
	{ 'z', "--.." },
	{ 'i', ".." },
	{ 'j', ".---" },
	{ 'k', "-.-" },
	{ 'l', ".-.." },
	{ 'm', "--" },
	{ 'n', "-." },
	{ 'o', "---" },
	{ 'p', ".--." },
	{ 'r', ".-." },
	{ 's', "..." },
	{ 't', "-" },
	{ 'u', "..-" },
	{ 'f', "..-." },
	{ 'h', "...." },
	{ 'c', "-.-." },
	{ 'q', "--.-" },
	{ 'y', "-.--" },
	{ 'x', "-..-" },
	{ '1', ".----" },
	{ '2', "..---" },
	{ '3', "...--" },
	{ '4', "....-" },
	{ '5', "....." },
	{ '6', "-...." },
	{ '7', "--..." },
	{ '8', "---.." },
	{ '9', "----." },
	{ '0', "-----" },
	{ '.', "......" },
	{ ',', ".-.-.-" },
	{ ':', "---..." },
	{ ';', "-.-.-." },
	{ '(', "-.--.-" },
	{ ')', "-.--.-" },
	{ '"', ".-..-." },
	{ '-', "-....-" },
	{ '/', "-..-." },
	{ '?', "..--.." },
	{ '!', "--..--" },
	{ ' ', "-...-" },
	{ '@', ".--.-." },
};

bool TextContainsJustSymbols(string tx)
{
	for (int i = 0; i < tx.size(); i++)
	{
		if (tx[i] == '?' || tx[i] == '-' || tx[i] == '.')
		{
		}
		else
		{
			return false;
		}
	}
}


string CinText()
{
	string text;
	cout << "Introduce 3 symbols '?' or '.' or '-': " << endl;

	while (text.size() == 0 || text.size() > 3 || !TextContainsJustSymbols(text))
	{
		cout << "Text size must be 3! and have correct symbols! " << endl;
		getline(cin, text);

	}
	return text;
}
/*
regex_match не ищет совпадение в обычном смысле. Она возвращает true только в случае, когда строка совпадает регулярным выражением. Функция regex_search больше похожа на работу оператора поиска совпадений, такого как m// в Perl.
На примере следующего кода, можно увидеть, как работают функции regex_search и regex_match.
std::string str = "Hello world";
std::tr1::regex rx("ello");
regex_match(str.begin(), str.end(), rx)
regex_search(str.begin(), str.end(), rx)

Функция regex_match вернет false, так как строка str отличается от регулярного выражения rx. 
А функция regex_search вернут true, так как регулярное выражение содержится в строке.
*/
vector<char> GetAnswer(string text)
{
	vector<char> CorrectChars;
	string EditedText;
	for (int i = 0; i < text.size(); i++)
	{
		//EditedText.push_back('"');

		if (text[i] == '-')
		{
			//EditedText.push_back('(');
			EditedText.push_back('\\');
			EditedText.push_back('-');
			//EditedText.push_back(')');
		}
		if (text[i] == '.')
		{
			//	EditedText.push_back('(');
			EditedText.push_back('\\');
			EditedText.push_back('.');
			//	EditedText.push_back(')');
		}
		if (text[i] == '?')
		{
			//EditedText.push_back('(');
			EditedText.push_back('[');
			EditedText.push_back('.');
			EditedText.push_back('-');
			EditedText.push_back(']');
			EditedText.push_back('?');
			//	EditedText.push_back(')');
		}
		//EditedText.push_back('"');
	}
	cout << EditedText << endl << endl;


	regex regular(EditedText);

	for (map<char, string>::iterator it = morze.begin(); it != morze.end(); ++it)	// добавление в CharsOfCorrectKeys по размеру
	{
		if (regex_match((*it).second, regular))
			CorrectChars.push_back((*it).first);
	}
	cout << endl;
	for (int i = 0; i < CorrectChars.size(); i++)
	{
		cout << CorrectChars[i];
	}
	return CorrectChars;
}



	//int main()
	//{
	//	return 0;
	//}
	SCENARIO("Text -.? and check the char")
	{
			GIVEN("text1 = ? ? ? ? ")
			{
				string text1;
				text1 = "????";

				vector<char> CorrectChars;
				CorrectChars = GetAnswer(text1);

				REQUIRE(CorrectChars == GetAnswer(text1));

				WHEN("we add . to the end")
				{
					text1.push_back('.');

					THEN("will be a few chars")
					{
						REQUIRE(CorrectChars == GetAnswer(text1));
					}
				}
			}
	}


