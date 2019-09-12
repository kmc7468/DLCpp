#pragma once

#include "Matrix.hpp"

class LossFunction {
private:
	double(*m_Function)(const Matrix&, const Matrix&);
	Matrix(*m_Derivative)(const Matrix&, const Matrix&);

public:
	LossFunction(double(*function)(const Matrix&, const Matrix&), Matrix(*derivative)(const Matrix&, const Matrix&)) noexcept;
	LossFunction(const LossFunction& function) noexcept = default;
	~LossFunction() = default;

public:
	LossFunction& operator=(const LossFunction& function) noexcept = default;
	double operator()(const Matrix& y, const Matrix& a) const;
	
public:
	Matrix GetGradient(const Matrix& y, const Matrix& a) const;
};

extern const LossFunction MSE;