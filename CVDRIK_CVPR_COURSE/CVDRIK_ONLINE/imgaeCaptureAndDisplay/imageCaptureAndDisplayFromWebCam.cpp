// Purpose : Image Capture and Display from Logitech QuickCam Series USB WebCam

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


// The Main Code
int main( int argc , char** argv )
{
	// Opening the Settings File for Reading
	FILE* fp;
	fp = fopen( "Settings_ImageCaptureAndDisplayFromWebCam.txt" , "r" );
	
	// Reading the Parameter File : Frame and Camera Information
	char paramNameString[100] , eqString[3] , headerString[100];
	fscanf( fp , "%s" , headerString );
	int camIndx;
	fscanf( fp , "%s%s%d" , paramNameString , eqString , &camIndx );
	int width;
	fscanf( fp , "%s%s%d" , paramNameString , eqString , &width );
	int height;
	fscanf( fp , "%s%s%d" , paramNameString , eqString , &height );
	int dropFrameNum;
	fscanf( fp , "%s%s%d" , paramNameString , eqString , &dropFrameNum );
	
	// Reading the Parameter File : Image File Information
	fscanf( fp , "%s" , headerString );
	int showInputImage;
	fscanf( fp , "%s%s%d" , paramNameString , eqString , &showInputImage );
	int waitKeyParam;
	fscanf( fp , "%s%s%d" , paramNameString , eqString , &waitKeyParam );
	int saveInputImage;
	fscanf( fp , "%s%s%d" , paramNameString , eqString , &saveInputImage );
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
	
	// Closing the File
	fclose( fp );
	
	// Initialize the Camera Capture Object
	CvCapture* cam = cvCreateCameraCapture( camIndx );//meaning of the structure and the function?
	
	// Setting the Property of the Capture
	cvSetCaptureProperty( cam , CV_CAP_PROP_FRAME_WIDTH , width );
	cvSetCaptureProperty( cam , CV_CAP_PROP_FRAME_HEIGHT , height );
	
	// Creating Windows for Showing the Images
	if( showInputImage != 0 )
	{
		cvNamedWindow( "frameData" , CV_WINDOW_AUTOSIZE );
		cvResizeWindow( "frameData" , width , height );
	}
	
	// Dropping the First Few Frames
	for( int counter = 1 ; counter <= dropFrameNum ; ++counter )
	{
		// Grabbing the Image
		// But, Not Using It
		IplImage* frameData = cvQueryFrame( cam );
	}
	
	// Looping for Camera Capture
	for( int counter = imgStartNum ; counter <= imgEndNum ; ++counter )
	{
		// Grabbing the Image
		IplImage* frameData = cvQueryFrame( cam );
		
		// Showing the Image
		if( showInputImage != 0 )
		{
			cvShowImage( "frameData" , frameData );
			cvWaitKey( waitKeyParam );
		}
		
		// Save the Current Frame If So is Desired
		if( saveInputImage != 0 )
		{
			// Prepare the Input Image Name
			char imgName[ 500 ];
			constructImageName( inpImgPath , inpImgBaseName , counter , inpImgFormat , zeroPaddingFormatSize , maxZeroPaddingImgIndx , imgName );
			
			// Save the Input Image
			cvSaveImage( imgName , frameData );
		}
	}
	
	// Releasing Camera Capture Structure
	cvReleaseCapture( &cam );
	
	// Releasing the Window
	if( showInputImage != 0 )
	{
		cvDestroyWindow( "frameData" );
	}
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}


