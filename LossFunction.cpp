#include "LossFunction.hpp"

#include <cmath>

LossFunction::LossFunction(double(*function)(const Matrix&, const Matrix&), Matrix(*derivative)(const Matrix&, const Matrix&)) noexcept
	: m_Function(function), m_Derivative(derivative) {
}

double LossFunction::operator()(const Matrix& y, const Matrix& a) const {
	return m_Function(y, a);
}

Matrix LossFunction::GetGradient(const Matrix& y, const Matrix& a) const {
	return m_Derivative(y, a);
}

namespace {
	double MSEF(const Matrix& y, const Matrix& a) {
		double result = 0.0;
		Matrix ya = y - a;
		for (std::size_t i = 0; i < ya.GetColumn(); ++i) {
			result += std::pow(ya(0, i), 2);
		}
		result /= ya.GetColumn();
		return result;
	}
	Matrix MSED(const Matrix& y, const Matrix& a) {
		Matrix ya = y - a;
		ya *= (2.0 / y.GetColumn());
		return ya;
	}
}

const LossFunction MSE(MSEF, MSED);