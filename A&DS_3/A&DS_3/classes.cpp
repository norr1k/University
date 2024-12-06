#pragma once

#include <stdexcept>

namespace my {
	template <typename _T>
	class stack {
	public:
		stack(size_t size = 64) : max_length(size) {
			top = nullptr;
			arr = new _T(max_length);
		};

		~stack() { delete[] arr; }							// Удаление мусора

		bool empty() {											// Проверить стек на пустоту
			return length == 0;
		}

		bool full() {											// Проверить стек на полноту
			return length == max_length;
		}

		size_t size() const {									// Вернуть длину стека
			return length;
		}

		void push(_T _elem) {									// Добавить элемент стека
			if (full)
				throw std::overflow_error("stack is full.");
			arr[length++] = _elem;
		}

		_T top() const {										// Вернуть верхний элемент стека
			if (empty)
				throw std::underflow_error("stack is empty.");
			return arr[length - 1];
		}

		_T pop() {												// Вернуть и удалить ("забыть") верхний элемент стека
			if (empty)
				throw std::underflow_error("stack is empty.");
			return arr[--length];
		}

	private:
		_T* arr;
		size_t length, max_length;
	};
}