#include <iostream>
#include <chrono>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
using namespace std;
using namespace cv;

//Инверсия кадра.
void invert(Mat& img) {
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            cv::Vec3b& pixel = img.at<cv::Vec3b>(i, j);
            pixel[0] = 255 - pixel[0];
            pixel[1] = 255 - pixel[1];
            pixel[2] = 255 - pixel[2];
        }
    }
}

int main() {
    int frames = 1000;      //Количество кадров, обрабатываемых программой
    int input = 0;
    int process = 0;
    int output = 0;
    int time = 0;
    int wait = 0;
    //Создаётся поток ввода видеоданных с первой камеры (нумерация начинается с нуля).
    //Результат операции – дескриптор обрабатываемого потока видеоданных.
    VideoCapture capture(0);
    if (!capture.isOpened()) {
        return 0;
    }
    //Создаётся объект матрицы, в которую будем складывать кадр в цикле.
    Mat frame;
    int framesLeft = frames;
    while (0 < framesLeft--) {
        //Засекаем начало итерации.
        auto iterStart = chrono::system_clock::now();
        //На каждой итерации извлекаем кадр из открытого потока ввода видеоданных.
        //В image кладём дескриптор матрицы растрового изображения,
        //которое будет содержать один кадр из потока видеоданных.
        capture.read(frame);
        // Засекаем конец загрузки кадра.
        auto iterInput = chrono::system_clock::now();
        //Преобразование кадра.
        invert(frame);
        //Засекаем конец обработки кадра.
        auto iterProcess = chrono::system_clock::now();
        //Текущий кадр выводим в окно с именем Image
        imshow("Image", frame);
        //Засекаем конец вывода кадра.
        auto iterOutput = chrono::system_clock::now();
        //Ожидаем нажатие Escape от пользователя.
        char c = waitKey(30);
        if (c == 27) {
            break;
        }
        //Засекаем конец итерации.
        auto iterEnd = chrono::system_clock::now();
        //Вычисляем время, затраченное на каждый из процессов.
        input += chrono::duration_cast<std::chrono::milliseconds>(iterInput - iterStart).count();
        process += chrono::duration_cast<std::chrono::milliseconds>(iterProcess - iterInput).count();
        output += chrono::duration_cast<std::chrono::milliseconds>(iterOutput - iterProcess).count();
        time += chrono::duration_cast<std::chrono::milliseconds>(iterEnd - iterStart).count();
        wait += chrono::duration_cast<std::chrono::milliseconds>(iterEnd - iterOutput).count();
    }
    capture.release();
    destroyWindow("Image");
    //Выводим полученные данные.
    double inp = (double)input * 100 / time;
    double prc = (double)process * 100 / time;
    double out = (double)output * 100 / time;
    double frm = (double)(frames – framesLeft) * 1000 / time;
    double wtk = (double)wait * 100 / time;
    cout << "Average FPS: " << frm << endl;
    cout << "Input: " << inp << "%" << endl;
    cout << "Process: " << prc << "%" << endl;
    cout << "Output: " << out << "%" << endl;
    cout << "WaitKey: " << wtk << "%" << endl;
    return 0;
}
