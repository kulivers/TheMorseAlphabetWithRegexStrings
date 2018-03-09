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


map <string, char> reverseMorze(map <char, string> morze)
{
	map<string, char> m2;
	for (map<char, string>::iterator it = morze.begin(); it != morze.end(); ++it)
		m2[it->second] = it->first;

	return m2;
}

map <string, char> reversedMorze = reverseMorze(morze);


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



//если приходит '..' ты вызываешь мэп
//если там есть знак вопроса, ты вызываешь сам себя три раза
string NothingInsteadQuestionMark(string text)
{
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == '?')
		{
			text.erase(i, 1);
			return text;
		}
	}
}

string PointInsteadQuestionMark(string text)
{
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == '?')
		{
			text[i] = '.';
			return text;
		}
	}
}

string HyphenInsteadQuestionMark(string text)
{
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == '?')
		{
			text[i] = '-';
			return text;
		}
	}
}

bool textHaveAskSymbols(string text)
{
	for (int i = 0; i < text.size(); i++)
	{
		if (text[i] == '?')
			return true;
	}
	return false;
}

string decodeMorze(string text)
{
	string convertedToChars;

	if (textHaveAskSymbols(text))
	{
		for (int i = 0; i < text.size(); i++)
		{
			if (text[i] == '?')
				return (decodeMorze(HyphenInsteadQuestionMark(text)) + decodeMorze(PointInsteadQuestionMark(text)) + decodeMorze(NothingInsteadQuestionMark(text)));

		}
	}
	else
	{
		convertedToChars.push_back(reversedMorze[text]);
		return convertedToChars;
	}
}

string clearOfDublicates(string text)//DOOOOOPISAAA		"ogmkdnmntwrausiaiemntaiete"
{

	std::sort(text.begin(), text.end());
	std::string::iterator it;
	it = std::unique(text.begin(), text.end());   

	text.resize(std::distance(text.begin(), it));
	return text;
}
vector<char> decodeMorzeByChars(string cintext)
{
	cintext = decodeMorze(cintext);
	string oneCharofMorze;
	vector<char> preparedChars;
	map <string, char> reversedMorze = reverseMorze(morze);

	for (int i = 0; i < cintext.size(); i++)
	{
		if (cintext[i] != ' ')
			oneCharofMorze.push_back(cintext[i]);
		else
		{
			preparedChars.push_back(reversedMorze[oneCharofMorze]);
			oneCharofMorze.clear();
		}
	}
	return preparedChars;
}

int main()
{
	string text1;
	text1 = "???";

	/*string FixedText = decodeMorze(text1);
	cout << FixedText;*/

	string testV = decodeMorze(text1);

	testV = clearOfDublicates(testV);

	for (int i = 0; i < testV.size(); i++)
	{
		cout << testV[i] << " ";
	}
	return 0;
}
/*
SCENARIO("Text -.? and check the char")
{
	GIVEN("text1 = ? ? ? ?, must return all chars")
	{
		string text1;
		text1 = "????";

		vector<char> CorrectChars;
		CorrectChars = GetAnswer(text1);

		REQUIRE(CorrectChars.size() == 26);


	}
	GIVEN("text1 = ???????, must return all symbols")
	{
		string text1;
		text1 = "???????";

		vector<char> CorrectChars;
		CorrectChars = GetAnswer(text1);

		REQUIRE(CorrectChars.size() == 49);


	}

	GIVEN("text1 = ??. must return DEGINRS ")
	{
		string text1;
		text1 = "??.";

		vector<char> CorrectChars;
		vector<char> Answer = { 'd','e','g','i','n','r','s' };
		CorrectChars = GetAnswer(text1);

		REQUIRE(CorrectChars == Answer);


	}


}

*/