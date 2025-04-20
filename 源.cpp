#include<iostream>
using namespace std;
#include"标头.h"

/*
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#ifdef _DEBUG
#define new  new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define  malloc(s) _malloc_dbg(s,_NORNAL_BLOCK,__FILE__,__LINE__)
#endif
*/

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	main_0();
	//_CrtDumpMemoryLeaks();
}

void main_0()
{
	int (*arr)[9] = new int[9][9];
	int (*answer_arr)[9] = new int[9][9];

	//int level = 0;
	//cout << "请选择难度：\n1. 简单（55 ~ 65）\n2. 普通（45 ~ 55）\n3. 困难（35 ~ 45）\n4. 大师（25 ~ 35）" << endl;

	int counter = 0;
	bool a = 1;
	int known_number = 81;
	do
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				arr[i][j] = 0;
				answer_arr[i][j] = 0;
			}
		}
		final_plate(answer_arr);

		int n = build(arr, answer_arr);
		cout << "1构：" << n;
		int k = 2;
		do
		{
			int m = build_1(arr);

			cout << "  " << k << "构：" << m;
			if (n == m)
			{
				if (m <= 22)
				{
					cout << endl;
					cout << m << endl;
					cout << "终盘如下：" << endl;
					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							cout << " " << answer_arr[i][j] << " ";
						}
						cout << endl;
					}
					cout << endl;



					cout << "表盘如下：" << endl;
					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							cout << " " << arr[i][j] << " ";
						}
						cout << endl;
					}
					cout << endl;
				}
				/*
				if (m <= 22)
				{
					a = 0;
				}
				*/

				cout << endl;
				break;
			}
			else
			{
				n = m;
				k++;
			}

		} while (1);


		counter++;
		if (counter % 10 == 0)
		{
			cout << "构造次数：" << counter << endl;
			/*
			if (counter % 100 == 0)
			{
				system("pause");
			}
			*/
		}
	} while (a);

	
	cout << "终盘如下：" << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << " " << answer_arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	


	cout << "表盘如下：" << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << " " << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	if (arr != NULL)
	{
		delete[] arr;
		arr = NULL;
	}

	if (answer_arr != NULL)
	{
		delete[] arr;
		answer_arr = NULL;
	}

	return;
}