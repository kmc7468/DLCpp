#include "ActivationFunction.hpp"

#include <algorithm>
#include <cmath>

ActivationFunction::ActivationFunction(Matrix(*function)(const Matrix&), Matrix(*derivative)(const Matrix&)) noexcept
	: m_Function(function), m_Derivative(derivative) {
}

Matrix ActivationFunction::operator()(const Matrix& x) const {
	return m_Function(x);
}

Matrix ActivationFunction::GetGradient(const Matrix& x) const {
	return m_Derivative(x);
}

namespace {
	Matrix SigmoidF(const Matrix& x) {
		Matrix result(x.GetRow(), x.GetColumn());
		for (std::size_t i = 0; i < x.GetRow(); ++i) {
			for (std::size_t j = 0; j < x.GetColumn(); ++j) {
				result(i, j) = 1 / (1 + std::exp(-x(i, j)));
			}
		}
		return result;
	}
	Matrix SigmoidD(const Matrix& x) {
		Matrix result(x.GetRow(), x.GetColumn());
		Matrix func = SigmoidF(x);
		for (std::size_t i = 0; i < x.GetRow(); ++i) {
			for (std::size_t j = 0; j < x.GetColumn(); ++j) {
				result(i, j) = func(i, j) * (1 - func(i, j));
			}
		}
		return result;
	}
	Matrix ReLUF(const Matrix& x) {
		Matrix result(x.GetRow(), x.GetColumn());
		for (std::size_t i = 0; i < x.GetRow(); ++i) {
			for (std::size_t j = 0; j < x.GetColumn(); ++j) {
				result(i, j) = std::max(0.0, x(i, j));
			}
		}
		return result;
	}
	Matrix ReLUD(const Matrix& x) {
		Matrix result(x.GetRow(), x.GetColumn());
		for (std::size_t i = 0; i < x.GetRow(); ++i) {
			for (std::size_t j = 0; j < x.GetColumn(); ++j) {
				result(i, j) = x(i, j) >= 0 ? 1 : 0;
			}
		}
		return result;
	}
}

const ActivationFunction Sigmoid(SigmoidF, SigmoidD);
const ActivationFunction ReLU(ReLUF, ReLUD);