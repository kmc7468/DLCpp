#pragma once

#include "ActivationFunction.hpp"
#include "Matrix.hpp"

#include <cstddef>

class WeightedNeuron {
public:
	Matrix m_X;
	Matrix m_W;
	Matrix m_U;
	Matrix m_DW;
	Matrix m_DB;
	double m_B;

public:
	explicit WeightedNeuron(std::size_t inputSize);
	WeightedNeuron(const WeightedNeuron& neuron) = delete;
	~WeightedNeuron() = default;

public:
	WeightedNeuron& operator=(const WeightedNeuron& neuron) = delete;

public:
	Matrix Forward(const Matrix& x);
	Matrix Backward(const Matrix& d);
	void Update(double alpha);
};

class ActivationNeuron {
private:
	Matrix m_U;
	Matrix m_Y;
	ActivationFunction m_F;

public:
	explicit ActivationNeuron(ActivationFunction function);
	ActivationNeuron(const ActivationNeuron& neuron) = delete;
	~ActivationNeuron() = default;

public:
	ActivationNeuron& operator=(const ActivationNeuron& neuron) = delete;

public:
	Matrix Forward(const Matrix& x);
	Matrix Backward(const Matrix& d);
};