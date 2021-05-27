#include <iostream>
#include <string>
#include <vector>
#define ll long long
#define RESET   "\033[0m"
#define BLACK   "\033[30m" // Black
#define BLUE    "\033[34m" // Blue
#define RED     "\033[31m" // Red
#define GREEN   "\033[32m" // Green
#define YELLOW  "\033[33m" // Yellow
#define BOLDWHITE   "\033[1m\033[37m" // Bold White

// Defining a struct for all the attributes of the longest common subsequence
struct longestCommonSubsequence {
	int n, m;
	ll int lcs_length;
	std::string lcs_string;

	longestCommonSubsequence(int n, int m)
	{
		n = n;
		m = m;
	}
};

// Adding a short-hand for longestCommmonSubsequence to just lcsStruct
typedef struct longestCommonSubsequence lcsStruct;

lcsStruct computeLCS(std::string text1, std::string text2) {
	int m = text1.length(); // columns
	int n = text2.length(); // rows

	lcsStruct lcs(n, m);
	std::vector<std::vector<int> > dp_matrix(n, std::vector<int> (m));
	
	for(int i = 0; i < lcs.n+1; i++)
	{
		for(int j = 0; j < lcs.m+1; j++)
		{
			if(i == 0 or j == 0)
			{
				dp_matrix[i][j] = 0;
				continue;
			}
			else if(text1[j-1] == text2[i-1])
			{
				// add 1 to diagonally top-left element
				dp_matrix[i][j] = dp_matrix[i-1][j-1] + 1;
			}
			else if(text1[j-1] != text2[i-1])
			{
				// take the maximum of left and above element
				dp_matrix[i][j] = std::max(dp_matrix[i][j-1], dp_matrix[i-1][j]);
			}
		}
	}

	// Length of LCS
	lcs.lcs_length = dp_matrix[lcs.n][lcs.m];

	// Building LCS
	int tracker[2] = {lcs.n, lcs.m};

	while(tracker[0] != 0 or tracker[1] != 0)
	{
		int x = tracker[0];
		int y = tracker[1];
		int current = dp_matrix[x][y];

		if(current == dp_matrix[x][y-1]) // equal to left element
		{
			tracker[1] -= 1;
		}
		else if(current == dp_matrix[x-1][y]) // equal to top element
		{
			tracker[0] -= 1;
		}
		else
		{
			lcs.lcs_string.insert(lcs.lcs_string.begin(), text1[y-1]);
			tracker[0] -= 1;
			tracker[1] -= 1;
		}
	}

	return lcs;
}

bool presentInLCS(std::string str, char character)
{
	// Perform search for the character in the LCS string
	int i = 0, n = str.length();

	while(i < n)
	{
		if(str[i] == character)
			return true;
		else
			i++;
	}

	return false;
}

void printDiff(std::string lcs, std::string oldFile, std::string newFile)
{
	// Deletions (items present in oldFile but not present in LCS)
	std::string deletions = "";

	int old_len = oldFile.length();
	for(int i = 0; i < old_len; i++)
	{
		if(!presentInLCS(lcs, oldFile[i]))
		{
			deletions.insert(deletions.end(), oldFile[i]);
		}
	}

	// Insertions (items present in newFile but not present in LCS)
	std::string insertions = "";
	int new_len = newFile.length();
	for(int i = 0; i < new_len; i++)
	{
		if(!presentInLCS(lcs, newFile[i]))
		{
			insertions.insert(insertions.end(), newFile[i]);
		}
	}

	std::cout << BLUE << "Deletions: " << RED;
	int del_len = deletions.length();
	for(int i = 0; i < del_len; i++)
	{
		std::cout << " -" << deletions[i];
	}

	std::cout << BLUE << std::endl << "Insertions: " << GREEN;
	int ins_len = insertions.length();
	for(int i = 0; i < ins_len; i++)
	{
		std::cout << " +" << insertions[i];
	}
	std::cout << RESET << std::endl;
}

void printLcsMatrix(std::vector<std::vector<int> > dp_matrix)
{
	std::cout << "DP Matrix: " << std::endl;
	for(int i = 0; i < dp_matrix.size()+1; i++)
	{
		for(int j = 0; j < dp_matrix[0].size()+1; j++)
		{
			std::cout << dp_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main()
{
	std::string text1, text2;
	std::cout << "Enter string 1: ";
	std::cin >> text1;

	std::cout << "Enter string 2: ";
	std::cin >> text2;

	lcsStruct lcs = computeLCS(text1, text2);
	std::cout << std::endl << BOLDWHITE << "Longest Common Subsequence is: " << YELLOW << lcs.lcs_string << RESET << std::endl;
	printDiff(lcs.lcs_string, text1, text2);
	return 0;
}