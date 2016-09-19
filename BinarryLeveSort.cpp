vector<vector<int>> LeveSort(TreeNode*root) //之字层序打印二叉树
{
	assert(root);
	TreeNode*cur=root;
	stack<TreeNode*>s1;
	stack<TreeNode*>s2;
	s1.push(root);
	vector<int> out;
	vector<vector<int>> res;
	while(!s1.empty()&&!s2.empty())
	{
		//奇数层放入s1
		while(!s1.empty())
		{
			cur=s1.front();
			s1.pop();
			out.push_back(cur->data);
			//从右到左将偶数层放入s2
			if(cur->right)
				s2.push(cur->right);
			if(cur->left)
				s2.push(cur->left);
		}
		res.push_back(out);
		out.clear();
		//偶数层放入s2
		while(!s2.empty())
		{
			cur=s2,front();
			s2.pop();
			out.push_back(cur->data);
			//从左到右将奇数层放入s1
			if(cur->left)
				s1.push(cur->left);
			if(cur->right)
				s1.push(cur->right);
		}
		res.push_back(out);
		out.clear();
	}
	return res;
}
