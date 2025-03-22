#pragma once
#include <stdexcept>

template <typename T>
class LVector {
protected:
	T* Data;
	size_t Size;

public:

	template <typename... Args>
	LVector(Args... inElements)
	{ 
		Size = sizeof...(inElements);
		Data = new T[Size];

		T elements[] = { inElements... };
		for (size_t i = 0; i < Size; ++i) {
			Data[i] = elements[i];
		}
	};

	~LVector() { delete[] Data; };

	LVector(const LVector& inOtherVector) : Size(inOtherVector.Size)
	{
		Data = new T[Size];
		for (size_t i = 0; i < Size; ++i) 
		{
			Data[i] = inOtherVector.Data[i];
		}
	}

	LVector(LVector&& inOtherVector) noexcept : Data(inOtherVector.Data), Size(inOtherVector.Size)
	{
		//delete[] Data;
		Data = inOtherVector.Data;
		Size = inOtherVector.Size;
		inOtherVector.Data = nullptr;
		inOtherVector.Size = 0;
	}

	size_t dimensions() { return Size; };
	T& operator[](const int inPos){	return Data[inPos];	};

	LVector& operator=(const LVector& inOtherVector)
	{
		if (this != &inOtherVector) {
			//delete[] Data;
			Size = inOtherVector.Size;
			Data = new T[Size];
			for (size_t i = 0; i < Size; ++i) 
			{
				Data[i] = inOtherVector.Data[i];
			}
		}
		return *this;
	}

	LVector& operator=(LVector&& inOtherVector) noexcept
	{
		if (this != &inOtherVector) {
			//delete[] Data;
			Data = inOtherVector.Data;
			Size = inOtherVector.Size;
			inOtherVector.Data = nullptr;
			inOtherVector.Size = 0;
		}
		return *this;
	}

	LVector operator+(const LVector& inOtherVector) const
	{
		if (Size != inOtherVector.Size)
		{
			throw std::invalid_argument("Vectors must be the same size.");
		}

		LVector result;
		result.Data = new T[Size];
		result.Size = Size;
		for (size_t i = 0; i < Size; ++i) 
		{
			result.Data[i] = Data[i] + inOtherVector.Data[i];
		}
		return result;
	}
	
	LVector operator-(const LVector& inOtherVector) const
	{
		if (Size != inOtherVector.Size)
		{
			throw std::invalid_argument("Vectors must be the same size.");
		}

		LVector result;
		result.Data = new T[Size];
		result.Size = Size;
		for (size_t i = 0; i < Size; ++i) 
		{
			result.Data[i] = Data[i] - inOtherVector.Data[i];
		}
		return result;
	}

	T operator*(LVector<T>& inOtherVector)
	{
		if (Size != inOtherVector.Size)
		{
			throw std::invalid_argument("Vectors must be the same size.");
		}

		T result = T();
		for (size_t i = 0; i < Size; ++i)
		{
			result += Data[i] * inOtherVector[i];
		}
		return result;
	};

	LVector operator*(const T& inScalar) const 
	{
		LVector result;
		result.Data = new T[Size];
		result.Size = Size;
		for (size_t i = 0; i < Size; ++i) {
			result.Data[i] = Data[i] * inScalar;
		}
		return result;
	}
};