#pragma once

#include "Matrix.hpp"

class ActivationFunction {
private:
	Matrix(*m_Function)(const Matrix&);
	Matrix(*m_Derivative)(const Matrix&);

public:
	ActivationFunction(Matrix(*function)(const Matrix&), Matrix(*derivative)(const Matrix&)) noexcept;
	ActivationFunction(const ActivationFunction& function) noexcept = default;
	~ActivationFunction() = default;

public:
	ActivationFunction& operator=(const ActivationFunction& function) noexcept = default;
	Matrix operator()(const Matrix& x) const;

public:
	Matrix GetGradient(const Matrix& x) const;
};

extern const ActivationFunction Sigmoid;
extern const ActivationFunction ReLU;