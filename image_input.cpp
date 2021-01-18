#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Data
{
    vector<uint8_t>image;
    int label;
    public:
    void append_image(uint8_t d)
    {
        image.push_back(d);
    }
    void set_label(int32_t l)
    {
        label=l;
    }
    uint8_t get_label()
    {
        return label;
    }
    void display()
    {
        for(int i=0; i<784; ++i) {
            if(i%28 == 0 && i) cout<<"\n";
            cout << (image[i]!=0);
        }
        cout << "\n";
        cout << "Label: " << label << "\n";
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
        d=0;
    }


    icin.close();
    printf("Successfully read image data: ");
    cout<<imageData.size()<<"\n";

    
    //printing images data
    // for(int i=0; i<num; i++)
    // { 
    //  cout << i << "\n";
    //     imageData[i]->display();
    //     printf("\n");
    // }
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
        if(icin.read((char*)elem,sizeof(elem))) {
            imageData[j]->set_label((int32_t)elem[0]);
        }
    }
   
    icin.close();
    printf("Successfully read image labels: ");
    cout << imageData.size() << "\n";
 }


int main() {
	int choice;
	while(true){
		cout<<"1. Train data \n\n2. Store weights in file\n\n3. Recognize the digit\n\n0. Exit\n\nselect : ";
		cin>>choice;
		if(choice==0)
		break;
		
	}
    ReadImageInput();
    ReadLabelInput();
    for(int i=0; i<imageData.size(); ++i) {
        imageData[i]->display();
        cout << "\n";
    }
    return 0;
}
