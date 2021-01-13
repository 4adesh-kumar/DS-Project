#include "Neuron.h"
Neuron::Neuron(int prev_layer_neurons)
{
	for (int i = 0; i <= prev_layer_neurons; i++)
	{
		weight.push_back(get_random_weight());
	}
}
double Neuron::get_output_val()
{
	return output_val;
}
double Neuron::get_random_weight()
{
	return (double) rand() / RAND_MAX;
}
double Neuron::get_weight(int index)
{
	if (index >= 0 && index < weight.size())
		return this->weight[index];

	else
		throw("Invalid weight index");
}
void Neuron::set_output_val(double output_val)
{
	this->output_val = output_val;
}
