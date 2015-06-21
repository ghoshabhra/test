/*********************************************************************************/

   PROJECT:			CVDRIK1

#include "func.h"

#define EPSILON 0.0001
#define PI 3.141593

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


// Function for Generating Negative of Image
unsigned char getNegImage( IplImage* img , IplImage* negimg )
{
	int i,j ;
	//Iplimage* negimg;
	//int imgWidth = img->width ;
	//int imgHeight = img->height ;
	
	/*unsigned char *N_Im , *Im ;
	N_Im = (unsigned char*) negimg->imageData ;
	Im =  (unsigned char*) img->imgData ;
*/
	int a = -negimg->widthStep;
	//int b = -img->widthStep ;

	for( i=0; i<(img->height) ; i++)
	{
		a += negimg->widthStep ;
		//b += img->widthStep ;
	for( j=0 ; j<img->widthStep ; j+=3)
	{
             //negimg->imagedata[i]=255-(img->imageData[i])
		negimg->imageData[a+j]     = 255 - img->imageData[a+j];
		negimg->imageData[a+j+1]   = 255 - img->imageData[a+j+1];
		negimg->imageData[a+j+2]   = 255 - img->imageData[a+j+2];
	}
	}
	return (0);
}

