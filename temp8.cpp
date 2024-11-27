#include <bits/stdc++.h>
using namespace std;

int calculateCompressedLength(const string &str, int start, int end)
{
    int compressedLength = 0;
    int i = start;
    while (i <= end)
    {
        int charCount = 1;
        while (i + 1 <= end && str[i] == str[i + 1])
        {
            ++i;
            ++charCount;
        }
        compressedLength += (charCount > 1) ? to_string(charCount).length() + 1 : 1;
        ++i;
    }
    return compressedLength;
}

int solution(string &inputString, int K)
{
    int totalLength = inputString.length();
    int minCompressedLength = INT_MAX;
    for (int startIndex = 0; startIndex <= totalLength - K; ++startIndex)
    {
        int endIndex = startIndex + K - 1;
        int prefixLength = (startIndex > 0) ? calculateCompressedLength(inputString, 0, startIndex - 1) : 0;
        int suffixLength = (endIndex < totalLength - 1) ? calculateCompressedLength(inputString, endIndex + 1, totalLength - 1) : 0;
        if (startIndex > 0 && endIndex < totalLength - 1 && inputString[startIndex - 1] == inputString[endIndex + 1])
        {
            int leftRun = 0, rightRun = 0;
            int i = startIndex - 1;
            while (i >= 0 && inputString[i] == inputString[startIndex - 1])
            {
                ++leftRun;
                --i;
            }
            int j = endIndex + 1;
            while (j < totalLength && inputString[j] == inputString[endIndex + 1])
            {
                ++rightRun;
                ++j;
            }
            int combinedRunLength = to_string(leftRun + rightRun).length() + 1;
            prefixLength -= (leftRun > 1) ? to_string(leftRun).length() + 1 : 1;
            suffixLength -= (rightRun > 1) ? to_string(rightRun).length() + 1 : 1;
            prefixLength += combinedRunLength;
        }
        int compressedTotal = prefixLength + suffixLength;
        minCompressedLength = min(minCompressedLength, compressedTotal);
    }

    return minCompressedLength;
}

int main()
{
    string example1 = "ABBBCCDDCCC";
    int K1 = 3;
    cout << "Minimum compressed length after removal: " << solution(example1, K1) << endl; // Expected: 5

    string example2 = "AAAAAAAAAABXXXAAAAAAAAAA";
    int K2 = 3;
    cout << "Minimum compressed length after removal: " << solution(example2, K2) << endl; // Expected: 3

    string example3 = "ABCDDDDEFG";
    int K3 = 2;
    cout << "Minimum compressed length after removal: " << solution(example3, K3) << endl; // Expected: 6

    return 0;
}
