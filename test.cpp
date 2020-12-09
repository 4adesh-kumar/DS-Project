#include <fstream>
#include <iostream>
using namespace std;

const int MAXN = 6e4 + 7;
unsigned int image[MAXN][28][28];
unsigned int num, magic, rows, cols;
unsigned int label[MAXN];

unsigned int in(ifstream& file, unsigned int size) {
    unsigned int ans = 0;
    for (int i = 0; i < size; i++) {
        unsigned char x;
        file.read((char*)&x, 1);
        unsigned int temp = x;
        ans *= 256;
        ans += temp;
    }
    return ans;
}

int main() {
	ifstream icin;
    icin.open("train-images.idx3-ubyte", ios::binary);
    magic = in(icin, 4);
    num = in(icin, 4);
    rows = in(icin, 4);
    cols = in(icin, 4);
    for (int i = 0; i < num; i++) {
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                image[i][x][y] = in(icin, 1);
                if(image[i][x][y] == 0) {
                	printf("-");
                } else {
                	printf("A");
                }
            }
            printf("\n");
        }
        printf("\n\n");
    }
    icin.close();
    icin.open("train-labels.idx1-ubyte", ios::binary);
    magic = in(icin, 4), num = in(icin, 4);
    for (int i = 0; i < num; i++) {
        label[i] = in(icin, 1);
    }
	return 0;
}