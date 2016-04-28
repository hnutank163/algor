#include <iostream>
#include <vector>
using namespace std;

class Solution{
public:
    void rotate(vector< vector<int> > &matrix){
        vector< vector<int> > temp = matrix;
        int i = 0;
        int j = matrix[0].size()-1;
        for(auto vec:temp)
        {
            for(auto val: vec)
            {
                matrix[i++][j] = val;
            }
            i=0;
            --j;
        }
    }

    void rotate2(vector< vector<int> > & matrix)
    {
        int temp;
        int n = matrix.size();
        int m = matrix[0].size();
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<m; ++j)
            {
                temp = matrix[i][j];
                matrix[i][j] =
            }
        }
    }

};

void print(vector< vector<int> > &matrix)
{
    for(auto vec: matrix){
        for(auto val: vec){
            cout<<val<<"  ";
        }
        cout<<endl;
    }
}

int main(){
    vector< vector<int> > matrix = { {1,2,3},{4,5,6},{7,8,9} };
    print(matrix);
    cout<<"after rotate\n";
    Solution sl;
    sl.rotate(matrix);
    print(matrix);
    return 0;
}
