#pragma once
#include <iostream>
#include "L3DVector.h"

template <typename T>
class LMatrix
{
protected:
	T* Data;
	size_t NumRows;
	size_t NumCols;

	LMatrix(size_t rows, size_t cols) : NumRows(rows), NumCols(cols) { Data = new T[NumRows * NumCols]; }

public:
	template <std::size_t Rows, std::size_t Cols, typename... Args>
	static LMatrix<T> Build(Args... inElements)
	{
		size_t dataSize = Rows * Cols;
		if (dataSize != sizeof...(inElements))
		{
			throw std::invalid_argument("The number of elements provided is different from the provided matrix size!");
		}

		LMatrix result(Rows, Cols);
		T elements[] = {inElements...};
		for (size_t i = 0; i < dataSize; ++i) {
			result.Data[i] = elements[i];
		}

		return result;
	}

	template <std::size_t Row, std::size_t Col>
	void Set(T value) { Data[Row * NumCols + Col] = value; }

	~LMatrix() { delete[] Data; };

	LMatrix(const LMatrix& inOtherMatrix) : NumCols(inOtherMatrix.NumCols), NumRows(inOtherMatrix.NumRows)
	{
		size_t dataSize = NumCols * NumRows;
		Data = new T[dataSize];
		for (size_t i = 0; i < dataSize; ++i)
		{
			Data[i] = inOtherMatrix.Data[i];
		}
	}

	LMatrix(LMatrix&& inOtherMatrix) noexcept : Data(inOtherMatrix.Data), NumCols(inOtherMatrix.NumCols), NumRows(inOtherMatrix.NumRows)
	{
		delete[] Data;
		inOtherMatrix.Data = nullptr;
		inOtherMatrix.NumCols = 0;
		inOtherMatrix.NumRows = 0;
	}

	size_t getNumCols() { return NumCols; };
	size_t getNumRows() { return NumRows; };
	const T& operator()(size_t row, size_t col) const { return Data[row * NumCols + col]; };

	LMatrix& operator=(const LMatrix& inOtherMatrix)
	{
		if (this != &inOtherMatrix) {
			delete[] Data;
			NumCols = inOtherMatrix.NumCols;
			NumRows = inOtherMatrix.NumRows;

			size_t dataSize = NumCols * NumRows;
			Data = new T[dataSize];
			for (size_t i = 0; i < dataSize; ++i)
			{
				Data[i] = inOtherMatrix.Data[i];
			}
		}
		return *this;
	}

	LMatrix& operator=(LMatrix&& inOtherMatrix) noexcept
	{
		if (this != &inOtherMatrix) {
			delete[] Data;
			NumCols = inOtherMatrix.NumCols;
			NumRows = inOtherMatrix.NumRows;

			inOtherMatrix.Data = nullptr;
			inOtherMatrix.NumCols = 0;
			inOtherMatrix.NumRows = 0;
		}
		return *this;
	}

	LMatrix operator+(const LMatrix& inOtherMatrix) const
	{
		if (NumCols != inOtherMatrix.NumCols || NumRows != inOtherMatrix.NumRows)
		{
			throw std::invalid_argument("Matrices must be the same size.");
		}

		LMatrix result(NumRows, NumCols);
		for (size_t i = 0; i < NumRows * NumCols; ++i)
		{
			result.Data[i] = Data[i] + inOtherMatrix.Data[i];
		}
		return result;
	}

	LMatrix operator-(const LMatrix& inOtherMatrix) const
	{
		if (NumCols != inOtherMatrix.NumCols || NumRows != inOtherMatrix.NumRows)
		{
			throw std::invalid_argument("Matrices must be the same size.");
		}

		LMatrix result(NumRows, NumCols);
		for (size_t i = 0; i < NumRows * NumCols; ++i)
		{
			result.Data[i] = Data[i] - inOtherMatrix.Data[i];
		}
		return result;
	}

	LMatrix operator*(const LMatrix& inOtherMatrix) const
	{
		if (NumCols != inOtherMatrix.NumRows)
		{
			throw std::invalid_argument("The matrix M2 must have the same number of ROWS as the number of COLUMNS in M1!");
		}

		LMatrix result(NumRows, inOtherMatrix.NumCols);
		for (size_t row = 0; row < NumRows; ++row) {
			for (size_t col = 0; col < inOtherMatrix.NumCols; ++col) {
				
				T value = 0;
				for (size_t i = 0; i < NumCols; ++i) {
					value += Data[row * NumCols + i] * inOtherMatrix(i, col);
				}
				result.Data[row * inOtherMatrix.NumCols + col] = value;
			}
		}
		return result;
	}

	T* GetData() { return Data; };

	void Print()
	{
		for (size_t row = 0; row < NumRows; ++row) {
			for (size_t col = 0; col < NumCols; ++col) {
				std::cout << Data[row * NumCols + col] << " , ";
			}
			std::cout << std::endl;
		}
	}

	void PrintDebug(L3DVector vec)
	{
		float X = Data[0] * vec.getX() + Data[4] * vec.getY() + Data[8] * vec.getZ() + Data[12];
		float Y = Data[1] * vec.getX() + Data[5] * vec.getY() + Data[9] * vec.getZ() + Data[13];
		float Z = Data[2] * vec.getX() + Data[6] * vec.getY() + Data[10] * vec.getZ() + Data[14];
		float W = Data[3] * vec.getX() + Data[7] * vec.getY() + Data[11] * vec.getZ() + Data[15];
		std::cout << "X: " << X << " , Y: " << Y << " , Z: " << Z << " , W: " << W << std::endl;
	}
};