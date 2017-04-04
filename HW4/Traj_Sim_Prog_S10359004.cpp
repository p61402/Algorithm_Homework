#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <time.h>
#include <Windows.h>
#define MAX_PLACES_NUM 10

using namespace std;

const string Place[MAX_PLACES_NUM] = { "南大宿舍", "早餐店", "府城校區", "榮譽校區", "學餐", "大東夜市", "杜卡勒小廚", "觀夕平台", "黃金海岸", "夢時代" };

double Find_LCS(vector<int>& lcs_route, int route[][20], int time[][20], int l1, int l2);	//Find LCS of two and return the similarity
void store_LCS(int i, int j, int s[], int pre[][21], vector<int>& route);
double Similarity(vector<int>& route, int travel[][20], int time[][20], int length);
void LCS_two_persons();
void LCS_n_persons(int humanbeings);
void LCS_you_and_n_persons(int humanbeings);

int main()
{
	LARGE_INTEGER ThisTime, ThatTime, PinTime;
	int humanbeings;

	cout << "(1)隨機產生2位同學的移動軌跡與駐留時間的序列，分析兩位同學移動軌跡的相似度\n\n";
	QueryPerformanceFrequency(&PinTime);
	QueryPerformanceCounter(&ThisTime);
	LCS_two_persons();
	QueryPerformanceCounter(&ThatTime);
	printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);
	cout << "----------------------------------------------------------------------------------\n";

	cout << "\n(2)隨機產生n位同學的移動軌跡與駐留時間的序列，並找出哪兩位同學的移動軌跡相似度最高\n\n";
	cout << "輸入人數(介於2~100): ";
	cin >> humanbeings;
	while (humanbeings < 2 || humanbeings > 100)
	{
		cout << "錯誤的輸入範圍! 人數必須介於2~100之間。\n";
		cout << "輸入人數(介於2~100): ";
		cin >> humanbeings;
	}
	QueryPerformanceFrequency(&PinTime);
	QueryPerformanceCounter(&ThisTime);
	LCS_n_persons(humanbeings);
	QueryPerformanceCounter(&ThatTime);
	printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);
	cout << "----------------------------------------------------------------------------------\n";
	
	cout << "\n(3)隨機產生n位同學的移動軌跡與駐留時間的序列，並找出哪位同學與你的的移動軌跡相似度最高\n";
	cout << "輸入人數(介於2~100): ";
	cin >> humanbeings;
	while (humanbeings < 2 || humanbeings > 100)
	{
		cout << "錯誤的輸入範圍! 人數必須介於2~100之間。\n";
		cout << "輸入人數(介於2~100): ";
		cin >> humanbeings;
	}
	QueryPerformanceFrequency(&PinTime);
	QueryPerformanceCounter(&ThisTime);
	LCS_you_and_n_persons(humanbeings);
	QueryPerformanceCounter(&ThatTime);
	printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

	system("pause");
	return 0;
}

double Find_LCS(vector<int>& lcs_route, int route[][20], int time[][20], int l1, int l2)
{
	int DP[21][21];
	int pre[21][21];	//top-left: 0, top: 1, left: 2
	int s1[21];
	int s2[21];

	/*
	for (int i = 0; i < l1; i++)
	{
		cout << route[0][i];
	}
	cout << endl;
	*/

	//cout << l1 << " " << l2 << endl;

	s1[0] = 0;
	s2[0] = 0;
	for (int i = 1; i <= l1; i++)
	{
		s1[i] = route[0][i-1];
	}
	for (int i = 1; i <= l2; i++)
	{
		s2[i] = route[1][i-1];
	}

	/*
	for (int x = 0; x <= l1; x++)
	{
		cout << s1[x];
	}
	cout << endl;

	for (int x = 0; x <= l2; x++)
	{
		cout << s2[x];
	}
	cout << endl;
	*/

	//cout << "\nTable:\n";
	for (int i = 0; i <= l1; i++)
	{
		DP[i][0] = 0;
	}
	for (int i = 0; i <= l2; i++)
	{
		DP[0][i] = 0;
	}

	for (int i = 1; i <= l1; i++)
	{
		for (int j = 1; j <= l2; j++)
		{
			if (s1[i] == s2[j])
			{
				DP[i][j] = DP[i - 1][j - 1] + 1;
				pre[i][j] = 0;
			}
			else
			{
				if (DP[i-1][j] < DP[i][j-1])
				{
					DP[i][j] = DP[i][j - 1];
					pre[i][j] = 1;
				}
				else
				{
					DP[i][j] = DP[i - 1][j];
					pre[i][j] = 2;
				}
			}
			//cout << DP[i][j] << " ";
		}
		//cout << endl;
	}

	//cout << "Length: " << DP[l1][l2] << endl;

	
	//cout << "LCS:";
	store_LCS(l1, l2, s1, pre, lcs_route);
	/*
	for (unsigned int i = 0; i < lcs_route.size(); i++)
	{
		cout << Place[lcs_route.at(i)];

		if (i != lcs_route.size() - 1)
		{
			cout << "->";

		}
	}
	cout << endl;
	*/

	return Similarity(lcs_route, route, time, max(l1, l2));
}

void store_LCS(int i, int j, int s[], int pre[][21], vector<int>& route)
{
	if (i == 0 || j == 0)
		return;

	if (pre[i][j] == 0)
	{
		store_LCS(i - 1, j - 1, s, pre, route);
		route.push_back(s[i]);
		//cout << s[i];
	}
	else if (pre[i][j] == 1)
		store_LCS(i, j - 1, s, pre, route);
	else if (pre[i][j] == 2)
		store_LCS(i - 1, j, s, pre, route);
}

double Similarity(vector<int>& route, int travel[][20], int time[][20], int length)
{
	int t1, t2;
	int x = 0, y = 0;
	int high, low;
	double similarity = 0.0;

	/*
	for (unsigned int i = 0; i < route.size(); i++)
	{
		cout << "route[i]: " << route.at(i) << endl;
	}

	cout << "travel 01\n";
	for (int i = 0; i < 20; i++)
	{
		cout << travel[0][i] << " ";
	}
	cout << endl;
	cout << "travel 02\n";
	for (int i = 0; i < 20; i++)
	{
		cout << travel[1][i] << " ";
	}
	cout << endl;
	*/

	for (unsigned int i = 0; i < route.size(); i++)
	{
		for (; x < 20; x++)
		{
			if (travel[0][x] == route.at(i))
			{
				t1 = time[0][x];
				break;
			}
		}

		for (; y < 20; y++)
		{
			if (travel[1][y] == route.at(i))
			{
				t2 = time[1][y];
				break;
			}
		}

		//cout << "t1 t2: " << t1 << " " << t2 << endl;

		high = max(t1, t2);
		low = min(t1, t2);

		//cout << "high low: " << high << " " << low << endl;

		similarity += (double)low / high;;

		//cout << "similarity: " << similarity << endl;
		//cout << endl;
	}

	similarity /= length;

	return similarity;
}

void LCS_two_persons()
{
	int trajectory[2][20];
	int stay_time[2][20];
	int numOfplaces[2];

	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);

	for (int n = 0; n < 2; n++)
	{
		numOfplaces[n] = rand() % 15 + 5;

		for (int i = 0; i < numOfplaces[n]; i++)
		{
			trajectory[n][i] = rand() % MAX_PLACES_NUM;
		}

		for (int i = 0; i < numOfplaces[n]; i++)
		{
			stay_time[n][i] = rand() % 100;
		}
	}
	
	/*
	for (int j = 0; j < numOfplaces[0]; j++)
	{
		cout << trajectory[0][j] << " ";
	}
	cout << endl;

	for (int j = 0; j < numOfplaces[1]; j++)
	{
		cout << trajectory[1][j] << " ";
	}
	cout << endl;
	*/
	
	vector<int> LCS_route;
	double similarity;

	similarity = Find_LCS(LCS_route, trajectory, stay_time, numOfplaces[0], numOfplaces[1]);

	cout << "結果:\n";
	cout << "LCS路徑為: ";
	for (unsigned int i = 0; i < LCS_route.size(); i++)
	{
		cout << Place[LCS_route.at(i)];

		if (i != LCS_route.size() - 1)
		{
			cout << "->";
		}
	}
	cout << endl;

	cout << "相似度: " << similarity << endl;
}

void LCS_n_persons(int humanbeings)
{
	int trajectory[100][20];
	int stay_time[100][20];
	int numOfplaces[100];
	double similarity[100][100];

	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);

	for (int n = 0; n < humanbeings; n++)
	{
		numOfplaces[n] = rand() % 15 + 5;

		for (int i = 0; i < numOfplaces[n]; i++)
		{
			trajectory[n][i] = rand() % MAX_PLACES_NUM;
		}

		for (int i = 0; i < numOfplaces[n]; i++)
		{
			stay_time[n][i] = rand() % 100;
		}
	}

	int temp_trajectory[2][20], temp_stay_time[2][20];

	for (int i = 0; i < humanbeings; i++)
	{
		for (int j = 0; j < humanbeings; j++)
		{
			if (i != j)
			{
				vector<int> LCS_route;

				for (int x = 0; x < 20; x++)
				{
					temp_trajectory[0][x] = trajectory[i][x];
					temp_stay_time[0][x] = stay_time[i][x];

					temp_trajectory[1][x] = trajectory[j][x];
					temp_stay_time[1][x] = stay_time[j][x];
				}

				similarity[i][j] = Find_LCS(LCS_route, temp_trajectory, temp_stay_time, numOfplaces[i], numOfplaces[j]);
			}
		}
	}

	double max_similarity = 0;
	int the_two_persons[2];
	for (int i = 0; i < humanbeings; i++)
	{
		for (int j = 0; j < humanbeings; j++)
		{
			if (i != j && similarity[i][j] > max_similarity)
			{
				max_similarity = similarity[i][j];
				the_two_persons[0] = i;
				the_two_persons[1] = j;
			}
		}
	}

	for (int x = 0; x < 20; x++)
	{
		temp_trajectory[0][x] = trajectory[the_two_persons[0]][x];
		temp_stay_time[0][x] = stay_time[the_two_persons[0]][x];

		temp_trajectory[1][x] = trajectory[the_two_persons[1]][x];
		temp_stay_time[1][x] = stay_time[the_two_persons[1]][x];
	}

	vector<int> LCS_route;
	Find_LCS(LCS_route, temp_trajectory, temp_stay_time, numOfplaces[the_two_persons[0]], numOfplaces[the_two_persons[1]]);

	cout << "\n結果:\n";
	cout << "同學" << the_two_persons[0] << "與同學" << the_two_persons[1] << "的相似度最高\n";
	cout << "LCS路徑為: ";
	for (unsigned int i = 0; i < LCS_route.size(); i++)
	{
		cout << Place[LCS_route.at(i)];

		if (i != LCS_route.size() - 1)
		{
			cout << "->";
		}
	}
	cout << "\n相似度為: " << max_similarity << endl;
}

void LCS_you_and_n_persons(int humanbeings)
{
	int my_trajectory[20] = { 0, 6, 5, 3, 7, 8, 4, 2, 0 };
	int my_stay_time[20] = { 23, 48, 36, 65, 87, 65, 98, 12, 40 };
	int my_numOfplaces = 9;
	int trajectory[100][20];
	int stay_time[100][20];
	int numOfplaces[100];
	double similarity[100];
	double threshold = 0.3;	//the threshhold of similarity (greater than or equal to 0 and smaller than or equal to 1)

	cout << "我的路徑為:";
	for (int i = 0; i < my_numOfplaces; i++)
	{
		cout << Place[my_trajectory[i]];

		if (i != my_numOfplaces - 1)
		{
			cout << "->";
		}
		else
		{
			cout << endl;
		}
	}

	cout << "相似度的最低門檻值預設為: " << threshold << endl;

	unsigned seed;
	seed = (unsigned)time(NULL);
	srand(seed);

	for (int n = 0; n < humanbeings; n++)
	{
		numOfplaces[n] = rand() % 15 + 5;

		for (int i = 0; i < numOfplaces[n]; i++)
		{
			trajectory[n][i] = rand() % MAX_PLACES_NUM;
		}

		for (int i = 0; i < numOfplaces[n]; i++)
		{
			stay_time[n][i] = rand() % 100;
		}
	}

	int temp_trajectory[2][20], temp_stay_time[2][20];
	for (int x = 0; x < 20; x++)
	{
		temp_trajectory[0][x] = my_trajectory[x];
		temp_stay_time[0][x] = my_stay_time[x];
	}

	for (int i = 0; i < humanbeings; i++)
	{
		vector<int> LCS_route;

		for (int x = 0; x < 20; x++)
		{
			temp_trajectory[1][x] = trajectory[i][x];
			temp_stay_time[1][x] = stay_time[i][x];
		}

		similarity[i] = Find_LCS(LCS_route, temp_trajectory, temp_stay_time, my_numOfplaces, numOfplaces[i]);
	}

	double max_similarity = 0;
	int the_person;
	for (int i = 0; i < humanbeings; i++)
	{
		if (similarity[i] > max_similarity)
		{
			max_similarity = similarity[i];
			the_person = i;;
		}
	}

	for (int x = 0; x < 20; x++)
	{
		temp_trajectory[0][x] = my_trajectory[x];
		temp_stay_time[0][x] = my_stay_time[x];

		temp_trajectory[1][x] = trajectory[the_person][x];
		temp_stay_time[1][x] = stay_time[the_person][x];
	}

	vector<int> LCS_route;
	Find_LCS(LCS_route, temp_trajectory, temp_stay_time, my_numOfplaces, numOfplaces[the_person]);

	cout << "\n結果:\n";
	if (max_similarity < threshold)
	{
		cout << "雖然最接近的相似度小於最低門檻值，但是我都已經找了那麼久，看在我的面子上還是輸出一下移動軌跡與你最相近的同學吧!\n";
	}

	cout << "同學" << the_person << "與你的的相似度最高\n";
	cout << "LCS路徑為: ";
	for (unsigned int i = 0; i < LCS_route.size(); i++)
	{
		cout << Place[LCS_route.at(i)];

		if (i != LCS_route.size() - 1)
		{
			cout << "->";
		}
	}
	cout << "\n相似度為: " << max_similarity << endl;
}