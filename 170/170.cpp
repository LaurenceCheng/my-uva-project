/* Volumn I, 170 - Clock Patience */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class CCard
{
public:
	CCard(string strInput);
	~CCard();
	string toString();
	void SetFaceUp(bool bFaceUp);
	bool IsFaceUp();
	int GetRank();

	static const int ACE_INT_VALUE = 1;
	static const int TEN_INT_VALUE = 10;
	static const int JACK_INT_VALUE = 11;
	static const int QUEEN_INT_VALUE = 12;
	static const int KING_INT_VALUE = 13;

	static const char ACE_STRING = 'A';
	static const char TEN_STRING = 'T';
	static const char JACK_STRING = 'J';
	static const char QUEEN_STRING = 'Q';
	static const char KING_STRING = 'K';
private:
	bool m_bFaceUp;
	string m_strSuit;
	int m_iRank;
};

CCard::CCard(string strInput):
m_bFaceUp(false),
m_strSuit(""),
m_iRank(0)
{
	switch (strInput[0])
	{
	case ACE_STRING:
		m_iRank = ACE_INT_VALUE;
		break;
	case TEN_STRING:
		m_iRank = TEN_INT_VALUE;
		break;
	case JACK_STRING:
		m_iRank = JACK_INT_VALUE;
		break;
	case QUEEN_STRING:
		m_iRank = QUEEN_INT_VALUE;
		break;
	case KING_STRING:
		m_iRank = KING_INT_VALUE;
		break;
	default:
		m_iRank = strInput[0] - 48;
		break;
	};
	m_strSuit = strInput[1];
}

CCard::~CCard()
{
}

string CCard::toString()
{
	string strRank;

	switch (m_iRank)
	{
	case ACE_INT_VALUE:
		strRank = ACE_STRING;
		break;
	case TEN_INT_VALUE:
		strRank = TEN_STRING;
		break;
	case JACK_INT_VALUE:
		strRank = JACK_STRING;
		break;
	case QUEEN_INT_VALUE:
		strRank = QUEEN_STRING;
		break;
	case KING_INT_VALUE:
		strRank = KING_STRING;
		break;
	default:
		ostringstream ssOut;
		ssOut << m_iRank;
		strRank = ssOut.str();
		break;
	};
	return strRank + m_strSuit;
}

void CCard::SetFaceUp(bool bFaceUp)
{
	m_bFaceUp = bFaceUp;
}

bool CCard::IsFaceUp()
{
	return m_bFaceUp;
}

int CCard::GetRank()
{
	return m_iRank;
}

// main functions of Clock Patience
class CGame
{
public:
	CGame();
	~CGame();
	void Deal(vector<CCard*> &vDeck);
	void Start();
private:
	static const int MAX_DECK_NUM_IN_GAME = 13;
	vector<CCard*> *avDecks[MAX_DECK_NUM_IN_GAME];
};

CGame::CGame()
{
	for (int i = 0; i < MAX_DECK_NUM_IN_GAME; i++)
	{
		avDecks[i] = new vector<CCard*>;
	}
}

CGame::~CGame()
{
	for (int i = 0; i < MAX_DECK_NUM_IN_GAME; i++)
	{
		delete avDecks[i];
	}
}

void CGame::Deal(vector<CCard*> &vDeck)
{
	int iPileIdx = 0;

	vector<CCard*>::iterator iter = vDeck.begin();
	while (iter != vDeck.end())
	{
		vector<CCard*> *pvDeck = avDecks[iPileIdx++];
		pvDeck->insert(pvDeck->begin(), *iter);
		if (iPileIdx >= MAX_DECK_NUM_IN_GAME)
		{
			iPileIdx = 0;
		}
		iter++;
	}
}

void CGame::Start()
{
	int iPileIdx = MAX_DECK_NUM_IN_GAME;
	int iExposedCards = 0;
	CCard* pCard = NULL;

	for (;;)
	{
		vector<CCard*> *pCurPile = avDecks[iPileIdx - 1], *pNextPile = NULL;
		
		pCard = pCurPile->front();
		pCard->SetFaceUp(true);
		iExposedCards++;
		
		pCurPile->erase(pCurPile->begin());
		
		int iNextPileIdx = pCard->GetRank();
		pNextPile = avDecks[iNextPileIdx - 1];
		if (pNextPile->front()->IsFaceUp())
		{
			break;
		}
		else
		{
			pNextPile->push_back(pCard);
			iPileIdx = iNextPileIdx;
		}
	}

	cout << setw(2) << setfill('0') << iExposedCards << "," << pCard->toString() << endl;
}

int main()
{
	string strCard;
	vector<CCard*> vDeck;
	const int MAX_DECK_SIZE = 52;

	while (cin >> strCard)
	{
		//cout << strCards << endl;
		if (strCard == "#") return 0;
		vDeck.insert(vDeck.begin(), new CCard(strCard));

		if (MAX_DECK_SIZE == vDeck.size())
		{
			//cout << "Game starting..." << endl;
			CGame obGame;
			obGame.Deal(vDeck);
			obGame.Start();

			vector<CCard*>::iterator iter = vDeck.begin();
			while (iter != vDeck.end())
			{
				delete (*iter);
				iter = vDeck.erase(iter);
			}
		}
		//cout << card.toString() << endl;
	}
	return 0;
}
