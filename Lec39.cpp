#include <iostream>
#include <vector>
using namespace std;

void stringPermutations(string str, vector<string> &ans, int index)
{
    if (index >= str.length())
    {
        //when all swapping for next done and reach end 
        ans.push_back(str);
        return;
    }
    for (int j = index; j < str.length(); j++)
    {
        swap(str[j], str[index]);//swap with self and then all next one by one 
        stringPermutations(str, ans, index + 1);
        // swap(str[index], str[j]); // backtracking; to avoid 
    }
}

vector<string> stringPerm(string str)
{
    vector<string> ans;
    int index = 0;
    stringPermutations(str, ans, index);
    // Print ans vector
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    return ans;
}

void numPermutations(vector<int>& nums,vector<vector<int>> &ans, int index){
    if(index >=nums.size()){
        ans.push_back(nums);
        return;
    }
    for(int j=index; j<nums.size();j++){
        swap(nums[index], nums[j]);//swap num with itself and then next back track for the next value of j and current index
        solve(nums, ans, index+1);
        swap(nums[j], nums[index]);//Back tracking
    }
}
vector<vector<int>> num(vector<int>& nums) {
    vector<vector<int>> ans;
    int index = 0;
    solve(nums, ans, index);
    for (int i = 0; i < ans.size(); i++)
    {
        for (int j = 0; j < ans[i].size(); j++)
        {
            cout << ans[i][j];
        } cout <<", ";
    }
    cout << endl;
    return ans;
}

int main()
{
    // vector<string> ans = stringPerm("abc");

    vector<int> nums = {1,2,3};
    vector <vector<int>> ans = permute(nums);
    return 0;
}