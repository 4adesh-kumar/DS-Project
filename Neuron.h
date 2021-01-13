#ifndef NEURON
#define NEURON
#include<vector>
#include<iostream>
#include<cstdlib>
using namespace std;

class Neuron
{
	vector<double> weight;                    // Weight from one node to next layer's node
	vector<double> change_in_weight;
	double output_val;
public:
	Neuron(int prev_layer_neurons=0);
	static double get_random_weight();
	double get_output_val();
	double get_weight(int index);
	void set_output_val(double output_val);
};


#endif // !NEURON



