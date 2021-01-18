#include "Network.h"
#include<cmath>
#include<iostream>
using namespace std;

Network::Network(vector<int> layer) 
{
	int prev = 0;
	for (int i = 0; i < layer.size(); i++) 
	{
		layers.push_back(vector<Neuron>());
		for (int j = 0; j <= layer[i]; j++)           // one extra bias neuron for every layer thatswhy <= 
		{ 
			this->layers[i].push_back(Neuron(prev));
			cout << "Neuron added in " << i << " layer!" << endl;
		}
		prev = layer[i];
	}
}
void Network::set_output_values(const vector<double> &input)        // Forward propogation 
{
	if (input.size() == layers[0].size() - 1)
	{
		double sum = 0;
		for (int i = 0; i < input.size(); i++)
		{
			layers[0][i].set_output_val(input[i]);     // input in input layer
		}
		for (int i = 0; i < layers.size(); i++)
		{
			layers[i][layers[i].size() - 1].set_output_val(1);              // every bias node have value 1 
		}
		for (int i = 1; i < layers.size(); i++)
		{
			for (int j = 0; j < layers[i].size()-1; j++)
			{
				sum = 0;
				for (int k = 0; k < layers[i - 1].size(); k++)
				{
					sum += layers[i - 1][k].get_output_val() * layers[i][j].get_weight(k);
				}
				layers[i][j].set_output_val(tanh(sum));     // activation function tanh
			}
		}
	}
	else
		throw("Invalid input size");
}
double Network::derivative_of_activation_function(double value)            // 1- tan^2x
{
	return 1 - (tanh(value) * tanh(value));
}
void Network::printOutput() {
	for (int i = 0; i < layers[layers.size() - 1].size(); i++) {
		cout << layers[layers.size() - 1][i].get_output_val() << endl;
	}
}
double Network::calculate_error(vector<double>& expected) {                     // Root mean square to calculating the total error
	double total_error = 0;
	for (int i = 0; i < layers[layers.size() - 1].size(); i++) {
		error[i] = expected[i] - layers[layers.size() - 1][i].get_output_val();  
		error[i] *= error[i];
		total_error += error[i];
	}
	total_error /= layers[layers.size() - 1].size();
	sqrt(total_error);
	return total_error;
}
