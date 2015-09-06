#include <vector>
#include <iostream>
using namespace std;

class Solution {
    int n;
	// k_th 从1开始，保证是较大的那个
    double  findMedian(vector<int>& nums1, vector<int>& nums2, int l, int r, int k_th) {
        if(l>r) return findMedian(nums2, nums1, std::max(0, n/2-(int)nums1.size()), std::min((int)nums2.size()-1, n/2), k_th);
        int i = (l+r+1)/2; // 保证i是较大的那个
        int j = k_th-i-1;
        
        if((j<0 || nums1[i]>=nums2[j]) && (j+1>=nums2.size() || nums1[i]<=nums2[j+1])) {
            if(n%2) return nums1[i];
            else {
                int left = INT_MIN;
                if(j>=0) left=std::max(left, nums2[j]);
                if(i-1>=0) left=std::max(left, nums1[i-1]);
                return (nums1[i]+left)/2.0;
            }
        }
        if(j>=0 && nums1[i]<nums2[j]) return findMedian(nums1, nums2, i+1, r, k_th);
        else return findMedian(nums1, nums2, l, i-1, k_th);
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        n = nums1.size()+nums2.size();
        // triky：上述算法需要工作在精确定位的边界[max{0, ceil(n/2)-lengthOfArray2}, min{lengthOfArray1-1, ceil(n)/2}]，否则会返回错误的结果
        return findMedian(nums1, nums2, std::max(0, n/2-(int)nums2.size()), std::min((int)nums1.size()-1,n/2), n/2);
    }
};

int main() {
	vector<int> nums1;
	vector<int> nums2;
	Solution s;
		
	nums1 = {1,2,3,5,6};
	nums2 = {4};
	cout << std::fixed << s.findMedianSortedArrays(nums1, nums2) << endl;
	cout << std::fixed << s.findMedianSortedArrays(nums2, nums1) << endl;
	
	nums1 = {1,2};
	nums2 = {1,1};
	cout << std::fixed << s.findMedianSortedArrays(nums1, nums2) << endl;
	cout << std::fixed << s.findMedianSortedArrays(nums2, nums1) << endl;

	nums1 = {1};
	nums2 = {2};
	cout << std::fixed << s.findMedianSortedArrays(nums1, nums2) << endl;
	cout << std::fixed << s.findMedianSortedArrays(nums2, nums1) << endl;
	
	nums1 = {1};
	nums2 = {2,3,4,5};
	cout << std::fixed << s.findMedianSortedArrays(nums1, nums2) << endl;
	cout << std::fixed << s.findMedianSortedArrays(nums2, nums1) << endl;
	
	nums1 = {1};
	nums2 = {2,3,4};
	cout << std::fixed << s.findMedianSortedArrays(nums1, nums2) << endl;
	cout << std::fixed << s.findMedianSortedArrays(nums2, nums1) << endl;
	
	nums1 = {};
	nums2 = {2,3};
	cout << std::fixed << s.findMedianSortedArrays(nums1, nums2) << endl;
	cout << std::fixed << s.findMedianSortedArrays(nums2, nums1) << endl;
	
}
