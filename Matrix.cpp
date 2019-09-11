#include "Matrix.hpp"

#include <cassert>
#include <utility>

Matrix::Matrix(std::size_t row, std::size_t column)
	: m_Data(row * column), m_Row(row), m_Column(column) {
	assert((row == 0 && column == 0) || (row > 0 && column > 0));
}
Matrix::Matrix(double value, std::size_t row, std::size_t column)
	: m_Data(row * column, value), m_Row(row), m_Column(column) {
	assert((row == 0 && column == 0) || (row > 0 && column > 0));
}
Matrix::Matrix(std::vector<double> data, std::size_t row, std::size_t column)
	: m_Data(data), m_Row(row), m_Column(column) {
	assert((row == 0 && column == 0) || (row > 0 && column > 0));
	assert(row * column == m_Data.size());
}
Matrix::Matrix(const Matrix& matrix)
	: m_Data(matrix.m_Data), m_Row(matrix.m_Row), m_Column(matrix.m_Column) {
}
Matrix::Matrix(Matrix&& matrix) noexcept
	: m_Data(std::move(matrix.m_Data)), m_Row(matrix.m_Row), m_Column(matrix.m_Column) {
	matrix.m_Row = matrix.m_Column = 0;
}

Matrix& Matrix::operator=(const Matrix& matrix) {
	m_Data = matrix.m_Data;
	m_Row = matrix.m_Row;
	m_Column = matrix.m_Column;

	return *this;
}
Matrix& Matrix::operator=(Matrix&& matrix) noexcept {
	m_Data = std::move(matrix.m_Data);
	m_Row = matrix.m_Row;
	m_Column = matrix.m_Column;

	matrix.m_Row = matrix.m_Column = 0;

	return *this;
}
double Matrix::operator[](const MatrixIndex& index) const noexcept {
	return (*this)(index.Row, index.Column);
}
double& Matrix::operator[](const MatrixIndex& index) noexcept {
	return (*this)(index.Row, index.Column);
}
double Matrix::operator()(std::size_t row, std::size_t column) const noexcept {
	assert(row < m_Row);
	assert(column < m_Column);

	return m_Data[row * m_Column + column];
}
double& Matrix::operator()(std::size_t row, std::size_t column) noexcept {
	assert(row < m_Row);
	assert(column < m_Column);

	return m_Data[row * m_Column + column];
}
Matrix Matrix::operator+(const Matrix& matrix) const {
	return Matrix(*this) += matrix;
}
Matrix Matrix::operator-(const Matrix& matrix) const {
	return Matrix(*this) -= matrix;
}
Matrix Matrix::operator*(double value) const {
	return Matrix(*this) *= value;
}
Matrix Matrix::operator*(const Matrix& matrix) const {
	assert(m_Column == matrix.m_Row);

	Matrix result(m_Row, matrix.m_Column);

	for (std::size_t i = 0; i < m_Row; ++i) {
		for (std::size_t j = 0; j < matrix.m_Column; ++j) {
			for (std::size_t k = 0; k < m_Column; ++k) {
				result(i, j) += (*this)(i, k) * matrix(k, j);
			}
		}
	}

	return result;
}
Matrix& Matrix::operator+=(const Matrix& matrix) noexcept {
	assert(m_Row == matrix.m_Row);
	assert(m_Column == matrix.m_Column);

	for (std::size_t i = 0; i < m_Data.size(); ++i) {
		m_Data[i] += matrix.m_Data[i];
	}

	return *this;
}
Matrix& Matrix::operator-=(const Matrix& matrix) noexcept {
	assert(m_Row == matrix.m_Row);
	assert(m_Column == matrix.m_Column);

	for (std::size_t i = 0; i < m_Data.size(); ++i) {
		m_Data[i] -= matrix.m_Data[i];
	}

	return *this;
}
Matrix& Matrix::operator*=(double value) noexcept {
	for (std::size_t i = 0; i < m_Data.size(); ++i) {
		m_Data[i] *= value;
	}

	return *this;
}

void Matrix::Clear() noexcept {
	m_Data.clear();
	m_Row = m_Column = 0;
}
bool Matrix::IsEmpty() const noexcept {
	return m_Data.empty();
}
void Matrix::Swap(Matrix& matrix) noexcept {
	if (this == &matrix) return;

	std::swap(m_Data, matrix.m_Data);
	std::swap(m_Row, matrix.m_Row);
	std::swap(m_Column, matrix.m_Column);
}
std::size_t Matrix::GetRow() const noexcept {
	return m_Row;
}
std::size_t Matrix::GetColumn() const noexcept {
	return m_Column;
}

void Matrix::Transpose() noexcept {
	Matrix temp(m_Column, m_Row);
	for (std::size_t i = 0; i < m_Row; ++i) {
		for (std::size_t j = 0; j < m_Column; ++j) {
			temp(j, i) = (*this)(i, j);
		}
	}
	Swap(temp);
}
void Matrix::HadamardProduct(const Matrix& matrix) noexcept {
	assert(m_Row == matrix.m_Row);
	assert(m_Column == matrix.m_Column);

	for (std::size_t i = 0; i < m_Data.size(); ++i) {
		m_Data[i] *= matrix.m_Data[i];
	}
}

Matrix operator*(double value, const Matrix& matrix) {
	return Matrix(matrix) *= value;
}
std::ostream& operator<<(std::ostream& stream, const Matrix& matrix) {
	stream << '[';

	bool isFirst = true;
	for (std::size_t i = 0; i < matrix.GetRow(); ++i) {
		if (isFirst) {
			isFirst = false;
		} else {
			stream << "\n ";
		}
		for (std::size_t j = 0; j < matrix.GetColumn(); ++j) {
			stream << ' ' << matrix(i, j);
		}
	}

	return stream << " ]";
}