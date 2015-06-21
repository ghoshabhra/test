/******************************************************************************

   PROJECT:			CVDRIK1
   FILE:			RGBtoGray.h
   AUTHOR:			ABHRA GHOSH
   DATE:
   DESCRIPTION:		Header for RGBtoGray Function

******************************************************************************/

#ifndef __RGBTOGRAY_H__
#define __RGBTOGRAY_H__

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
//#include "../CVDRIKMultiChannelImage/CVDRIKMultiChannelImage.h"
//#include "../CVDRIKMisc/CVDRIKMisc.h"

/*****************************************************************************/



/******************************************************************************

					RGBtoGray FUNCTION

******************************************************************************/

// Function for Constructing a Gray-scale image from a RGB image
// Inputs :-
//			IplImage* RGBImage
//		    IplImage* GRAYImage
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = constructGrayscale( RGBImage ,GRAYImage);
unsigned char constructGrayscale(IplImage* RGBImage ,IplImage* GRAYImage);
#endif