#include <iostream>
#include <vector>
using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int i = 0, j = 0, m = nums1.size(), n = nums2.size();
    vector<int> nums3;
    cout<<"m="<<m<<",n="<<n<<endl;
    while(i<m || j<n){
        cout<<"i="<<i<<"j="<<j<<endl;
        if(i >= m) nums3.push_back(nums2[j++]);
        if(j >= n) nums3.push_back(nums1[i++]);
        if(i < m && j<n) nums3.push_back(nums1[i] < nums2[j] ? nums1[i++]: nums2[j++]);
    }
    if((n+m)%2 == 1) return nums3[(m+n)/2];
    return double(nums3[(m+n)/2 - 1] + nums3[(m+n)/2])/2;
}

int main(){
    int n1[2] = {1,3};
    int n2[1] = {2};
    vector<int> nums1;
    vector<int> nums2(n2, n2+1);
    cout<<findMedianSortedArrays(nums1, nums2)<<endl;
}
