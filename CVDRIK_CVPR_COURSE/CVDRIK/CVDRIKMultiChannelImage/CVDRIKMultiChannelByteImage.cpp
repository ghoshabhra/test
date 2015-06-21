/******************************************************************************

   PROJECT:       CVDRIK1
   FILE:          CVDRIKMultiChannelByteImage.cpp
   AUTHOR:        PRITHWIJIT GUHA
   DATE:
   DESCRIPTION:   Functions for the Multi-Channel Byte Image

******************************************************************************/


/*************************** OTHER INCLUDE FILES *****************************/

#include "CVDRIKMultiChannelImage.h"

#define EPSILON 0.000001
#define PI 3.141593


/*****************************************************************************/


/******************************************************************************

                                FUNCTIONS

******************************************************************************/

// Function for Initializing Multi-Channel Byte Image
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) img : Pointer to the Image to be Initialized
// Outputs :-
//			None
// Invoked As : initMultiChannelByteImage( &img );
void initMultiChannelByteImage( CVDRIKMultiChannelByteImage* img )
{
	img->m_ImgSize = -1;
	img->m_Img = NULL;
}

// Function for Allocating a Multi-Channel Byte Image
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) multiChannelByteImg : Pointer to Multi-Channel Byte Image to be Created
//			(int) xMax : Image Width
//			(int) yMax : Image Height
//			(int) channelNum : Number of Channels
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = allocateMultiChannelByteImage( &multiChannelByteImg , xMax , yMax , channelNum );
unsigned char allocateMultiChannelByteImage( CVDRIKMultiChannelByteImage* multiChannelByteImg , int xMax , int yMax , int channelNum )
{
	// Check Input data
	if( ( xMax == 0 ) || ( yMax == 0 ) || ( channelNum == 0 ) )
	{
		// Error Code 1 : Invalid Input Variable
		return( 1 );
	}
	
	// Assigning Size Variables
	multiChannelByteImg->m_XMax = xMax;
	multiChannelByteImg->m_YMax = yMax;
	multiChannelByteImg->m_ChannelNum = channelNum;
	multiChannelByteImg->m_WidthStep = channelNum * xMax;
	multiChannelByteImg->m_ImgSize = channelNum * xMax * yMax;
	
	// Allocating Memory for Byte Array
	multiChannelByteImg->m_Img = (unsigned char*) malloc( ( multiChannelByteImg->m_ImgSize ) * sizeof( unsigned char ) );
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Copying MultiChannelByteImage
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) srcImg : Pointer to the Source Image
//			(CVDRIKMultiChannelByteImage*) destImg : Pointer to the Destination Image, Assumed to be Uninitialized
//			(bool) destImgAlreadyAllocated : Set to TRUE, If the Destination Image is Already Allocated
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = copyMultiChannelByteImage( &srcImg , &destImg , destImgAlreadyAllocated );
unsigned char copyMultiChannelByteImage( CVDRIKMultiChannelByteImage* srcImg , CVDRIKMultiChannelByteImage* destImg , bool destImgAlreadyAllocated )
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
		memcpy( destImg->m_Img , srcImg->m_Img , ( srcImg->m_ImgSize ) * sizeof( unsigned char ) );
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
		
		// Assign Parameters
		destImg->m_XMax = srcImg->m_XMax;
		destImg->m_YMax = srcImg->m_YMax;
		destImg->m_ImgSize = srcImg->m_ImgSize;
		destImg->m_ChannelNum = srcImg->m_ChannelNum;
		destImg->m_WidthStep = srcImg->m_WidthStep;
		
		// Allocating Memory
		destImg->m_Img = (unsigned char*) malloc( ( destImg->m_ImgSize ) * sizeof( unsigned char ) );
		
		// Copying Data
		memcpy( destImg->m_Img , srcImg->m_Img , ( ( destImg->m_ImgSize ) * sizeof( unsigned char ) ) );
	}
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Destroying a Multi-Channel Byte Image
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) multiChannelByteImg : Pointer to Multi-Channel Byte Image to be Destroyed
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = destroyMultiChannelByteImage( &multiChannelByteImg );
unsigned char destroyMultiChannelByteImage( CVDRIKMultiChannelByteImage* multiChannelByteImg )
{
	// Check Data Size
	if( multiChannelByteImg->m_ImgSize <= 0 )
	{
		// Error Code 2 : Null Data Size 
		return( 2 );
	}
	
	// Deallocating Memory for Byte Array
	multiChannelByteImg->m_ImgSize = -1;
	free( multiChannelByteImg->m_Img );
	multiChannelByteImg->m_Img = NULL;
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Check Belongingness of a Point In Image
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) multiChannelByteImg : Pointer to Multi-Channel Byte Image
//			(int) x : Abscissa
//			(int) y : Ordinate
// Outputs :-
//			(bool) isInsideFlag : TRUE, If (x,y) is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelByteImg , x , y );
bool isInside( CVDRIKMultiChannelByteImage* multiChannelByteImg , int x , int y )
{
	// Check Belongingness
	return( ( ( x >= 0 ) && ( x < multiChannelByteImg->m_XMax ) && ( y >= 0 ) && ( y < multiChannelByteImg->m_YMax ) ) ? true : false );
}

// Check Belongingness of a Rectangle In Image
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) multiChannelByteImg : Pointer to Multi-Channel Byte Image
//			(CvRect*) rect : Pointer to the Rectangle
// Outputs :-
//			(bool) isInsideFlag : TRUE, If the Rectangle is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelByteImg , &rect );
bool isInside( CVDRIKMultiChannelByteImage* multiChannelByteImg , CvRect* rect )
{
	// Compute the Right Bottom Rectangle Co-ordinates
	int rightBotX = ( rect->x ) + ( rect->width );
	int rightBotY = ( rect->y ) + ( rect->height );
	
	// Check Belongingness
	return( ( ( ( rect->x ) >= 0 ) && ( ( rect->x ) < multiChannelByteImg->m_XMax ) && ( ( rect->y ) >= 0 ) && ( ( rect->y ) < multiChannelByteImg->m_YMax ) && ( rightBotX >= 0 ) && ( rightBotX < multiChannelByteImg->m_XMax ) && ( rightBotY >= 0 ) && ( rightBotY < multiChannelByteImg->m_YMax ) ) ? true : false );
}

// Function for Acquiring a Pixel Value Vector
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) multiChannelByteImg : Pointer to Multi-Channel Byte Image to be Read
//			(int) x : Pixel Abscissa
//			(int) y : Pixel Ordinate
//			(unsigned char*) pixValVec : Pixel Value Vector Array
//			(int) channelNum : Number of Channels
// Outputs :-
//			errCode : The Error Code of Execution
// Invoked As : errCode = getPixel( &multiChannelByteImg , x , y , pixValVec , channelNum );
unsigned char getPixel( CVDRIKMultiChannelByteImage* multiChannelByteImg , int x , int y , unsigned char* pixValVec , int channelNum )
{
	// Check Channel Size
	if( multiChannelByteImg->m_ChannelNum != channelNum )
	{
		// Error Code 5 : Data Size Mismatch
		return( 5 );
	}
	
	// Check Whether Pixel Lies within Image Region
	if( ( x < 0 ) || ( x >= multiChannelByteImg->m_XMax ) || ( y < 0 ) || ( y >= multiChannelByteImg->m_YMax ) )
	{
		// Error Code 6 : Index Exceeds Data Bound
		return( 6 );
	}
	
	// Computing Base Address of the Pixel
	int pixBaseAddress = channelNum * ( ( y * multiChannelByteImg->m_XMax ) + x );
	
	// Reading the Pixel Values
	for( int channelCount = 0 ; channelCount < channelNum ; ++channelCount )
	{
		pixValVec[ channelCount ] = multiChannelByteImg->m_Img[ pixBaseAddress + channelCount ];
	}

	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Setting a Pixel Value Vector
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) multiChannelByteImg : Pointer to Multi-Channel Byte Image to be Read
//			(int) x : Pixel Abscissa
//			(int) y : Pixel Ordinate
//			(unsigned char*) pixValVec : Pixel Value Vector Array
//			(int) channelNum : Number of Channels
// Outputs :-
//			errCode : The Error Code of Execution
// Invoked As : errCode = setPixel( &multiChannelByteImg , x , y , pixValVec , channelNum );
unsigned char setPixel( CVDRIKMultiChannelByteImage* multiChannelByteImg , int x , int y , unsigned char* pixValVec , int channelNum )
{
	// Check Channel Size
	if( multiChannelByteImg->m_ChannelNum != channelNum )
	{
		// Error Code 5 : Data Size Mismatch
		return( 5 );
	}
	
	// Check Whether Pixel Lies within Image Region
	if( ( x < 0 ) || ( x >= multiChannelByteImg->m_XMax ) || ( y < 0 ) || ( y >= multiChannelByteImg->m_YMax ) )
	{
		// Error Code 6 : Index Exceeds Data Bound
		return( 6 );
	}
	
	// Computing Base Address of the Pixel
	int pixBaseAddress = channelNum * ( ( y * multiChannelByteImg->m_XMax ) + x );
	
	// Reading the Pixel Values
	for( int channelCount = 0 ; channelCount < channelNum ; ++channelCount )
	{
		multiChannelByteImg->m_Img[ pixBaseAddress + channelCount ] = pixValVec[ channelCount ];
	}

	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}


