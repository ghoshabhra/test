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
#include "../../CVDRIK/RGBtoGray/RGBtoGray.h"
#include "../../CVDRIK/edgeDetection/edgeDetection.h"

IplImage* blurring(IplImage*);

int main( int argc , char** argv ){

  // Check Usage
  if( argc != 2 )
  {
    // Show Purpose
    printf( "\n\n Purpose : creating grayscale image \n\n" );
    
    // Show Usage
    printf( "\n\n Usage As : grayscale <videoName>_ImageReadingAndDisplay.txt \n\n" );
    
    // Show Sample Command Line
    printf( "\n\n Sample Command Line : ./grayscale PETS2000_ImageReadingAndDisplay.txt \n\n" );
    
    return( 0 );
  }
  
  // Opening the Parameter File for Reading
  FILE* fp;
  fp = fopen( argv[1] , "r" );

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

  // Load the First Image as Previous RGB Image
  // This also helps in acquiring Image Dimensions
  // Which is Used Next to Decide the Window Sizes

  char imgName[500];
  constructImageName( inpImgPath , inpImgBaseName , imgStartNum , inpImgFormat , zeroPaddingFormatSize , maxZeroPaddingImgIndx , imgName);
  
  IplImage* img       = 0x00;
  IplImage* grayscale = 0x00;
  IplImage* edge_img  = 0x00;

  

  img = cvLoadImage( imgName );

  int width = img->width;
  int height = img->height;
  cvReleaseImage( &img );

  grayscale = cvCreateImage(cvSize(width ,height) , IPL_DEPTH_8U ,1);
  edge_img  = cvCreateImage(cvSize(width ,height) , IPL_DEPTH_8U ,1);

  // Create the Windows for Displaying Images
  cvNamedWindow( "frameData" , CV_WINDOW_AUTOSIZE );
  cvResizeWindow( "frameData" , width , height );

  for( int imgCount = imgStartNum ; imgCount <= imgEndNum ; ++imgCount )
	{
		// Show Frame Number
		printf( "\n\n************************************" );
		printf( "\n\n Reading Frame %d / %d \n\n" , imgCount , imgEndNum );
		 //printf("%s\n", imgName);
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

		unsigned char errCode = constructGrayscale( frameData ,grayscale);
        unsigned char errCode_2 = edgeDetection(grayscale ,edge_img);

        // Showing the Results
		cvShowImage( "frameData" , frameData );
		cvShowImage( "edge_img" , edge_img );
		cvShowImage( "grayscale" , grayscale);
		// Wait for some time...
		cvWaitKey( 5 );
		
		// Cleaning Memory
		cvReleaseImage( &frameData );
		
	}
  printf("%s\n", imgName);


  cvReleaseImage( &grayscale );
  cvReleaseImage( &edge_img );
  
  // Clening Memory : Destroying the Windows
  cvDestroyWindow( "frameData" );
  cvDestroyWindow( "edge_img" );
  cvDestroyWindow( "grayscale");	
  // Error Code 0 : All Well, That Ends Well
  return( 0 );
}


