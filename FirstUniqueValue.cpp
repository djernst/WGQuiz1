//============================================================================
// Name        : FirstUniqueValue.cpp
// Author      : Dan Ernst
// Version     :
// Copyright   : Ernstco
// Description : Quiz 1
//============================================================================


#include <iostream>
#include <vector>

using namespace std;

// This implementation consists of effectively two loops of iteration of the n elements in the input list. There is the outer loop which is obvious,
// And the two inner loops for iterating over the blacklist and the potientialUVList.  However, the number of elements in the inner loops
// will sum to be always less than or equal to the n elements in the input list.
// BigO is thus O(n^2)
//
// If I would have taken advantage of knowing all the numbers are unsigned 8-bit integers, then I could use the number as an index into a
// simple array.  Then instead of iterating over a list, I could update a frequency counter variable directly to keep track of occurrences
// of each value.
// After that I could then iterate over the fixed length list (256 elements) to find all the unique values.  In order to determine the first
// value I would need to flag incoming order as well.
// The BigO operation would be O(1) since the length of the array is fixed to 256 elements.

void printFirstUniqueValue(vector<int>& list, bool verbose = false){
	std::vector<int>::iterator listIt, blIt, pUVIt;
	std::vector<int> potentialUVList;
	std::vector<int> blacklisted;
	bool blackListed = false;

	blacklisted.clear();
	potentialUVList.clear();

	// Iterate over every value in the list
	for (listIt = list.begin();listIt != list.end(); listIt++){
		// first check if value is already black listed.  If so move on to next item in list.
		blackListed = false;
		for (blIt = blacklisted.begin(); blIt != blacklisted.end(); blIt++){
			if ((*listIt) == (*blIt)){
				blackListed = true;
				if (verbose) cout << "value " << (*listIt) << " already on blackList...continue on"  << endl;
				break;
			}
		}
		if (blackListed) continue;

		// Now check if item is already in potential Unique Value list... if so add value to black list and remove
		// from potential Unique Value list and then move on to next item in list.
		for (pUVIt = potentialUVList.begin(); pUVIt != potentialUVList.end(); pUVIt++){
			if ((*listIt) == (*pUVIt)){
				if (verbose) cout << "value " << (*listIt) << " already on potential Unique Value List. moving to blackList...continue on" << endl;
				blacklisted.insert(blacklisted.end(), (*listIt));
				potentialUVList.erase(pUVIt);
				blackListed = true;
				break;
			}
		}
		if (blackListed) continue;

		// If we made it this far, the value is unique and we should add it to the potential Unique Value list...
		if (verbose) cout << "first encounter of value " << (*listIt) << ". adding to potential Unique Value List" << endl;
		potentialUVList.insert(potentialUVList.end(), (*listIt));
	}

	// Since we always added new potential Unique values to the end of the list, the first item in the list will be the First Unique Value
	if (!potentialUVList.empty()){
	cout << "First Unique Value is " << (*potentialUVList.begin()) << endl;
	} else {
		cout << "No Unique Values exist in list" << endl;
	}

}

int main() {
    srand(time(NULL));

	std::vector<int> example = {4, 71, 16, 38, 16, 12, 4, 71, 71, 4, 205, 12, 71};
	std::vector<int> nullList;
	std::vector<int> singleValue = {1};
	std::vector<int> vec = {2, 3, 5, 5,5, 7, 11, 13, 17, 17, 19,2};
	std::vector<int> negValues = {-1, -2, -1, -2, -4, 17, 19, 0};
	std::vector<int> noUV = {2, 3, 5, 7, 11, 13, 17, 19, 2, 3, 5, 7, 11, 13, 17, 19};
	std::vector<int> lastItemUnique = {4,1,6,19,19,6,1,4,5};


	printFirstUniqueValue(example);
	printFirstUniqueValue(nullList);
	printFirstUniqueValue(singleValue);
	printFirstUniqueValue(vec);
	printFirstUniqueValue(negValues);
	printFirstUniqueValue(noUV);
	printFirstUniqueValue(lastItemUnique);

	return 0;
}
