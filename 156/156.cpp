/* Volumn I, 156 - Ananagrams */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool IsAnagram(string strWord1, string strWord2)
{
	int word1Length = strWord1.length();
	int word2Length = strWord2.length();

	if (word1Length != word2Length)
	{
		return false;
	}

	for (int i = 0; i < word1Length; i++)
	{
		for (int j = 0; j < word2Length; j++)
		{
			if (toupper(strWord1[i]) == toupper(strWord2[j]))
			{
				strWord2.erase(j, 1);
				word2Length--;
				break;
			}
			else if (j == word2Length - 1)
			{
				return false;
			}
		}
		if (word2Length == 0)
		{
			if (i == word1Length - 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

bool IsAnanagram(string strWord, vector<string> &vDictionary)
{
	int length = vDictionary.size();

	for (int i = 0; i < length; i++)
	{
		if (strWord == vDictionary[i])
		{
			continue;
		}
		if (IsAnagram(strWord, vDictionary[i]))
		{
			return false;
		}
	}
	return true;
}

void FindAnanagrams(vector<string> &vDictionary)
{
	int length = vDictionary.size();

	for (int i = 0; i < length; i++)
	{
		if (IsAnanagram(vDictionary[i], vDictionary))
		{
			cout << vDictionary[i] << endl;
		}
	}
}

int main()
{
	string strInput;
	vector<string> vDomain;

	while (cin >> strInput)
	{
		if ("#" == strInput)
		{
			break;
		}
		vDomain.push_back(strInput);
	}

	sort(vDomain.begin(), vDomain.end());
	
	FindAnanagrams(vDomain);
	return 0;
}
