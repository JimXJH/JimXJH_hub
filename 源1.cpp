#include"��ͷ.h"

mt19937_64 gen(chrono::system_clock::now().time_since_epoch().count());//ȫ�����������


bool solve(const int (*arr)[9])//Ψһ��У��
{
	//��¼�ո���λ��
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

	//������ʱ�������
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
		if (primary_solve(arr_1))//�������������
		{
			return 1;
		}
	}

	//�������޷������������ʹ����������ʹ�û��ݷ���
	//arr_2���ڶ��λ����ж�Ψһ��
	int arr_2[9][9] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			arr_2[i][j] = arr_1[i][j];
		}
	}

	vector<pair<int, int>>::iterator it = zero_v.begin();

	if (solve_1(zero_v, it, arr_1))//�н�
	{
		solve_2(zero_v, it, arr_2);//�ж�Ψһ��

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (arr_1[i][j] != arr_2[i][j])
				{
					return 0;//�ж��
				}
			}
		}
		return 1;//Ψһ��
	}
	else
	{
		return 0;//�޽�
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
			else//������
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
			else//������
			{
				return 1;
			}
		}
	}
	arr[i][j] = 0;
	return 0;
}

int build(int (*arr)[9], const int (*answer_arr)[9])//���ݸ������̳���
{
	//������ʱ����
	int t_arr[9][9] = { 0 };
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			t_arr[i][j] = answer_arr[i][j];
		}
	}

	//����λ�ñ�
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

	//���˳���ڿ�
	for (int f = 0; f < 81; f++)
	{
		uniform_int_distribution<int> distrib(0, 80 - f);
		int a = distrib(gen);//���������

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

	//д�����������
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			arr[i][j] = t_arr[i][j];
		}
	}

	//ͳ�����ָ���
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

int build_1(int (*arr)[9])//�����������ϼ�������
{
	//���ɿո���λ�ñ�
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

	//����ڿ�
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

	//ͳ�ƿո�����
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

bool final_plate(int(*arr)[9], const int serial)//��������
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

			if (serial != 80)//δ�������һ��
			{			
				int s = serial;
				if (final_plate(arr, ++s))
				{
					return 1;//ȫ��������
				}
			}
			else//�ѵ������һ��
			{
				return 1;//����
			}
		}
		else
		{
			//�����ֲ�����
		}
		//������һ����
	}

	//�޿������֣��������
	arr[i][j] = 0;
	return 0;
}

int exclusive(int (*number_arr)[9][9], int (*statistics)[9], int& x, int& y, const int(*arr)[9], const int add_number)//�ų���
{
	if (add_number == 0)//�״ε��ã�Ĭ�ϲ���Ϊ0��
	{
		//�������Ŷ�Ӧ�����ų���
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

			//����ͳ�ϱ�
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					statistics[i][j] += number_arr[n][i][j];
				}
			}
		}
	}
	else//��������
	{
		int n = add_number - 1;

		//��������ų���
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

		//�޸ĵ����ų���
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

		//��ص����ų���
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				statistics[i][j] += number_arr[n][i][j];
			}
		}
	}

	//��⼰�ж�
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
							return n + 1;//�ҵ���
						}
					}
				}
			}
		}
	}
	return -2;//δ�ҵ���
}

void exclusive_1(const int x, const int y, int (*arr)[9])//�����ų�����ĿǰΪ�С��к;Ź����ų�
{
	//��
	for (int j = 0; j < 9; j++)
	{
		arr[x][j] = 1;
	}

	//��
	for (int i = 0; i < 9; i++)
	{
		arr[i][y] = 1;
	}

	//�Ź���
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

int residual_difference(const int (*number_arr)[9][9], int& x, int& y, const int(*arr)[9])//��
{
	//��
	for (int i = 0; i < 9; i++)
	{
		int m_x = 0;
		int m_y = 0;
		int m_n = 0;

		//����ո���
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
			int a = 0;//�ո����ų���
			bool b = 0;//�����Ƿ��и������ж�
			for (int j = 0; j < 9; j++)
			{
				if (arr[i][j] == n + 1)
				{
					b = 1;
				}
			}

			if (b == 0)//����û�и�����
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

				if (zero.size() - a == 1)//����1
				{
					x = m_x;
					y = m_y;
					return m_n + 1;
				}
			}
		}
	}

	//��
	for (int j = 0; j < 9; j++)
	{
		int m_x = 0;
		int m_y = 0;
		int m_n = 0;

		//����ո���
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
			int a = 0;//�ո����ų���
			bool b = 0;//�����Ƿ��и������ж�
			for (int i = 0; i < 9; i++)
			{
				if (arr[i][j] == n + 1)
				{
					b = 1;
				}
			}

			if (b == 0)//����û�и�����
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

				if (zero.size() - a == 1)//����1
				{
					x = m_x;
					y = m_y;
					return m_n + 1;
				}
			}
		}
	}


	//�Ź���
	for (int m_i = 0; m_i < 3; m_i++)
	{
		for (int m_j = 0; m_j < 3; m_j++)
		{
			int m_x = 0;
			int m_y = 0;
			int m_n = 0;

			//����ո���
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
				int a = 0;//�ո����ų���
				bool b = 0;//�Ź������Ƿ��и������ж�

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

				if (b == 0)//�Ź�����û�и�����
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

					if (zero.size() - a == 1)//�Ź�����1
					{
						x = m_x;
						y = m_y;
						return m_n + 1;
					}
				}
			}
		}
	}
	return -3;//δ�ҵ���
}

int double_exclusive(int (*number_arr)[9][9], int (*statistics)[9], int& x, int& y, const int(*arr)[9])//�����ų�
{
	for (int n = 0; n < 9; n++)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if ((number_arr[n][i][j] == 0) && (arr[i][j] == 0))
				{
					bool a = 1;//����λ���ж�

					//������ʱ��
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


					for (int i = 0; i < 9; i++)//�г����ж�
					{
						bool b = 1;//��ȫ�ų����ж�
						for (int j = 0; j < 9; j++)
						{
							if ((t_n_arr[i][j] == 0) && (t_arr[i][j] == 0))
							{
								b = 0;
							}
						}

						if (b == 1)//����ȫ�ų���
						{
							bool c = 0;//���г����ж�
							for (int j = 0; j < 9; j++)
							{
								if (t_arr[i][j] == n + 1)
								{
									c = 1;
								}
							}

							if (c == 0)//���в�����
							{
								a = 0;
							}
						}
					}

					for (int j = 0; j < 9; j++)//�г����ж�
					{
						bool b = 1;//��ȫ�ų����ж�
						for (int i = 0; i < 9; i++)
						{
							if ((t_n_arr[i][j] == 0) && (t_arr[i][j] == 0))
							{
								b = 0;
							}
						}

						if (b == 1)//����ȫ�ų���
						{
							bool c = 0;//���г����ж�
							for (int i = 0; i < 9; i++)
							{
								if (t_arr[i][j] == n + 1)
								{
									c = 1;
								}
							}

							if (c == 0)//���в�����
							{
								a = 0;
							}
						}
					}

					//�Ź�������ж�
					for (int m_i = 0; m_i < 3; m_i++)
					{
						for (int m_j = 0; m_j < 3; m_j++)
						{
							bool b = 1;//��ȫ�ų��Ź����ж�
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

							if (b == 1)//����ȫ�ų��Ź���
							{
								bool c = 0;//���Ź�������ж�
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

								if (c == 0)//���Ź��񲻳���
								{
									a = 0;
								}
							}
						}
					}

					if (a == 0)//��λ�ò�����
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
	return -4;//�����ų�δ�ҵ�
}

bool primary_solve(int(*arr)[9])
{
	int (*number_arr)[9][9] = new int[9][9][9];//��Ӧ���֣��У���
	int statistics[9][9] = { 0 };//ͳ�ϱ�

	for (int i = 0; i < 9; i++)//��ʼ��
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

	int x = -1;//��
	int y = -1;//��
	int answer = 0;//��

	while (1)
	{
		answer = exclusive(number_arr, statistics, x, y, arr, answer);

		if (answer == -2)//�ų���δ�ҵ�
		{
			answer = residual_difference(number_arr, x, y, arr);
			if (answer == -3)//��δ�ҵ�
			{
				answer = double_exclusive(number_arr, statistics, x, y, arr);

				if (answer == -4)//�����ų�δ�ҵ�
				{
					bool a = 1;//�������ж�
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

					if (a == 1)//������
					{
						delete[] number_arr;
						return 1;
					}
					else//���δ���
					{
						delete[] number_arr;
						return 0;
					}
				}
				else//�����ų��ҵ�
				{
					arr[x][y] = answer;
				}
			}
			else//���ҵ�
			{
				arr[x][y] = answer;
			}
		}
		else//�ų����ҵ�
		{
			arr[x][y] = answer;
		}
	}
}