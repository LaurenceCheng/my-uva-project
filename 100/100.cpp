/* Volumn I, 100 - The 3n + 1 problem */

#include <iostream>
using namespace std;

int ThreeNPlusOne(int iNumber)
{
	//cout << iNumber << " ";
	int iCycleLength = 1;

	int n = iNumber;

	while (n != 1)
	{
		if (1 == n % 2)
		{
			n = 3 * n + 1;
		}
		else
		{
			n = n / 2;
		}
		//cout << n << " ";
		iCycleLength++;
	}

	//cout << endl;
	return iCycleLength;
}

int main()
{
	int iFirstNum = 0, iSecondNum = 0;

	while (cin >> iFirstNum >> iSecondNum)
	{
		int iMaxCycleLength = 0;

		cout << iFirstNum << " " << iSecondNum << " ";

		if (iFirstNum > iSecondNum)
		{
			int iTmp = iFirstNum;
			iFirstNum = iSecondNum;
			iSecondNum = iTmp;
		}

		for (int i = iFirstNum; i <= iSecondNum; i++)
		{
			int iCycleLength = ThreeNPlusOne(i);

			iMaxCycleLength = (iMaxCycleLength < iCycleLength) ? iCycleLength : iMaxCycleLength;
		}
		cout << iMaxCycleLength << endl;
	}
	return 0;
}