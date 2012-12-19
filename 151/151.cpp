/* Volumn I, 151 - Power Crisis */

#include <iostream>
#include <vector>
using namespace std;

int GetLastOff(vector<int> vRegions, int m)
{
	int iSize = (int) vRegions.size();
	int iOffIndex = 0;
	int iOffDiff = m - 1;
	
	//cout << "m:" << m << " ";

	while (1 < iSize)
	{
		//cout << *(vRegions.begin() + iOffIndex) << " ";
		vRegions.erase(vRegions.begin() + iOffIndex);

		iOffIndex += iOffDiff;
		iSize--;
		while (iOffIndex >= iSize)
		{
			iOffIndex -= iSize;
		}
	}
	//cout << endl;
	return vRegions[0];
}

int PowerCrisis(int iRegions)
{
	vector<int> vRegions;
	for (int i = 1; i <= iRegions; i++)
	{
		vRegions.push_back(i);
	}

	for (int m = 1; ; m++)
	{
		if (12 == m) continue;
		if (13 == GetLastOff(vRegions, m))
		{
			return m;
		}
	}
}

int main()
{
	int iRegions = 0;
	while (cin >> iRegions)
	{
		if (0 == iRegions)
		{
			break;
		}
		else
		{
			cout << PowerCrisis(iRegions) << endl;
			//cout << "PowerCrisis:" << PowerCrisis(iRegions) << endl;
		}
	}
	return 0;
}
