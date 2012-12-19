/* Volumn II, 256 - Quirksome Squares */

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

void PrintQuirksome(int iNumber, int iDigitNum)
{
	cout << setw(iDigitNum) << setfill('0') << iNumber << endl;
}

bool IsQuirksome(int iNumber, int iDivisor)
{
	int iHighPart = iNumber / iDivisor;
	int iLowPart = iNumber % iDivisor;

	int iSquare = (iHighPart + iLowPart) * (iHighPart + iLowPart);

	return (iNumber == iSquare);
}

void FindQuirksome(int iDigitNum)
{
	int iMaxRange = (int) pow((float) 10, (float) iDigitNum);
	int iDivisor = (int) pow((float) 10, (float) iDigitNum / 2);

	for (int i = 0; i < iMaxRange; i++)
	{
		if (IsQuirksome(i, iDivisor))
		{
			PrintQuirksome(i, iDigitNum);
		}
	}
}

int main()
{
	int iDigitNum = 0;
	
	while (cin >> iDigitNum)
	{
		if (iDigitNum % 2 == 0)
		{
			FindQuirksome(iDigitNum);
		}
	}
	return 0;
}
