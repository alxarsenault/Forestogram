#ifndef __R_MATRIX__
#define __R_MATRIX__

#include "RUtils.h"

namespace R
{
	template <typename T>
	class Matrix2D
	{
	public:
		Matrix2D(T* data, const Size2D& size):
		_data(data),
		_size(size)
		{

		}

		void PrintSize() const
		{
			R::Print("Matrix2D size :", _size.row, _size.col);
		}

		inline T& operator () (const unsigned int& row, const unsigned int& col)
		{
			unsigned int index = row + col * _size.row;
			return _data[index];
		}

		inline T& operator () (const unsigned int& index)
		{
			return _data[index];
		}

		T* GetData()
		{
			return _data;
		}

	private:
		T* _data;
		Size2D _size;
	};
}

#endif // __R_MATRIX__
