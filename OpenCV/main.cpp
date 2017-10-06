#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
//using namespace std;
//группа 4 Photoshop, GIMP (0.3 Red+ 0.59 Green + 0.11 Blue)


int main()
{
	Mat source;
	source = imread("circles.jpg");
	Mat inv_source = Mat::zeros(source.size(), CV_8UC3);// создание матрицы одинакого размера с source,
														//тип каждого элемента матрицы - трехкомпонентный вектоsр,
														//каждый элемент этого вектора кодируется unsigned char
														//инициализация нулями
	for (int i = 0; i < source.rows; ++i)
		for (int j = 0; j < source.cols; ++j)
			inv_source.at<Vec3b>(i, j) = Vec3b(255, 255, 255) - source.at<Vec3b>(i, j);

	//EDITED
	namedWindow("important", CV_WINDOW_NORMAL);	//}
	Mat inv_source8U;							// }
	inv_source.convertTo(inv_source8U, CV_8U);	// } - все это необходимо для работы imshow()
	imshow("inv_source8U", inv_source8U);
	imshow("source", source);
	waitKey(0);									//}
	//destroyAllWindows();

	Mat gray = Mat::zeros(source.size(), CV_8UC3);
	Mat inv_gray = Mat::zeros(source.size(), CV_8U); // аналогично предыдущему случаю, только каждый элемент матрицы - unsigned char

	//cvtColor(inv_source, gray, CV_BGR2GRAY); // использовать это не будем
	for (int i = 0; i < gray.rows; ++i)
		for (int j = 0; j < gray.cols; ++j)
		{
			int R = source.at<Vec3b>(i, j).val[0];
			int G = source.at<Vec3b>(i, j).val[1];
			int B = source.at<Vec3b>(i, j).val[2];
			int luminance = R*0.3 + G*0.59 + B*0.11;
			gray.at<Vec3b>(i, j).val[0] = luminance;	//R
			gray.at<Vec3b>(i, j).val[1] = luminance;	//G
			gray.at<Vec3b>(i, j).val[2] = luminance;	//B
		}
	imwrite("4_gray.jpg", gray);				// Просто посмотреть что на выходе

	return 0;
}