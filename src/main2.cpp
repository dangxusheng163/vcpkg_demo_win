// This is the second file in the project.

// 查找最大子序列和问题

#include <iostream>
#include <vector>

using namespace std;


/*写一个冒泡排序*/
/**
 * Sorts a vector of integers using the bubble sort algorithm.
 * 
 * @param nums The vector of integers to be sorted.
 */
void bubbleSort(vector<int> &nums) {
    int len = nums.size();
    for (int i = 0; i < len; i++) {
        for (int j = 1; j < len - i; j++) {
            if (nums[j - 1] > nums[j]) {
                swap(nums[j - 1], nums[j]);
            }
        }
    }
}

/*
 * 主函数
    */
int main() {
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    for(int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    
    return 0;
}