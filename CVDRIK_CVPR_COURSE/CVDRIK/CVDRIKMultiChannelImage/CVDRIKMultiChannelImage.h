/******************************************************************************

   PROJECT:			CVDRIK1
   FILE:			CVDRIKMultiChannelImage.h
   AUTHOR:			PRITHWIJIT GUHA
   DATE:
   DESCRIPTION:		Header for Multi-Channel Byte/Integer/Float Image

******************************************************************************/

#ifndef __CVDRIKMULTICHANNELIMAGE_H__
#define __CVDRIKMULTICHANNELIMAGE_H__


/*************************** OTHER INCLUDE FILES *****************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Include OpenCV Header Files Here
#include <cv.h>
#include <highgui.h>
#include <cvaux.h>
#include <cxcore.h>

// Include CVDRIK Header Files Here


/*****************************************************************************/


/******************************************************************************

				DATA STRUCTURE FOR MULTI-CHANNEL BYTE IMAGE

******************************************************************************/

// Multi-Channel Image Data Structure As BYTE Array
struct CVDRIKMultiChannelByteImage
{
	// The Image Width
	int m_XMax;
	
	// The Image Height
	int m_YMax;
	
	// The Number of Channels
	int m_ChannelNum;
	
	// Width Step or the Row Size
	int m_WidthStep;
	
	// The Image Data Array
	unsigned char* m_Img;
	
	// The Image Data Array Size
	int m_ImgSize;
};

/******************************************************************************

				FUNCTIONS FOR MULTI-CHANNEL BYTE IMAGE

******************************************************************************/

// Function for Initializing Multi-Channel Byte Image
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) img : Pointer to the Image to be Initialized
// Outputs :-
//			None
// Invoked As : initMultiChannelByteImage( &img );
void initMultiChannelByteImage( CVDRIKMultiChannelByteImage* img );

// Function for Allocating a Multi-Channel Byte Image
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) multiChannelByteImg : Pointer to Multi-Channel Byte Image to be Created
//			(int) xMax : Image Width
//			(int) yMax : Image Height
//			(int) channelNum : Number of Channels
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = allocateMultiChannelByteImage( &multiChannelByteImg , xMax , yMax , channelNum );
unsigned char allocateMultiChannelByteImage( CVDRIKMultiChannelByteImage* multiChannelByteImg , int xMax , int yMax , int channelNum );

// Function for Copying MultiChannelByteImage
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) srcImg : Pointer to the Source Image
//			(CVDRIKMultiChannelByteImage*) destImg : Pointer to the Destination Image, Assumed to be Uninitialized
//			(bool) destImgAlreadyAllocated : Set to TRUE, If the Destination Image is Already Allocated
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = copyMultiChannelByteImage( &srcImg , &destImg , destImgAlreadyAllocated );
unsigned char copyMultiChannelByteImage( CVDRIKMultiChannelByteImage* srcImg , CVDRIKMultiChannelByteImage* destImg , bool destImgAlreadyAllocated );

// Function for Destroying a Multi-Channel Byte Image
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) multiChannelByteImg : Pointer to Multi-Channel Byte Image to be Destroyed
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = destroyMultiChannelByteImage( &multiChannelByteImg );
unsigned char destroyMultiChannelByteImage( CVDRIKMultiChannelByteImage* multiChannelByteImg );

// Check Belongingness of a Point In Image
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) multiChannelByteImg : Pointer to Multi-Channel Byte Image
//			(int) x : Abscissa
//			(int) y : Ordinate
// Outputs :-
//			(bool) isInsideFlag : TRUE, If (x,y) is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelByteImg , x , y );
bool isInside( CVDRIKMultiChannelByteImage* multiChannelByteImg , int x , int y );

// Check Belongingness of a Rectangle In Image
// Inputs :-
//			(CVDRIKMultiChannelByteImage*) multiChannelByteImg : Pointer to Multi-Channel Byte Image
//			(CvRect*) rect : Pointer to the Rectangle
// Outputs :-
//			(bool) isInsideFlag : TRUE, If the Rectangle is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelByteImg , &rect );
bool isInside( CVDRIKMultiChannelByteImage* multiChannelByteImg , CvRect* rect );

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
unsigned char getPixel( CVDRIKMultiChannelByteImage* multiChannelByteImg , int x , int y , unsigned char* pixValVec , int channelNum );

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
unsigned char setPixel( CVDRIKMultiChannelByteImage* multiChannelByteImg , int x , int y , unsigned char* pixValVec , int channelNum );


/******************************************************************************

				DATA STRUCTURE FOR MULTI-CHANNEL FLOAT IMAGE

******************************************************************************/

// Multi-Channel Image Data Structure As FLOAT Array
struct CVDRIKMultiChannelFloatImage
{
	// The Image Width
	int m_XMax;
	
	// The Image Height
	int m_YMax;
	
	// The Number of Channels
	int m_ChannelNum;
	
	// Width Step or the Row Size
	int m_WidthStep;
	
	// The Image Data Array
	float* m_Img;
	
	// The Image Data Array Size
	int m_ImgSize;
};

/******************************************************************************

					FUNCTIONS FOR MULTI-CHANNEL FLOAT IMAGE

******************************************************************************/

// Function for Initializing Multi-Channel Float Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) img : Pointer to the Image to be Initialized
// Outputs :-
//			None
// Invoked As : initMultiChannelFloatImage( &img );
void initMultiChannelFloatImage( CVDRIKMultiChannelFloatImage* img );

// Function for Allocating a Multi-Channel Float Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) multiChannelFloatImg : Pointer to Multi-Channel Float Image to be Created
//			(int) xMax : Image Width
//			(int) yMax : Image Height
//			(int) channelNum : Number of Channels
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = allocateMultiChannelFloatImage( &multiChannelFloatImg , xMax , yMax , channelNum );
unsigned char allocateMultiChannelFloatImage( CVDRIKMultiChannelFloatImage* multiChannelFloatImg , int xMax , int yMax , int channelNum );

// Function for Copying MultiChannelFloat Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) srcImg : Pointer to the Source MultiChannel Float Image
//			(CVDRIKMultiChannelFloatImage*) destImg : Pointer to the Destination MultiChannel Float Image
//			(bool) destImgAlreadyAllocated : Set to TRUE, If the Destination Image is Already Allocated
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = copyMultiChannelFloatImage( &srcImg , &destImg , destImgAlreadyAllocated );
unsigned char copyMultiChannelFloatImage( CVDRIKMultiChannelFloatImage* srcImg , CVDRIKMultiChannelFloatImage* destImg , bool destImgAlreadyAllocated );

// Function for Destroying a Multi-Channel Float Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) multiChannelFloatImg : Pointer to Multi-Channel Float Image to be Destroyed
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = destroyMultiChannelFloatImage( &multiChannelFloatImg );
unsigned char destroyMultiChannelFloatImage( CVDRIKMultiChannelFloatImage* multiChannelFloatImg );

// Check Belongingness In Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) multiChannelFloatImg : Pointer to Multi-Channel Float Image
//			(int) x : Abscissa
//			(int) y : Ordinate
// Outputs :-
//			(bool) isInsideFlag : TRUE, If (x,y) is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelFloatImg , x , y );
bool isInside( CVDRIKMultiChannelFloatImage* multiChannelFloatImg , int x , int y );

// Check Belongingness of a Rectangle In Image
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) multiChannelFloatImg : Pointer to Multi-Channel Float Image
//			(CvRect*) rect : Pointer to the Rectangle
// Outputs :-
//			(bool) isInsideFlag : TRUE, If the Rectangle is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelFloatImg , &rect );
bool isInside( CVDRIKMultiChannelFloatImage* multiChannelFloatImg , CvRect* rect );

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
unsigned char getPixel( CVDRIKMultiChannelFloatImage* multiChannelFloatImg , int x , int y , float* pixValVec , int channelNum );

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
unsigned char setPixel( CVDRIKMultiChannelFloatImage* multiChannelFloatImg , int x , int y , float* pixValVec , int channelNum );

// Function for Writing the Multi-Channel Float Image to a File
// Inputs :-
//			(CVDRIKMultiCHannelFloatImage*) floatImg : Pointer to the Multi-Channel Float Image
//			(char*) floatImgFileName : Multi-Channel Float Image File Name
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = writeImage( &floatImg , floatImgFileName );
unsigned char writeImage( CVDRIKMultiChannelFloatImage* floatImg , char* floatImgFileName );

// Function for Reading the Multi-Channel Float Image from a File
// Inputs :-
//			(CVDRIKMultiCHannelFloatImage*) floatImg : Pointer to the Multi-Channel Float Image
//			(char*) floatImgFileName : Multi-Channel Float Image File Name
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = readImage( &floatImg , floatImgFileName );
unsigned char readImage( CVDRIKMultiChannelFloatImage* floatImg , char* floatImgFileName );

// Function for Converting a IplImage (Byte) to Multi-Channel Float Image
// Inputs :-
//			(IplImage*) iplImg : Pointer to the IplImage Data Structure
//			(CVDRIKMultiChannelFloatImage*) floatImg : Pointer to the Float Image
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = convertIplImageToMultiChannelFloatImage( &iplImg , floatImg );
unsigned char convertIplImageToMultiChannelFloatImage( IplImage* iplImg , CVDRIKMultiChannelFloatImage* floatImg );

// Function for Setting all Elements to a Single Value
// Inputs :-
//			(CVDRIKMultiChannelFloatImage*) floatImg : Pointer to the Multi-Channel Floating Point Image
//			(float) val : The Value to be Assigned
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = assignValueToMultiChannelFloatImage( &floatImg , val );
unsigned char assignValueToMultiChannelFloatImage( CVDRIKMultiChannelFloatImage* floatImg , float val );

/******************************************************************************

				DATA STRUCTURE FOR MULTI-CHANNEL INTEGER IMAGE

******************************************************************************/

// Multi-Channel Image Data Structure As INTEGER Array
struct CVDRIKMultiChannelIntImage
{
	// The Image Width
	int m_XMax;
	
	// The Image Height
	int m_YMax;
	
	// The Number of Channels
	int m_ChannelNum;
	
	// Width Step or the Row Size
	int m_WidthStep;
	
	// The Image Data Array
	int* m_Img;
	
	// The Image Data Array Size
	int m_ImgSize;
};


/******************************************************************************

					FUNCTIONS FOR MULTI-CHANNEL INTEGER IMAGE

******************************************************************************/

// Function for Initializing Multi-Channel Integer Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) img : Pointer to the Image to be Initialized
// Outputs :-
//			None
// Invoked As : initMultiChannelIntImage( &img );
void initMultiChannelIntImage( CVDRIKMultiChannelIntImage* img );

// Function for Allocating a Multi-Channel Integer Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) multiChannelIntImg : Pointer to Multi-Channel Integer Image to be Created
//			(int) xMax : Image Width
//			(int) yMax : Image Height
//			(int) channelNum : Number of Channels
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = allocateMultiChannelIntImage( &multiChannelIntImg , xMax , yMax , channelNum );
unsigned char allocateMultiChannelIntImage( CVDRIKMultiChannelIntImage* multiChannelIntImg , int xMax , int yMax , int channelNum );

// Function for Copying MultiChannel Integer Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) srcImg : Pointer to the Source MultiChannel Float Image
//			(CVDRIKMultiChannelIntImage*) destImg : Pointer to the Destination MultiChannel Float Image
//			(bool) destImgAlreadyAllocated : Set to TRUE, If the Destination Image is Already Allocated
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = copyMultiChannelIntImage( &srcImg , &destImg , destImgAlreadyAllocated );
unsigned char copyMultiChannelIntImage( CVDRIKMultiChannelIntImage* srcImg , CVDRIKMultiChannelIntImage* destImg , bool destImgAlreadyAllocated );

// Function for Destroying a Multi-Channel Integer Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) multiChannelIntImg : Pointer to Multi-Channel Integer Image to be Destroyed
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = destroyMultiChannelIntImage( &multiChannelIntImg );
unsigned char destroyMultiChannelIntImage( CVDRIKMultiChannelIntImage* multiChannelIntImg );

// Check Belongingness In Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) multiChannelIntImg : Pointer to Multi-Channel Float Image
//			(int) x : Abscissa
//			(int) y : Ordinate
// Outputs :-
//			(bool) isInsideFlag : TRUE, If (x,y) is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelIntImg , x , y );
bool isInside( CVDRIKMultiChannelIntImage* multiChannelIntImg , int x , int y );

// Check Belongingness of a Rectangle In Image
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) multiChannelIntImg : Pointer to Multi-Channel Int Image
//			(CvRect*) rect : Pointer to the Rectangle
// Outputs :-
//			(bool) isInsideFlag : TRUE, If the Rectangle is Inside Image Region
// Invoked As : isInsideFlag = isInside( &multiChannelIntImg , &rect );
bool isInside( CVDRIKMultiChannelIntImage* multiChannelIntImg , CvRect* rect );

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
unsigned char getPixel( CVDRIKMultiChannelIntImage* multiChannelIntImg , int x , int y , int* pixValVec , int channelNum );

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
unsigned char setPixel( CVDRIKMultiChannelIntImage* multiChannelIntImg , int x , int y , int* pixValVec , int channelNum );

// Function for Writing the Multi-Channel Integer Image to a File
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) intImg : Pointer to the Multi-Channel Integer Image
//			(char*) intImgFileName : Multi-Channel Integer Image File Name
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = writeImage( &intImg , intImgFileName );
unsigned char writeImage( CVDRIKMultiChannelIntImage* intImg , char* intImgFileName );

// Function for Reading the Multi-Channel Float Image from a File
// Inputs :-
//			(CVDRIKMultiChannelIntImage*) intImg : Pointer to the Multi-Channel Integer Image
//			(char*) intImgFileName : Multi-Channel Integer Image File Name
// Outputs :-
//			(unsigned char) errCode : The Error Code of Execution
// Invoked As : errCode = readImage( &intImg , intImgFileName );
unsigned char readImage( CVDRIKMultiChannelIntImage* intImg , char* intImgFileName );


#endif


