#include <iostream>
#include"Network.h"
#include <vector>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>


using namespace cv;
using namespace std;

void findDigit(string path,Network Net)
{
	Mat img;
	img = imread(path);
	img.convertTo(img, CV_32F);
	vector<float> imgMat;
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			imgMat.push_back(img.at<float>(i, j));
		}
	}

	// Net.predict(imgMat);              Net is object of trained neural network it will print the output of image
}

int main()
{
	vector<int> t;
	t.push_back(28 * 28);  // Input layer
	t.push_back(7);       // Hidden layer
	t.push_back(7);
	t.push_back(10);      // output layer
	Network net(t);
	string path = "nine.png";
	int ch;
	while (true) {
		cout << "1. find digit in image\n\n2. Train neural network \n\n3. Save neural network in file\n\n4. Get Trained Neural network from file\n\n0. Exit \n\n select : ";
		cin >> ch;
		if (ch == 1) {
			findDigit(path,net);
		}
		else if (ch == 2) {
			// net.train();
		}
		else if (ch == 3) {
			//net.saveThis();                            // Save this function will save/Write the object in file
		}
		else if(ch==4){
		   net.getTrainedNetwork();   
		}
		else if (ch == 0)
			break;
	}
}
