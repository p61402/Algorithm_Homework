#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <time.h>
#include <Windows.h>

using namespace std;

//Function Prototypes
int BruteForceENG(string pattern, string text);
int HorspoolENG(string pattern, string text);
int BoyerMooreENG(string pattern, string text);
void BadSymbolTable_ENG(int* table, string pattern);
void GoodSuffixTable_ENG(int* table, string pattern);

int BruteForceCHI(string pattern, string text);
int HorspoolCHI(string pattern, string text);
int BoyerMooreCHI(string pattern, string text);
int BadSymbolTable_CHI(int* ref_table[2], int* shift_table, string pattern);
void GoodSuffixTable_CHI(int* table, string pattern);

int BruteForceDNA(string pattern, string text);
int HorspoolDNA(string pattern, string text);
int BoyerMooreDNA(string pattern, string text);
void Bad_Symbol_DNA(int* table, string pattern);
void Good_Suffix_DNA(int* table, string pattern);
int GetSymbol(char c);

int main()
{
	char c;
	
	cout << "This is a string matching program\n";
	cout << "1.English\n2.Chinese\n3.DNA\n";
	cout << "Please enter the number to choice the language (or any other key to exit): ";
	cin >> c;
	cin.ignore();

	LARGE_INTEGER ThisTime, ThatTime, PinTime;

	if (c == '1')
	{
		ifstream inFile;
		inFile.open("Text01.txt");

		if (!inFile)
		{
			cout << "Failed to open the file.\n";
			return -1;
		}

		stringstream strStream;
		strStream << inFile.rdbuf();
		string t = strStream.str();

		cout << "Text:\n";
		for (unsigned int i = 0; i < t.length(); i++)
		{
			cout << t[i];
			t[i] = tolower(t[i]);
		}
		cout << endl;

		string p;
		cout << "Enter your pattern: ";
		getline(cin, p);

		for (unsigned int i = 0; i < p.length(); i++)
		{
			p[i] = tolower(p[i]);
			//cout << p[i];
		}
		cout << endl;

		QueryPerformanceFrequency(&PinTime);
		QueryPerformanceCounter(&ThisTime);
		cout << "BruteForce: " << BruteForceENG(p, t) << endl;
		QueryPerformanceCounter(&ThatTime);
		printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

		QueryPerformanceFrequency(&PinTime);
		QueryPerformanceCounter(&ThisTime);
		cout << "Horspool: " << HorspoolENG(p, t) << endl;
		QueryPerformanceCounter(&ThatTime);
		printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

		QueryPerformanceFrequency(&PinTime);
		QueryPerformanceCounter(&ThisTime);
		cout << "BoyerMoore: " << BoyerMooreENG(p, t) << endl;
		QueryPerformanceCounter(&ThatTime);
		printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

		cout << endl;

		inFile.close();
	}
	else if (c == '2')
	{
		ifstream inFile;

		inFile.open("news.txt");

		if (!inFile)
		{
			cout << "Failed to open the file.\n";
			return -1;
		}

		stringstream strStream;
		strStream << inFile.rdbuf();
		string t = strStream.str();

		cout << "Text:";
		for (unsigned int i = 0; i < t.length(); i++)
		{
			cout << t[i];
		}
		cout << endl;

		string p;
		cout << "Enter your pattern: ";
		getline(cin, p);

		QueryPerformanceFrequency(&PinTime);
		QueryPerformanceCounter(&ThisTime);
		cout << "BruteForce: " << BruteForceCHI(p, t) << endl;
		QueryPerformanceCounter(&ThatTime);
		printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

		QueryPerformanceFrequency(&PinTime);
		QueryPerformanceCounter(&ThisTime);
		cout << "Horspool: " << HorspoolCHI(p, t) << endl;
		QueryPerformanceCounter(&ThatTime);
		printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);
		
		QueryPerformanceFrequency(&PinTime);
		QueryPerformanceCounter(&ThisTime);
		cout << "BoyerMoore: " << BoyerMooreCHI(p, t) << endl;
		QueryPerformanceCounter(&ThatTime);
		printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

		inFile.close();
	}
	else if (c == '3')
	{
		ifstream inFile;
		inFile.open("DNA.txt");

		if (!inFile)
		{
			cout << "Failed to open the file.\n";
			return -1;
		}

		stringstream strStream;
		strStream << inFile.rdbuf();
		string t = strStream.str();

		cout << "Text:";
		for (unsigned int i = 0; i < t.length(); i++)
		{
			cout << t[i];
			t[i] = tolower(t[i]);
		}
		cout << endl;

		string p;
		cout << "Enter your pattern: ";
		getline(cin, p);

		for (unsigned int i = 0; i < p.length(); i++)
		{
			p[i] = tolower(p[i]);
			//cout << p[i];
		}
		cout << endl;

		QueryPerformanceFrequency(&PinTime);
		QueryPerformanceCounter(&ThisTime);
		cout << "BruteForce: " << BruteForceDNA(p, t) << endl;
		QueryPerformanceCounter(&ThatTime);
		printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);
		
		QueryPerformanceFrequency(&PinTime);
		QueryPerformanceCounter(&ThisTime);
		cout << "Horspool: " << HorspoolDNA(p, t) << endl;
		QueryPerformanceCounter(&ThatTime);
		printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);
		
		QueryPerformanceFrequency(&PinTime);
		QueryPerformanceCounter(&ThisTime);
		cout << "BoyerMoore: " << BoyerMooreDNA(p, t) << endl;
		QueryPerformanceCounter(&ThatTime);
		printf("Time: %.10fs\n\n", (double)(ThatTime.QuadPart - ThisTime.QuadPart) / PinTime.QuadPart);

		inFile.close();
	}
	else
	{
		;
	}

	system("pause");
	return 0;
}

//--------English String Matching Functions Starts--------
int BruteForceENG(string pattern, string text)
{
	for (unsigned int i = 0; i < text.length() - pattern.length() + 1; i++)
	{
		unsigned int j;
		for (j = 0; j < pattern.length(); j++)
		{
			//cout << text.at(i) << " " << pattern.at(j) << endl;
			if (text.at(i) != pattern.at(j))
			{
				break;
			}
			else
			{
				i++;
			}
		}

		i -= j;
		if (j == pattern.length())
		{
			return i;
		}
	}

	return -1;
}

int HorspoolENG(string pattern, string text)
{
	int table[26];

	BadSymbolTable_ENG(table, pattern);

	/*
	for (int i = 0; i < 26; i++)
	{
	cout << table[i];
	}
	cout << endl;
	*/

	int i = pattern.length() - 1;
	while (i < text.length())
	{
		int k = 0;

		//cout << pattern.at(pattern.length() - 1 - k) << " " << text.at(i - k) << endl;
		while (k < pattern.length() && pattern.at(pattern.length() - 1 - k) == text.at(i - k))
		{
			k++;
			//cout << "k= " << k;
		}

		if (k == pattern.length())
		{
			//cout << "I got you!\n";
			return i - pattern.length() + 1;
		}
		else
		{
			if (text.at(i) >= 97 && text.at(i) <= 122)
			{
				i += table[text.at(i) - 97];
			}
			else
			{
				i += pattern.length();
			}
		}
	}

	return -1;
}

int BoyerMooreENG(string pattern, string text)
{
	int BadSymbol[26];
	int* GoodSuffix = new int[pattern.length()];

	BadSymbolTable_ENG(BadSymbol, pattern);
	GoodSuffixTable_ENG(GoodSuffix, pattern);

	/*
	for (int i = 1; i < pattern.length(); i++)
	{
	cout << GoodSuffix[i];
	}
	cout << endl;
	*/

	int i = pattern.length() - 1;
	while (i < text.length())
	{
		int k = 0;

		//cout << "i: " << i << endl;
		//cout << pattern.at(pattern.length() - 1 - k) << " " << text.at(i - k) << endl;
		while (k < pattern.length() && pattern.at(pattern.length() - 1 - k) == text.at(i - k))
		{
			k++;
			//cout << "k= " << k;
		}
		//cout << k << " " << pattern.length() << endl;
		//cout << text.at(i - k) << endl;

		if (k == pattern.length())
		{
			delete[] GoodSuffix;

			return i - pattern.length() + 1;
		}
		else if (text.at(i - k) >= 97 && text.at(i - k) <= 122)
		{
			if (k == 0)
			{
				i += max(BadSymbol[text.at(i - k) - 97] - k, 1);
			}
			else
			{
				i += max(max(BadSymbol[text.at(i - k) - 97] - k, 1), GoodSuffix[k]);
			}
		}
		else
		{
			i += max(int(pattern.length() - k), GoodSuffix[k]);
		}
	}

	delete[] GoodSuffix;

	return -1;
}

void BadSymbolTable_ENG(int* table, string pattern)
{
	for (int i = 0; i < 26; i++)
	{
		table[i] = pattern.length();
		//cout << table[i] << " ";
	}

	for (unsigned int i = 0; i < pattern.length() - 1; i++)
	{
		table[pattern.at(i) - 97] = pattern.length() - 1 - i;
	}

	/*
	for (int i = 0; i < 26; i++)
	{
	cout << table[i] << " ";
	}
	*/
}

void GoodSuffixTable_ENG(int* table, string pattern)
{
	string s;
	for (unsigned int i = 1; i < pattern.length(); i++)
	{
		s = pattern.substr(pattern.length() - i, i);
		//cout << "s..." << s << endl;
		string sub;
		int x;
		for (x = pattern.length() - 2; x >= 0; x--)
		{
			if (x < s.length() - 1)
			{
				s = s.substr(s.length() - x - 1, x + 1);
			}

			//cout << "x: " << x << endl;
			//cout << "s: " << s << endl;

			sub = pattern.substr(x - s.length() + 1, s.length());

			//cout << "sub: " << sub << endl << endl;

			if (s == sub)
			{
				table[i] = pattern.length() - x - 1;
				break;
			}
		}

		//cout << "x: " << x << endl;
		if (x < 0)
		{
			//cout << "I did it!\n";
			//cout << "pattern.length: " << pattern.length() << endl;
			table[i] = pattern.length();
		}
	}

	/*
	for (unsigned int i = 1; i < pattern.length(); i++)
	{
	cout << table[i] << " ";
	cout << endl;
	}
	*/
}
//--------English String Matching Functions Ends--------

//--------Chinese String Matching Functions Starts--------
int BruteForceCHI(string pattern, string text)
{
	for (unsigned int i = 0; i < text.length(); i++)
	{
		unsigned int j;
		for (j = 0; j < pattern.length(); j++)
		{
			//cout << text.at(i) << " " << pattern.at(j) << endl;
			if (text.at(i) != pattern.at(j))
			{
				break;
			}
			else
			{
				i++;
			}
		}

		i -= j;
		if (j == pattern.length())
		{
			return i / 2;
		}
	}

	return -1;
}

int HorspoolCHI(string pattern, string text)
{
	int** refTable = new int*[pattern.length() / 2];
	for (unsigned int i = 0; i < pattern.length() / 2; i++)
	{
		refTable[i] = new int[2];
	}

	int* shiftTable = new int[pattern.length() / 2];
	int n = BadSymbolTable_CHI(refTable, shiftTable, pattern);

	/*
	cout << "reftable\n";
	for (int i = 0; i < n; i++)
	{
	cout << refTable[i][0] << " " << refTable[i][1] << endl;
	}

	cout << "\nshifttable\n";
	for (int i = 0; i < n; i++)
	{
	cout << shiftTable[i] << endl;
	}
	*/

	int i = pattern.length() / 2 - 1;
	while (i < text.length() / 2)
	{
		int k = 0;

		//cout << (int)pattern.at(pattern.length() - 2 * (1 + k)) << " " << (int)text.at(2 * (i - k)) << endl;
		while (k < pattern.length() / 2 && pattern.at(pattern.length() - 2 * (1 + k)) == text.at(2 * (i - k)) && pattern.at(pattern.length() - 2 * (1 + k) + 1) == text.at(2 * (i - k) + 1))
		{
			k++;
			//cout << "k= " << k;
		}

		if (k == pattern.length() / 2)
		{
			//cout << "I got you!\n";
			for (unsigned int z = 0; z < pattern.length() / 2; z++)
			{
				delete[] refTable[z];
			}
			delete[] refTable;
			delete[] shiftTable;

			return i - pattern.length() / 2 + 1;
		}
		else
		{
			bool found = false;
			for (int num = 0; num < n; num++)
			{
				if (refTable[num][0] == text.at(2 * i) && refTable[num][1] == text.at(2 * i + 1))
				{
					//cout << (int)refTable[num][0] << " " << (int)text.at(2 * i) << " " << (int)refTable[num][1] << " " << (int)text.at(2 * i + 1) << endl;
					//cout << "i += " << shiftTable[num] << endl;
					i += shiftTable[num];
					found = true;
					break;
				}
			}

			if (!found)
			{
				i += pattern.length() / 2;
			}
		}
	}


	for (unsigned int i = 0; i < pattern.length() / 2; i++)
	{
		delete[] refTable[i];
	}
	delete[] refTable;
	delete[] shiftTable;

	return -1;
}

int BoyerMooreCHI(string pattern, string text)
{
	int** refTable = new int*[pattern.length() / 2];
	for (unsigned int i = 0; i < pattern.length() / 2; i++)
	{
		refTable[i] = new int[2];
	}

	int* badtable = new int[pattern.length() / 2];
	int n = BadSymbolTable_CHI(refTable, badtable, pattern);

	int* goodtable = new int[pattern.length() / 2];
	GoodSuffixTable_CHI(goodtable, pattern);

	int i = pattern.length() / 2 - 1;
	while (i < text.length() / 2)
	{
		int k = 0;

		//cout << "i: " << i << endl;
		//cout << pattern.at(pattern.length() - 1 - k) << " " << text.at(i - k) << endl;
		while (k < pattern.length() / 2 && pattern.at(pattern.length() - 2 * (1 + k)) == text.at(2 * (i - k)) && pattern.at(pattern.length() - 2 * (1 + k) + 1) == text.at(2 * (i - k) + 1))
		{
			k++;
			//cout << "k= " << k;
		}
		//cout << k << " " << pattern.length() << endl;
		//cout << text.at(i - k) << endl;

		if (k == pattern.length() / 2)
		{
			for (unsigned int z = 0; z < pattern.length() / 2; z++)
			{
				delete[] refTable[z];
			}
			delete[] refTable;
			delete[] badtable;
			delete[] goodtable;

			return i - pattern.length() / 2 + 1;
		}
		else if (k == 0)
		{
			bool found = false;
			int t = pattern.length() / 2;
			for (int num = 0; num < n; num++)
			{
				if (refTable[num][0] == text.at(2 * (i - k)) && refTable[num][1] == text.at(2 * (i - k) + 1))
				{
					t = badtable[num];
					found = true;
					break;
				}
			}

			i += max(t - k, 1);
		}
		else
		{
			bool found = false;
			int t1 = pattern.length() / 2;
			for (int num = 0; num < n; num++)
			{
				if (refTable[num][0] == text.at(2 * (i - k)) && refTable[num][1] == text.at(2 * (i - k) + 1))
				{
					t1 = badtable[num];
					found = true;
					break;
				}
			}

			i += max(max(t1 - k, 1), goodtable[k]);
		}
	}

	for (unsigned int i = 0; i < pattern.length() / 2; i++)
	{
		delete[] refTable[i];
	}
	delete[] refTable;
	delete[] badtable;
	delete[] goodtable;

	return -1;
}

int BadSymbolTable_CHI(int* ref_table[2], int* shift_table, string pattern)
{
	int num = 0;
	for (unsigned int i = 0; i < pattern.length() / 2; i++)
	{
		bool repeat = false;
		for (int j = 0; j < i; j++)
		{
			if (ref_table[j][0] == pattern.at(2 * i) && ref_table[j][1] == pattern.at(2 * i + 1))
			{
				//cout << j << " I got it!\n";
				repeat = true;
			}
		}

		if (repeat == true)
		{
			continue;
		}

		ref_table[num][0] = pattern.at(2 * i);
		ref_table[num][1] = pattern.at(2 * i + 1);

		shift_table[num] = pattern.length() / 2;

		num++;
	}

	for (unsigned int i = 0; i < pattern.length() / 2 - 1; i++)
	{
		for (int j = 0; j < num; j++)
		{
			if (ref_table[j][0] == pattern.at(2 * i) && ref_table[j][1] == pattern.at(2 * i + 1))
			{
				shift_table[j] = pattern.length() / 2 - 1 - i;
			}
		}
	}

	/*
	cout << "num: " << num;
	cout << "\nBAD:\n";
	for (unsigned int i = 0; i < num; i++)
	{
	cout << "\nref " << i << endl;
	cout << ref_table[i][0] << " ";
	cout << ref_table[i][1] << " ";
	cout << "\nshift\n";
	cout << shift_table[i] << " ";
	}
	cout << endl;
	*/

	return num;
}

void GoodSuffixTable_CHI(int* table, string pattern)
{
	string s;
	for (unsigned int i = 1; i < pattern.length() / 2; i++)
	{
		s = pattern.substr(pattern.length() - 2 * i, 2 * i);
		//cout << "s..." << s << endl;
		string sub;
		int x;
		for (x = pattern.length() / 2 - 2; x >= 0; x--)
		{
			if (2 * x < s.length() - 2)
			{
				s = s.substr(s.length() - 2 * (x + 1), 2 * (x + 1));
			}

			//cout << "x: " << x << endl;
			//cout << "s: " << s << endl;

			sub = pattern.substr(2 * x - s.length() + 2, s.length());

			//cout << "sub: " << sub << endl << endl;

			if (s == sub)
			{
				table[i] = pattern.length() / 2 - x - 1;
				break;
			}
		}

		if (x < 0)
		{
			table[i] = pattern.length() / 2;
		}
	}

	/*
	cout << "GoodTable\n";
	for (unsigned int i = 1; i < pattern.length() / 2; i++)
	{
	cout << table[i] << " ";
	cout << endl;
	}
	*/
}
//--------Chinese String Matching Functions Ends--------

//--------DNA String Matching Functions Starts--------
int BruteForceDNA(string pattern, string text)
{
	for (unsigned int i = 0; i < text.length() - pattern.length() + 1; i++)
	{
		unsigned int j;
		for (j = 0; j < pattern.length(); j++)
		{
			//cout << text.at(i) << " " << pattern.at(j) << endl;
			if (text.at(i) != pattern.at(j))
			{
				break;
			}
			else
			{
				i++;
			}
		}

		i -= j;
		if (j == pattern.length())
		{
			return i;
		}
	}

	return -1;
}

int HorspoolDNA(string pattern, string text)
{
	int table[4];

	Bad_Symbol_DNA(table, pattern);

	/*
	for (int i = 0; i < 26; i++)
	{
	cout << table[i];
	}
	cout << endl;
	*/

	int i = pattern.length() - 1;
	while (i < text.length())
	{
		int k = 0;

		//cout << pattern.at(pattern.length() - 1 - k) << " " << text.at(i - k) << endl;
		while (k < pattern.length() && pattern.at(pattern.length() - 1 - k) == text.at(i - k))
		{
			k++;
			//cout << "k= " << k;
		}

		if (k == pattern.length())
		{
			//cout << "I got you!\n";
			return i - pattern.length() + 1;
		}
		else
		{
			int index = GetSymbol(text.at(i));

			i += table[index];
		}
	}

	return -1;
}

int BoyerMooreDNA(string pattern, string text)
{
	int BadSymbol[4];
	int* GoodSuffix = new int[pattern.length()];

	Bad_Symbol_DNA(BadSymbol, pattern);
	Good_Suffix_DNA(GoodSuffix, pattern);

	/*
	for (int i = 1; i < pattern.length(); i++)
	{
	cout << GoodSuffix[i];
	}
	cout << endl;
	*/

	int i = pattern.length() - 1;
	while (i < text.length())
	{
		int k = 0;

		//cout << "i: " << i << endl;
		//cout << pattern.at(pattern.length() - 1 - k) << " " << text.at(i - k) << endl;
		while (k < pattern.length() && pattern.at(pattern.length() - 1 - k) == text.at(i - k))
		{
			k++;
			//cout << "k= " << k;
		}
		//cout << k << " " << pattern.length() << endl;
		//cout << text.at(i - k) << endl;

		if (k == pattern.length())
		{
			delete[] GoodSuffix;

			return i - pattern.length() + 1;
		}
		else if (k == 0)
		{
			int index = GetSymbol(text.at(i - k));
			i += max(BadSymbol[index] - k, 1);
		}
		else
		{
			int index = GetSymbol(text.at(i - k));
			i += max(max(BadSymbol[index] - k, 1), GoodSuffix[k]);
		}
	}

	delete[] GoodSuffix;

	return -1;
}

void Bad_Symbol_DNA(int* table, string pattern)
{
	for (int i = 0; i < 4; i++)
	{
		table[i] = pattern.length();
	}

	for (int i = 0; i < pattern.length() - 1; i++)
	{
		int index = GetSymbol(pattern.at(i));

		table[index] = pattern.length() - 1 - i;
	}
}

void Good_Suffix_DNA(int* table, string pattern)
{
	string s;
	for (unsigned int i = 1; i < pattern.length(); i++)
	{
		s = pattern.substr(pattern.length() - i, i);
		//cout << "s..." << s << endl;
		string sub;
		int x;
		for (x = pattern.length() - 2; x >= 0; x--)
		{
			if (x < s.length() - 1)
			{
				s = s.substr(s.length() - x - 1, x + 1);
			}

			//cout << "x: " << x << endl;
			//cout << "s: " << s << endl;

			sub = pattern.substr(x - s.length() + 1, s.length());

			//cout << "sub: " << sub << endl << endl;

			if (s == sub)
			{
				table[i] = pattern.length() - x - 1;
				break;
			}
		}

		//cout << "x: " << x << endl;
		if (x < 0)
		{
			//cout << "I did it!\n";
			//cout << "pattern.length: " << pattern.length() << endl;
			table[i] = pattern.length();
		}
	}
}

int GetSymbol(char c)
{
	switch (c)
	{
	case 'a':
		return 0;
	case 'c':
		return 1;
	case 'g':
		return 2;
	case 't':
		return 3;
	}

	return -1;
}
//--------DNA String Matching Functions Ends--------