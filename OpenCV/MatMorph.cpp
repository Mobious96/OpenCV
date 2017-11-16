#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <time.h>
#include <math.h>
using namespace cv;
class TMatrix
{
	int H, W;
	int** matrix;
public:
	int GetH()
	{
		return H;
	}
	int GetW()
	{
		return W;
	}
	int** GetMatrix()
	{
		return matrix;
	}

	TMatrix(int _H, int _W)
	{
		H = _H;
		W = _W;
		matrix = new int*[H];
		for (int i = 0; i < H; i++)
		{
			matrix[i] = new int[W];
		}
	}


	void InitMatrix()
	{
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				//if((i == H/2)&&(j==W/2))//центральный пиксель
				//	matrix[i][j] = 0;
				//else
					matrix[i][j] = 1;
			}
	}

	int FindMaxInMat(Mat& image, int source_i, int source_j)
	{
		int max = 0;
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if ((matrix[i][j]) && (image.at<uchar>(source_i + (i-H/2), source_j + (j-W/2)) > max))
				{
					max = image.at<uchar>(source_i + (i - H / 2), source_j + (j - W / 2));
				}
			}
		return max;
	}
	int FindMinInMat(Mat& image, int source_i, int source_j)
	{
		int min = 255;
		for (int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if ((matrix[i][j]) && (image.at<uchar>(source_i + (i - H / 2), source_j + (j - W / 2)) < min))
				{
					min = image.at<uchar>(source_i + (i - H / 2), source_j + (j - W / 2));
				}
			}
		return min;
	}
};
Mat Dilation(Mat &source, TMatrix &mask)
{
	Mat result = Mat::zeros(source.size(), CV_8UC1);
	for (int i = mask.GetH()/2; i < result.rows-mask.GetH()/2; i++)
		for (int j = mask.GetW()/2; j < result.cols-mask.GetW()/2; j++)
		{
			result.at<uchar>(i,j) = mask.FindMaxInMat(source, i, j);
		}
	return result;
}
Mat Erosion(Mat &source, TMatrix &mask)
{
	Mat result;// = Mat::zeros(source.size(), CV_8UC1);
	source.copyTo(result);
	for (int i = mask.GetH() / 2; i < result.rows - mask.GetH() / 2; i++)
		for (int j = mask.GetW() / 2; j < result.cols - mask.GetW() / 2; j++)
		{
			result.at<uchar>(i, j) = mask.FindMinInMat(source, i, j);
		}
	return result;
}
int RayleighRand(int sigma, int max)
{
	double u = (double)((1.0*rand()) / RAND_MAX);
	double rmax = sigma*sqrt(-2.0 * log(0.01));
	double r = double(sqrt(-2.0*(pow(sigma,2)*log(u))) / rmax) * max;
	return r;
}
Mat Noise(Mat &source, int sigma, int max, int percent)
{
	int count = 0;
	Mat result;// = Mat::zeros(source.size(), CV_8UC1);
	source.copyTo(result);
	for (int i = 0; i < ((source.rows*source.cols) / 100) * percent; i++)
	{
		result.at<uchar>(rand() % source.rows, rand() % source.cols) = RayleighRand(sigma, max);
	}
	return result;
}
int main()
{
	srand(time(0));
	Mat source;
	source = imread("test.png", 0); // 0 - import as grayscale image.
	TMatrix mask(3, 3);
	mask.InitMatrix();
	imwrite("4_Dilation.png", Dilation(source, mask));
	imwrite("4_Erosion.png", Erosion(source, mask));

	imwrite("4_Noise.png", Noise(source, 1, 255, 5));
	Mat noise = imread("4_Noise.png", 0);
	imwrite("4_Dilation_N.png", Dilation(noise, mask));
	imwrite("4_Erosion_N.png", Erosion(noise, mask));
	imwrite("4_Rayleigh.png", Dilation(Erosion(noise, mask), mask));
	//system("pause");
	return 0;
}