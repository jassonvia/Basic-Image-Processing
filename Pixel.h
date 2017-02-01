//Karen Wang
//wangkh@usc.edu
//Sept 18 2016

#ifndef Pixel_h
#define Pixel_h
/* This struct holds 3 properties of a pixel- 1) x & y position, 
2) grayscale intensity and 3) Priority (whether the pixel has been accessed/altered previously)
*/


struct Pixel{
    int row;
    int col;
    int intensity;
    int priority;
    
    Pixel(){}
    
    Pixel(int x,int y,int InputIntensity)
    {
        row=x;
        col=y;
        intensity=InputIntensity;
        priority=0;
    }
    
    int getRow()
    {
        return row;
    }
    
    int getCol()
    {
        return col;
    }
    
    int getIntensity()
    {
        return intensity;
    }
    
    int getPriority()
    {
        return priority;
    }
    
    void setRow(int inputRow)
    {
        row=inputRow;
    }
    
    void setCol(int inputCol)
    {
        col=inputCol;
    }
    
    void setIntensity(int inputIntensity)
    {
        intensity=inputIntensity;
    }
    
    void setPriority(int inputPriority)
    {
        priority=inputPriority;
    }
    
    
};//class pixel

#endif /* Pixel_h */
