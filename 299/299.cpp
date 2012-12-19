/* Volumn II, 299 - Train Swapping */

#include <iostream>
#include <vector>
using namespace std;

int BubbleSort(vector<int> &vTrainCarriage)
{
	int iTrainLength = vTrainCarriage.size();

	if (0 == iTrainLength || 1 == iTrainLength)
	{
		return 0;
	}

	int iSwapCount = 0;
	for (int i = 0; i < iTrainLength; i++)
	{
		for (int j = iTrainLength - 1; j > i; j--)
		{
			if (vTrainCarriage[j] < vTrainCarriage[j-1])
			{
				int iTmp = vTrainCarriage[j];
				vTrainCarriage[j] = vTrainCarriage[j-1];
				vTrainCarriage[j-1] = iTmp;
				
				iSwapCount++;
			}
		}
	}
	
	return iSwapCount;
}

int main()
{
	int iTestCaseNum = 0;
	cin >> iTestCaseNum;

	vector<int> vTrainCarriage;
	for (int i = 0; i < iTestCaseNum; i++)
	{
		int iTrainLength = 0;
		cin >> iTrainLength;
		vTrainCarriage.clear();

		for (int j = 0; j < iTrainLength; j++)
		{
			int iCarriage = 0;
			cin >> iCarriage;
			vTrainCarriage.push_back(iCarriage);
		}

		cout << "Optimal train swapping takes " << BubbleSort(vTrainCarriage) << " swaps." << endl;
	}
	return 0;
}
