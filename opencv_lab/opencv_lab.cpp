#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>  

using namespace std;
using namespace cv;
using namespace std::chrono;

void print_FPS_Share(long double in_total, long double transform_total, long double show_total, size_t frame_count) {
    long double total_duration = in_total + transform_total + show_total;

    long double in_share = (in_total / total_duration) * 100.0;
    long double transform_share = (transform_total / total_duration) * 100.0;
    long double show_share = (show_total / total_duration) * 100.0;

    long double fps = frame_count / total_duration;

    cout << "Общее количество кадров: " << frame_count << endl;
    cout << "Общая продолжительность обработки: " << total_duration << " секунд" << endl;
    cout << "FPS: " << fps << " кадров/сек" << endl;
    cout << "Доля времени на ввод: " << in_share << "%" << endl;
    cout << "Доля времени на обработку: " << transform_share << "%" << endl;
    cout << "Доля времени на показ: " << show_share << "%" << endl;
}

int main() {
    long double in_total = 0;
    long double transform_total = 0;
    long double show_total = 0;
    size_t frame_count = 0;

    VideoCapture cap(0);
    Mat img;
    
    for (;;) {
        auto start = high_resolution_clock::now();

        cap.read(img);  
        auto in_time = high_resolution_clock::now();

        Mat processed_img;
        GaussianBlur(img, processed_img, Size(15, 15), 0);
        auto transform_time = high_resolution_clock::now();

        imshow("OpenCVLab", processed_img);
        auto show_time = high_resolution_clock::now();

        auto in_duration = duration_cast<duration<long double>>(in_time - start).count();
        auto transform_duration = duration_cast<duration<long double>>(transform_time - in_time).count();
        auto show_duration = duration_cast<duration<long double>>(show_time - transform_time).count();

        in_total += in_duration;
        transform_total += transform_duration;
        show_total += show_duration;
        frame_count++;

        if (frame_count % 100 == 0) {
            print_FPS_Share(in_total, transform_total, show_total, frame_count);
        }

        if (waitKey(30) == 'q') {
            break;
        }
    }

    print_FPS_Share(in_total, transform_total, show_total, frame_count);

    return 0;
}
