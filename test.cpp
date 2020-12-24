#include <fstream>
#include <iostream>
#include<vector>
using namespace std;

//const int MAXN = 6e4 + 7;
//unsigned int image[MAXN][28][28];
//unsigned int label[MAXN];

class Data
{
    vector<uint8_t>image;
    uint8_t label;
    public:
    void append_image(uint8_t d)
    {
        image.push_back(d);
    }
    void set_label(uint8_t l)
    {
        label=l;
    }
    uint8_t get_label()
    {
        return label;
    }
};

uint32_t format(const unsigned char* bytes)
{
  return (uint32_t)((bytes[0] << 24) |
                    (bytes[1] << 16)  |
                    (bytes[2] << 8)   |
                    (bytes[3]));
}
vector<Data*>imageData;
Data *d = new Data;
void ReadImageInput()
{
    uint32_t num, magic, rows, cols; //32 bits data
    // ifstream *icin;
    FILE *icin=fopen("train-images.idx3-ubyte", "r");
    unsigned char bytes[4];
    int i=0;
    while(i<4)
    {
        if(fread(bytes,sizeof(bytes),1,icin)) //reading 32 bits
        {
            if(i==0)
                magic=format(bytes); //format will convert 32 bits to little endian order
            else if(i==1)
                num=format(bytes);
            else if(i==2)
                rows=format(bytes);
            else if(i==3)
                cols=format(bytes);
            i++;
        }

    }
    
    uint32_t imageSize=rows*cols;
    for(int i=0; i<num;i++)
    {
        uint8_t elem;
        for(int j=0; j<imageSize;j++)
        {
            if(fread(bytes,sizeof(bytes),1,icin))
            {
                d->append_image(elem);
            }
        }
        imageData.push_back(d);
    }
    printf("Successfully read image data: ");
    cout<<imageData.size()<<"\n";

}

    //ReadLabelInput will read label for each image and store it in uint8_t label in Data
 void ReadLabelInput()
 {
     uint32_t num, magic; //32 bits data
    // ifstream *icin;
    FILE *icin=fopen("train-labels.idx1-ubyte", "r");
    unsigned char bytes[4];
    int i=0;
    while(i<2)
    {
        if(fread(bytes,sizeof(bytes),1,icin)) //reading 32 bits
        {
            if(i==0)
                magic=format(bytes); //format will convert 32 bits to little endian order
            else if(i==1)
                num=format(bytes);
            
            i++;
        }

    }
    //reading data of each image byte by byte and pushing it in imageData
    for(int j=0; j<num;j++)
    {
        uint8_t elem[1];
            if(fread(elem,sizeof(elem),1,icin))
            {
                d->set_label(elem[0]);
            }
        
        imageData.push_back(d);
    }
    printf("Successfully read image labels: ");
    cout<<imageData.size()<<"\n";
 }

// unsigned int in(ifstream& file, unsigned int size) {
//     unsigned int ans = 0;
//     for (int i = 0; i < size; i++) {
//         unsigned char x;
//         file.read((char*)&x, 1);
//         unsigned int temp = x;
//         ans *= 256;
//         ans += temp;
//     }
//     return ans;
// }


int main() {
    ReadImageInput();
	ReadLabelInput();
    // ifstream icin;
    // icin.open("train-images.idx3-ubyte", ios::binary);
    // magic = in(icin, 4);
    // num = in(icin, 4);
    // rows = in(icin, 4);
    // cols = in(icin, 4);
    // for (int i = 0; i < num; i++) {
    //     for (int x = 0; x < rows; x++) {
    //         for (int y = 0; y < cols; y++) {
    //             image[i][x][y] = in(icin, 1);
    //             if(image[i][x][y] == 0) {
    //             	printf("-");
    //             } else {
    //             	printf("A");
    //             }
    //         }
    //         printf("\n");
    //     }
    //     printf("\n\n");
    // }
    // icin.close();
    // icin.open("train-labels.idx1-ubyte", ios::binary);
    // magic = in(icin, 4), num = in(icin, 4);
    // for (int i = 0; i < num; i++) {
    //     label[i] = in(icin, 1);
    // }
	return 0;
}