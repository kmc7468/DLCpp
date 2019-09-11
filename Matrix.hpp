#pragma once

#include <cstddef>
#include <ostream>
#include <vector>

struct MatrixIndex {
	std::size_t Row, Column;
};

class Matrix {
private:
	std::vector<double> m_Data;
	std::size_t m_Row = 0, m_Column = 0;

public:
	Matrix() noexcept = default;
	Matrix(std::size_t row, std::size_t column);
	Matrix(double value, std::size_t row, std::size_t column);
	Matrix(std::vector<double> data, std::size_t row, std::size_t column);
	Matrix(const Matrix& matrix);
	Matrix(Matrix&& matrix) noexcept;
	~Matrix() = default;

public:
	Matrix& operator=(const Matrix& matrix);
	Matrix& operator=(Matrix&& matrix) noexcept;
	double operator[](const MatrixIndex& index) const noexcept;
	double& operator[](const MatrixIndex& index) noexcept;
	double operator()(std::size_t row, std::size_t column) const noexcept;
	double& operator()(std::size_t row, std::size_t column) noexcept;
	Matrix operator+(const Matrix& matrix) const;
	Matrix operator-(const Matrix& matrix) const;
	Matrix operator*(double value) const;
	Matrix operator*(const Matrix& matrix) const;
	Matrix& operator+=(const Matrix& matrix) noexcept;
	Matrix& operator-=(const Matrix& matrix) noexcept;
	Matrix& operator*=(double value) noexcept;

public:
	void Clear() noexcept;
	bool IsEmpty() const noexcept;
	void Swap(Matrix& matrix) noexcept;
	std::size_t GetRow() const noexcept;
	std::size_t GetColumn() const noexcept;

	void Transpose() noexcept;
	void HadamardProduct(const Matrix& matrix) noexcept;
};

Matrix operator*(double value, const Matrix& matrix);
std::ostream& operator<<(std::ostream& stream, const Matrix& matrix);