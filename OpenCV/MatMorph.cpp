#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
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
				if((i == H/2)&&(j==W/2))//центральный пиксель
					matrix[i][j] = 0;
				else
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
int main()
{
	Mat source;
	source = imread("test.png", 0);
	TMatrix mask(3, 3);
	mask.InitMatrix();
	imwrite("4_Dilation.png", Dilation(source, mask));
	return 0;
}