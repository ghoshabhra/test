/******************************************************************************

   PROJECT:       CVDRIK1
   FILE:          CVDRIKMultiChannelFloatImage.cpp
   AUTHOR:        PRITHWIJIT GUHA
   DATE:
   DESCRIPTION:   Functions for the Multi-Channel Float Image

******************************************************************************/


/*************************** OTHER INCLUDE FILES *****************************/

#include "CVDRIKMultiChannelImage.h"

#define EPSILON 0.0001

/*****************************************************************************/


/******************************************************************************

                                FUNCTIONS

******************************************************************************/

// Function for Initializing Multi-Channel Float Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) img : Pointer to the Image to be Initialized
// Outputs :-
//			None
// Invoked As : initMultiChannelFloatImage( &img );
void initMultiChannelFloatImage( CVDRIKMultiChannelFloatImage* img )
{
	img->m_ImgSize = -1;
	img->m_Img = NULL;
}

// Function for Allocating a Multi-Channel Float Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) multiChannelFloatImg : Pointer to Multi-Channel Float Image to be Created
//			(int) xMax : Image Width
//			(int) yMax : Image Height
//			(int) channelNum : Number of Channels
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = allocateMultiChannelFloatImage( &multiChannelFloatImg , xMax , yMax , channelNum );
unsigned char allocateMultiChannelFloatImage( CVDRIKMultiChannelFloatImage* multiChannelFloatImg , int xMax , int yMax , int channelNum )
{
	// Check Input data
	if( ( xMax <= 0 ) || ( yMax <= 0 ) || ( channelNum <= 0 ) )
	{
		// Error Code 1 : Invalid Input Variable
		return( 1 );
	}
	
	// Assigning Size Variables
	multiChannelFloatImg->m_XMax = xMax;
	multiChannelFloatImg->m_YMax = yMax;
	multiChannelFloatImg->m_ChannelNum = channelNum;
	multiChannelFloatImg->m_WidthStep = channelNum * xMax;
	multiChannelFloatImg->m_ImgSize = channelNum * xMax * yMax;
	
	// Allocating Memory for Float Array
	multiChannelFloatImg->m_Img = (float*) malloc( ( multiChannelFloatImg->m_ImgSize ) * sizeof( float ) );
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Copying MultiChannelFloat Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) srcImg : Pointer to the Source MultiChannel Float Image
//			(CVDRIKMultiChannelFloatImage*) destImg : Pointer to the Destination MultiChannel Float Image
//			(bool) destImgAlreadyAllocated : Set to TRUE, If the Destination Image is Already Allocated
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = copyMultiChannelFloatImage( &srcImg , &destImg , destImgAlreadyAllocated );
unsigned char copyMultiChannelFloatImage( CVDRIKMultiChannelFloatImage* srcImg , CVDRIKMultiChannelFloatImage* destImg , bool destImgAlreadyAllocated )
{
	// Destination Image Already Allocated
	if( destImgAlreadyAllocated )
	{
		// Check Inputs
		if( ( srcImg->m_ImgSize <= 0 ) || ( destImg->m_ImgSize <= 0 ) )
		{
			// Error Code 1 : Invalid Input
			return( 1 );
		}
		
		// Check Data Size Match
		if( ( srcImg->m_XMax != destImg->m_XMax ) || ( destImg->m_YMax != destImg->m_YMax ) || ( srcImg->m_ChannelNum != destImg->m_ChannelNum ) )
		{
			// Error Code 5 : Data Size Mismatch
			return( 5 );
		}
		
		// Copy the Image Data
		memcpy( destImg->m_Img , srcImg->m_Img , ( srcImg->m_ImgSize ) * sizeof( float ) );
	}
	// Otherwise...
	else
	{
		// Check Inputs
		if( ( srcImg->m_ImgSize <= 0 ) || ( destImg->m_ImgSize > 0 ) )
		{
			// Error Code 1 : Invalid Input
			return( 1 );
		}
		
		// Assigning Image Size
		destImg->m_XMax = srcImg->m_XMax;
		destImg->m_YMax = srcImg->m_YMax;
		destImg->m_ChannelNum = srcImg->m_ChannelNum;
		destImg->m_WidthStep = srcImg->m_WidthStep;
		destImg->m_ImgSize = srcImg->m_ImgSize;
		
		// Allocating Memory
		destImg->m_Img = (float*) malloc( ( destImg->m_ImgSize ) * sizeof( float ) );
		
		// Copying Data
		memcpy( destImg->m_Img , srcImg->m_Img , ( destImg->m_ImgSize ) * sizeof( float ) );
	}
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Destroying a Multi-Channel Float Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) multiChannelFloatImg : Pointer to Multi-Channel Float Image to be Destroyed
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = destroyMultiChannelFloatImage( &multiChannelFloatImg );
unsigned char destroyMultiChannelFloatImage( CVDRIKMultiChannelFloatImage* multiChannelFloatImg )
{
	// Check Data Size
	if( multiChannelFloatImg->m_ImgSize <= 0 )
	{
		// Error Code 2 : Null Data Size 
		return( 2 );
	}
	
	// Deallocating Memory for Float Array
	multiChannelFloatImg->m_ImgSize = -1;
	free( multiChannelFloatImg->m_Img );
	multiChannelFloatImg->m_Img = NULL;
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Check Belongingness In Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) multiChannelFloatImg : Pointer to Multi-Channel Float Image
//			(int) x : Abscissa
//			(int) y : Ordinate
// Outputs :-
//			(bool) isInsideFlag : TRUE, If (x,y) is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelFloatImg , x , y );
bool isInside( CVDRIKMultiChannelFloatImage* multiChannelFloatImg , int x , int y )
{
	return( ( ( x >= 0 ) && ( x < multiChannelFloatImg->m_XMax ) && ( y >= 0 ) && ( y < multiChannelFloatImg->m_YMax ) ) ? true : false );
}

// Check Belongingness of a Rectangle In Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) multiChannelFloatImg : Pointer to Multi-Channel Float Image
//			(CvRect*) rect : Pointer to the Rectangle
// Outputs :-
//			(bool) isInsideFlag : TRUE, If the Rectangle is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelFloatImg , &rect );
bool isInside( CVDRIKMultiChannelFloatImage* multiChannelFloatImg , CvRect* rect )
{
	// Compute the Right Bottom Rectangle Co-ordinates
	int rightBotX = ( rect->x ) + ( rect->width );
	int rightBotY = ( rect->y ) + ( rect->height );
	
	// Check Belongingness
	return( ( ( ( rect->x ) >= 0 ) && ( ( rect->x ) < multiChannelFloatImg->m_XMax ) && ( ( rect->y ) >= 0 ) && ( ( rect->y ) < multiChannelFloatImg->m_YMax ) && ( rightBotX >= 0 ) && ( rightBotX < multiChannelFloatImg->m_XMax ) && ( rightBotY >= 0 ) && ( rightBotY < multiChannelFloatImg->m_YMax ) ) ? true : false );
}

// Function for Acquiring a Pixel Value Vector
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) multiChannelFloatImg : Pointer to Multi-Channel Float Image to be Read
//			(int) x : Pixel Abscissa
//			(int) y : Pixel Ordinate
//			(float*) pixValVec : Pixel Value Vector Array
//			(int) channelNum : Number of Channels
// Outputs :-
//			errCode : The Error Code of Execution
// Invoked As : errCode = getPixel( &multiChannelFloatImg , x , y , pixValVec , channelNum );
unsigned char getPixel( CVDRIKMultiChannelFloatImage* multiChannelFloatImg , int x , int y , float* pixValVec , int channelNum )
{
	// Check Channel Size
	if( multiChannelFloatImg->m_ChannelNum != channelNum )
	{
		// Error Code 5 : Data Size Mismatch
		return( 5 );
	}
	
	// Check Whether Pixel Lies within Image Region
	if( ( x < 0 ) || ( x >= multiChannelFloatImg->m_XMax ) || ( y < 0 ) || ( y >= multiChannelFloatImg->m_YMax ) )
	{
		// Error Code 6 : Index Exceeds Data Bound
		return( 6 );
	}
	
	// Computing Base Address of the Pixel
	int pixBaseAddress = channelNum * ( ( y * multiChannelFloatImg->m_XMax ) + x );
	
	// Reading the Pixel Values
	for( int channelCount = 0 ; channelCount < channelNum ; ++channelCount )
	{
		pixValVec[ channelCount ] = multiChannelFloatImg->m_Img[ pixBaseAddress + channelCount ];
	}

	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Setting a Pixel Value Vector
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) multiChannelFloatImg : Pointer to Multi-Channel Float Image to be Read
//			(int) x : Pixel Abscissa
//			(int) y : Pixel Ordinate
//			(float*) pixValVec : Pixel Value Vector Array
//			(int) channelNum : Number of Channels
// Outputs :-
//			errCode : The Error Code of Execution
// Invoked As : errCode = setPixel( &multiChannelFloatImg , x , y , pixValVec , channelNum );
unsigned char setPixel( CVDRIKMultiChannelFloatImage* multiChannelFloatImg , int x , int y , float* pixValVec , int channelNum )
{
	// Check Channel Size
	if( multiChannelFloatImg->m_ChannelNum != channelNum )
	{
		// Error Code 5 : Data Size Mismatch
		return( 5 );
	}
	
	// Check Whether Pixel Lies within Image Region
	if( ( x < 0 ) || ( x >= multiChannelFloatImg->m_XMax ) || ( y < 0 ) || ( y >= multiChannelFloatImg->m_YMax ) )
	{
		// Error Code 6 : Index Exceeds Data Bound
		return( 6 );
	}
	
	// Computing Base Address of the Pixel
	int pixBaseAddress = channelNum * ( ( y * multiChannelFloatImg->m_XMax ) + x );
	
	// Reading the Pixel Values
	for( int channelCount = 0 ; channelCount < channelNum ; ++channelCount )
	{
		multiChannelFloatImg->m_Img[ pixBaseAddress + channelCount ] = pixValVec[ channelCount ];
	}

	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Writing the Multi-Channel Float Image to a File
// Inputs :-
//			(CVDRIKMultiCHannelFloatImage*) floatImg : Pointer to the Multi-Channel Float Image
//			(char*) floatImgFileName : Multi-Channel Float Image File Name
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = writeImage( &floatImg , floatImgFileName );
unsigned char writeImage( CVDRIKMultiChannelFloatImage* floatImg , char* floatImgFileName )
{
	// Check Inputs
	if( floatImg->m_ImgSize <= 0 )
	{
		// Error Code 2 : Null Data Size
		return( 2 );
	}
	
	// Opening File for Writing
	FILE *fp;
	fp = fopen( floatImgFileName , "w" );
	
	// Writing Image Size Parameters
	fprintf( fp , "%d\n" , floatImg->m_XMax );
	fprintf( fp , "%d\n" , floatImg->m_YMax );
	fprintf( fp , "%d\n" , floatImg->m_ChannelNum );
		
	// Writing Float Image Data
	for( int counter = 0 ; counter < floatImg->m_ImgSize ; ++counter )
	{
		fprintf( fp , "%f\n" , floatImg->m_Img[ counter ] );
	}
	
	// Closing File
	fclose( fp );
}

// Function for Reading the Multi-Channel Float Image from a File
// Inputs :-
//			(CVDRIKMultiCHannelFloatImage*) floatImg : Pointer to the Multi-Channel Float Image
//			(char*) floatImgFileName : Multi-Channel Float Image File Name
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = readImage( &floatImg , floatImgFileName );
unsigned char readImage( CVDRIKMultiChannelFloatImage* floatImg , char* floatImgFileName )
{
	// Check Whether Memory is Allocated
	// If Memory is Not Allocated
	if( floatImg->m_ImgSize <= 0 )
	{
		// Opening File for Reading
		FILE *fp;
		fp = fopen( floatImgFileName , "r" );
	
		// Reading Image Size Parameters
		fscanf( fp , "%d" , &floatImg->m_XMax );
		fscanf( fp , "%d" , &floatImg->m_YMax );
		fscanf( fp , "%d" , &floatImg->m_ChannelNum );
	
		// Set the Image Width
		floatImg->m_WidthStep = ( floatImg->m_XMax ) * ( floatImg->m_ChannelNum );
	
		// Allocating Memory
		floatImg->m_ImgSize = ( floatImg->m_XMax ) * ( floatImg->m_YMax ) * ( floatImg->m_ChannelNum );
		floatImg->m_Img = (float*) malloc( ( floatImg->m_ImgSize ) * sizeof( float ) );
	
		// Reading Float Image Data
		for( int counter = 0 ; counter < floatImg->m_ImgSize ; ++counter )
		{
			float tempVal;
			fscanf( fp , "%f" , &tempVal );
			floatImg->m_Img[ counter ] = tempVal;
		}
	
		// Closing File
		fclose( fp );
	}
	// Otherwise, If Memory is Allocated
	else
	{
		// Opening File for Reading
		FILE *fp;
		fp = fopen( floatImgFileName , "r" );
	
		// Reading Image Size Parameters
		int xMax;
		fscanf( fp , "%d" , &xMax);
		int yMax;
		fscanf( fp , "%d" , &yMax );
		int channelNum;
		fscanf( fp , "%d" , &channelNum );
	
		// Checking Image Dimensions
		if( ( xMax != floatImg->m_XMax ) || ( yMax != floatImg->m_YMax ) || ( channelNum != floatImg->m_ChannelNum ) )
		{
			// Closing the File
			fclose( fp );
			
			// Error Code 5 : Data Size Mismatch
			return( 5 );
		}
		
		// Reading Float Image Data
		for( int counter = 0 ; counter < floatImg->m_ImgSize ; ++counter )
		{
			float tempVal;
			fscanf( fp , "%f" , &tempVal );
			floatImg->m_Img[ counter ] = tempVal;
		}
	
		// Closing File
		fclose( fp );
	}
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Converting a IplImage (Byte) to Multi-Channel Float Image
// Inputs :-
//			(IplImage*) iplImg : Pointer to the IplImage Data Structure
//			(CVDRIKMultiChannelFloatImage*) floatImg : Pointer to the Float Image
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = convertIplImageToMultiChannelFloatImage( &iplImg , floatImg );
unsigned char convertIplImageToMultiChannelFloatImage( IplImage* iplImg , CVDRIKMultiChannelFloatImage* floatImg )
{
	// Check Inputs
	if( ( iplImg->imageSize <= 0 ) || ( floatImg->m_ImgSize <= 0 ) )
	{
		// Error Code 1 : Invalid Input
		return( 1 );
	}
	
	// Check Data Size Match
	if( ( iplImg->nChannels != floatImg->m_ChannelNum ) || ( iplImg->width != floatImg->m_XMax ) || ( iplImg->height != floatImg->m_YMax ) )
	{
		// Error Code 5 : Data Size Mismatch
		return( 5 );
	}
	
	// If the Width Step Sizes Match
	// Then, use a Single FOR loop
	if( ( iplImg->widthStep == floatImg->m_WidthStep ) && ( iplImg->imageSize == floatImg->m_ImgSize ) )
	{
		// Copying the Pixel Values Directly
		for( int counter = 0 ; counter < floatImg->m_ImgSize ; ++counter )
		{
			floatImg->m_Img[ counter ] = (unsigned char) iplImg->imageData[ counter ];
		}
	}
	// Otherwise, Use Two FOR loops
	// By Looping Over Width and Height
	else
	{
		// Initialize Indices
		int floatImgBaseIndx = -( floatImg->m_WidthStep );
		int iplImgBaseIndx = -( iplImg->widthStep );
		for( int y = 0 ; y < iplImg->height ; ++y )
		{
			// Update Base Indices
			iplImgBaseIndx = iplImgBaseIndx + ( iplImg->widthStep );
			floatImgBaseIndx = floatImgBaseIndx + ( floatImg->m_WidthStep );
			
			// Looping Over the Width
			int currIplImgIndx = iplImgBaseIndx - ( iplImg->nChannels );
			int currFloatImgIndx = floatImgBaseIndx - ( floatImg->m_ChannelNum );
			for( int x = 0 ; x < iplImg->width ; ++x )
			{
				// Update Current Indices
				currIplImgIndx = currIplImgIndx + ( iplImg->nChannels );
				currFloatImgIndx = currFloatImgIndx + ( floatImg->m_ChannelNum );
				
				// Looping Over the Channel to Copy Pixel Values
				for( int counter = 0 ; counter < floatImg->m_ChannelNum ; ++counter )
				{
					floatImg->m_Img[ currFloatImgIndx + counter ] = (unsigned char) iplImg->imageData[ currIplImgIndx + counter ];
				}
			}
		}
	}
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Setting all Elements to a Single Value
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) floatImg : Pointer to the Multi-Channel Floating Point Image
//			(float) val : The Value to be Assigned
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = assignValueToMultiChannelFloatImage( &floatImg , val );
unsigned char assignValueToMultiChannelFloatImage( CVDRIKMultiChannelFloatImage* floatImg , float val )
{
	// Check Inputs
	if( ( floatImg->m_XMax <= 0 ) || ( floatImg->m_YMax <= 0 ) || ( floatImg->m_ImgSize <= 0 ) || ( floatImg->m_ChannelNum <= 0 ) )
	{
		// Error Code 1 : Invalid Input
		return( 1 );
	}
	
	// Setting the Value to All Elements of the Image
	for( int counter = 0 ; counter < floatImg->m_ImgSize ; ++counter )
	{
		floatImg->m_Img[ counter ] = val;
	}
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

	
	












