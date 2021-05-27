#define ll long long
#define RESET   "\033[0m"
#define BLACK   "\033[30m" // Black
#define BLUE    "\033[34m" // Blue
#define RED     "\033[31m" // Red
#define GREEN   "\033[32m" // Green
#define YELLOW  "\033[33m" // Yellow
#define BOLDWHITE   "\033[1m\033[37m" // Bold White
#include<string>

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

typedef struct longestCommonSubsequence lcsStruct;

lcsStruct computeLCS(std::string, std::string);
bool presentInLCS(std::string str, char character);
void printDiff(std::string lcs, std::string oldFile, std::string newFile);
void printLcsMatrix(std::vector<std::vector<int> > dp_matrix);
