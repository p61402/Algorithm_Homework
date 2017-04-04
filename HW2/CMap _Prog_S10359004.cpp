#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

typedef struct {
	int x;
	int y;
} Point;

int count;
int pos1, pos2;

double minDistance(Point*, int);
double maxDistance(Point*, int);
double Convex_Hull(Point*, int);
int Hungarian(Point*, Point*, int);
int cross(Point, Point);
double Distance(Point, Point);
void print_table(int [][100], int);

int main()
{
	FILE *fp;
	int n;
	Point station[100], scooter[100];
	int x;
	LARGE_INTEGER ThisTime, ThatTime, PinTime;

	fopen_s(&fp, "Map1.txt", "r");

	fscanf_s(fp, "%d", &n);

	for (int i = 0; i < n; i++)
	{
		fscanf_s(fp, "%d", &station[i].x);
		fscanf_s(fp, "%d", &station[i].y);
		//printf("%d %d\n", station[i][0], station[i][1]);
	}

	for (int i = 0; i < n; i++)
	{
		fscanf_s(fp, "%d", &scooter[i].x);
		fscanf_s(fp, "%d", &scooter[i].y);
		//printf("%d %d\n", scooter[i][0], scooter[i][1]);
	}

	//Problem 1
	QueryPerformanceFrequency(&PinTime);
	QueryPerformanceCounter(&ThisTime);
	printf("(1) The closest two stations.(Using Brute-Force Algorithm)\n");
	x = (int)minDistance(station, n);
	printf("Station no.%d(%d, %d) and Station no.%d(%d, %d) are closest.\n", pos1 + 1, station[pos1].x, station[pos1].y, pos2 + 1, station[pos2].x, station[pos2].y);
	printf("min: %d km\n", x);
	QueryPerformanceCounter(&ThatTime);
	printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

	//Problem 2
	QueryPerformanceFrequency(&PinTime);
	QueryPerformanceCounter(&ThisTime);
	printf("-------------------------------------------------------------------------------------------------");
	printf("\n(2) The clostest two scooters.(Using Brute-Force Algorithm)\n");
	x = (int)minDistance(scooter, n);
	printf("Scooter no.%d(%d, %d) and Scooter no.%d(%d, %d) are closest.\n", pos1 + 1, scooter[pos1].x, scooter[pos1].y, pos2 + 1, scooter[pos2].x, scooter[pos2].y);
	printf("min: %d km\n", x);
	QueryPerformanceCounter(&ThatTime);
	printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

	//Problem 3
	QueryPerformanceFrequency(&PinTime);
	QueryPerformanceCounter(&ThisTime);
	printf("-------------------------------------------------------------------------------------------------");
	printf("\n(3) The Area of all the stations, that is, find the Convex-Hull.(Using Brute-Force Algorithm)\n");
	int area1 = (int)Convex_Hull(station, n);
	printf("Area: %d\n", area1);
	QueryPerformanceCounter(&ThatTime);
	printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

	//Problem 4
	QueryPerformanceFrequency(&PinTime);
	QueryPerformanceCounter(&ThisTime);
	printf("-------------------------------------------------------------------------------------------------");
	printf("\n(4) The Area of all the scooters, that is, find the Convex-Hull.(Using Brute-Force Algorithm)\n");
	int area2 = (int)Convex_Hull(scooter, n);
	printf("Area: %d\n", area2);
	QueryPerformanceCounter(&ThatTime);
	printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

	//Problem 5
	QueryPerformanceFrequency(&PinTime);
	QueryPerformanceCounter(&ThisTime);
	printf("-------------------------------------------------------------------------------------------------");
	printf("\n(5) The efficient way to assign each scooter to a station.(Using Hungarian Algorithm)\n\n");
	int cost = Hungarian(scooter, station, n);
	printf("Total distance: %dkm\n", cost);
	printf("Total energy consumption: %.2fkwh/km\n", (double)cost * 0.024);
	QueryPerformanceCounter(&ThatTime);
	printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

	fclose(fp);

	system("pause");
	return 0;
}

double minDistance(Point* pos, int n)
{
	int adjacency_Matrix[100][100] = { 0 };
	int x, y, count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n, i != j; j++)
		{
			x = (pos[i].x - pos[j].x) * (pos[i].x - pos[j].x);
			y = (pos[i].y - pos[j].y) * (pos[i].y - pos[j].y);

			adjacency_Matrix[i][j] = x + y;
		}
	}

	count = 0;
	int min = 999999;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (adjacency_Matrix[i][j] <= min)
			{
				min = adjacency_Matrix[i][j];
				pos1 = i;
				pos2 = j;
			}
		}
	}

	return sqrt(min);
}

double maxDistance(Point* pos, int n)
{
	int adjacency_Matrix[100][100] = { 0 };
	int x, y, count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n, i != j; j++)
		{
			x = (pos[i].x - pos[j].x) * (pos[i].x - pos[j].x);
			y = (pos[i].y - pos[j].y) * (pos[i].y - pos[j].y);

			adjacency_Matrix[i][j] = x + y;
		}
	}

	count = 0;
	int max = 0;
	for (int i = 1; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (adjacency_Matrix[i][j] >= max)
			{
				max = adjacency_Matrix[i][j];
				pos1 = i;
				pos2 = j;
			}
		}
	}

	return sqrt(max);
}

double Convex_Hull(Point* pos, int n)
{
	int convex[100] = { 0 };
	int a, b, c;
	int oneSide, anotherSide;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			a = pos[j].y - pos[i].y;
			b = pos[i].x - pos[j].x;
			c = pos[i].x * pos[j].y - pos[i].y * pos[j].x;

			oneSide = 0;
			anotherSide = 0;
			for (int k = 0; k < n; k++)
			{
				if (a * pos[k].x + b * pos[k].y - c > 0)
				{
					oneSide++;
				}
				else if (a * pos[k].x + b * pos[k].y - c < 0)
				{
					anotherSide++;
				}
			}
			//printf("i=%d, j=%d, %d %d\n",i, j, oneSide, anotherSide);

			if ((oneSide > 0 && anotherSide == 0) || (oneSide == 0 && anotherSide > 0))
			{
				convex[i] = 1;
				convex[j] = 1;
			}
		}
	}

	Point newPos[100];
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (convex[i] == 1)
		{
			newPos[count].x = pos[i].x;
			newPos[count].y = pos[i].y;
			count++;
		}
	}

	/*
	for (int i = 0; i < count; i++)
	{
	printf("newArr[%d] = %d, %d\n", i, newArr[i].x, newArr[i].y);
	}
	*/

	//Calcualting the area
	double slope[100];		//the slpoe of every point to the leftmost point
	int minX = newPos[0].x;
	int minX_index = 0;

	//Find leftmost point (which have the smallest x value)
	for (int i = 1; i < count; i++)
	{
		if (newPos[i].x < minX)
		{
			minX = newPos[i].x;
			minX_index = i;
		}
		else if (newPos[i].x == minX)		//if x values are same, compare y value, pick the smaller one
		{
			if (newPos[i].y < newPos[minX_index].y)
			{
				minX = newPos[i].x;
				minX_index = i;
			}
		}
	}

	int delta_X, delta_Y;
	for (int i = 0; i < count; i++)
	{
		if (i != minX_index)
		{
			delta_X = newPos[i].x - newPos[minX_index].x;
			delta_Y = newPos[i].y - newPos[minX_index].y;

			if (delta_X == 0)
			{
				slope[i] = 99999 - newPos[i].y;
			}
			else
			{
				slope[i] = (double)delta_Y / delta_X;
			}
		}
		else
		{
			slope[i] = -99999;
		}
	}

	/*
	for (int i = 0; i < count; i++)
	{
		printf("slope[%d] = %f\n", i, slope[i]);
	}
	*/

	int slopeIndex[101];
	for (int i = 0; i < count; i++)
	{
		slopeIndex[i] = i;
	}

	//Sorting the slopes in ascending order
	for (int i = 1; i < count; i++)
	{
		double v = slope[i];
		int j = i - 1;
		int vIndex = slopeIndex[i];

		while (j >= 0 && slope[j] > v)
		{
			slope[j + 1] = slope[j];
			slopeIndex[j + 1] = slopeIndex[j];
			j--;
		}
		slope[j + 1] = v;
		slopeIndex[j + 1] = vIndex;
	}


	/*
	if (slopeIndex[0] == minX_index)
	{
	printf("Incredible! %d\n", slopeIndex[0]);
	}
	*/

	slopeIndex[count] = slopeIndex[0];	//important!!

	int area = 0;
	for (int i = 0; i < count; i++)
	{
		area += cross(newPos[slopeIndex[i]], newPos[slopeIndex[i + 1]]);
		//printf("area=%d\n", area);
	}

	int max_distance = (int)maxDistance(newPos, count);
	printf("max_distance=%d\n", max_distance);

	return abs(area) / 2;
}

int Hungarian(Point* position1, Point* position2, int n)
{
	int table[100][100];
	int tempTable[100][100];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			table[i][j] = (int)Distance(position1[i], position2[j]);
			tempTable[i][j] = table[i][j];
		}

	printf("Original\n");
	print_table(table, n);

	for (int i = 0; i < n; i++)
	{
		int min = table[i][0];
		for (int j = 1; j < n; j++)
		{
			if (table[i][j] < min)
			{
				min = table[i][j];
			}
		}

		for (int k = 0; k < n; k++)
		{
			table[i][k] -= min;
		}
	}

	//printf("\nStep 1\n");
	//print_table(table, n);

	for (int i = 0; i < n; i++)
	{
		int min = table[0][i];
		for (int j = 1; j < n; j++)
		{
			if (table[j][i] < min)
			{
				min = table[j][i];
			}
		}

		for (int k = 0; k < n; k++)
		{
			table[k][i] -= min;
		}
	}

	//printf("\nStep 2\n");
	//print_table(table, n);


	int sum;
	while (true)
	{
		sum = 0;
		int zero_count[100] = { 0 };
		Point zero_value[10000];
		int count = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (table[i][j] == 0)
				{
					zero_count[i]++;
					zero_value[count].x = i;
					zero_value[count].y = j;
					count++;
				}
			}
		}

		int execute_order[100];
		for (int i = 0; i < n; i++)
		{
			execute_order[i] = i;
		}

		for (int i = 1; i < n; i++)
		{
			int v = zero_count[i];
			int j = i - 1;
			int x = execute_order[i];
			while (j >= 0 && zero_count[j] > v)
			{
				zero_count[j + 1] = zero_count[j];
				execute_order[j + 1] = execute_order[j];
				j--;
			}
			zero_count[j + 1] = v;
			execute_order[j + 1] = x;
		}

		/*
		printf("execute order: ");
		for (int i = 0; i < n; i++)
		{
			printf("%d ", execute_order[i]);
		}
		printf("\n");
		*/

		bool CompleteAssign = true;
		int result[100];
		for (int i = 0; i < n; i++)
		{
			result[i] = -1;
		}
		int stopRow[100] = { 0 }, stopColumn[100] = { 0 };
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (table[execute_order[i]][j] == 0 && stopRow[execute_order[i]] == 0 && stopColumn[j] == 0)
				{
					if (result[j] >= 0)
					{
						//no complete assign
						CompleteAssign = false;
					}
					else
					{
						result[j] = execute_order[i];
						stopRow[execute_order[i]] = 1;
						stopColumn[j] = 1;
						//printf("%d %d\n", execute_order[i], j);
						break;
					}
				}
			}
		}

		int number = 0;
		for (int i = 0; i < n; i++)
		{
			if (result[i] < 0)
			{
				CompleteAssign = false;
			}
		}

		/*
		printf("\nStep 3\n");
		print_table(table, n);
		for (int i = 0; i < n; i++)
		{
			printf("%d ", result[i]);
		}
		printf("\n");
		*/

		//Final Answer
		//result[i] = j : the task i for worker j
		if (CompleteAssign)
		{
			printf("\nLast Step\n");
			print_table(table, n);
			printf("\nAssignment:\n");

			for (int i = 0; i < n; i++)
			{
				sum += tempTable[result[i]][i];
				printf("Station %d for Scooter %d\n", i + 1, result[i] + 1);
			}
			break;
		}

		int deleted_row[100] = { 0 }, deleted_column[100] = { 0 };
		for (int i = 0; i < count; i++)
		{
			if (deleted_row[zero_value[i].x] == 1 || deleted_column[zero_value[i].y] == 1)
			{
				continue;
			}

			int zeroNum_row = 0, zeroNum_col = 0;

			for (int a = 0; a < n; a++)
			{
				if (table[zero_value[i].x][a] == 0)
				{
					zeroNum_row++;
				}
			}

			for (int b = 0; b < n; b++)
			{
				if (table[b][zero_value[i].y] == 0)
				{
					zeroNum_col++;
				}
			}

			if (zeroNum_row >= zeroNum_col)
			{
				deleted_row[zero_value[i].x] = 1;
			}
			else
			{
				deleted_column[zero_value[i].y] = 1;
			}
		}

		/*
		printf("\nStep 4\n");
		printf("Row: ");
		for (int x = 0; x < n; x++)
		{
			if (deleted_row[x] == 1)
			{
				printf("%d, ", x);
			}
		}
		printf("Column: ");
		for (int x = 0; x < n; x++)
		{
			if (deleted_column[x] == 1)
			{
				printf("%d, ", x);
			}
		}
		*/

		//Find the minimum value from the unmarked elements
		int min = 999999;
		for (int i = 0; i < n; i++)
		{
			if (deleted_row[i] == 1)
			{
				continue;
			}

			for (int j = 0; j < n; j++)
			{
				if (deleted_column[j] == 1)
				{
					continue;
				}

				if (table[i][j] < min)
				{
					min = table[i][j];
				}
			}
		}

		bool isNegative[100] = { false };
		for (int i = 0; i < n; i++)
		{
			if (deleted_row[i] == 0)
			{
				for (int j = 0; j < n; j++)
				{
					table[i][j] -= min;
					if (table[i][j] < 0)
					{
						isNegative[j] = true;
					}
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (isNegative[i])
			{
				for (int j = 0; j < n; j++)
				{
					table[j][i] += min;
				}
			}
		}

		//printf("\nStep 5\n");
		//print_table(table, n);
	}

	return sum;
}

int cross(Point p1, Point p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

double Distance(Point p1, Point p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void print_table(int table[][100], int n)
{
	printf("Cost Table | ");
	for (int i = 0; i < n; i++)
	{
		printf("station%3d | ", i + 1);
	}
	printf("\n");

	printf("------------");
	for (int i = 0; i < n; i++)
	{
		printf("-------------");
	}
	printf("\n");


	for (int i = 0; i < n; i++)
	{
		printf("scooter%3d | ", i + 1);
		for (int j = 0; j < n; j++)
		{
			printf(" %7d   | ", table[i][j]);
		}
		printf("\n");
	}
}