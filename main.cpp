#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

const cv::String photoPath = R"(pics\hot-charcoal.jpg)";
const cv::String addPhotoPath = R"(pics\smile.png)";

void onMouse(int event, int x, int y, int flags, void *param) {
    Mat *im = reinterpret_cast<Mat *>(param);
    switch (event) { // Диспетчимо подію
        case EVENT_LBUTTONDOWN:
            cout << "at (" << x << "," << y << ") gray value is:" << static_cast<int>(im->at<uchar>(Point(x, y)))
                 << endl;
            break;
    }
}

int main(int argc, char *argv[]) {
    cv::Mat ima(500,500,CV_8U,50);
    // 1. Зчитування зображення
    Mat image;
    image = imread(photoPath);
    namedWindow("Original image");
    imshow("Original image", image);

    // 2. Перевертання зображення за допомогою функції flip()
    Mat result;
    flip(image, result, 0);
    namedWindow("Flipped image0");
    imshow("Flipped image0", result);

    flip(image, result, -1);
    namedWindow("Flipped image2");
    imshow("Flipped image2", result);

    flip(image, image, 1);
    namedWindow("Flipped in place");
    imshow("Flipped in place", image);
    //imwrite("flip.bmp", result);

    // 3. Зчитування зображення як 3х канального, кольорового
    image = imread(photoPath, IMREAD_COLOR);
    namedWindow("COLOR");
    imshow("COLOR", image);
    cout << "Image size: " << image.rows << " x " << image.cols << endl;
    cout << "Image channels: " << image.channels() << endl;

    // 4. Зчитування зображення в градаціях сірого
    image = imread(photoPath, IMREAD_GRAYSCALE);
    namedWindow("GRAYSCALE");
    imshow("GRAYSCALE", image);

    setMouseCallback("GRAYSCALE", onMouse, reinterpret_cast<void *>(&image));

    // 5.  Малювання фігурами по фото
    image = imread(photoPath);
    circle(image,
           Point(150, 200),
           40,
           Scalar(0, 255, 255),
           3,
           3
    );

    int nWidth = image.cols;
    int nHeight = image.rows;
    ellipse(image,
            Point(nWidth / 6, nHeight / 4),
            Size(nWidth / 10, nWidth / 16),
            30,
            0,
            360,
            Scalar(100, 210, 0),
            2,
            8
    );

    Rect r = Rect(165, 59, 40, 60);
    rectangle(image,
              r,
              Scalar(50, 23, 200),
              10,
              8,
              0
    );
    namedWindow("FIGURES");
    imshow("FIGURES", image);

    // 6. Текст на фото
    image = imread(photoPath);
    putText(image,
            "By Demydenko M.B.",
            Point(5, 40),
            FONT_HERSHEY_PLAIN,
            1.5,
            Scalar(255, 255, 255),
            2
    );
    namedWindow("TEXT");
    imshow("TEXT", image);

    // 7. Накладення зверху іншого зображення
    Mat addPhotoMat = imread(addPhotoPath);
    image = imread(photoPath);
    Rect Rec(0, 0, 200, 200);
    rectangle(addPhotoMat,
              Rec,
              Scalar(255),
              0,
              1,
              0
    );
    Mat Roi = addPhotoMat(Rec);
    Rect WhereRec(40, 40, Roi.cols, Roi.rows);
    Roi.copyTo(image(WhereRec));
    namedWindow("IMAGE INSERTION", WINDOW_AUTOSIZE);
    imshow("IMAGE INSERTION", image);


    // 8. Накладення зверху іншого зображення за допомогою маски
    image = imread(photoPath);

    Mat imageROI = image(cv::Rect(40, 40, 200, 200));
    cv::Mat mask(addPhotoMat);
    addPhotoMat.copyTo(imageROI, mask);
    namedWindow("IMAGE INSERTION MASK", WINDOW_AUTOSIZE);
    imshow("IMAGE INSERTION MASK", image);

    waitKey(0);
    return 0;
}
