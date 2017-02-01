# Basic-Image-Processing
Summary: Sample codes to crop, resize, auto-enhance contrast and manipulate histogram of input image

Input image: .RAW format

Programs: 
1) cropping.cpp - Crops input image according to user-defined dimensions
2) resize.cpp - Resize (shrink or enlarge) input image according to user-defined dimensions. 
Note: resize.cpp uses bilinear interpolation for image enlargment.
3) Contrast_enhence.cpp - Uses cumulative probability to equalize intensities across histogram. 
Note: Contrast_enhence.cpp supports grayscale and RGB histogram equalization. 
4) gaussian_transform.cpp + Pixel.h - Redistributes grayscale intensities such that the histogram has a Gaussian distribution.
