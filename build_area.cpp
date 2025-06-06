#include"Head.h"

/* 00 */Polyomino_5 X = Polyomino_5(1, -1, 1, 0, 1, 1, 2, 0);//十
/* 01 */Polyomino_5 I_1 = Polyomino_5(1, 0, 2, 0, 3, 0, 4, 0);//I
/* 02 */Polyomino_5 I_2 = Polyomino_5(0, 1, 0, 2, 0, 3, 0, 4);//一
/* 03 */Polyomino_5 Z_1 = Polyomino_5(0, 1, 1, 1, 2, 1, 2, 2);//Z
/* 04 */Polyomino_5 Z_2 = Polyomino_5(0, 1, 1, 0, 2, -1, 2, 0);//S
/* 05 */Polyomino_5 Z_3 = Polyomino_5(1, -2, 1, -1, 1, 0, 2, -2);//Z顺时针旋转90°
/* 06 */Polyomino_5 Z_4 = Polyomino_5(1, 0, 1, 1, 1, 2, 2, 2);//S顺时针旋转90°
/* 07 */Polyomino_5 V_1 = Polyomino_5(1, 0, 2, -2, 2, -1, 2, 0);//L逆时针旋转90°
/* 08 */Polyomino_5 V_2 = Polyomino_5(1, 0, 2, 0, 2, 1, 2, 2);//L
/* 09 */Polyomino_5 V_3 = Polyomino_5(0, 1, 0, 2, 1, 0, 2, 0);//L顺时针旋转90°
/* 10 */Polyomino_5 V_4 = Polyomino_5(0, 1, 0, 2, 1, 2, 2, 2);//L顺时针旋转180°
/* 11 */Polyomino_5 W_1 = Polyomino_5(1, -1, 1, 0, 2, -2, 2, -1);//W开口朝左上
/* 12 */Polyomino_5 W_2 = Polyomino_5(0, 1, 1, 1, 1, 2, 2, 2);//W开口朝左下
/* 13 */Polyomino_5 W_3 = Polyomino_5(0, 1, 1, -1, 1, 0, 2, -1);//W开口朝右下
/* 14 */Polyomino_5 W_4 = Polyomino_5(1, 0, 1, 1, 2, 1, 2, 2);//W开口朝右上
/* 15 */Polyomino_5 T_1 = Polyomino_5(0, 1, 0, 2, 1, 1, 2, 1);//T
/* 16 */Polyomino_5 T_2 = Polyomino_5(1, 0, 2, -1, 2, 0, 2, 1);//T镜像（上下翻转）
/* 17 */Polyomino_5 T_3 = Polyomino_5(1, 0, 1, 1, 1, 2, 2, 0);//T下端指向右
/* 18 */Polyomino_5 T_4 = Polyomino_5(1, -2, 1, -1, 1, 0, 2, 0);//T下端指向左
/* 19 */Polyomino_5 U_1 = Polyomino_5(0, 2, 1, 0, 1, 1, 1, 2);//U
/* 20 */Polyomino_5 U_2 = Polyomino_5(0, 1, 1, 0, 2, 0, 2, 1);//U顺时针旋转90°
/* 21 */Polyomino_5 U_3 = Polyomino_5(0, 1, 0, 2, 1, 0, 1, 2);//U顺时针旋转180°
/* 22 */Polyomino_5 U_4 = Polyomino_5(0, 1, 1, 1, 2, 0, 2, 1);//U顺时针旋转90°
/* 23 */Polyomino_5 F_1 = Polyomino_5(0, 1, 1, -1, 1, 0, 2, 0);//F（左低右高）
/* 24 */Polyomino_5 F_2 = Polyomino_5(1, -1, 1, 0, 1, 1, 2, 1);//F顺时针旋转90°
/* 25 */Polyomino_5 F_3 = Polyomino_5(1, 0, 1, 1, 2, -1, 2, 0);//F顺时针旋转180°
/* 26 */Polyomino_5 F_4 = Polyomino_5(1, 0, 1, 1, 1, 2, 2, 1);//F逆时针旋转90°
/* 27 */Polyomino_5 F_5 = Polyomino_5(0, 1, 1, 1, 1, 2, 2, 1);//F镜像（左右翻转）
/* 28 */Polyomino_5 F_6 = Polyomino_5(1, -2, 1, -1, 1, 0, 2, -1);//F镜像顺时针旋转90°
/* 29 */Polyomino_5 F_7 = Polyomino_5(1, -1, 1, 0, 2, 0, 2, 1);//F镜像顺时针旋转180°
/* 30 */Polyomino_5 F_8 = Polyomino_5(1, -1, 1, 0, 1, 1, 2, -1);//F镜像逆时针旋转90°
/* 31 */Polyomino_5 L_1 = Polyomino_5(1, 0, 2, 0, 3, 0, 3, 1);//L
/* 32 */Polyomino_5 L_2 = Polyomino_5(0, 1, 0, 2, 0, 3, 1, 0);//L顺时针旋转90°
/* 33 */Polyomino_5 L_3 = Polyomino_5(0, 1, 1, 1, 2, 1, 3, 1);//L顺时针旋转180°
/* 34 */Polyomino_5 L_4 = Polyomino_5(1, -3, 1, -2, 1, -1, 1, 0);//L逆时针旋转90°
/* 35 */Polyomino_5 L_5 = Polyomino_5(1, 0, 2, 0, 3, -1, 3, 0);//L镜像（左右翻转）
/* 36 */Polyomino_5 L_6 = Polyomino_5(1, 0, 1, 1, 1, 2, 1, 3);//L镜像顺时针旋转90°
/* 37 */Polyomino_5 L_7 = Polyomino_5(0, 1, 1, 0, 2, 0, 3, 0);//L镜像顺时针旋转180°
/* 38 */Polyomino_5 L_8 = Polyomino_5(0, 1, 0, 2, 0, 3, 1, 3);//L镜像逆时针旋转90°
/* 39 */Polyomino_5 N_1 = Polyomino_5(1, 0, 2, -1, 2, 0, 3, -1);//N
/* 40 */Polyomino_5 N_2 = Polyomino_5(0, 1, 1, 1, 1, 2, 1, 3);//N顺时针旋转90°
/* 41 */Polyomino_5 N_3 = Polyomino_5(1, -1, 1, 0, 2, -1, 3, -1);//N顺时针旋转180°
/* 42 */Polyomino_5 N_4 = Polyomino_5(0, 1, 0, 2, 1, 2, 1, 3);//N逆时针旋转90°
/* 43 */Polyomino_5 N_5 = Polyomino_5(1, 0, 2, 0, 2, 1, 3, 1);//N镜像（左右翻转）
/* 44 */Polyomino_5 N_6 = Polyomino_5(0, 1, 0, 2, 1, -1, 1, 0);//N镜像顺时针旋转90°
/* 45 */Polyomino_5 N_7 = Polyomino_5(1, 0, 1, 1, 2, 1, 3, 1);//N镜像顺时针旋转180°
/* 46 */Polyomino_5 N_8 = Polyomino_5(0, 1, 1, -2, 1, -1, 1, 0);//N镜像逆时针旋转90°
/* 47 */Polyomino_5 P_1 = Polyomino_5(0, 1, 1, 0, 1, 1, 2, 0);//P
/* 48 */Polyomino_5 P_2 = Polyomino_5(0, 1, 0, 2, 1, 1, 1, 2);//P顺时针旋转90°
/* 49 */Polyomino_5 P_3 = Polyomino_5(1, -1, 1, 0, 2, -1, 2, 0);//P顺时针旋转180°
/* 50 */Polyomino_5 P_4 = Polyomino_5(0, 1, 1, 0, 1, 1, 1, 2);//P逆时针旋转90°
/* 51 */Polyomino_5 P_5 = Polyomino_5(0, 1, 1, 0, 1, 1, 2, 1);//P镜像（左右翻转）
/* 52 */Polyomino_5 P_6 = Polyomino_5(0, 1, 1, -1, 1, 0, 1, 1);//P镜像顺时针旋转90°
/* 53 */Polyomino_5 P_7 = Polyomino_5(1, 0, 1, 1, 2, 0, 2, 1);//P镜像顺时针旋转180°
/* 54 */Polyomino_5 P_8 = Polyomino_5(0, 1, 0, 2, 1, 0, 1, 1);//P镜像逆时针旋转90°
/* 55 */Polyomino_5 Y_1 = Polyomino_5(1, -1, 1, 0, 2, 0, 3, 0);//Y
/* 56 */Polyomino_5 Y_2 = Polyomino_5(1, -2, 1, -1, 1, 0, 1, 1);//Y顺时针旋转90°
/* 57 */Polyomino_5 Y_3 = Polyomino_5(1, 0, 2, 0, 2, 1, 3, 0);//Y顺时针旋转180°
/* 58 */Polyomino_5 Y_4 = Polyomino_5(0, 1, 0, 2, 0, 3, 1, 1);//Y逆时针旋转90°
/* 59 */Polyomino_5 Y_5 = Polyomino_5(1, 0, 1, 1, 2, 0, 3, 0);//Y镜像（左右翻转）
/* 60 */Polyomino_5 Y_6 = Polyomino_5(0, 1, 0, 2, 0, 3, 1, 2);//Y镜像顺时针旋转90°
/* 61 */Polyomino_5 Y_7 = Polyomino_5(1, 0, 2, -1, 2, 0, 3, 0);//Y镜像顺时针旋转180°
/* 62 */Polyomino_5 Y_8 = Polyomino_5(1, -1, 1, 0, 1, 1, 1, 2);//Y镜像逆时针旋转90°


Polyomino_5 area_plate[63] = { X,I_1,I_2,Z_1,Z_2,Z_3,Z_4,V_1,V_2,V_3,V_4,W_1,W_2,
W_3,W_4,T_1,T_2,T_3,T_4,U_1,U_2,U_3,U_4,F_1,F_2,F_3,F_4,F_5,F_6,F_7,F_8,
L_1,L_2,L_3,L_4,L_5,L_6,L_7,L_8,N_1,N_2,N_3,N_4,N_5,N_6,N_7,N_8,P_1,P_2,
P_3,P_4,P_5,P_6,P_7,P_8,Y_1,Y_2,Y_3,Y_4,Y_5,Y_6,Y_7,Y_8 };

vector<Polyomino_5> P5_plate(area_plate, area_plate + 63);

Polyomino_5::Polyomino_5()
{
}

Polyomino_5::Polyomino_5(short x2, short y2, short x3, short y3, short x4, short y4, short x5, short y5)
{
	pair<short, short> p2(x2, y2);
	polyomino.push_back(p2);
	pair<short, short> p3(x3, y3);
	polyomino.push_back(p3);
	pair<short, short> p4(x4, y4);
	polyomino.push_back(p4);
	pair<short, short> p5(x5, y5);
	polyomino.push_back(p5);
}

Polyomino_5::Polyomino_5(pair<short, short> p2)
{
	polyomino.push_back(p2);
}

Polyomino_5::~Polyomino_5()
{
	polyomino.clear();
}

Polyomino_6::Polyomino_6()
{
}

Polyomino_6::Polyomino_6(pair<short, short> p2)
{
	polyomino.push_back(p2);
}

Polyomino_6::~Polyomino_6()
{
	polyomino.clear();
}

Polyomino_7::Polyomino_7()
{
}

Polyomino_7::Polyomino_7(pair<short, short> p2)
{
	polyomino.push_back(p2);
}

Polyomino_7::~Polyomino_7()
{
	polyomino.clear();
}


Polyomino_8::Polyomino_8()
{
}

Polyomino_8::Polyomino_8(pair<short, short> p2)
{
	polyomino.push_back(p2);
}

Polyomino_8::~Polyomino_8()
{
	polyomino.clear();
}


Polyomino_9::Polyomino_9()
{
}

Polyomino_9::Polyomino_9(pair<short, short> p2)
{
	polyomino.push_back(p2);
}

Polyomino_9::~Polyomino_9()
{
	polyomino.clear();
}

ostream& operator<<(ostream& cout, Polyomino_6 p)
{
	for (auto it = p.polyomino.begin();it != p.polyomino.end();it++)
	{
		cout << "(" << it->first << ", " << it->second << ")";
	}
	return cout;
}

ostream& operator<<(ostream& cout, Polyomino_5 p)
{
	for (auto it = p.polyomino.begin();it != p.polyomino.end();it++)
	{
		cout << "(" << it->first << ", " << it->second << ")";
	}
	return cout;
}

ostream& operator<<(ostream& cout, Polyomino_7 p)
{
	for (auto it = p.polyomino.begin();it != p.polyomino.end();it++)
	{
		cout << "(" << it->first << ", " << it->second << ")";
	}
	return cout;
}

ostream& operator<<(ostream& cout, Polyomino_8 p)
{
	for (auto it = p.polyomino.begin();it != p.polyomino.end();it++)
	{
		cout << "(" << it->first << ", " << it->second << ")";
	}
	return cout;
}

ostream& operator<<(ostream& cout, Polyomino_9 p)
{
	for (auto it = p.polyomino.begin();it != p.polyomino.end();it++)
	{
		cout << "(" << it->first << ", " << it->second << ")";
	}
	return cout;
}


// 辅助函数：标准化骨牌表示
vector<pair<short, short>> normalize_polyomino(const vector<pair<short, short>>& coords) {
	if (coords.empty()) return {};

	// 找到最小坐标
	short min_x = coords[0].first, min_y = coords[0].second;
	for (const auto& p : coords) {
		if (p.first < min_x) min_x = p.first;
		if (p.second < min_y) min_y = p.second;
	}

	// 平移并排序
	vector<pair<short, short>> normalized;
	for (const auto& p : coords) {
		normalized.push_back({ p.first - min_x, p.second - min_y });
	}

	// 排序确保比较一致性
	sort(normalized.begin(), normalized.end());
	return normalized;
}