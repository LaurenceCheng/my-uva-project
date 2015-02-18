/* Volumn II, 278 - Chess */

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

// debug memory allocation enhancement
#ifdef _DEBUG
    #include <crtdbg.h>
    #define DEBUG_NEW    new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
    #define DEBUG_NEW    new
#endif

// enable this to detect memory leak
#ifdef _DEBUG
    #define new    DEBUG_NEW
#endif

const string KING_STR = string("K");
const string QUEEN_STR = string("Q");
const string ROOK_STR = string("r");
const string KNIGHT_STR = string("k");

int main()
{
	int iProblemNum = 0;

	cin >> iProblemNum;

	for (int i = 0; i < iProblemNum; i++)
	{
		std::string strPiece;
		int iRows = 0, iCols = 0;

		cin >> strPiece;
		cin >> iRows >> iCols;

		// cout << strPiece << ":" << iRows << "," << iCols << endl;

		int iCount = 0;
		if (strPiece == KING_STR)
		{
			iCount = ((iRows + 1) / 2)  * ((iCols + 1) / 2);
		}
		else if (strPiece == QUEEN_STR)
		{
			iCount = min(iRows, iCols);
		}
		else if (strPiece == ROOK_STR)
		{
			iCount = min(iRows, iCols);
		}
		else if (strPiece == KNIGHT_STR)
		{
			iCount = (iRows * iCols + 1) / 2;
		}

		cout << iCount << endl;
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
