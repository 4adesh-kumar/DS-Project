#include "Network.h"

Network::Network(vector<int> layers) 
{
	int prev = 0;
	for (int i = 0; i < layers.size(); i++) 
	{
		vector<Neuron> v;
		this->layers.push_back(v);
		for (int j = 0; j <= layers[i]; j++)           // one extra bias neuron for every layer thatswhy <= 
		{ 
			this->layers[i].push_back(Neuron(prev));
			cout << "Neuron added in " << i << " layer!" << endl;
		}
		prev = layers[i];
	}
}
void Network::set_output_values(const vector<Neuron> &input)
{
	if (input.size() == layers[0].size())
	{
		double sum = 0;
		for (int i = 0; i < input.size(); i++)
		{
			layers[0][i] = input[i];
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
					sum += layers[i - 1][k].get_output_val() * layers[i - 1][k].get_weight(j);
				}
				layers[i][j].set_output_val(sum);
			}
		}
	}
	else
		throw("Invalid input size");
}

