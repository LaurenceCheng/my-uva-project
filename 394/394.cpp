/* Volumn III, 394 - Mapmaker */

#include <cinttypes>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class Array
{
public:
	Array(string& strDefine)
	{
		stringstream oss(strDefine);
		string input;

		oss >> input;
		m_uiBaseAddr = stoi(input);

		oss >> input;
		m_uiElementSize = stoi(input);

		oss >> input;
		m_uiDimensions = stoi(input);

		for (uint8_t i = 0; i < m_uiDimensions; i++)
		{
			int32_t iLowBound = 0, iHighBound = 0;

			oss >> input;
			iLowBound = stoi(input);
			oss >> input;
			iHighBound = stoi(input);

			m_listBounds.push_back(pair<int32_t, int32_t>(iLowBound, iHighBound));
		}
	}
	virtual ~Array(void) = default;

	uint32_t getAddr(vector<int32_t>& indice)
	{
		uint32_t result = m_uiBaseAddr;
		auto sizeIndice = indice.size();

		if (sizeIndice != m_uiDimensions) return 0;

		uint32_t numElements = 0;
		uint32_t multiplier = 1;

		for (int32_t i = sizeIndice - 1; i >= 0; i--)
		{
			numElements += (indice[i] - m_listBounds[i].first) * multiplier;
			multiplier *= m_listBounds[i].second - m_listBounds[i].first + 1;
		}

		result += m_uiElementSize * numElements;

		return result;
	}
private:
	uint32_t m_uiBaseAddr;
	uint8_t m_uiDimensions;
	uint32_t m_uiElementSize;
	vector<pair<int32_t, int32_t>> m_listBounds;
};

int main(void)
{
	string input;

	cin >> input;
	uint32_t numDefines = stoi(input);
	
	cin >> input;
	uint32_t numRefers = stoi(input);

	getline(cin, input);

	map<string, Array> mapArrays;
	for (uint32_t i = 0; i < numDefines; i++)
	{
		string arrName;
		cin >> arrName;
		getline(cin, input);
		mapArrays.insert(pair<string, Array>(arrName, Array(input)));
	}

	for (uint32_t i = 0; i < numRefers; i++)
	{
		string arrName;
		cin >> arrName;
		
		auto targetPair = mapArrays.find(arrName);
		auto array = targetPair->second;
		
		getline(cin, input);
		stringstream oss(input);
		vector<int32_t> arrIndice;
		while (oss >> input)
		{
			arrIndice.push_back(stoi(input));
		}

		cout << arrName << "[";
		auto iter = arrIndice.begin();
		while (iter != arrIndice.end())
		{
			if (iter != arrIndice.begin()) cout << ", ";
			cout << *iter;
			iter++;
		}
		cout << "]" << " = " << array.getAddr(arrIndice) << endl;
	}

	return 0;
}
