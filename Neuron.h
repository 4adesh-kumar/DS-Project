#ifndef NEURON
#define NEURON
#include<vector>
#include<iostream>
#include<cstdlib>
using namespace std;

class Neuron
{
	vector<double> weights;                    // Weight from one node to next layer's node
	double output_val;
	double bias;
	double activation;
public:
	Neuron(int prev_layer_neurons=0);
	static double get_random_weight();
	double get_output_val();
	double get_weight(int index);
	void set_output_val(double output_val);
	friend class Network;
};


#endif // !NEURON
