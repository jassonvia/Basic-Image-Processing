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
    
    // Check for proper syntax
    if (argc < 3){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name [input_image.raw] [output_image.raw] [BytesPerPixel] [Width] [Height]" << endl;
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
    
    int newWidth;
    int newHeight;
    
    if (argc<6) {
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel] [InputImageWidth] [InputImageHeight]" << endl;
        exit(1);
    }
    
    //------------------ Output to Command Line--------------------//
    //User inputs:
    cout<<"User Inputs:"<<endl;
    //cout<<argv[0]<<endl;
    cout<<"Input filename: "<<argv[1]<<endl;
    cout<<"Output filename: "<<argv[2]<<endl;
    cout<<"Bytes Per Pixel: "<<argv[3]<<endl;
    cout<<"Input Image Width: "<<argv[4]<<endl;
    cout<<"Input Image Height: "<<argv[5]<<endl;
    newHeight=SizeHeight;
    newWidth=SizeWidth;
    

   //------------------ Histogram Equalization Algorithim --------------------//
    //Initialization of Output Image:
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
    
    
    //Variable declaration:
    double intensityFreq[256]={0};
    int pixelCount=SizeHeight*SizeWidth;
    double cmp=0.00;
    
    //Record Pixel Intensity frequencies
    for (int k=0; k<BytesPerPixel; k++) {
        for (int i=0; i<newHeight; i++) {
            for (int j=0; j<newWidth; j++) {
                intensityFreq[(int)Imagedata[i][j][k]]++;
            }
        }
        
        
        //Uncomment below to output Histogram data to commandline
        /*
        cout<<"Histogram Data:"<<endl;
        cout<<"[Pixel Intensity]: Frequency"<<endl;
        cout <<"\nTotal # of Pixels= "<< pixelCount << endl;
        cout<<"freq["<<i<<"]"<<intensityFreq[i]<<endl;
        */
        
        //CMP Calculation
        cout<<"BytePerPixel="<<k<<endl;
        for (int i=0; i<256; i++) {
            //Step2: convert freq to probability
            intensityFreq[i]= double(intensityFreq[i])/double(pixelCount);
            
            //Step3: convert individual probability to cumulative probability
            cmp+=intensityFreq[i];
            intensityFreq[i]=cmp;
            
            //Step4: multiply by range 0-255, then take floor values:
            intensityFreq[i]=int(intensityFreq[i]*256.0);
            
        }
        
        //Write to output
        for (int i=0; i<newHeight; i++) {
            for (int j=0; j<newWidth; j++) {
                //Convert via mapping
                tempImage[i][j][k]=char(intensityFreq[int(Imagedata[i][j][k])]);
            }
        }
        
        
        //Reinitalize crucial veriables
        cmp=0.00;
        for (int a=0; a<255; a++) {
            intensityFreq[a]=0;
        }
    }

    

    //------------------ Output to Command Line --------------------//
    //New image specs:
    cout<<"\nNew Image Specifications:"<<endl;
    cout << "newWidth= "<<newWidth<<endl;
    cout << "newHeight= "<<newHeight<<endl;
    
    
    
    //------------------ Output to Image --------------------//
    // Write image data (filename specified by second argument) from image data matrix
    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(tempImage, sizeof(unsigned char),  newHeight*newWidth*BytesPerPixel, file);
    fclose(file);
    
    return 0;
}
