/* Volumn II, 278 - Chess */

#include <iostream>
#include <string>
#include <vector>
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

class CBoardPosition
{
public:
	CBoardPosition(int iRow, int iCol);
	CBoardPosition(CBoardPosition &position);
	~CBoardPosition();

	int GetRow() const;
	int GetCol() const;
	void SetPosition(CBoardPosition &position);
	bool operator ==(CBoardPosition &position) const;
private:
	int m_iRow, m_iCol;
};

CBoardPosition::CBoardPosition(int iRow, int iCol)
: m_iRow(iRow), m_iCol(iCol)
{
}

CBoardPosition::CBoardPosition(CBoardPosition &position)
: m_iRow(position.GetRow()), m_iCol(position.GetCol())
{
}

CBoardPosition::~CBoardPosition()
{
}

int CBoardPosition::GetRow() const
{
	return m_iRow;
}

int CBoardPosition::GetCol() const
{
	return m_iCol;
}

void CBoardPosition::SetPosition(CBoardPosition &position)
{
	m_iRow = position.GetRow();
	m_iCol = position.GetCol();
}

bool CBoardPosition::operator ==(CBoardPosition &position) const
{
	return (position.GetRow() == m_iRow) && (position.GetCol() == m_iCol);
}


class CPiece
{
public:
	static const int KING = 1;
	static const int QUEEN = 2;
	static const int ROOK = 3;
	static const int KNIGHT = 4;

	static const string KING_STR;
	static const string QUEEN_STR;
	static const string ROOK_STR;
	static const string KNIGHT_STR;

	CPiece(CBoardPosition &position);
	CPiece(CBoardPosition &position, int iRank);
	CPiece(int iRow, int iCol);
	CPiece(int iRow, int iCol, int iRank);
	~CPiece();

	void SetPosition(CBoardPosition &position);
	CBoardPosition& GetPosition();
	virtual bool Capture(CBoardPosition &position);

	virtual bool Move(CBoardPosition &position) = 0;
	virtual CPiece* Clone() = 0;
protected:
	CBoardPosition m_Pos;
	int m_iRank;
};

const string CPiece::KING_STR = string("K");
const string CPiece::QUEEN_STR = string("Q");
const string CPiece::ROOK_STR = string("r");
const string CPiece::KNIGHT_STR = string("k");

CPiece::CPiece(CBoardPosition &position)
: m_Pos(position), m_iRank(KING)
{
}

CPiece::CPiece(CBoardPosition &position, int iRank)
: m_Pos(position), m_iRank(iRank)
{
}

CPiece::CPiece(int iRow, int iCol)
: m_Pos(iRow, iCol), m_iRank(KING)
{
}

CPiece::CPiece(int iRow, int iCol, int iRank)
: m_Pos(iRow, iCol), m_iRank(iRank)
{
}

CPiece::~CPiece()
{
}

void CPiece::SetPosition(CBoardPosition &position)
{
	m_Pos.SetPosition(position);
}

CBoardPosition& CPiece::GetPosition()
{
	return m_Pos;
}

bool CPiece::Capture(CBoardPosition &position)
{
	return Move(position);
}

class CKing: public CPiece
{
public:
	CKing(CBoardPosition &position);
	~CKing();

	virtual bool Move(CBoardPosition &position);
	CPiece* Clone();
private:
};

CKing::CKing(CBoardPosition &position)
: CPiece(position, CPiece::KING)
{
}

CKing::~CKing()
{
}

bool CKing::Move(CBoardPosition &position)
{
	if (1 == abs(position.GetRow() - m_Pos.GetRow()) ||
		1 == abs(position.GetCol() - m_Pos.GetCol()))
	{
		return true;
	}

	return false;
}

CPiece* CKing::Clone()
{
	return new CKing(*this);
}

class CKnight: public CPiece
{
public:
	CKnight(CBoardPosition &position);
	~CKnight();

	virtual bool Move(CBoardPosition &position);
	CPiece* Clone();
private:
};

CKnight::CKnight(CBoardPosition &position)
: CPiece(position, CPiece::KNIGHT)
{
}

CKnight::~CKnight()
{
}

bool CKnight::Move(CBoardPosition &position)
{
	return false;
}

CPiece* CKnight::Clone()
{
	return new CKnight(*this);
}

class CQueen: public CPiece
{
public:
	CQueen(CBoardPosition &position);
	~CQueen();

	virtual bool Move(CBoardPosition &position);
	CPiece* Clone();
private:
};

CQueen::CQueen(CBoardPosition &position)
: CPiece(position, CPiece::QUEEN)
{
}

CQueen::~CQueen()
{
}

bool CQueen::Move(CBoardPosition &position)
{
	if (position.GetRow() == m_Pos.GetRow() ||
		position.GetCol() == m_Pos.GetCol())
	{
		return true;
	}

	int i_dx = position.GetRow() - m_Pos.GetRow(),
		i_dy = position.GetCol() - m_Pos.GetCol();

	double dSlope = (double)i_dy / i_dx;

	if (1.0f == dSlope || -1.0f == dSlope)
	{
		return true;
	}

	return false;
}

CPiece* CQueen::Clone()
{
	return new CQueen(*this);
}

class CRook: public CPiece
{
public:
	CRook(CBoardPosition &position);
	~CRook();

	virtual bool Move(CBoardPosition &position);
	CPiece* Clone();
private:
};

CRook::CRook(CBoardPosition &position)
: CPiece(position, CPiece::ROOK)
{
}

CRook::~CRook()
{
}

bool CRook::Move(CBoardPosition &position)
{
	if (position.GetRow() == m_Pos.GetRow() ||
		position.GetCol() == m_Pos.GetCol())
	{
		return true;
	}
	return false;
}

CPiece* CRook::Clone()
{
	return new CRook(*this);
}

class CChessBoard
{
public:
	CChessBoard(int iRows, int iCols);
	~CChessBoard();

	int GetMaxPeacePieceCount(CPiece *pPiece);
	bool IsAbleToPutPieces(int iPiecesCount, CPiece *pPiece, CBoardPosition &positionStart);
	bool PutPiece(CPiece *pPiece);
	void RemovePiece(CBoardPosition &position);
private:
	int m_iRows;
	int m_iCols;
	vector<CPiece*> vPieces;
};

CChessBoard::CChessBoard(int iRows, int iCols)
: m_iRows(iRows), m_iCols(iCols)
{
}

CChessBoard::~CChessBoard()
{
	vector<CPiece*>::iterator iter = vPieces.begin();
	while (iter != vPieces.end())
	{
		delete (*iter);
		iter = vPieces.erase(iter);
	}
}

int CChessBoard::GetMaxPeacePieceCount(CPiece *pPiece)
{
	int iPieceCount = 0;
	CBoardPosition position(0, 0);
	
	while (IsAbleToPutPieces(iPieceCount + 1, pPiece, position))
	{
		iPieceCount++;
	}

	return iPieceCount;
}

bool CChessBoard::IsAbleToPutPieces(int iPiecesCount, CPiece *pPiece, CBoardPosition &positionStart)
{
	if (0 == iPiecesCount) return true;
	if (m_iRows * m_iCols < iPiecesCount) return false;

	int iRow = positionStart.GetRow(),
		iCol = positionStart.GetCol();

	for (; iRow < m_iRows; iRow++)
	{
		for (iCol = 0; iCol < m_iCols; iCol++)
		{
			bool bRet = false;

			CPiece *pNewPiece = pPiece->Clone();
			pNewPiece->SetPosition(CBoardPosition(iRow, iCol));

			if (PutPiece(pNewPiece))
			{
				bRet = IsAbleToPutPieces(iPiecesCount - 1, pPiece, CBoardPosition(iRow, iCol + 1));
				RemovePiece(pNewPiece->GetPosition());
			}
			else
			{
				delete pNewPiece;
			}

			if (bRet)
			{
				return true;
			}
		}
	}
	return false;
}

bool CChessBoard::PutPiece(CPiece *pNewPiece)
{
	if (0 == vPieces.size())
	{
		vPieces.push_back(pNewPiece);
		return true;
	}

	int iSize = vPieces.size();

	for (int i = 0; i < iSize; i++)
	{
		CPiece *pPiece = vPieces[i];

		if (pPiece->GetPosition() == pNewPiece->GetPosition() || 
			pPiece->Capture(pNewPiece->GetPosition()))
		{
			return false;
		}
	}

	vPieces.push_back(pNewPiece);
	return true;
}

void CChessBoard::RemovePiece(CBoardPosition &position)
{
	vector<CPiece*>::iterator iter = vPieces.begin();

	while (iter != vPieces.end())
	{
		if ((*iter)->GetPosition() == position)
		{
			delete (*iter);
			vPieces.erase(iter);
			break;
		}
		iter++;
	}
}

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

		cout << strPiece << ":" << iRows << "," << iCols << endl;

		CChessBoard obBoard(iRows, iCols);
		CPiece *pPiece = NULL;

		if (strPiece == CPiece::KING_STR)
		{
			pPiece = new CKing(CBoardPosition(0, 0));
		}
		else if (strPiece == CPiece::QUEEN_STR)
		{
			pPiece = new CQueen(CBoardPosition(0, 0));
		}
		else if (strPiece == CPiece::ROOK_STR)
		{
			pPiece = new CRook(CBoardPosition(0, 0));
		}
		else if (strPiece == CPiece::KNIGHT_STR)
		{
			pPiece = new CKnight(CBoardPosition(0, 0));
		}

		int iCount = obBoard.GetMaxPeacePieceCount(pPiece);

		cout << iCount << endl;
		
		delete pPiece;
	}

	_CrtDumpMemoryLeaks();
	return 0;
}
