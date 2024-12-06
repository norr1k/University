#include "Header.h"

namespace my{

	template <typename _T>					// Конструктор
	TreeNode<_T>::TreeNode(_T _value){
		value = _value;
		ptr_left = ptr_right = nullptr;
	}

	template <typename _T>					// Деструктор
	TreeNode<_T>::~TreeNode(){
		ptr_right = ptr_left = nullptr;
	}

	template <typename _T>					// Поиск максимума в заданном узле
	TreeNode<_T> TreeNode<_T>::max(TreeNode where_to_search) {
		where_to_search->ptr_right == nullptr ?		// Если есть значение больше
			return where_to_search : max(ptr_right);		// Возвращаем узел с этим значением. Иначе - рекурсия
	}

	template <typename _T>					// Поиск минимума в заданном узле
	TreeNode<_T> TreeNode<_T>::min(TreeNode where_to_search) {
		where_to_search->ptr_left == nullptr ?		// Если есть значение меньше
			return where_to_search : max(ptr_left);			// Возвращаем узел с этим значением. Иначе - рекурсия
	}

	template <typename _T>					// Вставка
	void TreeNode<_T>::insert(_T _value) {
		if (_value < value)					// Если новое знач. меньше нынешнего - проверяем левую ветку:
		{
			ptr_left == nullptr ?					// Если слева пусто - записываем значение. Иначе - рекурсия
				ptr_left = &TreeNode(value) : ptr_left->insert(_value);
		}
		else								// Если новое знач. больше нынешнего - проверяем правую ветку:
		{
			ptr_right == nullptr ?					// Если справа пусто - записываем значение. Иначе - рекурсия
				ptr_right = &TreeNode(value) : ptr_right->insert(_value);
		}
	}

	template <typename _T>					// Удаление
	TreeNode<_T> TreeNode<_T>::remove(_T _value, TreeNode where_to_delete) {
		if (where_to_delete == nullptr) return nullptr;				// Если удаляемой ноды не нашлось - возвращаем 0
		else if (_value > where_to_delete.value) remove(where_to_delete->ptr_right);	// Если искомое значение больше - переходим вправо
		else if (_value < where_to_delete.value) remove(where_to_delete->ptr_left);		// Если искомое значение меньше - переходим влево
		else
		{
			if ((where_to_delete->ptr_left == nullptr) or (where_to_delete->ptr_right == nullptr))		// Если один ребёнок (или их нет)
			{
				where_to_delete = (where_to_delete->ptr_left != nullptr) ?				// Он слева?
					where_to_delete->ptr_left :				// Заменям на левого
					where_to_delete->ptr_right;				// Заменяем на правого
			}
			else
			{
				TreeNode new_node = min(where_to_delete->ptr_right);	// Минимальный из больших детей
				where_to_delete->value = new_node->value;				// Переписываем значение
				new_node->ptr_right = remove(new_node->value; where_to_delete->ptr_right);		// Перезаписываем ноду с украденным значением
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