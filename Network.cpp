#include "Network.h"
#include<cmath>
#include<iostream>
using namespace std;

Network::Network(vector<int> layer)
{
	learning_rate = 0.2;
	epoch_lim = 100;
	int prev = 0;
	for (int i = 0; i < layer.size(); i++)
	{
		layers.push_back(vector<Neuron>());
		for (int j = 0; j < layer[i]; j++)
		{
			this->layers[i].push_back(Neuron(prev));
			cout << "Neuron added in " << i << " layer!" << endl;
		}
		prev = layer[i];
	}
}
void Network::train(int Y , const vector<double>&input)
{
	vector<double> expected(10);
	printf("\t\t\t\ label: %u", Y);
	for (int i = 0; i < 10; ++i)
	{
		if (i == Y)
			expected[i] = 0.9;
		else
			expected[i] = 0;
	}
	cout << "\n";
	for (int i = 0; i < epoch_lim; i++)
	{
		forward_feed(input);
		back_propagation(expected);
		cout << "\noutput\n";
		printOutput();
	}
	if (Y == max())
	{
		cout << "\n\t\t\tCorrect Output.." << "\n";
	}
	else
	{
		cout <<"\t\t\t"<< Y << "and" << max();
		cout << "\n\t\t\tIncorrect Output.." << "\n";
	}
}
int Network::max()
{
	int max_index=0;
	double maxVal = layers[layers.size() - 1][0].activation;
	for(int i = 0; i < layers[layers.size() - 1].size(); i++)
	{
		if ((layers[layers.size() - 1][i].activation) > maxVal)
		{
			max_index = i;
			maxVal = layers[layers.size() - 1][i].activation;
		}
	}
	return max_index;
}
void Network::forward_feed(const vector<double>& input)        // Forward propogation 
{
	if (input.size() == layers[0].size())
	{
		for (int i = 0; i < input.size(); i++)
		{
			layers[0][i].activation = input[i];     // input in input layer
		}
		for (int i = 1; i < layers.size(); i++)
		{
			for (int j = 0; j < layers[i].size(); j++)
			{
				layers[i][j].output_val = 0;
				for (int k = 0; k < layers[i - 1].size(); k++)
				{
					layers[i][j].output_val += layers[i - 1][k].activation * layers[i][j].weights[k];
				}
				layers[i][j].output_val += layers[i][j].bias;
				layers[i][j].activation = activation(layers[i][j].output_val);
			}
		}
		
			/*double maxi = 0;
			int predict;
			for (int i = 0; i < layers[3].size(); ++i)
			{
				if (maxi < layers[3][i].activation)
				{
					maxi = layers[3][i].activation;
					predict = i;
				}
			}
			cout << predict << endl;
	*/	
	}
	else
		throw("Invalid input size");
}

void Network::back_propagation(const vector<double>& expected)
{
	double d[4][10] = { 0 };		// differential of Error function w.r.t layers[i][j].activation
	double step_size;

	// Used error function : 1/2 (output - predicted)^2

	for (int i = 0; i < layers[3].size(); ++i)
	{
		d[3][i] = -(expected[i] - layers[3][i].activation);
	}

	for (int i = 2; i >= 1; --i)
	{
		for (int j = 0; j < layers[i].size(); ++j)
		{
			for (int k = 0; k < layers[i + 1].size(); ++k)
			{
				d[i][j] += d[i + 1][k] * layers[i + 1][k].weights[j] * derivative(layers[i + 1][k].output_val);
			}
		}
	}

	for (int i = 3; i >= 1; --i)
	{
		for (int j = 0; j < layers[i].size(); ++j)
		{
			for (int k = 0; k < layers[i - 1].size(); ++k)
			{
				step_size = layers[i][j].weights[k] * d[i][j] * derivative(layers[i][j].output_val);
				layers[i][j].weights[k] = layers[i][j].weights[k] - step_size * learning_rate;
			}
			step_size = d[i][j] * derivative(layers[i][j].output_val);
			layers[i][j].bias = layers[i][j].bias - step_size * learning_rate;
		}
	}
	//cout << calculate_error(expected)<<"\n";
}

double Network::activation(double n)
{
	return 1.00 / (1.00 + expf(-n));
}

double Network::derivative(double value)            // sigmoid function derivative
{
	return activation(value) * (1.00 - activation(value));
}

void Network::printOutput() {
	for (int i = 0; i < layers[layers.size() - 1].size(); i++) {
		cout << layers[layers.size() - 1][i].activation << endl;
	}
}

double Network::calculate_error(const vector<double>& expected) {                     // Root mean square to calculating the total error
	double total_error = 0;
	double error[15];
	for (int i = 0; i < layers[layers.size() - 1].size(); i++) {
		error[i] = expected[i] - layers[layers.size() - 1][i].get_output_val();
		error[i] *= error[i];
		total_error += error[i];
	}
	total_error /= layers[layers.size() - 1].size();
	sqrt(total_error);
	return total_error;
}


