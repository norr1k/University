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

		~stack() { delete[] arr; }							// �������� ������

		bool empty() {											// ��������� ���� �� �������
			return length == 0;
		}

		bool full() {											// ��������� ���� �� �������
			return length == max_length;
		}

		size_t size() const {									// ������� ����� �����
			return length;
		}

		void push(_T _elem) {									// �������� ������� �����
			if (full)
				throw std::overflow_error("stack is full.");
			arr[length++] = _elem;
		}

		_T top() const {										// ������� ������� ������� �����
			if (empty)
				throw std::underflow_error("stack is empty.");
			return arr[length - 1];
		}

		_T pop() {												// ������� � ������� ("������") ������� ������� �����
			if (empty)
				throw std::underflow_error("stack is empty.");
			return arr[--length];
		}

	private:
		_T* arr;
		size_t length, max_length;
	};
}