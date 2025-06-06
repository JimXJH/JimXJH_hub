#include"MyWnd.h"
using namespace std;
#include"CommCtrl.h"

HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本

HWND hMain = NULL;                              // 主窗口
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名


///////////////////////////////////////////////////////////////////////////////////////////////
// 菜单

HWND hMenu = NULL;                                                //菜单
WCHAR szWindowClass_MainMenu[MAX_LOADSTRING] = L"MenuWindowClass";//菜单窗口类名

HWND hTextWnd_hMenu_1;//显示界面语句

HWND hButton_ChooseSize_5;//5 * 5盘面选择按钮
//1005
HWND hButton_ChooseSize_6;//6 * 6盘面选择按钮
//1006
HWND hButton_ChooseSize_7;//7 * 7盘面选择按钮
//1007
HWND hButton_ChooseSize_8;//8 * 8盘面选择按钮
//1008
HWND hButton_ChooseSize_9;//9 * 9盘面选择按钮
//1009


///////////////////////////////////////////////////////////////////////////////////////////////////////
// 游玩窗口

HWND hPlay = NULL;                                             // 游玩窗口
WCHAR szWindowClass_Play[MAX_LOADSTRING] = L"PlayWindowClass"; // 游玩窗口类名

HWND hBackToMenu_hPlay = NULL;//退出按钮

// 盘面展示组件
vector<vector<HWND>> hWndPlate;//盘面展示窗口组
std::map<int, HBRUSH> hBrushes_Plate;//盘面划分画刷图

// 盘面按钮控件组和高亮状态
vector<vector<HWND>> hBtnPlate(9, vector<HWND>(9, NULL));  // 按钮控件组
vector<vector<bool>> v_highlight(9, vector<bool>(9, false)); // 高亮状态
int lastClicked_i = -1;
int lastClicked_j = -1;

// 高亮颜色画刷
HBRUSH hHighlightBrush_1 = CreateSolidBrush(RGB(255, 204, 0));
HBRUSH hHighlightBrush_2 = CreateSolidBrush(RGB(255, 255, 153));

// 透明按钮的子类化窗口过程
LRESULT CALLBACK TransparentButtonProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    switch (uMsg)
    {
    case WM_ERASEBKGND:
        return 1; // 已处理，避免擦除背景
    case WM_NCDESTROY:
        RemoveWindowSubclass(hWnd, TransparentButtonProc, uIdSubclass);
        break;
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

// 游玩交互组件
HWND hNumButtons[9] = { NULL };
HWND hEraseButton = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 加载界面

HWND hLoading = NULL;                                               //加载界面窗口
WCHAR szWindowClass_Loading[MAX_LOADSTRING] = L"LoadingWindowClass";//加载界面窗口类名

HWND hTextWnd_hLoading_1;//显示界面语句
HWND hBackToMenu_hLoading;//取消按钮

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 答案展示窗口

HWND hAnswer = NULL;                                               //答案展示窗口
WCHAR szWindowClass_Answer[MAX_LOADSTRING] = L"AnswerWindowClass";//答案展示窗口类名

// 答案盘面展示组件
vector<vector<HWND>> hWndAnswerPlate(9, vector<HWND>(9, NULL));//答案盘面展示窗口组

// 显示答案按钮
HWND hShowAnswerButton = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////////
// 通用

//盘面展示所需参数
vector<vector<int>> v_area_plate;
vector<vector<int>> v_ori_plate;
vector<vector<int>> v_ans_plate;
map<pair<int, int>, int> map_area_plate;
vector<vector<int>> v_dynamic_plate;
volatile int line_wnd_priv = 0;

// 背景色画刷
HBRUSH hBrush_Background = CreateSolidBrush(RGB(181, 135, 107));//背景（拿铁色）

// 字体控件
HFONT g_hTextFont = CreateFont
(
    30,                       // 字体高度
    0,                        // 宽度（0表示默认）
    0,                        // 文本倾斜度
    0,                        // 字体倾斜度
    FW_NORMAL,                // 粗细（FW_BOLD为加粗）
    FALSE,                    // 非斜体
    FALSE,                    // 无下划线
    FALSE,                    // 无删除线
    DEFAULT_CHARSET,          // 字符集
    OUT_OUTLINE_PRECIS,       // 输出精度
    CLIP_DEFAULT_PRECIS,      // 剪裁精度
    CLEARTYPE_QUALITY,        // 清晰度
    DEFAULT_PITCH | FF_SWISS, // 字间距和字体族
    L"Arial"                  // 字体名称
);

