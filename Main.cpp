// Main.cpp
#include "LossFunction.hpp"
#include "Neuron.hpp"

#include <iostream>

int main() {
	WeightedNeuron wn(2);
	ActivationNeuron an(Sigmoid);

	Matrix input({ 0, 1, 0, 1,
				   0, 0, 1, 1 }, 2, 4);
	Matrix output({ 0, 1, 1, 1 }, 1, 4);

	for (int i = 0; i < 1000; ++i) {
		Matrix y = wn.Forward(input);
		y = an.Forward(y);
		std::cout << "Epoch " << i + 1 << ": MSE " << MSE(y, output) << '\n';
		Matrix d = an.Backward(MSE.GetGradient(y, output));
		wn.Backward(d);
		wn.Update(0.3);
	}

	Matrix y = wn.Forward(input);
	y = an.Forward(y);
	std::cout << y << '\n';

	return 0;
}