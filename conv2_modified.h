#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace cv;
using namespace std;


void ZeroPadding(int* pnChannels, int *pW, int *pP, int****p1, Mat pimage){

    *p1 = (int***)malloc(*pnChannels * sizeof(int **));
    for(int i=0; i< *pnChannels; i++){
        *((*p1)+i) = (int**)malloc((*pW + 2*(*pP)) * sizeof(int*));
        for(int j=0; j< *pW + 2*(*pP);j++){
            *(*((*p1)+i)+j) = (int *)malloc((*pW + 2*(*pP)) * sizeof(int));
        }
    }

    for(int i= 0; i< *pW+ 2*(*pP); i++){
        for(int j =0; j< *pW + 2*(*pP); j++){
            if (i <= *pP - 1 || j <= *pP - 1 || i >=  *pP + *pW || j >= *pP + *pW ){
                for(int k=0; k< *pnChannels; k++){
                    (*p1)[k][i][j] = 0;
                }
            }                    
            else{
                    Vec3b* pixel = pimage.ptr<Vec3b>(i-*pP);
                    for(int k=0; k< *pnChannels; k++){
                    (*p1)[k][i][j] = pixel[j-*pP][k];
                    }
            }                  
        }
    }  
}


void Filters(int *pW, int *pP, int *pS, int *pnResultSize,int *pF, int *pnFilters, float ****p2){

    int nF_Switch = 6;
    printf("What filter do you want for Conv ?o? \n");
    printf("---------------------------------------------------------------------------------\n");
    printf("-   1. 3 X 3 Blur  2. 5 X 5 Blur   3. 3 X 3 Edge Detect    4. 5 X 5 Edge Detect -\n");
    printf("-   5. 3 X 3 Sharpening(x)                                 6. User Input Filter -\n");
    printf("---------------------------------------------------------------------------------\n");
    scanf("%d", &nF_Switch);
    switch (nF_Switch){
        case 1: 
            printf("Enter Stride: ");
                scanf("%d", pS);
                *pnFilters = 1;
                *pF = 3;
                *pnResultSize = ((*pW - *pF +(2*(*pP)))/ *pS) +1;

                if (*pnResultSize <=0)
                    printf("Result Size Error! :/\n");
                else{
                    printf("Conv Result Size: %d\n", *pnResultSize);
                    
                    *p2 = (float***)malloc(*pnFilters * sizeof(float **));
                    for(int i=0; i< *pnFilters; i++){
                        *((*p2)+i) = (float**)malloc(*pF * sizeof(float*));
                        for(int j=0; j< *pF;j++){
                            *(*((*p2)+i)+j) = (float *)malloc(*pF * sizeof(float));
                        }
                    }
                       (*p2)[0][0][0] =1/16.0;
                       (*p2)[0][0][1] =1/8.0;
                       (*p2)[0][0][2] =1/16.0;
                       (*p2)[0][1][0] =1/8.0;
                       (*p2)[0][1][1] =1/4.0;
                       (*p2)[0][1][2] =1/8.0;     
                       (*p2)[0][2][0] =1/16.0;
                       (*p2)[0][2][1] =1/8.0;
                       (*p2)[0][2][2] =1/16.0;
   

                    for(int k=0;k<*pnFilters;k++){
                        printf("[3 X 3 Blur Filter]\n");
                        for (int i = 0; i < *pF; i++) {
                            for (int j = 0; j < *pF; j++) {
                                printf("%f\t", (*p2)[k][i][j]);
                            }
                        puts("\n");    
                        }
                    }
                }            
            break; 
        case 2: 
            printf("Enter Stride: ");
                scanf("%d", pS);        
                *pnFilters = 1;
                *pF = 5;
				*pnResultSize = ((*pW - *pF + (2 * (*pP))) / *pS) + 1;
                printf("Conv Result Size: %d\n", *pnResultSize);                   
                if (*pnResultSize <=0)
                    printf("Result Size Error! :/\n");
                else{
                    
                    *p2 = (float***)malloc(*pnFilters * sizeof(float **));
                    for(int i=0; i< *pnFilters; i++){
                        *((*p2)+i) = (float**)malloc(*pF * sizeof(float*));
                        for(int j=0; j< *pF;j++){
                            *(*((*p2)+i)+j) = (float *)malloc(*pF * sizeof(float));
                        }
                    }
                       (*p2)[0][0][0] =1/273.0;
                       (*p2)[0][0][1] =4/273.0;
                       (*p2)[0][0][2] =7/273.0;
                       (*p2)[0][0][3] =4/273.0;
                       (*p2)[0][0][4] =1/273.0;                    
                       (*p2)[0][1][0] =4/273.0;
                       (*p2)[0][1][1] =16/273.0;
                       (*p2)[0][1][2] =26/273.0;
                       (*p2)[0][1][3] =16/273.0;
                       (*p2)[0][1][4] =4/273.0;
                       (*p2)[0][2][0] =7/273.0;
                       (*p2)[0][2][1] =26/273.0;
                       (*p2)[0][2][2] =41/273.0;
                       (*p2)[0][2][3] =26/273.0;
                       (*p2)[0][2][4] =7/273.0;
                       (*p2)[0][3][0] =4/273.0;
                       (*p2)[0][3][1] =16/273.0;
                       (*p2)[0][3][2] =26/273.0;
                       (*p2)[0][3][3] =16/273.0;
                       (*p2)[0][3][4] =4/273.0;
                       (*p2)[0][4][0] =1/273.0;
                       (*p2)[0][4][1] =4/273.0;
                       (*p2)[0][4][2] =7/273.0;
                       (*p2)[0][4][3] =4/273.0;
                       (*p2)[0][4][4] =1/273.0;


                    for(int k=0;k<*pnFilters;k++){
                        printf("[5 X 5 Blur Filter]\n");
                        for (int i = 0; i < *pF; i++) {
                            for (int j = 0; j < *pF; j++) {
                                printf("%f\t", (*p2)[k][i][j]);
                            }
                        puts("\n");    
                        }
                    }
                } 
        break;
        case 3:  
            printf("Enter Stride: ");
                scanf("%d", pS);                       
                *pnFilters = 1;
                *pF = 3;
				*pnResultSize = ((*pW - *pF + (2 * (*pP))) / *pS) + 1;
                printf("Conv Result Size: %d\n", *pnResultSize);       
                if (*pnResultSize <=0)
                    printf("Result Size Error! :/\n");
                else{
                    
                    *p2 = (float***)malloc(*pnFilters * sizeof(float **));
                    for(int i=0; i< *pnFilters; i++){
                        *((*p2)+i) = (float**)malloc(*pF * sizeof(float*));
                        for(int j=0; j< *pF;j++){
                            *(*((*p2)+i)+j) = (float *)malloc(*pF * sizeof(float));
                        }
                    }
                       (*p2)[0][0][0] =-1;
                       (*p2)[0][0][1] =-1;
                       (*p2)[0][0][2] =-1;
                       (*p2)[0][1][0] =-1;
                       (*p2)[0][1][1] =8;
                       (*p2)[0][1][2] =-1;     
                       (*p2)[0][2][0] =-1;
                       (*p2)[0][2][1] =-1;
                       (*p2)[0][2][2] =-1;
   

                    for(int k=0;k<*pnFilters;k++){
                        printf("[3 X 3 Edge Filter]\n");
                        for (int i = 0; i < *pF; i++) {
                            for (int j = 0; j < *pF; j++) {
                                printf("%f\t", (*p2)[k][i][j]);
                            }
                        puts("\n");    
                        }
                    }
                } 
        break;
        case 4: break;
        case 5: break;
        case 6:
        
            printf("Enter Filter Size: ");
            scanf("%d", pF);
            printf("Enter Fliters_Num :/\n");
            scanf("%d", &*pnFilters);            
            printf("Enter Stride: ");
            scanf("%d", pS); 	
            printf("Enter the Values of %dX%d Filter Matrix\n", *pF, *pF);
				*pnResultSize = ((*pW - *pF + (2 * (*pP))) / *pS) + 1;
             printf("Conv Result Size: %d\n", *pnResultSize);              
                if (*pnResultSize <=0)
                    printf("Result Size Error! :/\n");
            else{
                printf("Result Size: %d\n", *pnResultSize);       
                *p2 = (float***)malloc(*pnFilters * sizeof(float **));
                for(int i=0; i< *pnFilters; i++){
                    *((*p2)+i) = (float**)malloc(*pF * sizeof(float*));
                    for(int j=0; j< *pF;j++){
                        *(*((*p2)+i)+j) = (float *)malloc(*pF * sizeof(float));
                    }
                }
                for(int k=0;k<*pnFilters;k++){
                    printf("%d-Filter: ", k + 1);
                    for (int i = 0; i < *pF; i++) {
                        for (int j = 0; j < *pF; j++) {
                            printf("input(%d, %d)= ", i, j);
                            scanf("%f", &(*p2)[k][i][j]);
                        }
                    }
                }
                break;
            }
        default: printf("Error: Wrong Input! :/ \n");
    }
}

void Conv(int *pnChannels, int *pnFilters, int *pnResultSize, int *pW, int *pP, int *pS, int *pF, int ****p1, float ****p2, float ****p3){


	*p3 = (float***)malloc(*pnChannels * sizeof(float**));
    for(int i=0; i<*pnChannels;i++){
        *((*p3)+i)= (float**)malloc(*pnResultSize * sizeof(float*));
	    for (int j = 0; j < *pnResultSize; j++) {
		    *(*((*p3)+i)+j) = (float*)malloc(*pnResultSize * sizeof(float));
	    }
    }

    for (int i = 0; i< *pnResultSize; i++){

        for(int j=0;j<*pnResultSize;j++){
            for(int k=0;k<*pnChannels;k++){
                (*p3)[k][i][j] = 0.0;
            }
        }
    }

for(int k=0; k<*pnChannels; k++){    
    for(int z=0; z< *pnFilters; z++){
	    for (int i = 0;i < *pnResultSize; i++) {
		    for (int j = 0;j < *pnResultSize; j++) {
			    for (int y = 0;y < *pF; y++) {
				    for (int x = 0;x < *pF; x++) {
(*p3)[k][i][j]+= (*p1)[k][(*pS)*i+y][(*pS)*j+x] * (*p2)[z][y][x];
				    }
			    }
                if((*p3)[k][i][j] > 255)
					(*p3)[k][i][j] = 255.0;
                else if((*p3)[k][i][j] < 0)
					(*p3)[k][i][j] = 0;
                (*p3)[k][i][j] = floor((*p3)[k][i][j]+0.5);
		    }
	    }                
    }
}
	printf("Conv Completed!\n");
}
void conv2(Mat src, Mat *pdst,int kernel_size)
{
    cv::Mat kernel( kernel_size, kernel_size, CV_32F, cv::Scalar(0) );
    kernel.at<float>(0,0) = 1/16.0;
    kernel.at<float>(0,1) = 1/8.0;
    kernel.at<float>(0,2) = 1/16.0;
    kernel.at<float>(1,0) = 1/8.0;
    kernel.at<float>(1,1) = 1/4.0;
    kernel.at<float>(1,2) = 1/8.0;
    kernel.at<float>(2,0) = 1/16.0;
    kernel.at<float>(2,1) = 1/8.0;
    kernel.at<float>(2,2) = 1/16.0;
    
    /// Apply filter
    filter2D(src, *pdst, src.depth(), kernel, cv::Point(-1,-1), 0.0,0 );
}
  


int MaxPooling (int * pmW, int *pmS, int *pmF, int*pnChannels, float ****pp_mW, int ****pp_mR){

    printf("Enter Max Pooling Filter Size:");
    scanf("%d", pmF);
    printf("Enter Pooling Stride: ");
    scanf("%d", &*pmS);      
    int nMaxPool_Size = (*pmW- *pmF)/(*pmS)+1;
    if (nMaxPool_Size<=0)
        printf("Max Pooling Error :/");
    else{
        printf("Max Pooling Result Size : %d\n", nMaxPool_Size);
        *pp_mR = (int***)malloc(*pnChannels * sizeof(int **));
        for(int i=0; i< *pnChannels; i++){
            *((*pp_mR)+i) = (int**)malloc(nMaxPool_Size * sizeof(int*));
            for(int j=0; j< nMaxPool_Size;j++){
                *(*((*pp_mR)+i)+j) = (int *)malloc(nMaxPool_Size * sizeof(int));
            }
        }
        int nMax = 0;
        for(int k = 0; k < *pnChannels; k++){
            for(int i = 0; i < nMaxPool_Size; i++){
                for(int j = 0; j < nMaxPool_Size;j++){
                    nMax = 0;
                    for(int y = 0; y< *pmF; y++){     
                            for(int x = 0; x< *pmF; x++){
                                nMax = MAX(nMax , (*pp_mW)[k][y+i * (*pmS)][x+j * (*pmS)]);
                            }
                    }
                    (*pp_mR)[k][i][j] = nMax;
                }
            }
        }
    }
    return nMaxPool_Size;
}

void con_Activation_Func(int *pnChannels, int *pnFilters, int * pnResultSize , float ****p3){
    int b =0;
    for (int i = 0; i< *pnResultSize; i++){
        for(int j=0;j<*pnResultSize;j++){
            for(int k=0;k<*pnChannels;k++){
            (*p3)[k][i][j]= 1/(1 + exp(-((*p3)[k][i][j] + b)));
            }
        }
    }
}
