#ifndef NETWORK
#define NETWORK
#include"Neuron.h"
#include<vector>
#include<iostream>
using namespace std;

class Network
{
	vector<vector<Neuron>> layers;    
public:
	Network(vector<int> layers);  // Every index represents layer and value represents total number of neurons in that layer
	void set_output_values(const vector<double> &input);
	void printOutput();
	double derivative_of_activation_function(double value);
};


#endif // !NETWORK


