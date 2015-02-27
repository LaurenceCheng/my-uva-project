/* Volumn III, 344 - Roman Digititis */

#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <string>
using namespace std;

const string ONE("i");
const string FIVE("v");
const string TEN("x");
const string FIFTY("l");
const string HUNDRED("c");

const string FOUR(ONE + FIVE);
const string NINE(ONE + TEN);
const string FOURTY(TEN + FIFTY);
const string NINETY(TEN + HUNDRED);

string ProcessRomanString(const int number, const string &one_series, const string& five_series, const string &four_series, const string &nine_series)
{
	string result;

	if (0 < number && number < 4)
	{
		result.resize(number);
		fill_n(result.begin(), number, one_series[0]);
	}
	else if (4 < number && number < 9)
	{
		result.append(five_series);
		result.resize(1 + number - 5);
		fill_n(result.begin() + 1, number - 5, one_series[0]);
	}
	else if (4 == number)
	{
		result.append(four_series);
	}
	else if (9 == number)
	{
		result.append(nine_series);
	}

	return result;
}

string Number2RomanString(const int number)
{
	string result;
	int first_digit = number % 10,
		second_digit = (number / 10) % 10,
		third_digit = ((number / 10) / 10) % 10;

	if (1 == third_digit) result.append(HUNDRED);

	result.append(ProcessRomanString(second_digit, TEN, FIFTY, FOURTY, NINETY));
	result.append(ProcessRomanString(first_digit, ONE, FIVE, FOUR, NINE));

	return result;
}

void OutputResult(const int pages, string &result)
{
	cout << pages << ": "
		<< count(result.begin(), result.end(), 'i') << " i, "
		<< count(result.begin(), result.end(), 'v') << " v, "
		<< count(result.begin(), result.end(), 'x') << " x, "
		<< count(result.begin(), result.end(), 'l') << " l, "
		<< count(result.begin(), result.end(), 'c') << " c" << endl;
}

int main()
{
	string input;
	

	while (cin >> input)
	{
		uint8_t pages = stoi(input);

		if (0 == pages) break;

		string result;
		for (auto i = 1; i <= pages; i++)
		{
			result.append(Number2RomanString(i));
		}

		OutputResult(pages, result);
	}

	return 0;
}
