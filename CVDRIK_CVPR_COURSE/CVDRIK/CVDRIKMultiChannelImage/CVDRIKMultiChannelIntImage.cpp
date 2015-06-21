/******************************************************************************

   PROJECT:       CVDRIK1
   FILE:          CVDRIKMultiChannelIntImage.cpp
   AUTHOR:        PRITHWIJIT GUHA
   DATE:
   DESCRIPTION:   Functions for the Multi-Channel Int Image

******************************************************************************/


/*************************** OTHER INCLUDE FILES *****************************/

#include "CVDRIKMultiChannelImage.h"

#define EPSILON 0.0001

/*****************************************************************************/


/******************************************************************************

                                FUNCTIONS

******************************************************************************/

// Function for Initializing Multi-Channel Integer Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) img : Pointer to the Image to be Initialized
// Outputs :-
//			None
// Invoked As : initMultiChannelIntImage( &img );
void initMultiChannelIntImage( CVDRIKMultiChannelIntImage* img )
{
	img->m_ImgSize = -1;
	img->m_Img = NULL;
}

// Function for Allocating a Multi-Channel Integer Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) multiChannelIntImg : Pointer to Multi-Channel Integer Image to be Created
//			(int) xMax : Image Width
//			(int) yMax : Image Height
//			(int) channelNum : Number of Channels
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = allocateMultiChannelIntImage( &multiChannelIntImg , xMax , yMax , channelNum );
unsigned char allocateMultiChannelIntImage( CVDRIKMultiChannelIntImage* multiChannelIntImg , int xMax , int yMax , int channelNum )
{
	// Check Input data
	if( ( multiChannelIntImg->m_ImgSize > 0 ) || ( xMax <= 0 ) || ( yMax <= 0 ) || ( channelNum <= 0 ) )
	{
		// Error Code 1 : Invalid Input Variable
		return( 1 );
	}
	
	// Assigning Size Variables
	multiChannelIntImg->m_XMax = xMax;
	multiChannelIntImg->m_YMax = yMax;
	multiChannelIntImg->m_ChannelNum = channelNum;
	multiChannelIntImg->m_WidthStep = channelNum * xMax;
	multiChannelIntImg->m_ImgSize = channelNum * xMax * yMax;
	
	// Allocating Memory for Float Array
	multiChannelIntImg->m_Img = (int*) malloc( ( multiChannelIntImg->m_ImgSize ) * sizeof( int ) );
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Copying MultiChannel Integer Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) srcImg : Pointer to the Source MultiChannel Float Image
//			(CVDRIKMultiChannelIntImage*) destImg : Pointer to the Destination MultiChannel Float Image
//			(bool) destImgAlreadyAllocated : Set to TRUE, If the Destination Image is Already Allocated
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = copyMultiChannelIntImage( &srcImg , &destImg , destImgAlreadyAllocated );
unsigned char copyMultiChannelIntImage( CVDRIKMultiChannelIntImage* srcImg , CVDRIKMultiChannelIntImage* destImg , bool destImgAlreadyAllocated )
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
		memcpy( destImg->m_Img , srcImg->m_Img , ( srcImg->m_ImgSize ) * sizeof( int ) );
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
		destImg->m_Img = (int*) malloc( ( destImg->m_ImgSize ) * sizeof( int ) );
		
		// Copying Data
		memcpy( destImg->m_Img , srcImg->m_Img , ( destImg->m_ImgSize ) * sizeof( int ) );
	}
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Destroying a Multi-Channel Integer Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) multiChannelIntImg : Pointer to Multi-Channel Integer Image to be Destroyed
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = destroyMultiChannelIntImage( &multiChannelIntImg );
unsigned char destroyMultiChannelIntImage( CVDRIKMultiChannelIntImage* multiChannelIntImg )
{
	// Check Data Size
	if( multiChannelIntImg->m_ImgSize <= 0 )
	{
		// Error Code 2 : Null Data Size 
		return( 2 );
	}
	
	// Deallocating Memory for Float Array
	multiChannelIntImg->m_ImgSize = -1;
	free( multiChannelIntImg->m_Img );
	multiChannelIntImg->m_Img = NULL;
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Check Belongingness In Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) multiChannelIntImg : Pointer to Multi-Channel Float Image
//			(int) x : Abscissa
//			(int) y : Ordinate
// Outputs :-
//			(bool) isInsideFlag : TRUE, If (x,y) is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelIntImg , x , y );
bool isInside( CVDRIKMultiChannelIntImage* multiChannelIntImg , int x , int y )
{
	return( ( ( x >= 0 ) && ( x < multiChannelIntImg->m_XMax ) && ( y >= 0 ) && ( y < multiChannelIntImg->m_YMax ) ) ? true : false );
}

// Check Belongingness of a Rectangle In Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) multiChannelIntImg : Pointer to Multi-Channel Int Image
//			(CvRect*) rect : Pointer to the Rectangle
// Outputs :-
//			(bool) isInsideFlag : TRUE, If the Rectangle is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelIntImg , &rect );
bool isInside( CVDRIKMultiChannelIntImage* multiChannelIntImg , CvRect* rect )
{
	// Compute the Right Bottom Rectangle Co-ordinates
	int rightBotX = ( rect->x ) + ( rect->width );
	int rightBotY = ( rect->y ) + ( rect->height );
	
	// Check Belongingness
	return( ( ( ( rect->x ) >= 0 ) && ( ( rect->x ) < multiChannelIntImg->m_XMax ) && ( ( rect->y ) >= 0 ) && ( ( rect->y ) < multiChannelIntImg->m_YMax ) && ( rightBotX >= 0 ) && ( rightBotX < multiChannelIntImg->m_XMax ) && ( rightBotY >= 0 ) && ( rightBotY < multiChannelIntImg->m_YMax ) ) ? true : false );
}

// Function for Acquiring a Pixel Value Vector
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) multiChannelIntImg : Pointer to Multi-Channel Float Image to be Read
//			(int) x : Pixel Abscissa
//			(int) y : Pixel Ordinate
//			(int*) pixValVec : Pixel Value Vector Array
//			(int) channelNum : Number of Channels
// Outputs :-
//			errCode : The Error Code of Execution
// Invoked As : errCode = getPixel( &multiChannelIntImg , x , y , pixValVec , channelNum );
unsigned char getPixel( CVDRIKMultiChannelIntImage* multiChannelIntImg , int x , int y , int* pixValVec , int channelNum )
{
	// Check Channel Size
	if( multiChannelIntImg->m_ChannelNum != channelNum )
	{
		// Error Code 5 : Data Size Mismatch
		return( 5 );
	}
	
	// Check Whether Pixel Lies within Image Region
	if( ( x < 0 ) || ( x >= multiChannelIntImg->m_XMax ) || ( y < 0 ) || ( y >= multiChannelIntImg->m_YMax ) )
	{
		// Error Code 6 : Index Exceeds Data Bound
		return( 6 );
	}
	
	// Computing Base Address of the Pixel
	int pixBaseAddress = channelNum * ( ( y * multiChannelIntImg->m_XMax ) + x );
	
	// Reading the Pixel Values
	for( int channelCount = 0 ; channelCount < channelNum ; ++channelCount )
	{
		pixValVec[ channelCount ] = multiChannelIntImg->m_Img[ pixBaseAddress + channelCount ];
	}

	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Setting a Pixel Value Vector
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) multiChannelIntImg : Pointer to Multi-Channel Float Image to be Read
//			(int) x : Pixel Abscissa
//			(int) y : Pixel Ordinate
//			(int*) pixValVec : Pixel Value Vector Array
//			(int) channelNum : Number of Channels
// Outputs :-
//			errCode : The Error Code of Execution
// Invoked As : errCode = setPixel( &multiChannelIntImg , x , y , pixValVec , channelNum );
unsigned char setPixel( CVDRIKMultiChannelIntImage* multiChannelIntImg , int x , int y , int* pixValVec , int channelNum )
{
	// Check Channel Size
	if( multiChannelIntImg->m_ChannelNum != channelNum )
	{
		// Error Code 5 : Data Size Mismatch
		return( 5 );
	}
	
	// Check Whether Pixel Lies within Image Region
	if( ( x < 0 ) || ( x >= multiChannelIntImg->m_XMax ) || ( y < 0 ) || ( y >= multiChannelIntImg->m_YMax ) )
	{
		// Error Code 6 : Index Exceeds Data Bound
		return( 6 );
	}
	
	// Computing Base Address of the Pixel
	int pixBaseAddress = channelNum * ( ( y * multiChannelIntImg->m_XMax ) + x );
	
	// Reading the Pixel Values
	for( int channelCount = 0 ; channelCount < channelNum ; ++channelCount )
	{
		multiChannelIntImg->m_Img[ pixBaseAddress + channelCount ] = pixValVec[ channelCount ];
	}

	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}

// Function for Writing the Multi-Channel Integer Image to a File
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) intImg : Pointer to the Multi-Channel Integer Image
//			(char*) intImgFileName : Multi-Channel Integer Image File Name
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = writeImage( &intImg , intImgFileName );
unsigned char writeImage( CVDRIKMultiChannelIntImage* intImg , char* intImgFileName )
{
	// Check Inputs
	if( intImg->m_ImgSize <= 0 )
	{
		// Error Code 2 : Null Data Size
		return( 2 );
	}
	
	// Opening File for Writing
	FILE *fp;
	fp = fopen( intImgFileName , "w" );
	
	// Writing Image Size Parameters
	fprintf( fp , "%d\n" , intImg->m_XMax );
	fprintf( fp , "%d\n" , intImg->m_YMax );
	fprintf( fp , "%d\n" , intImg->m_ChannelNum );
		
	// Writing Float Image Data
	for( int counter = 0 ; counter < intImg->m_ImgSize ; ++counter )
	{
		fprintf( fp , "%d\n" , intImg->m_Img[ counter ] );
	}
	
	// Closing File
	fclose( fp );
}

// Function for Reading the Multi-Channel Float Image from a File
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) intImg : Pointer to the Multi-Channel Integer Image
//			(char*) intImgFileName : Multi-Channel Integer Image File Name
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = readImage( &intImg , intImgFileName );
unsigned char readImage( CVDRIKMultiChannelIntImage* intImg , char* intImgFileName )
{
	// Check Inputs
	if( intImg->m_ImgSize > 0 )
	{
		// Error Code 2 : Invalid Input
		return( 2 );
	}
	
	// Opening File for Reading
	FILE *fp;
	fp = fopen( intImgFileName , "r" );
	
	// Reading Image Size Parameters
	fscanf( fp , "%d" , &intImg->m_XMax );
	fscanf( fp , "%d" , &intImg->m_YMax );
	fscanf( fp , "%d" , &intImg->m_ChannelNum );
	
	// Set the Image Width Step
	intImg->m_WidthStep = ( intImg->m_XMax ) * ( intImg->m_ChannelNum );
	
	// Allocating Memory
	intImg->m_ImgSize = ( intImg->m_XMax ) * ( intImg->m_YMax ) * ( intImg->m_ChannelNum );
	intImg->m_Img = (int*) malloc( ( intImg->m_ImgSize ) * sizeof( int ) );
	
	// Reading Float Image Data
	for( int counter = 0 ; counter < intImg->m_ImgSize ; ++counter )
	{
		int tempVal;
		fscanf( fp , "%d" , &tempVal );
		intImg->m_Img[ counter ] = tempVal;
	}
	
	// Closing File
	fclose( fp );
	
	// Error Code 0 : All Well, That Ends Well
	return( 0 );
}











