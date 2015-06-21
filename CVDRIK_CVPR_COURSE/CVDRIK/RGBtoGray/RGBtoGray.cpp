/*********************************************************************************

   PROJECT:			CVDRIK1
   FILE:			RGBtoGray.cpp
   AUTHOR:			ABHRA GHOSH
   DATE:
   DESCRIPTION:		CPP File for RGBtoGray Function

*********************************************************************************/


/*************************** OTHER INCLUDE FILES *****************************/

#include "RGBtoGray.h"

/*****************************************************************************/


/******************************************************************************

                                FUNCTIONS

******************************************************************************/

// Function for Constructing a Gray-scale image from a RGB image
// Inputs :-
//			IplImage* RGBImage
//		    IplImage* GRAYImage
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = constructGrayscale( RGBImage ,GRAYImage);
unsigned char constructGrayscale(IplImage* RGBImage ,IplImage* GRAYImage)
{ if (RGBImage->nChannels != 3)
    {  
      // Error Code 1 : Invalid Inputs
	  return( 1 );
    }
  
  int a = 0;//RGBImage->widthStep index
  int c = 0;//GRAYImage->widthStep index
  for (int i = 0; i < RGBImage->height; ++i)
  {  
    
    for (int j = 0 ,k = 0 ; j < RGBImage->widthStep; j+=3 )
    { 
     //taking average of all the three pixcel value to get grayscale
     GRAYImage->imageData[ c + k ] = (unsigned char)( ( (unsigned char)RGBImage->imageData[ a + j ] + (unsigned char)RGBImage->imageData[ a + j + 1 ] + (unsigned char)RGBImage->imageData[ a + j + 2 ] )*0.33 );
     

     k++;//k is the index for GRAYImage having one channel
    
    }

    a = a + RGBImage->widthStep; 
    c = c + GRAYImage->widthStep;
  }


return ( 0 );

}



