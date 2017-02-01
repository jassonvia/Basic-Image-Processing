//Karen Wang
//wangkh@usc.edu
//Sept 18 2016

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])

{
    //------------------ Command Line Input --------------------//
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;//greyscale or RGB
    int SizeWidth = 256; //default width
    int SizeHeight= 256; //default height
    int newWidth;
    int newHeight;
    
    // Check for proper syntax
    if (argc < 3){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 250x300]" << endl;
        return 0;
    }
    
    // Check if image is grayscale or color
    if (argc < 4){
        BytesPerPixel = 1; // default is grey image
    }
    else {
        BytesPerPixel = atoi(argv[3]);
        // Check if size is specified
        if (argc >= 5){
            SizeWidth = atoi(argv[4]);
            SizeHeight= atoi(argv[5]);
        }
    }
    
    // Allocate original image data array
    unsigned char Imagedata[SizeHeight][SizeWidth][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), SizeHeight*SizeWidth*BytesPerPixel, file);
    fclose(file);
    
    if (argc<8) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel] [InputImageWidth] [InputImageHeight] [ResizeWidth] [ResizeHeight]" << endl;
        exit(1);
    }
    else
    {
        newWidth = atoi(argv[6]);
        newHeight = atoi(argv[7]);
    }
    
    
    //------------------ Output to Command Line--------------------//
    //outputs user inputs to command line
    cout<<"User Inputs:"<<endl;
    //cout<<argv[0]<<endl;
    cout<<"Input filename: "<<argv[1]<<endl;
    cout<<"Output filename: "<<argv[2]<<endl;
    cout<<"Bytes Per Pixel: "<<argv[3]<<endl;
    cout<<"Input Image Width: "<<argv[4]<<endl;
    cout<<"Input Image Height: "<<argv[5]<<endl;
    cout<<"Desired Resize Width: "<<argv[6]<<endl;
    cout<<"Desired Resize Height: "<<argv[7]<<endl;
    
    //------------------ Resize Algorithim --------------------//

    //Initialize Output Image Array
    unsigned char tempImage[newHeight][newWidth][BytesPerPixel];
    for (int i=0; i<newHeight; i++) {
        for(int j=0; j<newWidth; j++)
        {
            for (int k=0; k<BytesPerPixel; k++)
            {
                tempImage[i][j][k]=0;
            }
        }
    }
    
    
    //Define Resize Variables
    float widthRatio = (float)SizeWidth/(float)newWidth;
    float heightRatio= (float)SizeHeight/(float)newHeight;
    int topleft, topright, bottomleft, bottomright,result;
    float i_r, j_r;
    float i_d, j_d;

    
    for (int i=1; i<newHeight-1; i++) {
        i_r = heightRatio*i; //modified small i/height
        i_d = i_r-floor(i_r);//delta i or variable b in dis. slides
        
        for (int j=1; j<newWidth-1; j++) {
            j_r=widthRatio*j; //modified small j/width
            j_d=j_r-floor(j_r);//delta j or variable a in dis. slides

            
            for (int k=0; k<BytesPerPixel; k++) {
                //Get RGB values from 4 neighboring points:
                topleft=(int)Imagedata[(int)floor(i_r)][(int)floor(j_r)][k];
                topright=(int)Imagedata[(int)floor(i_r)][(int)floor(j_r)+1][k];
                bottomleft=(int)Imagedata[(int)floor(i_r)+1][(int)floor(j_r)][k];
                bottomright=(int)Imagedata[(int)floor(i_r)+1][(int)floor(j_r)+1][k];
                
                //Bilinear Interpolation:
                result =(1-i_d)*((1-j_d)*topleft+(j_d)*topright)+i_d*((1-j_d)*bottomleft+(j_d)*bottomright);
                tempImage[i][j][k]=(char)result;
            }
        }
    }
    
    //------------------ Output to Command Line --------------------//
    //New image specs:
    cout<<"\nNew Image Specifications:"<<endl;
    cout << "newWidth= "<<newWidth<<endl;
    cout << "newHeight= "<<newHeight<<endl;
    
    //------------------ Output to New Image --------------------//
    // Write image data (filename specified by second argument) from image data matrix
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(tempImage, sizeof(unsigned char),  newHeight*newWidth*BytesPerPixel, file);
    fclose(file);
    
    return 0;
}
