#include <iostream>
#include <vector>
#include <map>
#include <assert.h>
#include <stdlib.h>     /* srand, rand */
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
            // std::cout << "idx1 : " << idx1 << std::endl;
            int idx2 = winnerIndexes[i+1];
            // std::cout << "idx2 : " << idx2 << std::endl;
            // std::cout << "numbers[idx1] = " << numbers[idx1] << std::endl;
            // std::cout << "numbers[idx2] = " << numbers[idx2] << std::endl;
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

int MaxPairwiseProduct(const vector<int>& numbers) {
    //std::cout << "MaxPairwiseProd" << std::endl;
    std::vector<int> winnerIndexes;
    for (int i = 0; i < numbers.size(); ++i) {
        //std::cout << "i = " << i << std::endl;
        winnerIndexes.push_back(i);
    }
    std::map<int, std::vector<int>> winnerComparisons;
    //std::cout << "calling maximun" << std::endl;
    getMaximun(numbers, winnerIndexes, winnerComparisons);
    // At the end we have the index of the maximun element store in the winnerIndexes vector
    // The numbers that need to be compared to know the second max is in the vector indexed by winnerIndex in
    // winnerComparisons
    assert(winnerIndexes.size() == 1);
    int maxNum = numbers[winnerIndexes.front()];
    //std::cout << "Max: " << maxNum << std::endl;
    winnerIndexes = winnerComparisons[winnerIndexes.front()];
    //std::cout << "winnerIndexes.size() = " << winnerIndexes.size() << std::endl;
    //for (int i : winnerIndexes) {
    //    std::cout << "compared max with index: " << i << std::endl;
    //}
    winnerComparisons.clear();
    //std::cout << "calling maximun2" << std::endl;
    getMaximun(numbers, winnerIndexes, winnerComparisons);
    assert(winnerIndexes.size() == 1);
    int secMaxNum = numbers[winnerIndexes.front()];
    //std::cout << "secMax: " << secMaxNum << std::endl;

    return maxNum * secMaxNum;
}

int MaxPairwiseProductNaive(const vector<int>& numbers) {
	int product = 0;
  	int n = numbers.size();
  	for (int i = 0; i < n; ++i) {
   		for (int j = i + 1; j < n; ++j) {
			product = max(product, numbers[i] * numbers[j]);
   		}
	}
  	return product;
}

int main() {
    /* initialize random seed: */
    for (int exec = 0; exec < 100; ++exec) {
        std::cout << "exec: " << exec << std::endl;
        srand (exec);
        // 2 < n < 100
	    int n = (rand() % 98) + 2;
   	    //cin >> n;
   	    vector<int> numbers(n);
	    for (int i = 0; i < n; ++i) {
   	    //	cin >> numbers[i];
            numbers[i] = rand() % 100;
	    }
        for (int i : numbers) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
	    int product1 = MaxPairwiseProductNaive(numbers);
	    int product2 = MaxPairwiseProduct(numbers);
        std::cout << "Prod1 = " << product1 << " - Prod2 = " << product2 << std::endl;
        assert(product1 == product2);
	    cout << product2 << "\n";
    }
	return 0;
}
