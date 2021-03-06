// Purpose : Reading and Displaying Color Image Sequence

// Include Standard C/C++ Header Files Here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Include OpenCV Header Files Here
#include <cv.h>
#include <highgui.h>
#include <cvaux.h>
#include <cxcore.h>

// Include CVDRIK Header Files Here
#include "../../CVDRIK/CVDRIKMisc/CVDRIKMisc.h"
#include "../../CVDRIK/CVDRIKMultiChannelImage/CVDRIKMultiChannelImage.h"

// The Main Code
int main( int argc , char** argv )
{
	// Check Usage
	if( argc != 2 )
	{
		// Show Purpose
		printf( "\n\n Purpose : Reading and Displaying Color Image Sequence \n\n" );
		
		// Show Usage
		printf( "\n\n Usage As : imageReadingAndDisplay <videoName>_ImageReadingAndDisplay.txt \n\n" );
		
		// Show Sample Command Line
		printf( "\n\n Sample Command Line : ./imageReadingAndDisplay PETS2000_ImageReadingAndDisplay.txt \n\n" );
		
		return( 0 );
	}
	
	// Opening the Parameter File for Reading
	FILE* fp;
	fp = fopen( argv[1] , "r" );

	//fp = fopen( "info.txt" , "r" );
	
	//checkPoint( 1 );
	
	// Reading the Parameter File : Image File Information
	char paramNameString[100] , eqString[3] , headerString[100];
	fscanf( fp , "%s" , headerString );
	char inpImgPath[100];
	fscanf( fp , "%s%s%s" , paramNameString , eqString , inpImgPath );
	char inpImgBaseName[100];
	fscanf( fp , "%s%s%s" , paramNameString , eqString , inpImgBaseName );
	char inpImgFormat[5];
	fscanf( fp , "%s%s%s" , paramNameString , eqString , inpImgFormat );
	int imgStartNum;
	fscanf( fp , "%s%s%d" , paramNameString , eqString , &imgStartNum );
	int imgEndNum;
	fscanf( fp , "%s%s%d" , paramNameString , eqString , &imgEndNum );
	int zeroPaddingFormatSize;
	fscanf( fp , "%s%s%d" , paramNameString , eqString , &zeroPaddingFormatSize );
	int maxZeroPaddingImgIndx;
	fscanf( fp , "%s%s%d" , paramNameString , eqString , &maxZeroPaddingImgIndx );
		
	// Closing Parameter File
	fclose( fp );
     
    //DEBUGGING
    printf("%s\n", inpImgPath);
    printf("%s\n", inpImgBaseName);
    printf("%s\n", inpImgFormat);
    printf("%d\n", imgStartNum);
    printf("%d\n", imgEndNum);
    printf("%d\n", zeroPaddingFormatSize);
    printf("%d\n", maxZeroPaddingImgIndx);
    

	
	// Load the First Image as Previous RGB Image
	// This also helps in acquiring Image Dimensions
	// Which is Used Next to Decide the Window Sizes
	char imgName[500];
	constructImageName( inpImgPath , inpImgBaseName , imgStartNum , inpImgFormat , zeroPaddingFormatSize , maxZeroPaddingImgIndx , imgName);
	IplImage* img = 0x00;
	IplImage* negImg = 0x00;
    
    printf("%s\n", imgName);

	img = cvLoadImage( imgName );
	negImg = cvLoadImage ( imgName );
	


	int width = img->width;
	int height = img->height;
	cvReleaseImage( &img );
	//negImg = cvCreateImage( cvSize( width , height), IPL_DEPTH_8U , 3);
	// Create the Windows for Displaying Images
	cvNamedWindow( "frameData" , CV_WINDOW_AUTOSIZE );
	cvResizeWindow( "frameData" , width , height );
	
	for( int imgCount = imgStartNum ; imgCount <= imgEndNum ; ++imgCount )
	{
		// Show Frame Number
		printf( "\n\n************************************" );
		printf( "\n\n Reading Frame %d / %d \n\n" , imgCount , imgEndNum );
		
		// Prepare the Input Image Name
		constructImageName( inpImgPath , inpImgBaseName , imgCount , inpImgFormat , zeroPaddingFormatSize , maxZeroPaddingImgIndx , imgName );
		
		// Read the Current Frame
		IplImage* frameData = 0x00;
		frameData = cvLoadImage( imgName );
		if( !frameData )
		{
    		// Continue to Next Image
			printf( "\n\n Can not read frame number %d \n\n" , imgCount );
			continue;
		}
		//IplImage* negImg = 0x00;
		//negImg = cvLoadImage ( imgName );
		// Negative of Image
		//getNegImage( frameData , negImg );

	    int a = -negImg->widthStep;

	    for(int i=0; i<(frameData->height) ; i++)
	    {
		   a += negImg->widthStep ;
		  //b += img->widthStep ;
	      for(int j=0 ; j<frameData->widthStep ; j+=3)
	      {
             //negimg->imagedata[i]=255-(img->imageData[i])
		       negImg->imageData[a+j]     = 255 - frameData->imageData[a+j];
		       negImg->imageData[a+j+1]   = 255 - frameData->imageData[a+j+1];
		       negImg->imageData[a+j+2]   = 255 - frameData->imageData[a+j+2];
	      }
	    }

		// Showing the Results
		cvShowImage( "frameData" , frameData );
		cvShowImage( "negImg" , negImg );
		// Wait for some time...
		cvWaitKey( 10 );
		
		// Cleaning Memory
		cvReleaseImage( &frameData );
		
	}

    printf("%s\n", imgName);


	cvReleaseImage( &negImg );
	// Clening Memory : Destroying the Windows
	cvDestroyWindow( "frameData" );
	//cvDestroyWindow( "negImg" );	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

