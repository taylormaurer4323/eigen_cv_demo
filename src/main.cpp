#include <iostream>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>


namespace test_functions {

    void cv2eigen2cv_test(){
        //Some Eigen tips,
        //Doing the following is generally not recommanded and will fail because you are tyriong
        //to allocate too much memory locally (ie. on the stack)
        //Eigen::Matrix<float, 512, 512> image_eig;
        //Instead dynamically allocate on the heap using
        std::cout<<"cv2eigen2cv_test\n";
        Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> image_eig;

        cv::Mat image_cv;
        image_cv = cv::imread("/mnt/e/projects/new_project/src/lena_img.png", cv::IMREAD_GRAYSCALE);

        std::cout<<"    size of CV Image: <"<<image_cv.rows<<" x "<<image_cv.cols<<" x "<<image_cv.channels()<<">"<<std::endl;

        //Convert into the eigen array
        cv::cv2eigen(image_cv, image_eig);

        std::cout<<"    Size of EIG array "<<image_eig.rows()<<" x "<<image_eig.cols()<<std::endl;

        cv::eigen2cv(image_eig, image_cv);
        std::cout<<"    size of CV Image back as image_cv: <"<<image_cv.rows<<" x "<<image_cv.cols<<" x "<<image_cv.channels()<<">"<<std::endl;

        cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
        //opencv does a display on the order of magnitude of 0 to 1. OpenCV displays float/double from 0 to 1, and then saves
        //it from 0 to 255. Since we force that conversion into Eigen that's what is happening
        cv::imshow("Display Image", image_cv*(1.0/255.0));
        cv::waitKey(0);
    }

    void eigen_image_shift_test()
    {
        std::cout<<"Is image shift a thing??\n";
        cv::Mat image_cv = cv::imread("/mnt/e/projects/new_project/src/lena_img.png", cv::IMREAD_GRAYSCALE);
        //Convert to eigen to perform the test
        Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> image_eig;

        cv::cv2eigen(image_cv, image_eig);

       //create a new image thats the size of the image but+2 in the width direction
       //trying to create image shift, and then will do subtraction to get the image difference (gradient)
       int s_r = 1; int s_c = 1;
       Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> image_eig_shift = image_eig.block(s_r, s_c, image_eig.rows() - s_r, image_eig.cols() - s_c);              
       std::cout<<"IMAGE EIG SIZE: "<<image_eig.rows()<<" x "<<image_eig.cols()<<std::endl;
       std::cout<<"IMAGE image_eig_shift SIZE: "<<image_eig_shift.rows()<<" x "<<image_eig_shift.cols()<<std::endl;
       //Now you have to remove the non-matching columns at the end since it won't have any difference
       Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> image_eig_sub = image_eig.block(0, 0, image_eig.rows() - s_r, image_eig.cols() - s_c);
       std::cout<<"IMAGE image_eig_sub SIZE: "<<image_eig_sub.rows()<<" x "<<image_eig_sub.cols()<<std::endl;
       //NOw matrix subntraction...
       Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> image_diff = image_eig_sub - image_eig_shift;
       cv::eigen2cv(image_diff, image_cv);
       cv::namedWindow("display image", cv::WINDOW_AUTOSIZE);
       cv::imshow("display image", image_cv*(1.0/255.0));
       cv::waitKey(0);
    }




} /* END test_functions */


int main() {

    //test_functions::cv2eigen2cv_test();    
    test_functions::eigen_image_shift_test();
    return 0;
    //this works and I guess xwindows is forwarded horray! Next step is take gradient of image
    //as that will be required to do a lot of the Horn/Shuck method
}