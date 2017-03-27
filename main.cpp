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
int transBMP(double dt,double ds,double mt,double ms,double p);
void Image_color(BMP s,BMP t, const char *OutputName);
int main(int argc, char** argv)
{
	BMP s1,s2,s3,s4;
    BMP t1,t2,t3,t4;
    
    s1.ReadFromFile("s1.bmp"); 
    s2.ReadFromFile("s2.bmp");
    s3.ReadFromFile("s3.bmp");
    s4.ReadFromFile("s4.bmp");
    t1.ReadFromFile("t1.bmp");
    t2.ReadFromFile("t2.bmp");
    t3.ReadFromFile("t3.bmp");
    t4.ReadFromFile("t4.bmp");
    
    Image_color(s1,t1,"r1.bmp");
    Image_color(s2,t2,"r2.bmp");
    Image_color(s3,t3,"r3.bmp");
    Image_color(s4,t4,"r4.bmp");
    
	return 0;
}
int transBMP(double dt,double ds,double mt,double ms,double p){
    return dt/ds*(p-ms)+mt;
}
void Image_color(BMP s,BMP t, const char *OutputName)
{
    BMP Output;
    Output.SetSize(s.TellWidth() ,s.TellHeight());
    Output.SetBitDepth(24);

    for(int i=0; i<s.TellHeight(); i++)
    {
        for(int j=0; j<s.TellWidth(); j++)
        {
            RGBApixel NewPixel = s.GetPixel(i, j);  //讀取單一個像素結構。P.S.也可以自行改成先讀取成(R,G,B)陣列後，再做應用。 

            //----------------------------在這部分做像素的修改--------------------------------//
            NewPixel.Red = transBMP(redSD(t),redSD(s),redMean(t),redMean(s),);
            NewPixel.Green = transBMP(greenSD(t),greenSD(s),greenMean(t),greenMean(s),);
            NewPixel.Blue = transBMP(blueSD(t),blueSD(s),blueMean(t),blueMean(s),);
            //----------------------------修改影像結束--------------------------------//

            Output.SetPixel(i, j, NewPixel);  //儲存單一個像素結構
        }
    }
    Output.WriteToFile(OutputName);  //儲存的圖檔名字
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

