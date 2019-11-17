#include<iostream>
#include<stdio.h>
#include <sys/time.h>
using namespace std;
double GetWallTime() {
struct timeval tp;
int rtn = gettimeofday(&tp, NULL);
return ((double) tp.tv_sec + (1.e-6)*tp.tv_usec);
}
int main(int argc, char ** argv)
{
	bool flag_file=1;
	if (argc >= 3) {
		double start = GetWallTime();
		char * image = argv[1];
		char * mask = argv[2];
		char * newImg = argv[3];
		int * * image2D;
		int  mask2D[3][3];
		int imagedimension[2];
		FILE * readImg = fopen(image, "r+");
		FILE * readMask = fopen(mask, "r+");
		FILE * storeImg = fopen(newImg, "w+");
		fscanf(readImg, "%d %d", &imagedimension[0], &imagedimension[1]);
		int * * newimage;
		image2D = new int *[imagedimension[0]];
		newimage = new  int *[imagedimension[0]];
		for (int i = 0; i < imagedimension[0]; i++) {
			image2D[i] = new int[imagedimension[1]];
			newimage[i] = new int[imagedimension[1]];
		}
		for (int i = 0; i < imagedimension[0]; i++) {
			for (int j = 0; j < imagedimension[1]; j++) {
				fscanf(readImg, "%d", &image2D[i][j]);
				newimage[i][j] = image2D[i][j];
			}
		}
		int maskrow = 0, maskcol = 0;
		while (!feof(readMask))
		{
			if (maskcol < 3 && maskrow < 3) {
				fscanf(readMask, "%d", &mask2D[maskrow][maskcol]);
				maskcol++;
			}
			else if (maskrow > 3)
				break;
			else
			{
				maskrow++;
				maskcol = 0;
			}

		}
		fclose(readImg);
		int summation = 0;
		int row, col;
		for (int i = 0; i < imagedimension[0] && (i + 2) <imagedimension[0]; )
		{
			row = i;
			for (int j = 0; j < imagedimension[1] && (j + 2) < imagedimension[1];  row = row - 3)
			{
				col = j;
				for (int maskr = 0; maskr < 3; maskr++, row++, col = col - 3)
				{
					for (int maskc = 0; maskc < 3; maskc++, col++)
					{
						
						summation =summation+ image2D[row][col] * mask2D[maskr][maskc];
						
					//	cout << " row = " << row << " col = " << col << " maskr = " << maskr << " maskc = " << maskc << endl;
						
					
						
						
					}
				}
				if(flag_file==0)
				summation = summation/16;
				fprintf(storeImg, "%d ", summation);
				newimage[i+1][j+1] = summation;
				summation = 0;
				j++;
			}
			fprintf(storeImg, "\n");
			i++;
		}
		double finish = GetWallTime();
		cout << "Elapsed time = "<< finish - start << endl;
	}

	return 0;
}

