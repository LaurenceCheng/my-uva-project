/* Volumn I, 146 - ID Codes */

#include <iostream>
#include <string>
#include <map>
using namespace std;

class IDGenerator
{
public:
	IDGenerator(string strID);
	~IDGenerator();
	string GetSuccessor();
private:
	void Sort(int iStartIndex);
	string m_strCurrentID;
};

IDGenerator::IDGenerator(string strID)
{
	m_strCurrentID = strID;
}

IDGenerator::~IDGenerator()
{
}

void IDGenerator::Sort(int iStartIndex)
{
	int iLength = m_strCurrentID.length();

	for (int i = iStartIndex; i < iLength; i++)
	{
		for (int j = iLength - 1; j > i; j--)
		{
			if (m_strCurrentID[j] < m_strCurrentID[j - 1])
			{
				char tmp = m_strCurrentID[j];
				m_strCurrentID[j] = m_strCurrentID[j - 1];
				m_strCurrentID[j - 1] = tmp;
			}
		}
	}
}

string IDGenerator::GetSuccessor()
{
	int iLenth = m_strCurrentID.length();
	int iRepositionIndex = -1;

	for (int i = iLenth - 1; i > 0; i--)
	{
		if (m_strCurrentID[i - 1] < m_strCurrentID[i])
		{
			iRepositionIndex = i - 1;
			break;
		}
	}

	if (-1 == iRepositionIndex)
	{
		return string("No Successor");
	}
	else
	{
		int iCloestIndex = iRepositionIndex + 1;
		for (int i = iRepositionIndex + 1; i < iLenth; i++)
		{
			if (m_strCurrentID[i] > m_strCurrentID[iRepositionIndex])
			{
				if (m_strCurrentID[i] < m_strCurrentID[iCloestIndex])
				{
					iCloestIndex = i;
				}
			}
		}

		char tmp = m_strCurrentID[iCloestIndex];
		m_strCurrentID[iCloestIndex] = m_strCurrentID[iRepositionIndex];
		m_strCurrentID[iRepositionIndex] = tmp;

		Sort(iRepositionIndex + 1);

		return m_strCurrentID;
	}
}

int main()
{
	std::string strID;

	while (cin >> strID)
	{
		if ("#" == strID)
		{
			break;
		}
		else
		{
			IDGenerator id(strID);
			cout << id.GetSuccessor() << endl;
		}
	}
	return 0;
}
