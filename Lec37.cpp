#include <iostream>
#include <vector>
using namespace std;

void subsequenceSolve(string str, string output, int index, vector <string> &ans){
    if(index >= str.length()){
        ans.push_back(output);
        return;
    }
    subsequenceSolve(str, output, index+1, ans);

    char element = str[index];
    output+= element;
    subsequenceSolve(str, output, index+1, ans);
}

vector<string> subsequences(string str){
    string output ="";
    vector<string> ans;
    int index =0;
    subsequenceSolve(str, output, index,ans );
     for (int i = 0; i < ans.size(); i++)
    {
        cout<<"{";
        for (int j = 0; j < ans[i].length(); j++)
        {
            cout << ans[i][j] << ",";
        }
        cout <<"}"<< endl;
    }
    return ans;

}

void subsetSolve(vector<int> nums, vector<int> output, int index, vector<vector<int>> &ans)
{
    if (index >= nums.size())
    {
        // all include exclude for all cases done then index exceeds array
        ans.push_back(output);
        return;
    }
    // exclude current index element and move to next index+1
    subsetSolve(nums, output, index + 1, ans);

    // including that element and move to next index+1
    int element = nums[index];
    output.push_back(element);
    subsetSolve(nums, output, index + 1, ans);
}

vector<vector<int>> subsets(vector<int> &nums)
{
    vector<int> output;
    vector<vector<int>> ans;
    subsetSolve(nums, output, 0, ans);
    // for (int i = 0; i < ans.size(); i++)
    // {
    //     cout<<"{";
    //     for (int j = 0; j < ans[i].size(); j++)
    //     {
    //         cout << ans[i][j] << ",";
    //     }
    //     cout <<"}"<< endl;
    // }
    return ans;
}

int main()
{
    vector<int> arr = {1, 2, 3};
    subsequences("abc");
    return 0;
}