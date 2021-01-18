#ifndef NETWORK
#define NETWORK
#include"Neuron.h"
#include<vector>
#include<iostream>
using namespace std;

class Network
{
	vector<vector<Neuron>> layers;
	double learning_rate;
	int epoch_lim;
public:
	Network(vector<int> layers);  // Every index represents layer and value represents total number of neurons in that layer
	void forward_feed(const vector<double> &input, bool a, int y=-1);
	void back_propagation(const vector<double> &expected);
	void printOutput();
	double derivative(double value);
	double activation(double value);
	double calculate_error(vector<double>& expected);
};


#endif // !NETWORK
