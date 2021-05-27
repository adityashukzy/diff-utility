#include <iostream>
#include <string>
using namespace std;

string longestCommonSubsequence(string text1, string text2) {
	int m = text1.length(); // columns
	int n = text2.length(); // rows
	int dp[n+1][m+1];
	
	for(int i = 0; i < n+1; i++)
	{
		for(int j = 0; j < m+1; j++)
		{
			if(i == 0 or j == 0)
			{
				dp[i][j] = 0;
				continue;
			}
			else if(text1[j-1] == text2[i-1])
			{
				// add 1 to diagonally top-left element
				dp[i][j] = dp[i-1][j-1] + 1;
			}
			else if(text1[j-1] != text2[i-1])
			{
				// take the maximum of left and above element
				dp[i][j] = std::max(dp[i][j-1], dp[i-1][j]);
			}
		}
	}
	
	// cout << "DP Matrix: " << endl;
	// for(int i = 0; i < n+1; i++)
	// {
	// 	for(int j = 0; j <= m; j++)
	// 	{
	// 		cout << dp[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	// Length of LCS
	// cout << "Length of LCS: " << dp[n][m] << endl;

	// Building LCS
	int tracker[2] = {n, m};
	string lcs = "";

	while(tracker[0] != 0 or tracker[1] != 0)
	{
		int x = tracker[0];
		int y = tracker[1];
		int current = dp[x][y];

		if(current == dp[x][y-1]) // equal to left element
		{
			tracker[1] -= 1;
		}
		else if(current == dp[x-1][y]) // equal to top element
		{
			tracker[0] -= 1;
		}
		else
		{
			lcs.insert(lcs.begin(), text1[y-1]);
			tracker[0] -= 1;
			tracker[1] -= 1;
		}
	}

	return lcs;
}

bool presentInLCS(string str, char character)
{
	// Perform search for the character in the LCS string
	int i = 0;
	while(i < str.length())
	{
		if(str[i] == character)
			return true;
		else
			i++;
	}

	return false;
}

void printDiff(string lcs, string oldFile, string newFile)
{
	// Deletions (items present in oldFile but not present in LCS)
	string deletions = "";

	for(int i = 0; i < oldFile.length(); i++)
	{
		if(!presentInLCS(lcs, oldFile[i]))
		{
			deletions.insert(deletions.end(), oldFile[i]);
		}
	}

	// Insertions (items present in newFile but not present in LCS)
	string insertions = "";

	for(int i = 0; i < newFile.length(); i++)
	{
		if(!presentInLCS(lcs, newFile[i]))
		{
			insertions.insert(insertions.end(), newFile[i]);
		}
	}

	cout << "Deletions: ";
	for(int i = 0; i < deletions.length(); i++)
	{
		cout << " -" << deletions[i];
	}

	cout << endl << "Insertions: ";
	for(int i = 0; i < insertions.length(); i++)
	{
		cout << " +" << insertions[i];
	}
	cout << endl;
}

int main()
{
	string text1, text2;
	cout << "Enter string 1: ";
	cin >> text1;

	cout << "Enter string 2: ";
	cin >> text2;

	string lcs = longestCommonSubsequence(text1, text2);
	cout << endl << "Longest Common Subsequence is: " << lcs << endl;
	printDiff(lcs, text1, text2);
	return 0;
}