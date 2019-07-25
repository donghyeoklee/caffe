#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "conv2_modified.h"
using namespace cv;
using namespace std;

int main(){

// Opencv Image Read
    Mat image;
    Mat image_cmp;
    Mat dst;
//    Mat blurred;
    int E;
    image =imread("test_dog_cut.jpg", IMREAD_COLOR);
    image_cmp =imread("test_dog_cut.jpg", IMREAD_COLOR);
    if(image.empty())
    {
        cout << "Could not open or find the image1" << endl;
        return -1;
    }
// Initialize Valuables
    int nChannels = 3;
    int nFilters  = 1;
    int nMaxPool_Size = 0;
	int*** p1 = NULL; // Zero padding
	float*** p2 = NULL; // Filter
	float*** p3 = NULL; // Conv Result
    int ***p_mR = NULL; // Max Pooling Result 
    int xW = image.cols; // Input Size: image.cols X image.rows
	int yW = image.rows; 
    int cS = 0; // Filter Stride: 0
    int mS = 0;// MaxPooling Stride: 0
    int F = 3; // Filter Size: 3
    int mF = 0; // Max Pooing Filter Size: 0
    int P = 1; // Zero Padding 
    int nResultSize = 0; 

// 1. 3-Channel & Zero Padding    

    ZeroPadding(&nChannels, &xW, &P, &p1, image);

// 2. Cov Filter & ResultSize
    for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
            printf("%3d ", p1[0][i][j]);
        }
        printf("\n");
    }
            printf("\n");
    for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
            printf("%3d ", image_cmp.at<cv::Vec3b>(i,j)[0]);
        }
        printf("\n");
    }
            printf("\n");
    Filters(&xW, &P, &cS, &nResultSize,&F, &nFilters, &p2);
	clock_t begin = clock(); 
    Conv(&nChannels, &nFilters, &nResultSize, &xW, &P, &cS, &F, &p1, &p2, &p3);
    clock_t end = clock();
    double elapsed_secs = double(end-begin);
    cout<<"Conv Time: "<<elapsed_secs<<endl;
    conv2(image_cmp, &dst,3);
    namedWindow( "filter2D Demo", CV_WINDOW_AUTOSIZE );imshow( "filter2D Demo", dst );
//    blur(image, blurred, Size(5,5));
//    imshow("Blurred Image", blurred);
// 3. Activation Function
//conv_Activation_Func(&nChannels, &nFilters, &nResultSize, &p3);


// 4. Conv Image Show   
    Mat image_Conv_result(nResultSize,nResultSize, image.type());
	for(int i= 0; i< nResultSize; i++){
	    for(int j =0; j< nResultSize; j++){
	            for(int k=0;k<nChannels* nFilters;k++){
	                image_Conv_result.at<cv::Vec3b>(i,j)[k] = p3[k][i][j];
	            }
	        }
	}
    for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
            printf("%3d ", image_Conv_result.at<cv::Vec3b>(i,j)[0]);
        }
        printf("\n");
    }
            printf("\n");


    for(int i=0; i<3; i++){
        for(int j=0; j<3;j++){
            printf("%3d ", dst.at<cv::Vec3b>(i,j)[0]);
        }
        printf("\n");
    }
            printf("\n");




    Mat image_cmp_result(nResultSize,nResultSize, image.type());
    cout<<dst.size()<<endl;
    cout<<image_Conv_result.size()<<endl;
    image_cmp_result = dst-image_Conv_result;
	for(int k=0;k<nChannels* nFilters;k++){
    for(int i= 0; i< nResultSize; i++){
	    for(int j =0; j< nResultSize; j++){
	                printf("%d",image_cmp_result.at<cv::Vec3b>(i,j)[k]);
	            }
                printf("\n");
	        }
	}
    namedWindow("Conv_cmp");
    imshow("Conv_cmp", image_cmp_result);

    namedWindow("Conv");
    imshow("Conv", image_Conv_result);
   



// 4. Max Pooling
int nMaxPooling_Switch =0; // Max Pooling Off

if (nMaxPooling_Switch == 1){
    nMaxPool_Size  = MaxPooling(&nResultSize, &mS, &mF, &nChannels, &p3, &p_mR);
    
// 5. Max Pooling Image Show
    Mat image_MaxPool_result(nMaxPool_Size,nMaxPool_Size, image.type());
    
    for(int i= 0; i< nMaxPool_Size; i++){
        for(int j =0; j< nMaxPool_Size; j++){
            for(int k=0;k<nChannels;k++){
                image_MaxPool_result.at<cv::Vec3b>(i,j)[k] = p_mR[k][i][j];
            }
       
        }
    }

    namedWindow("Maxpooling");
    imshow("Maxpooling", image_MaxPool_result);
  
}

//5. Original Image Show

    namedWindow("Original");
    imshow("Original", image);
    waitKey();

// Free
printf("Conv Operation is Completed. Free Start!\n");

    for (int i = 0; i<nChannels; i++){
	    for (int j = 0; j < xW + 2*P; j++){
		    free(*(*(p1 + i)+j));
        }
        free(*(p1+i));
    }
	free(p1);
    printf("p1 Free OK\n");

        for (int i = 0; i<nFilters; i++){
            for (int j = 0; j <F; j++){
                free(*(*(p2 + i)+j));
            }
            free(*(p2+i));
        }
        free(p2);
    printf("p2 Free OK\n");

        for (int i = 0; i<nChannels * nFilters; i++){
            for (int j = 0; j <nResultSize; j++){
                free(*(*(p3 + i)+j));
            }
            free(*(p3+i));
        }
        free(p3);
    printf("p3 Free OK\n");
 

if (nMaxPooling_Switch == 1){

        for (int i = 0; i<nChannels; i++){
            for (int j = 0; j <nMaxPool_Size; j++){
                free(*(*(p_mR + i)+j));
            }
            free(*(p_mR+i));
        }
        free(p_mR);
    printf("p_mR Free OK\n");
}
    printf("End Conv Program :)\n");

    return 0;
}