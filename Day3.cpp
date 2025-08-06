// 3479. Fruits Into Baskets III
// Medium
// Topics
// premium lock icon
// Companies
// Hint
// You are given two arrays of integers, fruits and baskets, each of length n, where fruits[i] represents the quantity of the ith type of fruit, and baskets[j] represents the capacity of the jth basket.

// From left to right, place the fruits according to these rules:

// Each fruit type must be placed in the leftmost available basket with a capacity greater than or equal to the quantity of that fruit type.
// Each basket can hold only one type of fruit.
// If a fruit type cannot be placed in any basket, it remains unplaced.
// Return the number of fruit types that remain unplaced after all possible allocations are made.

 

// Example 1:

// Input: fruits = [4,2,5], baskets = [3,5,4]

// Output: 1

// Explanation:

// fruits[0] = 4 is placed in baskets[1] = 5.
// fruits[1] = 2 is placed in baskets[0] = 3.
// fruits[2] = 5 cannot be placed in baskets[2] = 4.
// Since one fruit type remains unplaced, we return 1.

// Example 2:

// Input: fruits = [3,6,1], baskets = [6,4,7]

// Output: 0

// Explanation:

// fruits[0] = 3 is placed in baskets[0] = 6.
// fruits[1] = 6 cannot be placed in baskets[1] = 4 (insufficient capacity) but can be placed in the next available basket, baskets[2] = 7.
// fruits[2] = 1 is placed in baskets[1] = 4.
// Since all fruits are successfully placed, we return 0.

 

// Constraints:

// n == fruits.length == baskets.length
// 1 <= n <= 105
// 1 <= fruits[i], baskets[i] <= 109

/*------------------------Solution------------------------------*/
class Solution {
    vector<int> segTree;

    void buildSegTreeRMQ(vector<int>& baskets,int low,int high,int st_idx){
        if(low==high){
            segTree[st_idx] = baskets[low];
            return;
        }

        int mid = low + (high-low)/2;
        buildSegTreeRMQ(baskets,low,mid,2*st_idx);
        buildSegTreeRMQ(baskets,mid+1,high,2*st_idx+1);
        segTree[st_idx] = max(segTree[2*st_idx],segTree[2*st_idx+1]);
    }
    int findLeftmostBasket(const int& fruit,int low,int high,int st_idx){
        if(segTree[st_idx]<fruit)
            return -1;
        if(low==high){
            segTree[st_idx] = -1;
            return 1;//1 shows the basket was found
        }
        
        int val;
        int mid = low + (high-low)/2;
        if(segTree[2*st_idx]>=fruit)    val = findLeftmostBasket(fruit,low,mid,2*st_idx);
        else                            val = findLeftmostBasket(fruit,mid+1,high,2*st_idx+1);
        segTree[st_idx] = max(segTree[2*st_idx],segTree[2*st_idx+1]);
        return val;
    }
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size();
        segTree = vector<int>(4*n+1);

        //Step-1: Build Segment Tree RMQ
        int st_idx = 1;
        buildSegTreeRMQ(baskets,0,n-1,st_idx);

        //Step-2: Query the leftmost basket to be used
        int count = 0;
        for(int i=0;i<n;++i){
            if(findLeftmostBasket(fruits[i],0,n-1,st_idx)==-1)
                count++;
        }
        return count;
    }
};