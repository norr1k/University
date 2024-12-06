#pragma once

namespace my {
	template <typename _T>
	class TreeNode
	{
	public:
		TreeNode(_T);
		~TreeNode();
		void insert(_T);
		TreeNode<_T> remove(_T, TreeNode);
		TreeNode max(TreeNode);
		TreeNode min(TreeNode);
	private:
		_T value;

		TreeNode* ptr_left, ptr_right;
	};

	template <typename _T>
	class AVL_tree : public TreeNode
	{
	public:
		AVL_tree(_T); 
		~AVL_tree();
	private:
		int heigth;
	};
	
}


