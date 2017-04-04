#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <Windows.h>

long long int rec_Fib(int);
long long int nonRec_Fib(int);
long long int Formula(int);
long long int seq_matrix(int);
long long int log_matrix(int);

int main()
{
	int numOfmethod, n;
	long long int result;
	LARGE_INTEGER ThisTime, ThatTime, PinTime;

	while (true)
	{
		printf("1.Recursive\n2.Nonrecursive\n3.Explict Formula\n4.Sequential(Matrix)\n5.Logarithmic(Matrix)\n");
		printf("Enter the number of method(algorithm) or -1 to exit: ");

		scanf_s("%d", &numOfmethod);

		if (numOfmethod == -1)
		{
			break;
		}
		else
		{
			printf("Enter the term of Fabinocci series: ");
			scanf_s("%d", &n);

			QueryPerformanceFrequency(&PinTime);

			QueryPerformanceCounter(&ThisTime);

			switch (numOfmethod)
			{
			case 1:
				result = rec_Fib(n);
				break;
			case 2:
				result = nonRec_Fib(n);
			case 3:
				result = Formula(n);
			case 4:
				result = seq_matrix(n);
			case 5:
				result = log_matrix(n);
			default:
				break;
			}

			QueryPerformanceCounter(&ThatTime);

			printf("\nFib(%d) = %lld\n", n, result);

			printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);
		}
	}

	return 0;
}

long long int rec_Fib(int n)
{
	if (n == 0)
	{
		return 0;
	}
	else if (n == 1)
	{
		return 1;
	}
	else
	{
		return rec_Fib(n - 1) + rec_Fib(n - 2);
	}
}

long long int nonRec_Fib(int n)
{
	if (n == 0)
	{
		return 0;
	}
	else if (n == 1)
	{
		return 0;
	}

	long long int fib = 1;
	long long int temp;
	long long int x = 0;
	for (int i = 2; i <= n; i++)
	{
		temp = fib;
		fib += x;
		x = temp;
	}

	return fib;
}

long long int Formula(int n)
{
	double x = sqrt(5);

	return (1 / x)*pow((1 + x) / 2, n) - (1 / x)*pow((1 - x) / 2, n);
}

long long int seq_matrix(int n)
{
	long long int a[4] = { 0, 1, 1, 1 };
	long long int a0, a1, a2, a3;

	for (int i = 0; i < n; i++)
	{
		a0 = a[1];
		a1 = a[0] + a[1];
		a2 = a[3];
		a3 = a[2] + a[3];

		a[0] = a0;
		a[1] = a1;
		a[2] = a2;
		a[3] = a3;
	}

	return a[0];
}

long long int log_matrix(int n)
{
	if (n == 0)
	{
		return 0;
	}

	int temp[100] = { 0 };
	int count = 0;

	while (true)
	{
		if (n == 1)
		{
			break;
		}
		else if (n % 2 == 0)
		{
			n /= 2;
			count++;
		}
		else
		{
			n--;
			n /= 2;
			temp[count++] = 1;
		}
	}

	long long int a0 = 0, a1 = 1, a2 = 1, a3 = 1;

	while (--count >= 0)
	{
		long long int b[4] = { a0, a1, a2, a3 };
		a0 = b[0] * b[0] + b[1] * b[2];
		a1 = b[0] * b[1] + b[1] * b[3];
		a2 = b[2] * b[0] + b[3] * b[2];
		a3 = b[2] * b[1] + b[3] * b[3];

		if (temp[count] == 1)
		{
			long long int a[4] = { a0, a1, a2, a3 };
			a0 = a[1];
			a1 = a[0] + a[1];
			a2 = a[3];
			a3 = a[2] + a[3];
		}
	}

	return a1;
}