#include"Head.h"
mt19937_64 gen(chrono::system_clock::now().time_since_epoch().count());//全局随机数引擎

bool test_ans(const int line, const vector<vector<short>>& v_area_plate);

int main()
{
	vector<vector<short>> final_plate_5(5, vector<short>(5, 0));
	vector<vector<short>> final_plate_6(6, vector<short>(6, 0));
	vector<vector<short>> final_plate_7(7, vector<short>(7, 0));
	vector<vector<short>> final_plate_8(8, vector<short>(8, 0));
	vector<vector<short>> final_plate_9(9, vector<short>(9, 0));
	vector<Polyomino_6> P6_plate;
	vector<Polyomino_7> P7_plate;
	vector<Polyomino_8> P8_plate;
	vector<Polyomino_9> P9_plate;
	build_Polyomino_plate(P5_plate, P6_plate);
	build_Polyomino_plate(P6_plate, P7_plate);
	build_Polyomino_plate(P7_plate, P8_plate);
	build_Polyomino_plate(P8_plate, P9_plate);



	ofstream ofs_8;////////
	int line = 8;/////////


	for (int count = 1;count <= 50;count++)
	{
		cout << count << endl;
		while (1)
		{
			build_area(final_plate_8, 1, P8_plate);//////////////

			if (test_ans(line, final_plate_8))///////////////
			{
				ofs_8.open("8联骨牌盘面（最终版50个）.txt", ios::out | ios::app);///////////////
				cout << "有解：" << endl;
				for (int i = 0;i < line;i++)
				{
					for (int j = 0;j < line;j++)
					{
						cout << final_plate_8[i][j] << " ";///////////////
						ofs_8 << final_plate_8[i][j] << " ";////////////////
					}
					cout << endl;
					ofs_8 << endl;
				}
				cout << endl;
				ofs_8 << endl;
				ofs_8.close();
				break;
			}
			else
			{
				cout << "无解" << endl;
			}
			final_plate_8 = vector<vector<short>>(line, vector<short>(line, 0));////////////
		}
	}
	return 0;
}