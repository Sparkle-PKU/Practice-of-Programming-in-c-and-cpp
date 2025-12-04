#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;
#pragma pack(1)
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;
typedef unsigned char BYTE;

class BITMAPFILEHEADER
{
public:
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
};

class BITMAPINFOHEADER
{
public:
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
};

class Pixel
{
public:
    BYTE blue;
    BYTE green;
    BYTE red;
};

int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        cerr<<"Invalid Input!"<<endl;
        exit(EXIT_FAILURE);
    }
    string in_name=argv[1];
    string out_name=argv[2];
    ifstream file_in(in_name,ios::binary);
    ofstream file_out(out_name,ios::binary);
    if((!file_in)||(!file_out))
    {
        cerr<<"Cannot Open File!"<<endl;
        exit(EXIT_FAILURE);
    }
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    file_in.read(reinterpret_cast<char*>(&fileHeader),sizeof(fileHeader));
    file_in.read(reinterpret_cast<char*>(&infoHeader),sizeof(infoHeader));
    if(fileHeader.bfType!=0x4D42||infoHeader.biBitCount!=24||infoHeader.biCompression)//仅支持24位、不压缩的图像
    {
        cerr<<"Unsupported Format!"<<endl;
        exit(EXIT_FAILURE);
    }
    int width=infoHeader.biWidth;
    int height=infoHeader.biHeight;
    //由于每一行总pixel必须是4倍数，故需要padding
    int padding=((width*3+3)/4)*4-width*3;
    vector<vector<Pixel> >src(height,vector<Pixel>(width));
    //小心！应该从底下开始读
    for(int i=height-1;i>=0;i--)
    {
        for(int j=0;j<width;j++)
        {
            Pixel p;
            file_in.read(reinterpret_cast<char*>(&p),sizeof(Pixel));
            src[i][j]=p;
        }
        file_in.ignore(padding);//跳过需要padding的字节
    }
    //行列互换，注意大小也要互换
    vector<vector<Pixel> >rotated(width,vector<Pixel>(height));
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            rotated[j][height-1-i]=src[i][j];
        }
    }
    int new_padding=((height*3+3)/4)*4-height*3;
    infoHeader.biWidth=height;
    infoHeader.biHeight=width;
    infoHeader.biSizeImage=(((height*3+3)/4)*4)*width;
    fileHeader.bfSize=sizeof(fileHeader)+sizeof(infoHeader)+infoHeader.biSizeImage;
    file_out.write(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file_out.write(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    BYTE zero[3]={0};
    for(int i=width-1;i>=0;i--)
    {
        for(int j=0;j<height;j++)
        {
            file_out.write(reinterpret_cast<char*>(&rotated[i][j]),sizeof(Pixel));
        }
        file_out.write(reinterpret_cast<char*>(zero),new_padding);
    }
    file_in.close();
    file_out.close();
    return 0;
}   