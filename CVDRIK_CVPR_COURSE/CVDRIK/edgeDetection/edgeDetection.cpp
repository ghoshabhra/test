/*********************************************************************************

   PROJECT:			CVDRIK1
   FILE:			edgeDetection.cpp
   AUTHOR:			ABHRA GHOSH
   DATE:
   DESCRIPTION:		CPP File for edgeDetection Function

*********************************************************************************/


/*************************** OTHER INCLUDE FILES *****************************/

#include "edgeDetection.h"

/*****************************************************************************/


/******************************************************************************

                                FUNCTIONS

******************************************************************************/

/// Function for Constructing a Gray-scale image from a RGB image
// Inputs :-
//			IplImage* GRAYImage
//		    IplImage* edgeImage
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = edgeDetection( GRAYImage ,edgeImage);

unsigned char edgeDetection(IplImage* GRAYImage ,IplImage* edgeImage)
{   int derivative_X = 0;
	int derivative_Y = 0;
	int derivative_mag = 0;
	int threshold = 0;

	for (int i = 0; i < GRAYImage->imageSize; ++i)
	{
		if ( !(i%GRAYImage->widthStep) || !((i+1)%GRAYImage->widthStep) )
		{
			derivative_X = 0;
			derivative_Y = ((unsigned char)GRAYImage->imageData[i + GRAYImage->widthStep] - (unsigned char)GRAYImage->imageData[i - GRAYImage->widthStep])*0.5;
		}

        else if (i < GRAYImage->widthStep || i > ((GRAYImage->height - 1)*GRAYImage->widthStep) )
        {
        	derivative_X = ((unsigned char)GRAYImage->imageData[i + 1] - (unsigned char)GRAYImage->imageData[i - 1])*0.5;
        	derivative_Y = 0;
        }

        else
        {
        	derivative_X = ((unsigned char)GRAYImage->imageData[i + 1] - (unsigned char)GRAYImage->imageData[i - 1])*0.5;
        	derivative_Y = ((unsigned char)GRAYImage->imageData[i + GRAYImage->widthStep] - (unsigned char)GRAYImage->imageData[i - GRAYImage->widthStep])*0.5;
        }

        derivative_mag =  sqrt( pow(derivative_X ,2) + pow(derivative_Y ,2) );

        edgeImage->imageData[i]   =  (unsigned char)(derivative_mag);

        threshold      =  threshold + derivative_mag;
	}


	threshold = threshold/GRAYImage->imageSize;

	edgeImage->imageData[0]                                             = ( 0 );
	edgeImage->imageData[GRAYImage->widthStep - 1]                      = ( 0 );
    edgeImage->imageData[(GRAYImage->height - 1)*GRAYImage->widthStep ] = ( 0 );
    edgeImage->imageData[GRAYImage->imageSize - 1]                      = ( 0 );
    
    for (int i = 0; i < GRAYImage->imageSize; ++i)
    {
    	if (edgeImage->imageData[i] >= 2*(unsigned char)threshold)
    	{
    		edgeImage->imageData[i] = 255;
    	}

    	else
    	{
    		edgeImage->imageData[i] = 0;
    	}
    }

    return ( 0 );

}


















	//(i - 1) < 0 || (i + 1) >= GRAYImage->imageSize || 