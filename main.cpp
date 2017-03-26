#include <iostream>
#include <fstream>  
#include <bitset>
#include <limits.h>
#include <cmath>
#include <iomanip>
#include "MyBMP.h"

using namespace std;
double redMean(BMP Img_In);
double greenMean(BMP Img_In);
double blueMean(BMP Img_In);
double redSD(BMP Img_In,double m);
double greenSD(BMP Img_In,double m);
double blueSD(BMP Img_In,double m);
string toBinary32( float inp_ );
int main(int argc, char** argv)
{
	char input[100];
	cin >> input;
	BMP Img[10];
    Img.ReadFromFile(input); 
    fstream fp;
    fp.open("416.txt",ios::out);
    fp <<fixed << setprecision(6) << redMean(Img) << endl;
    fp << toBinary32(redMean(Img)) << endl;
    fp <<fixed << setprecision(6) << greenMean(Img) << endl;
    fp << toBinary32(greenMean(Img)) << endl;
    fp <<fixed << setprecision(6) << blueMean(Img) << endl;
    fp << toBinary32(blueMean(Img)) << endl;    
    fp <<fixed << setprecision(6) << redSD(Img,redMean(Img)) << endl;
    fp << toBinary32(redSD(Img,redMean(Img))) << endl;
    fp <<fixed << setprecision(6) << greenSD(Img,greenMean(Img)) << endl;
    fp << toBinary32(greenSD(Img,greenMean(Img))) << endl;
    fp <<fixed << setprecision(6) << blueSD(Img,blueMean(Img)) << endl;
    fp << toBinary32(blueSD(Img,blueMean(Img))) << endl;
    
	return 0;
}
string toBinary32( float inp_ )
{
    union { 
        float input;
        int output;
    } data ;
    data.input = inp_;
    bitset<sizeof(float) * CHAR_BIT> bits(data.output); 
    return bits.to_string();
}
double redMean(BMP Img_In)
{
	int red = 0;
	double mean = 0.0;
	int pixel = Img_In.TellHeight()*Img_In.TellWidth();
    for(int i=0; i<Img_In.TellHeight(); i++)
    {
        for(int j=0; j<Img_In.TellWidth(); j++)
        {
            RGBApixel NewPixel = Img_In.GetPixel(i, j); 
			red += int(NewPixel.Red);
        }
    }
    mean = (double)red/(double)pixel;
    return mean;
}
double greenMean(BMP Img_In)
{
	int green = 0;
	double mean = 0.0;
	int pixel = Img_In.TellHeight()*Img_In.TellWidth();
    for(int i=0; i<Img_In.TellHeight(); i++)
    {
        for(int j=0; j<Img_In.TellWidth(); j++)
        {
            RGBApixel NewPixel = Img_In.GetPixel(i, j); 
			green += int(NewPixel.Green);
        }
    }
    mean = (double)green/(double)pixel;
    return mean;
}
double blueMean(BMP Img_In)
{
	int blue = 0;
	double mean = 0.0;
	int pixel = Img_In.TellHeight()*Img_In.TellWidth();
    for(int i=0; i<Img_In.TellHeight(); i++)
    {
        for(int j=0; j<Img_In.TellWidth(); j++)
        {
            RGBApixel NewPixel = Img_In.GetPixel(i, j); 
			blue += int(NewPixel.Blue);
        }
    }
    mean = (double)blue/(double)pixel;
    return mean;
}
double redSD(BMP Img_In,double m){
	double sqsum = 0;
	int pixel = Img_In.TellHeight()*Img_In.TellWidth();
	for(int i=0; i<Img_In.TellHeight(); i++)
    {
        for(int j=0; j<Img_In.TellWidth(); j++)
        {
            RGBApixel NewPixel = Img_In.GetPixel(i, j); 
			double sq = (double(NewPixel.Red)-m)*(double(NewPixel.Red)-m);
			sqsum += sq;
        }
    }
    double sd = sqrt(sqsum / pixel);
    return sd;
}
double greenSD(BMP Img_In,double m){
	double sqsum = 0;
	int pixel = Img_In.TellHeight()*Img_In.TellWidth();
	for(int i=0; i<Img_In.TellHeight(); i++)
    {
        for(int j=0; j<Img_In.TellWidth(); j++)
        {
            RGBApixel NewPixel = Img_In.GetPixel(i, j); 
			double sq = (double(NewPixel.Green)-m)*(double(NewPixel.Green)-m);
			sqsum += sq;
        }
    }
    double sd = sqrt(sqsum / pixel);
    return sd;
}
double blueSD(BMP Img_In,double m){
	double sqsum = 0;
	int pixel = Img_In.TellHeight()*Img_In.TellWidth();
	for(int i=0; i<Img_In.TellHeight(); i++)
    {
        for(int j=0; j<Img_In.TellWidth(); j++)
        {
            RGBApixel NewPixel = Img_In.GetPixel(i, j); 
			double sq = (double(NewPixel.Blue)-m)*(double(NewPixel.Blue)-m);
			sqsum += sq;
        }
    }
    double sd = sqrt(sqsum / pixel);
    return sd;
}

