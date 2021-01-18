#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Data
{
    vector<bool>image;
    int label;
    public:
    void append_image(uint8_t d)
    {
        if (d == 0)
        {
            image.push_back(0);
        }
        else
        {
            image.push_back(1);
        }
        
    }
    void set_label(int32_t l)
    {
        label=l;
    }
    vector<bool>& get_image() {
        return image;
    }
    uint8_t get_label()
    {
        return label;
    }
    void display()
    {
        for(int i = 0; i < image.size(); ++i)
        {
            if(i%28 == 0 && i > 0) cout << "\n";
            cout << image[i];
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
    uint32_t num=0, key=0, rows=0, cols=0; //32 bits data
     ifstream file;
     file.open("train-images.idx3-ubyte", ios::binary);
    unsigned char bytes[4];
    int i=0;
    while(i<4)
    {
        if(file.read((char*)bytes,sizeof(bytes))) //reading 32 bits
        {
            if(i==0)
            {
                key=format(bytes); //format will convert 32 bits to little endian order
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
            file.read((char*)elem,sizeof(elem));   
            d->append_image(elem[0]);            
        }
        imageData.push_back(d);
        d=0;
    }


    file.close();
    printf("Successfully read image data: ");
    cout<<imageData.size()<<"\n";

}

    //ReadLabelInput will read label for each image and store it in uint8_t label in Data
 void ReadLabelInput()
 {
     uint32_t num, key; //32 bits data
     ifstream file;
    file.open("train-labels.idx1-ubyte", ios::binary);
    unsigned char bytes[4];
    int i=0;
    while(i<2)
    {
        if(file.read((char*)bytes,sizeof(bytes))) //reading 32 bits
        {
            if(i==0)
                key=format(bytes); //format will convert 32 bits to little endian order
            else if(i==1)
                num=format(bytes);
            
            i++;
        }

    }
    //reading data of each image byte by byte and pushing it in imageData
    for(int j=0; j<num;j++)
    {
        uint8_t elem[1];
        if(file.read((char*)elem,sizeof(elem))) {
            imageData[j]->set_label((int32_t)elem[0]);
        }
    }
   
    file.close();
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
