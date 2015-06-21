/******************************************************************************

   PROJECT:			CVDRIK1
   FILE:			func.h
   AUTHOR:			RAJUL GUPTA
   DATE:
   DESCRIPTION:		Header for Functions

******************************************************************************/

#ifndef __FUNC_H__
#define __FUNC_H__

/*************************** OTHER INCLUDE FILES *****************************/

// Include Standard C/C++ Header Files Here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Include OpenCV Header Files Here
#include <cv.h>
#include <highgui.h>
#include <cvaux.h>
#include <cxcore.h>

// Include CVDRIK Header Files Here
#include "../CVDRIKMultiChannelImage/CVDRIKMultiChannelImage.h"


/*****************************************************************************/



/******************************************************************************

					FUNCTIONS

******************************************************************************/

// Function for Constructing the Image Name for Frame Number Indexed Images
// Inputs :-
//			(char*) imgPath : The Image Path
//			(char*) imgBaseName : The Image Base Name
//			(int) imgIndx : The Image Index
//			(char*) imgFormat : The Image Format
//			(int) zeroPaddingFormatSize : The Size of the Zero Padding
//			NOTE: This is Required to Zero Pad the Index e.g. f_9 becomes f_0009
//			NOTE: For a Zero Padding Size of 4
//			(int) maxZeroPaddingImgIndx : The Maximum Image Index for Zero Padding
//			(char*) imgName : The Image Name
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = constructImageName( imgPath , imgBaseName , imgIndx , imgFormat , zeroPaddingFormatSize , maxZeroPaddingImgIndx , imgName );


// Function for Genarating Negative of Image
unsigned char getNegImage( IplImage* img , IplImage* negimg );

#endif
