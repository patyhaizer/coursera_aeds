#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
using std::vector;
using std::cin;
using std::cout;
using std::max;

// This function calculates the maximun value in numbers by comparing then 2 by two
// like a tournament. For example: in the vector 4 5 8 9
// 4 is compared to 5 -> 5 wins and it is stored to be compared in the next round
// 4 is stored in the winnerComparison list for 5
// 8 is compared with 9 -> 9 wins and it is sotored to be compared in the next round
// 8 is stored in the winnerComparison list for 9
// 4  5 8  9
// \ /  \ /
//  5    9
//  \    /
//    9 
void
getMaximun(const vector<int>& numbers, std::vector<int>& winnerIndexes,
           std::map<int, std::vector<int>>& winnerComparisons) {
    while (winnerIndexes.size() > 1) {
        std::vector<int> tmpWinnerIndexes;
        for (int i = 0; i < winnerIndexes.size() - 1; i+=2) {
            int idx1 = winnerIndexes[i];
            int idx2 = winnerIndexes[i+1];
            if (numbers[idx1] > numbers[idx2]) {
                tmpWinnerIndexes.push_back(idx1);
                winnerComparisons[idx1].push_back(idx2);
            } else {
                tmpWinnerIndexes.push_back(idx2);
                winnerComparisons[idx2].push_back(idx1);
            }
        }
        if (winnerIndexes.size() % 2) {
            tmpWinnerIndexes.push_back(winnerIndexes.back());
        }
        winnerIndexes = tmpWinnerIndexes;
    }
}

int64_t MaxPairwiseProduct(const vector<int>& numbers) {
    std::vector<int> winnerIndexes;
    for (int i = 0; i < numbers.size(); ++i) {
        winnerIndexes.push_back(i);
    }
    std::map<int, std::vector<int>> winnerComparisons;
    getMaximun(numbers, winnerIndexes, winnerComparisons);
    // At the end we have the index of the maximun element store in the winnerIndexes vector
    // The numbers that need to be compared to know the second max is in the vector indexed by winnerIndex in
    // winnerComparisons
    assert(winnerIndexes.size() == 1);
    int maxNum = numbers[winnerIndexes.front()];
    winnerIndexes = winnerComparisons[winnerIndexes.front()];
    winnerComparisons.clear();
    getMaximun(numbers, winnerIndexes, winnerComparisons);
    assert(winnerIndexes.size() == 1);
    int secMaxNum = numbers[winnerIndexes.front()];

    return (int64_t) maxNum * secMaxNum;
}

int main() {
	int n;
   	cin >> n;
   	vector<int> numbers(n);
	for (int i = 0; i < n; ++i) {
   	    cin >> numbers[i];
	}
	int64_t product = MaxPairwiseProduct(numbers);
	cout << product << "\n";
	return 0;
}
