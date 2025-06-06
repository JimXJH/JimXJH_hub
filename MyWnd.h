#pragma once
#include "resource.h"

#define _WIN32_WINNT 0x0A00
#include "framework.h"
#include <Uxtheme.h>
#pragma comment(lib, "UxTheme.lib")
#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "comctl32.lib")

#include<map>
#include<vector>
////////////////////////////////////////////////////////////////////////////////////////////////////////
//按钮汇总

extern HWND hButton_ChooseSize_5;//5 * 5盘面选择按钮
//1005
extern HWND hButton_ChooseSize_6;//6 * 6盘面选择按钮
//1006
extern HWND hButton_ChooseSize_7;//7 * 7盘面选择按钮
//1007
extern HWND hButton_ChooseSize_8;//8 * 8盘面选择按钮
//1008
extern HWND hButton_ChooseSize_9;//9 * 9盘面选择按钮
//1009

extern HWND hBackToMenu_hPlay;//hPlay退出按钮
//2001
extern HWND hBackToMenu_hLoading;//hloading取消按钮
//2002

extern std::vector<std::vector<HWND>> hBtnPlate;//按钮控件组
//3000 -- 3088

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 程序实例
#define MAX_LOADSTRING 100

extern HINSTANCE hInst;                                // 当前实例
extern WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本


//////////////////////////////////////////////////////////////////////////////////////////////
//主窗口
extern HWND hMain;                                     //主窗口
extern WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

ATOM RegisterClass_Main(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    MainWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//////////////////////////////////////////////////////////////////////////////////////////////
// 菜单
extern HWND hMenu;                                     //菜单窗口
extern WCHAR szWindowClass_MainMenu[MAX_LOADSTRING];   // 菜单窗口类名
LRESULT CALLBACK	MenuWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
ATOM				RegisterClass_Menu(HINSTANCE hInstance);

extern HWND hTextWnd_hMenu_1;//显示界面语句
extern HWND hTextWnd_2;//显示界面语句

extern HWND hButton_ChooseSize_5;//5 * 5盘面选择按钮
#define ID_Button_ChooseSize_5 1005
extern HWND hButton_ChooseSize_6;//6 * 6盘面选择按钮
#define ID_Button_ChooseSize_6 1006
extern HWND hButton_ChooseSize_7;//7 * 7盘面选择按钮
#define ID_Button_ChooseSize_7 1007
extern HWND hButton_ChooseSize_8;//8 * 8盘面选择按钮
#define ID_Button_ChooseSize_8 1008
extern HWND hButton_ChooseSize_9;//9 * 9盘面选择按钮
#define ID_Button_ChooseSize_9 1009

// 创建盘面组件
extern volatile int line_wnd_priv;
extern std::vector<std::vector<int>> v_area_plate;
extern std::vector<std::vector<int>> v_ori_plate;
extern std::vector<std::vector<int>> v_ans_plate;
extern volatile int line_wnd_priv;

void final_func(const int line, std::vector<std::vector<int>>& v_area_plate, std::vector<std::vector<int>>& v_ori_plate,
	std::vector<std::vector<int>>& v_ans_plate, std::map<std::pair<int, int>, int>& map_area_plate);

//////////////////////////////////////////////////////////////////////////////////////////////
// 游玩窗口
extern HWND hPlay;                               // 游玩窗口
extern WCHAR szWindowClass_Play[MAX_LOADSTRING]; // 游玩窗口类名
LRESULT CALLBACK    PlayWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
ATOM                RegisterClass_Play(HINSTANCE hInstance);

extern HWND hBackToMenu_hPlay;//退出按钮
#define ID_Button_BackToMenu_Play 2001 

// 盘面展示组件
extern std::vector<std::vector<HWND>> hWndPlate;//盘面展示窗口组
extern std::map<int, HBRUSH> hBrushes_Plate;//盘面划分画刷图


// 盘面按钮控件组和高亮状态
extern std::vector<std::vector<HWND>> hBtnPlate;  // 按钮控件组
extern std::vector<std::vector<bool>> v_highlight; // 高亮状态
extern int lastClicked_i, lastClicked_j;           // 上一次点击的位置

// 透明按钮的子类化窗口过程
LRESULT CALLBACK	TransparentButtonProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass,DWORD_PTR dwRefData);

// 高亮颜色画刷
extern HBRUSH hHighlightBrush_1;
extern HBRUSH hHighlightBrush_2;

// 游玩交互组件
extern HWND hNumButtons[9];   // 数字按钮 (1-9)
extern HWND hEraseButton;     // 擦除按钮

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 加载界面

extern HWND hLoading;                                               //加载界面窗口
extern WCHAR szWindowClass_Loading[MAX_LOADSTRING];//加载界面窗口类名
LRESULT CALLBACK    LoadingWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
ATOM                RegisterClass_Loading(HINSTANCE hInstance);

extern HWND hTextWnd_hLoading_1;//显示界面语句
extern HWND hBackToMenu_hLoading;//取消按钮
#define ID_Button_Cancel_Loading 2002


////////////////////////////////////////////////////////////////////////////////////////////////////////
// 答案展示窗口

extern HWND hAnswer;                                               //答案展示窗口
extern WCHAR szWindowClass_Answer[MAX_LOADSTRING];//答案展示窗口类名
LRESULT CALLBACK    AnswerWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
ATOM                RegisterClass_Answer(HINSTANCE hInstance);

// 答案盘面展示组件
extern std::vector<std::vector<HWND>> hWndAnswerPlate;//答案盘面展示窗口组

// 显示答案按钮
extern HWND hShowAnswerButton;
#define ID_Button_ShowAnswer 4011

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 通用

// 盘面展示所需参数
extern std::vector<std::vector<int>> v_area_plate;
extern std::vector<std::vector<int>> v_ori_plate;
extern std::vector<std::vector<int>> v_ans_plate;
extern std::map<std::pair<int, int>, int> map_area_plate;
extern std::vector<std::vector<int>> v_dynamic_plate;
extern volatile int line_wnd_priv;

// 背景色画刷
extern HBRUSH hBrush_Background;

// 字体控件
extern HFONT g_hTextFont;

// 线程结束消息
#define WM_THREAD_COMPLETE_Build_Plate (WM_USER + 1)

