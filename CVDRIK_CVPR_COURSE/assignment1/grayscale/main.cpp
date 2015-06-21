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


//IplImage* constructGrayscale(IplImage*);
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

  char imgName[500];
  constructImageName( inpImgPath , inpImgBaseName , imgStartNum , inpImgFormat , zeroPaddingFormatSize , maxZeroPaddingImgIndx , imgName);
  
  IplImage* img       = 0x00;
  IplImage* grayscale = 0x00;
  IplImage* edge_img  = 0x00;
  //IplImage* im_gray = cvLoadImage(imgName );
  img = cvLoadImage( imgName );

  

  
  
   int width = img->width;
   int height = img->height;
   int channel = img->nChannels;
   int widthstep = img->widthStep;
   int imagesize = img->imageSize;
  
  grayscale = cvCreateImage(cvSize(width ,height) , IPL_DEPTH_8U ,1);
  edge_img  = cvCreateImage(cvSize(width ,height) , IPL_DEPTH_8U ,1);

  unsigned char errCode = constructGrayscale( img ,grayscale);
  unsigned char errCode_2 = edgeDetection(grayscale ,edge_img);
  IplImage* blurr = blurring(img);
  
  // printf("errCode = %c\n", errCode );
   //printf("grayscale->width = %d\n", grayscale->width );
  //IplImage* grayscale = constructGrayscale(img);


 // for (int i = 0; i < grayscale->imageSize; ++i)
  //{
    //printf("%d\n",(unsigned int)grayscale->imageData[ i ] );
 // }


  cvNamedWindow( "frameData_1" , CV_WINDOW_AUTOSIZE );
  cvResizeWindow( "frameData_1" , width , height );
  cvShowImage( "frameData_1" , grayscale );


  //cvNamedWindow( "frameData_2" , CV_WINDOW_AUTOSIZE );
  //cvResizeWindow( "frameData_2" , width , height );
  cvShowImage( "frameData_2" , img );


 // cvNamedWindow( "frameData_3" , CV_WINDOW_AUTOSIZE );
 // cvResizeWindow( "frameData_3" , width , height );
  cvShowImage( "frameData_3" , edge_img );

  
  cv::waitKey(0);
  cvReleaseImage( &img );
  cvReleaseImage( &grayscale );
  cvReleaseImage( &edge_img );
  

  //cvDestroyWindow( "frameData" );
  return( 0 );
}
    


/*
IplImage* constructGrayscale(IplImage* inpImage)
{
  int width = inpImage->width;
  int height = inpImage->height;
  int channel = inpImage->nChannels;
  int widthstep = inpImage->widthStep;
  int imagesize = inpImage->imageSize;

  IplImage* grayscale = 0x00;
  grayscale = cvCreateImage(cvSize(width ,height) , IPL_DEPTH_8U ,1);
  

  int a = 0;
  int c = 0;
  for (int i = 0; i < inpImage->height; ++i)
  {  
    
    for (int j = 0 ,k = 0 ; j < inpImage->widthStep; j+=3 )
    { //int r ,g ,b;

      //r = (unsigned char)inpImage->imageData[ a + j ];
      //g = (unsigned char)inpImage->imageData[ a + j + 1 ];
      //b = (unsigned char)inpImage->imageData[ a + j + 2 ];
     // printf("%d\n", (int)r);
      //  printf("%d\n", (int)b);
      

     // grayscale->imageData[ c + k ]  = (unsigned char)( ( r + g + b )/3 );

      /*
      grayscale->imageData[ b + k ] = (r + g + b)/3;
      //grayscale->imageData[ a + j + 1] = g;
      //grayscale->imageData[ a + j + 2] = b;
     

     grayscale->imageData[ c + k ] = (unsigned char)( ( (unsigned char)inpImage->imageData[ a + j ] + (unsigned char)inpImage->imageData[ a + j + 1 ] + (unsigned char)inpImage->imageData[ a + j + 2 ] )/3 );
     //printf("%d\n",(unsigned int)grayscale->imageData[ c + k ] );
      
     k++;





    }

    a = a + inpImage->widthStep; 
    c = c + grayscale->widthStep;
  }
return grayscale;

}
*/

IplImage* blurring(IplImage* inpImage)
{
  int width = inpImage->width;
  int height = inpImage->height;
  int channel = inpImage->nChannels;
  int widthstep = inpImage->widthStep;
  int imagesize = inpImage->imageSize;

  IplImage* blurr = 0x00;
  blurr = inpImage;

  for (int i = widthstep; i < imagesize - 1 - widthstep; i = i + widthstep)
  {
    for (int j = 3; j < widthstep - 3; j = j+3)
    {
      /*blurr->imageData[ i + j ] = (blurr->imageData[ i + j - 3 ] + blurr->imageData[ i + j ] + blurr->imageData[ i + j + 3 ] + blurr->imageData[ i - widthstep + j - 3] + blurr->imageData[ i - widthstep + j ]+ blurr->imageData[ i - widthstep + j + 3]+ blurr->imageData[ i + widthstep + j - 3] + blurr->imageData[ i + widthstep + j ]+ blurr->imageData[ i + widthstep + j + 3])/9;
      blurr->imageData[ i + j + 1] = (blurr->imageData[ i + j + 1 - 3] + blurr->imageData[ i + j + 1 ] + blurr->imageData[ i + j + 1 + 3 ] + blurr->imageData[ i - widthstep + j + 1 - 3] + blurr->imageData[ i - widthstep + j + 1 ]+ blurr->imageData[ i - widthstep + j + 1 + 3]+ blurr->imageData[ i + widthstep + j + 1 - 3] + blurr->imageData[ i + widthstep + j + 1 ] + blurr->imageData[ i + widthstep + j + 1 + 3])/9;
      blurr->imageData[ i + j + 2] = (blurr->imageData[ i + j + 2 - 3] + blurr->imageData[ i + j + 2 ] + blurr->imageData[ i + j + 2 + 3 ] + blurr->imageData[ i - widthstep + j + 2 - 3] + blurr->imageData[ i - widthstep + j + 2 ]+ blurr->imageData[ i - widthstep + j + 2 + 3]+ blurr->imageData[ i + widthstep + j + 2 - 3] + blurr->imageData[ i + widthstep + j + 2 ] + blurr->imageData[ i + widthstep + j + 2 + 3])/9;
      */
      blurr->imageData[ i + j ] = (unsigned char)((unsigned char)blurr->imageData[ i + j - 3 ] + (unsigned char)blurr->imageData[ i + j ] + (unsigned char)blurr->imageData[ i + j + 3 ] + (unsigned char)blurr->imageData[ i - widthstep + j - 3] + (unsigned char)blurr->imageData[ i - widthstep + j ]+ (unsigned char)blurr->imageData[ i - widthstep + j + 3]+ (unsigned char)blurr->imageData[ i + widthstep + j - 3] + (unsigned char)blurr->imageData[ i + widthstep + j ]+ (unsigned char)blurr->imageData[ i + widthstep + j + 3])/9;
      blurr->imageData[ i + j + 1] = (unsigned char)((unsigned char)blurr->imageData[ i + j + 1 - 3] + (unsigned char)blurr->imageData[ i + j + 1 ] + (unsigned char)blurr->imageData[ i + j + 1 + 3 ] + (unsigned char)blurr->imageData[ i - widthstep + j + 1 - 3] + (unsigned char)blurr->imageData[ i - widthstep + j + 1 ]+ (unsigned char)blurr->imageData[ i - widthstep + j + 1 + 3]+ (unsigned char)blurr->imageData[ i + widthstep + j + 1 - 3] + (unsigned char)blurr->imageData[ i + widthstep + j + 1 ] + (unsigned char)blurr->imageData[ i + widthstep + j + 1 + 3])/9;
      blurr->imageData[ i + j + 2] = (unsigned char)((unsigned char)blurr->imageData[ i + j + 2 - 3] + (unsigned char)blurr->imageData[ i + j + 2 ] + (unsigned char)blurr->imageData[ i + j + 2 + 3 ] + (unsigned char)blurr->imageData[ i - widthstep + j + 2 - 3] + (unsigned char)blurr->imageData[ i - widthstep + j + 2 ]+ (unsigned char)blurr->imageData[ i - widthstep + j + 2 + 3]+ (unsigned char)blurr->imageData[ i + widthstep + j + 2 - 3] + (unsigned char)blurr->imageData[ i + widthstep + j + 2 ] + (unsigned char)blurr->imageData[ i + widthstep + j + 2 + 3])/9;


    }
  }

 return blurr;

}