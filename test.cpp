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
    void display()
    {
        for(auto i : image)
        {
            printf("%u",i);
        }
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

void ReadImageInput()
{
    uint32_t num=0, magic=0, rows=0, cols=0; //32 bits data
     ifstream icin;
     icin.open("train-images.idx3-ubyte", ios::binary);
    unsigned char bytes[4];
    int i=0;
    while(i<4)
    {
        if(icin.read((char*)bytes,sizeof(bytes))) //reading 32 bits
        {
            if(i==0)
            {
                magic=format(bytes); //format will convert 32 bits to little endian order
                i++;
            }
            else if(i==1)
            {
                num=format(bytes);
                i++;
            }
            else if(i==2)
            {
                rows=format(bytes);
                i++;
            }
            else if(i==3)
            {
                cols=format(bytes);
                i++;
            }
        }

    }
    
    uint32_t imageSize=rows*cols;
    Data *d =0;
    for(int i=0; i<num;i++)
    {
        uint8_t elem[1];
        d = new Data();
        for(int j=0; j<imageSize;j++)
        {
            icin.read((char*)elem,sizeof(elem));   
            d->append_image(elem[0]);            
        }
        imageData.push_back(d);
     
        //d->display();
        //cout<<"\n";
        d=0;
    }

    printf("Successfully read image data: ");
    cout<<imageData.size()<<"\n";

    
    //printing images data
    for(int i=0; i<num; i++)
    { 
        imageData[i]->display();
        printf("\n");
    }


    
}

    //ReadLabelInput will read label for each image and store it in uint8_t label in Data
 void ReadLabelInput()
 {
     uint32_t num, magic; //32 bits data
     ifstream icin;
    icin.open("train-labels.idx1-ubyte", ios::binary);
    unsigned char bytes[4];
    int i=0;
    while(i<2)
    {
        if(icin.read((char*)bytes,sizeof(bytes))) //reading 32 bits
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
        //Data* d;
        //d=imageData[i];
            if(icin.read((char*)elem,sizeof(elem)))
            {
                imageData[i]->set_label(elem[0]);
            }
        
        //imageData.push_back(d);
        cout<<"\n";
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
	//ReadLabelInput();
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