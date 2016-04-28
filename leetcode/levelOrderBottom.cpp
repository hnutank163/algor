/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector< vector<TreeNode *> >  vec;
        vector< vector<int> > res;
        if(root==NULL)
            return res;
        res.push_back(vector<int>());
        vec.push_back(vector<TreeNode *>());
        vec[0].push_back(root);
        int i = 0;
        int cont = 0;
        while(true){
            cont = 0;
            vec.push_back(vector<TreeNode*>());
            for(auto val:vec[i]){
                res[i].push_back(val->val);
                if(val->left){
                    vec[i+1].push_back(val->left);
                    cont = 1;
                }
                if(val->right){
                    vec[i+1].push_back(val->right);
                    cont = 1;
                }
                
            }
            if(cont==0)
                break;
            else{
                res.push_back(vector<int>());
            }
                
            ++i;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
