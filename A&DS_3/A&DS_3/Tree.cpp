#include "Header.h"

namespace my{

	template <typename _T>					// �����������
	TreeNode<_T>::TreeNode(_T _value){
		value = _value;
		ptr_left = ptr_right = nullptr;
	}

	template <typename _T>					// ����������
	TreeNode<_T>::~TreeNode(){
		ptr_right = ptr_left = nullptr;
	}

	template <typename _T>					// ����� ��������� � �������� ����
	TreeNode<_T> TreeNode<_T>::max(TreeNode where_to_search) {
		where_to_search->ptr_right == nullptr ?		// ���� ���� �������� ������
			return where_to_search : max(ptr_right);		// ���������� ���� � ���� ���������. ����� - ��������
	}

	template <typename _T>					// ����� �������� � �������� ����
	TreeNode<_T> TreeNode<_T>::min(TreeNode where_to_search) {
		where_to_search->ptr_left == nullptr ?		// ���� ���� �������� ������
			return where_to_search : max(ptr_left);			// ���������� ���� � ���� ���������. ����� - ��������
	}

	template <typename _T>					// �������
	void TreeNode<_T>::insert(_T _value) {
		if (_value < value)					// ���� ����� ����. ������ ��������� - ��������� ����� �����:
		{
			ptr_left == nullptr ?					// ���� ����� ����� - ���������� ��������. ����� - ��������
				ptr_left = &TreeNode(value) : ptr_left->insert(_value);
		}
		else								// ���� ����� ����. ������ ��������� - ��������� ������ �����:
		{
			ptr_right == nullptr ?					// ���� ������ ����� - ���������� ��������. ����� - ��������
				ptr_right = &TreeNode(value) : ptr_right->insert(_value);
		}
	}

	template <typename _T>					// ��������
	TreeNode<_T> TreeNode<_T>::remove(_T _value, TreeNode where_to_delete) {
		if (where_to_delete == nullptr) return nullptr;				// ���� ��������� ���� �� ������� - ���������� 0
		else if (_value > where_to_delete.value) remove(where_to_delete->ptr_right);	// ���� ������� �������� ������ - ��������� ������
		else if (_value < where_to_delete.value) remove(where_to_delete->ptr_left);		// ���� ������� �������� ������ - ��������� �����
		else
		{
			if ((where_to_delete->ptr_left == nullptr) or (where_to_delete->ptr_right == nullptr))		// ���� ���� ������ (��� �� ���)
			{
				where_to_delete = (where_to_delete->ptr_left != nullptr) ?				// �� �����?
					where_to_delete->ptr_left :				// ������� �� ������
					where_to_delete->ptr_right;				// �������� �� �������
			}
			else
			{
				TreeNode new_node = min(where_to_delete->ptr_right);	// ����������� �� ������� �����
				where_to_delete->value = new_node->value;				// ������������ ��������
				new_node->ptr_right = remove(new_node->value; where_to_delete->ptr_right);		// �������������� ���� � ���������� ���������
			}
		}
		return where_to_delete;
	}


	template <typename _T>
	AVL_tree<_T>::AVL_tree(_T _value): TreeNode<_T>(_T _value)
	{
		ptr_left = ptr_right = nullptr;
		heigth = 0;
	}

	template <typename _T>
	AVL_tree<_T>::~AVL_tree()
	{

	}
}