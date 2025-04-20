#pragma once
using namespace std;

#include<iostream>
#include<vector>
#include<random>
#include<chrono>

bool solve(const int (*arr)[9]);//唯一解校验
bool solve_1(const vector<pair<int, int>>& v, const vector<pair<int, int>>::iterator it, int(*arr)[9]);
bool solve_2(const vector<pair<int, int>>& v, const vector<pair<int, int>>::iterator it, int(*arr)[9]);

void main_0();

int build(int (*arr)[9], const int (*answer_arr)[9]);
int build_1(int (*arr)[9]);


bool final_plate(int(*arr)[9], const int serial = 0);
//生成终盘

int exclusive(int (*number_arr)[9][9], int (*statistics)[9], int& x, int& y, const int(*arr)[9], const int add_number);
//排除法
void exclusive_1(const int x, const int y, int (*arr)[9]);//数字排除规则，目前为行、列和九宫格排除
int residual_difference(const int (*number_arr)[9][9], int& x, int& y, const int(*arr)[9]);//余差法
int double_exclusive(int (*number_arr)[9][9], int (*statistics)[9], int& x, int& y, const int(*arr)[9]);//二级排除

bool primary_solve(int(*arr)[9]);