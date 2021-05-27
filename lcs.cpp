#include <iostream>
#include <string>
using namespace std;

int[] lcs_tabulation(string text1, string text2) {
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

