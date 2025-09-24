#include <iostream>
#include <vector>
#include <string>


using namespace std;


void removeElement(vector<int>& nums, int val) 
{
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function removes all occurrences of a        |
	//   |   given value ('val') from an integer vector.       |
	//   | - It modifies the input vector 'nums'.              |
	//   |                                                     |
	//   | Return type: void                                   |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - Uses two pointers 'i' and 'j' for traversal.      |
	//   | - 'i' points to the last element that is not 'val'. |
	//   | - 'j' is used for iterating over the array.         |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+

    size_t i = 0;
    
    for (size_t j = 0; j < nums.size(); j++) 
    {
        if (nums[j] != val) 
        {
            // keep only desired values into vector
            nums[i] = nums[j];
            i++;
        }
    }

    // Resizing the vector to i ensures we remove all positions after that
    nums.resize(i);
}


vector<int> findMaxMin(vector<int>& myList) 
{
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function finds the maximum and minimum       |
	//   |   values in a given list of integers.               |
	//   | - It uses a single loop to go through the list.     |
	//   |                                                     |
	//   | Return type: vector<int>                            |
	//   | - Returns a vector containing maximum and minimum.  |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'maximum' and 'minimum' keep track of the         |
	//   |   highest and lowest values found.                  |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+

    vector<int> result = {__INT32_MAX__, __INT32_MAX__};
    
    if (myList.size() == 0) return result;
    
    int min = myList[0];
    int max = myList[0];
    
    
    for(auto num : myList)
    {
        if(num > max)
        {
            max = num;
        }
        else if(num < min)
        {
            min = num;
        }
    }
    
    result[0] = max;
    result[1] = min;
    
    
    
    return result;
}

string findLongestString(vector<string>& stringList) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function finds the longest string in         |
	//   |   a given list of strings.                          |
	//   | - It uses a single loop to check the length         |
	//   |   of each string.                                   |
	//   |                                                     |
	//   | Return type: string                                 |
	//   | - Returns the longest string found in the list.     |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'longestString' keeps track of the longest        |
	//   |   string found so far.                              |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
	
	if(stringList.size() == 0) return "";
	
	string max_len_str = stringList[0];
	
	for(auto str : stringList)
	{
	    if(str.length() > max_len_str.length())
	    {
	        max_len_str = str;
	    }
	}
	
	return max_len_str;
}

int removeDuplicates(vector<int>& nums) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function removes duplicate integers          |
	//   |   from a sorted array in-place.                     |
	//   | - It uses two pointers to achieve this.             |
	//   |                                                     |
	//   | Return type: int                                    |
	//   | - Returns the length of the new array.              |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'writePointer' is used for storing unique values. |
	//   | - 'readPointer' is used for reading array values.   |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
	
	if(nums.size() == 0) return 0;
	
	size_t write_pointer = 1;
	size_t read_pointer = 1;
	
	for(read_pointer = 1; read_pointer < nums.size() ; read_pointer++)
	{
	    if(nums[read_pointer] != nums[read_pointer-1])
	    {
	        nums[write_pointer] = nums[read_pointer];
	        write_pointer++;
	    }
	}
	
	return write_pointer;
}

int maxProfit(vector<int>& prices) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function calculates the maximum profit       |
	//   |   from buying and selling a stock.                  |
	//   | - It iterates through the 'prices' array once.      |
	//   |                                                     |
	//   | Return type: int                                    |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'minPrice' keeps track of the lowest price.       |
	//   | - 'maxProfit' stores the maximum profit found.      |
	//   | - Use 'min' and 'max' functions to update values.   |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
	
	if(prices.size() == 0)
	{
	    std::cout << "empty input argument " << "\n";
	    return 0;
	}
	size_t min = prices[0];
	vector<int> max_profits(prices.size());
	max_profits[0] = -1;
	for(size_t i = 1; i < prices.size() ; i++)
	{
	    max_profits[i] = prices[i] - min;
	    
	    if(prices[i] < min)
	    {
	        min = prices[i];
	    }
	}
	
	auto res = std::max_element(max_profits.begin(), max_profits.end());
	return (*res > 0) ? *res : 0;
}


#include "Rotate.h"


void rotate(vector<int>& nums, int k) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function rotates the array 'nums' to the     |
	//   |   right by 'k' steps.                               |
	//   | - The method used involves reversing parts of the   |
	//   |   array.                                            |
	//   |                                                     |
	//   | Return type: void                                   |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'k' is first made smaller by taking modulo size.  |
	//   | - Three reversals are done to achieve the rotation. |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
	
	    if (nums.empty()) return;
    
    k = k % nums.size();
 
    // Reverse the first part
    for (int start = 0, end = nums.size() - k - 1; start < end; start++, end--) {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
    }
 
    // Reverse the second part
    for (int start = nums.size() - k, end = nums.size() - 1; start < end; start++, end--) {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
    }
 
    // Reverse the whole array
    for (int start = 0, end = nums.size() - 1; start < end; start++, end--) {
        int temp = nums[start];
        nums[start] = nums[end];
        nums[end] = temp;
    }

}

#include "MaxSubarray.h"


int maxSubarray(vector<int>& nums) {
	//   +=====================================================+
	//   |                 WRITE YOUR CODE HERE                |
	//   | Description:                                        |
	//   | - This function finds the sum of the contiguous     |
	//   |   subarray with the largest sum from the given      |
	//   |   array 'nums'.                                     |
	//   | - It uses Kadane's algorithm for this task.         |
	//   |                                                     |
	//   | Return type: int                                    |
	//   |                                                     |
	//   | Tips:                                               |
	//   | - 'maxSum' stores the maximum subarray sum.         |
	//   | - 'currentSum' keeps track of the sum of the        |
	//   |   subarray ending at the current index.             |
	//   | - Use 'max' to update 'maxSum' and 'currentSum'.    |
	//   | - Check output from Test.cpp in "User logs".        |
	//   +=====================================================+
	
	if(nums.size() == 0) return 0;
	
	    int maxSum = nums[0];
        int currentSum = nums[0];
     
        for (int i = 1; i < nums.size(); i++) 
        {
            currentSum = max(nums[i], currentSum + nums[i]);
            maxSum = max(maxSum, currentSum);
        }
     
        return maxSum;

	
}

void vector_exercises_main()
{
    std::cout << "Vector Exercises \n\n";
    vector<int> num_list = {2,5,7,3,8,41,16,59};

    removeElement(num_list, 3);

    auto res = findMaxMin(num_list);

    auto res2 = removeDuplicates(num_list);
}