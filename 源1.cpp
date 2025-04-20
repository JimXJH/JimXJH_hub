#include"自制数独.h"

mt19937_64 gen(chrono::system_clock::now().time_since_epoch().count());//全局随机数引擎


bool solve(const int (*arr)[9])//唯一解校验
{
	//记录空格子位置
	vector<pair<int, int>> zero_v;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] == 0)
			{
				pair<int, int> p(i, j);
				zero_v.push_back(p);
			}
		}
	}

	//创建临时数组对象
	int arr_1[9][9] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			arr_1[i][j] = arr[i][j];
		}
	}

	if (zero_v.size() > 50)
	{
		if (primary_solve(arr_1))//尝试推理方法解答
		{
			return 1;
		}
	}

	//推理方法无法解出，或不适宜使用推理方法。使用回溯法。
	//arr_2用于二次回溯判断唯一解
	int arr_2[9][9] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			arr_2[i][j] = arr_1[i][j];
		}
	}

	vector<pair<int, int>>::iterator it = zero_v.begin();

	if (solve_1(zero_v, it, arr_1))//有解
	{
		solve_2(zero_v, it, arr_2);//判断唯一解

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (arr_1[i][j] != arr_2[i][j])
				{
					return 0;//有多解
				}
			}
		}
		return 1;//唯一解
	}
	else
	{
		return 0;//无解
	}
}


bool solve_1(const vector<pair<int, int>>& v, const vector<pair<int, int>>::iterator it, int(*arr)[9])
{
	const int i = it->first;
	const int j = it->second;

	for (int k = 0; k < 9; k++)
	{
		bool a = 1;
		for (int x = 0; x < 9; x++)
		{
			if (arr[x][j] == k + 1)
			{
				a = 0;
			}
		}
		for (int y = 0; y < 9; y++)
		{
			if (arr[i][y] == k + 1)
			{
				a = 0;
			}
		}
		for (int x = i / 3 * 3; x < i / 3 * 3 + 3; x++)
		{
			for (int y = j / 3 * 3; y < j / 3 * 3 + 3; y++)
			{
				if (arr[x][y] == k + 1)
				{
					a = 0;
				}
			}
		}

		if (a)
		{
			arr[i][j] = k + 1;
			vector<pair<int, int>>::iterator it_2 = it;
			it_2++;
			if (it_2 != v.end())
			{
				if (solve_1(v, it_2, arr))
				{
					return 1;
				}
			}
			else//解答完成
			{
				return 1;
			}
		}
	}
	arr[i][j] = 0;
	return 0;
}


bool solve_2(const vector<pair<int, int>>& v, const vector<pair<int, int>>::iterator it, int(*arr)[9])
{
	const int i = it->first;
	const int j = it->second;

	for (int k = 8; k >= 0; k--)
	{
		bool a = 1;
		for (int x = 0; x < 9; x++)
		{
			if (arr[x][j] == k + 1)
			{
				a = 0;
			}
		}
		for (int y = 0; y < 9; y++)
		{
			if (arr[i][y] == k + 1)
			{
				a = 0;
			}
		}
		for (int x = i / 3 * 3; x < i / 3 * 3 + 3; x++)
		{
			for (int y = j / 3 * 3; y < j / 3 * 3 + 3; y++)
			{
				if (arr[x][y] == k + 1)
				{
					a = 0;
				}
			}
		}

		if (a)
		{
			arr[i][j] = k + 1;
			vector<pair<int, int>>::iterator it_2 = it;
			it_2++;
			if (it_2 != v.end())
			{
				if (solve_2(v, it_2, arr))
				{
					return 1;
				}
			}
			else//解答完成
			{
				return 1;
			}
		}
	}
	arr[i][j] = 0;
	return 0;
}

int build(int (*arr)[9], const int (*answer_arr)[9])//根据给定终盘出题
{
	//生成临时数组
	int t_arr[9][9] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			t_arr[i][j] = answer_arr[i][j];
		}
	}

	//生成位置表
	int rand_arr[81] = { 0 };
	int t_index = 0;
	for (int m = 11; m < 100; m++)
	{
		if (m % 10 != 0)
		{
			rand_arr[t_index] = m;
			t_index++;
		}
	}

	//随机顺序挖空
	for (int f = 0; f < 81; f++)
	{
		uniform_int_distribution<int> distrib(0, 80 - f);
		int a = distrib(gen);//生成随机数

		int x = rand_arr[a] / 10 - 1;
		int y = rand_arr[a] % 10 - 1;
		int temp = t_arr[x][y];
		t_arr[x][y] = 0;
		if (!solve(t_arr))
		{
			t_arr[x][y] = temp;
		}

		for (int i = a; i < 80; i++)
		{
			rand_arr[a] = rand_arr[a + 1];
		}
	}

	//写入参数数组中
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			arr[i][j] = t_arr[i][j];
		}
	}

	//统计数字个数
	int n = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j])
			{
				n++;
			}
		}
	}
	return n;
}

int build_1(int (*arr)[9])//在已有题面上减少数字
{
	//生成空格子位置表
	vector<pair<int, int>> site_v;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j])
			{
				pair<int, int> p(i, j);
				site_v.push_back(p);
			}
		}
	}
	int size = site_v.size();

	//随机挖空
	for (int f = 0; f < size; f++)
	{
		uniform_int_distribution<int> distrib(0, size - f - 1);
		int m = distrib(gen);

		vector<pair<int, int>>::iterator it = site_v.begin();
		for (int k = 0; k < m; k++)
		{
			it++;
		}

		int i = it->first;
		int j = it->second;
		int temp = arr[i][j];
		arr[i][j] = 0;
		if (!solve(arr))
		{
			arr[i][j] = temp;
		}

		while (it != (--site_v.end()))
		{
			*it = *(++it);
		}
	}

	//统计空格子数
	int n = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j])
			{
				n++;
			}
		}
	}
	return n;
}

bool final_plate(int(*arr)[9], const int serial)//生成终盘
{
	const int i = serial / 9;
	const int j = serial % 9;

	int k;
	int t_arr[9] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		t_arr[i] = i + 1;
	}

	for (int f = 0; f < 9; f++)
	{
		uniform_int_distribution<int> distrib(0, 8 - f);
		k = distrib(gen);

		int number = t_arr[k];
		for (int g = k; g < 8; g++)
		{
			t_arr[g] = t_arr[g + 1];
		}

		bool a = 1;
		for (int x = 0; x < 9; x++)
		{
			if (arr[x][j] == number)
			{
				a = 0;
			}
		}
		for (int y = 0; y < 9; y++)
		{
			if (arr[i][y] == number)
			{
				a = 0;
			}
		}
		for (int x = i / 3 * 3; x < i / 3 * 3 + 3; x++)
		{
			for (int y = j / 3 * 3; y < j / 3 * 3 + 3; y++)
			{
				if (arr[x][y] == number)
				{
					a = 0;
				}
			}
		}

		if (a)
		{
			arr[i][j] = number;

			if (serial != 80)//未到达最后一格
			{			
				int s = serial;
				if (final_plate(arr, ++s))
				{
					return 1;//全部填充完毕
				}
			}
			else//已到达最后一格
			{
				return 1;//可填
			}
		}
		else
		{
			//该数字不可填
		}
		//尝试下一个数
	}

	//无可填数字，不填并回退
	arr[i][j] = 0;
	return 0;
}

int exclusive(int (*number_arr)[9][9], int (*statistics)[9], int& x, int& y, const int(*arr)[9], const int add_number)//排除法
{
	if (add_number == 0)//首次调用（默认参数为0）
	{
		//创建九张对应数字排除表
		for (int n = 0; n < 9; n++)
		{
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					if (arr[i][j] == n + 1)
					{
						number_arr[n][i][j] = 1;
						exclusive_1(i, j, number_arr[n]);
					}
				}
			}

			//创建统合表
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					statistics[i][j] += number_arr[n][i][j];
				}
			}
		}
	}
	else//后续调用
	{
		int n = add_number - 1;

		//抽出单张排除表
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (number_arr[n][i][j] == 1)
				{
					statistics[i][j]--;
				}
			}
		}

		//修改单张排除表
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (arr[i][j] == add_number)
				{
					number_arr[n][i][j] = 1;
					exclusive_1(i, j, number_arr[n]);
				}
			}
		}

		//插回单张排除表
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				statistics[i][j] += number_arr[n][i][j];
			}
		}
	}

	//求解及判定
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] == 0)
			{
				if (statistics[i][j] == 8)
				{
					x = i;
					y = j;
					for (int n = 0; n < 9; n++)
					{
						if (number_arr[n][i][j] == 0)
						{
							return n + 1;//找到答案
						}
					}
				}
			}
		}
	}
	return -2;//未找到答案
}

void exclusive_1(const int x, const int y, int (*arr)[9])//数字排除规则，目前为行、列和九宫格排除
{
	//列
	for (int j = 0; j < 9; j++)
	{
		arr[x][j] = 1;
	}

	//行
	for (int i = 0; i < 9; i++)
	{
		arr[i][y] = 1;
	}

	//九宫格
	int a = x / 3 * 3;
	int b = y / 3 * 3;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			arr[a + i][b + j] = 1;
		}
	}
	return;
}

int residual_difference(const int (*number_arr)[9][9], int& x, int& y, const int(*arr)[9])//余差法
{
	//行
	for (int i = 0; i < 9; i++)
	{
		int m_x = 0;
		int m_y = 0;
		int m_n = 0;

		//保存空格子
		vector<pair<int, int>> zero;
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] == 0)
			{
				pair<int, int> p(i, j);
				zero.push_back(p);
			}
		}

		for (int n = 0; n < 9; n++)
		{
			int a = 0;//空格子排除数
			bool b = 0;//行内是否有该数字判定
			for (int j = 0; j < 9; j++)
			{
				if (arr[i][j] == n + 1)
				{
					b = 1;
				}
			}

			if (b == 0)//行内没有该数字
			{

				for (vector<pair<int, int>>::iterator it = zero.begin(); it != zero.end(); it++)
				{
					if (number_arr[n][it->first][it->second] == 1)
					{
						a++;
					}
					else
					{
						m_x = it->first;
						m_y = it->second;
						m_n = n;
					}
				}

				if (zero.size() - a == 1)//行余1
				{
					x = m_x;
					y = m_y;
					return m_n + 1;
				}
			}
		}
	}

	//列
	for (int j = 0; j < 9; j++)
	{
		int m_x = 0;
		int m_y = 0;
		int m_n = 0;

		//保存空格子
		vector<pair<int, int>> zero;
		for (int i = 0; i < 9; i++)
		{
			if (arr[i][j] == 0)
			{
				pair<int, int> p(i, j);
				zero.push_back(p);
			}
		}

		for (int n = 0; n < 9; n++)
		{
			int a = 0;//空格子排除数
			bool b = 0;//列内是否有该数字判定
			for (int i = 0; i < 9; i++)
			{
				if (arr[i][j] == n + 1)
				{
					b = 1;
				}
			}

			if (b == 0)//列内没有该数字
			{
				for (vector<pair<int, int>>::iterator it = zero.begin(); it != zero.end(); it++)
				{
					if (number_arr[n][it->first][it->second] == 1)
					{
						a++;
					}
					else
					{
						m_x = it->first;
						m_y = it->second;
						m_n = n;
					}
				}

				if (zero.size() - a == 1)//列余1
				{
					x = m_x;
					y = m_y;
					return m_n + 1;
				}
			}
		}
	}


	//九宫格
	for (int m_i = 0; m_i < 3; m_i++)
	{
		for (int m_j = 0; m_j < 3; m_j++)
		{
			int m_x = 0;
			int m_y = 0;
			int m_n = 0;

			//保存空格子
			vector<pair<int, int>> zero;
			for (int i = m_i * 3; i < m_i * 3 + 3; i++)
			{
				for (int j = m_j * 3; j < m_j * 3 + 3; j++)
				{
					if (arr[i][j] == 0)
					{
						pair<int, int> p(i, j);
						zero.push_back(p);
					}
				}
			}

			for (int n = 0; n < 9; n++)
			{
				int a = 0;//空格子排除数
				bool b = 0;//九宫格内是否有该数字判定

				for (int i = m_i * 3; i < m_i * 3 + 3; i++)
				{
					for (int j = m_j; j < m_j * 3 + 3; j++)
					{
						if (arr[i][j] == n + 1)
						{
							b = 1;
						}
					}
				}

				if (b == 0)//九宫格内没有该数字
				{
					for (vector<pair<int, int>>::iterator it = zero.begin(); it != zero.end(); it++)
					{
						if (number_arr[n][it->first][it->second] == 1)
						{
							a++;
						}
						else
						{
							m_x = it->first;
							m_y = it->second;
							m_n = n;
						}
					}

					if (zero.size() - a == 1)//九宫格余1
					{
						x = m_x;
						y = m_y;
						return m_n + 1;
					}
				}
			}
		}
	}
	return -3;//未找到答案
}

int double_exclusive(int (*number_arr)[9][9], int (*statistics)[9], int& x, int& y, const int(*arr)[9])//二级排除
{
	for (int n = 0; n < 9; n++)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if ((number_arr[n][i][j] == 0) && (arr[i][j] == 0))
				{
					bool a = 1;//可填位置判定

					//创建临时表
					int t_n_arr[9][9] = { 0 };
					int t_arr[9][9] = { 0 };
					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							t_n_arr[i][j] = number_arr[n][i][j];
							t_arr[i][j] = arr[i][j];
						}
					}
					t_n_arr[i][j] = 1;
					exclusive_1(i, j, t_n_arr);
					t_arr[i][j] = n + 1;


					for (int i = 0; i < 9; i++)//行成立判定
					{
						bool b = 1;//完全排除行判定
						for (int j = 0; j < 9; j++)
						{
							if ((t_n_arr[i][j] == 0) && (t_arr[i][j] == 0))
							{
								b = 0;
							}
						}

						if (b == 1)//是完全排除行
						{
							bool c = 0;//单行成立判定
							for (int j = 0; j < 9; j++)
							{
								if (t_arr[i][j] == n + 1)
								{
									c = 1;
								}
							}

							if (c == 0)//单行不成立
							{
								a = 0;
							}
						}
					}

					for (int j = 0; j < 9; j++)//列成立判定
					{
						bool b = 1;//完全排除列判定
						for (int i = 0; i < 9; i++)
						{
							if ((t_n_arr[i][j] == 0) && (t_arr[i][j] == 0))
							{
								b = 0;
							}
						}

						if (b == 1)//是完全排除列
						{
							bool c = 0;//单列成立判定
							for (int i = 0; i < 9; i++)
							{
								if (t_arr[i][j] == n + 1)
								{
									c = 1;
								}
							}

							if (c == 0)//单列不成立
							{
								a = 0;
							}
						}
					}

					//九宫格成立判定
					for (int m_i = 0; m_i < 3; m_i++)
					{
						for (int m_j = 0; m_j < 3; m_j++)
						{
							bool b = 1;//完全排除九宫格判定
							for (int i = m_i * 3; i < m_i * 3 + 3; i++)
							{
								for (int j = m_j * 3; j < m_j * 3 + 3; j++)
								{
									if ((t_n_arr[i][j] == 0) && (t_arr[i][j] == 0))
									{
										b = 0;
									}
								}
							}

							if (b == 1)//是完全排除九宫格
							{
								bool c = 0;//单九宫格成立判定
								for (int i = m_i * 3; i < m_i * 3 + 3; i++)
								{
									for (int j = m_j * 3; j < m_j * 3 + 3; j++)
									{
										if (t_arr[i][j] == n + 1)
										{
											c = 1;
										}
									}
								}

								if (c == 0)//单九宫格不成立
								{
									a = 0;
								}
							}
						}
					}

					if (a == 0)//该位置不可填
					{
						number_arr[n][i][j] = 1;
						statistics[i][j] += 1;
					}
				}
			}
		}
	}

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (arr[i][j] == 0)
			{
				if (statistics[i][j] == 8)
				{
					x = i;
					y = j;
					for (int n = 0; n < 9; n++)
					{
						if (number_arr[n][i][j] == 0)
						{
							return n + 1;
						}
					}
				}
			}
		}
	}
	return -4;//二级排除未找到
}

bool primary_solve(int(*arr)[9])
{
	int (*number_arr)[9][9] = new int[9][9][9];//对应数字，行，列
	int statistics[9][9] = { 0 };//统合表

	for (int i = 0; i < 9; i++)//初始化
	{
		for (int j = 0; j < 9; j++)
		{
			statistics[i][j] = 0;
			for (int n = 0; n < 9; n++)
			{
				number_arr[n][i][j] = 0;
			}
		}
	}

	int x = -1;//行
	int y = -1;//列
	int answer = 0;//答案

	while (1)
	{
		answer = exclusive(number_arr, statistics, x, y, arr, answer);

		if (answer == -2)//排除法未找到
		{
			answer = residual_difference(number_arr, x, y, arr);
			if (answer == -3)//余差法未找到
			{
				answer = double_exclusive(number_arr, statistics, x, y, arr);

				if (answer == -4)//二级排除未找到
				{
					bool a = 1;//解答完成判定
					for (int i = 0; i < 9; i++)
					{
						for (int j = 0; j < 9; j++)
						{
							if (arr[i][j] == 0)
							{
								a = 0;
							}
						}
					}

					if (a == 1)//解答完成
					{
						delete[] number_arr;
						return 1;
					}
					else//解答未完成
					{
						delete[] number_arr;
						return 0;
					}
				}
				else//二级排除找到
				{
					arr[x][y] = answer;
				}
			}
			else//余差法找到
			{
				arr[x][y] = answer;
			}
		}
		else//排除法找到
		{
			arr[x][y] = answer;
		}
	}
}
