#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>

using namespace cv;
using namespace std;

int computeOutput(int, int, int, int, int);

int main()
{
    Mat image = imread("/home/../lenna.jpg");
    Mat new_image = image.clone();

    //cvtColor( new_image, new_image, COLOR_BGR2GRAY );

    int r1, s1, r2, s2;

    r1 = 90;
    s1 = 150;
    r2 = 150;
    s2 = 255;

 /*   cout<<"Enter r1: "<<endl; cin>>r1;
    cout<<"Enter s1: "<<endl; cin>>s1;
    cout<<"Enter r2: "<<endl; cin>>r2;
    cout<<"Enter s2: "<<endl; cin>>s2;*/



    for(int y = 0; y < image.rows; y++){
        for(int x = 0; x < image.cols; x++){
            for(int c = 0; c < 3; c++){
                int output = computeOutput(image.at<Vec3b>(y,x)[c], r1, s1, r2, s2);
                new_image.at<Vec3b>(y,x)[c] = saturate_cast<uchar>(output);
                if (y == 1 && x ==1 &&  c ==0)     cout<<"\nRed channel  => "<< "x =  "<<(int)image.at<Vec3b>(y,x)[c] <<" output =  " << output;
                if (y == 1 && x ==1 &&  c ==1)     cout<<"\nGreen channel=> "<< "x =  "<<(int)image.at<Vec3b>(y,x)[c] <<" output =  " << output;
                if (y == 1 && x ==1 &&  c ==2)     cout<<"\nBlue channel => "<< "x =  "<<(int)image.at<Vec3b>(y,x)[c] <<" output =  " << output;
            }
        }
    }

    namedWindow("Original Image", 1);
    imshow("Original Image", image);

    namedWindow("New Image", 1);
    imshow("New Image", new_image);

    waitKey();

    return 0;
}

int computeOutput(int x, int r1, int s1, int r2, int s2)
{


    float result;
    if(0 <= x && x <= r1){
        result = s1/r1 * x;
    }else if(r1 < x && x <= r2){
        result = ((s2 - s1)/(r2 - r1)) * (x - r1) + s1;
    }else if(r2 < x && x <= 255){
        result = ((255 - s2)/(255 - r2)) * (x - r2) + s2;
    }
    return (int)result;
}