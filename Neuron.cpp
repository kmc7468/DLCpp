#include "Neuron.hpp"

#include <random>

WeightedNeuron::WeightedNeuron(std::size_t inputSize)
	: m_W(1, inputSize) {
	std::random_device rd;
	std::mt19937_64 mt(rd());
	std::uniform_real_distribution dist(0.0, 1.0);
	
	for (std::size_t i = 0; i < inputSize; ++i) {
		while ((m_W(0, i) = dist(mt)) == 0);
	}
	while ((m_B = dist(mt)) == 0);
}

Matrix WeightedNeuron::Forward(const Matrix& x) {
	m_X = x;
	m_U = m_W * x;
	for (std::size_t i = 0; i < m_U.GetColumn(); ++i) {
		m_U(0, i) += m_B;
	}
	return m_U;
}
Matrix WeightedNeuron::Backward(const Matrix& d) {
	Matrix xT(m_X);
	xT.Transpose();
	m_DW = d * xT;
	m_DB = d * Matrix(1, m_X.GetColumn(), 1);
	
	Matrix wT(m_W);
	wT.Transpose();
	return wT * d;
}
void WeightedNeuron::Update(double alpha) {
	m_W -= alpha * m_DW;
	m_B -= alpha * m_DB(0, 0);
}

ActivationNeuron::ActivationNeuron(ActivationFunction function)
	: m_F(function) {
}

Matrix ActivationNeuron::Forward(const Matrix& x) {
	m_U = x;
	m_Y = m_F(x);
	return m_Y;
}
Matrix ActivationNeuron::Backward(const Matrix& d) {
	Matrix up = m_F.GetGradient(m_U);
	up.HadamardProduct(d);
	return up;
}