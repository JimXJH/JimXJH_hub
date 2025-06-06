// 数独游戏_5_20.cpp : 定义应用程序的入口点。
//
#include"MyWnd.h"
#include <fcntl.h>
#include <io.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    
    // 创建控制台窗口
    AllocConsole();

    // 重定向标准输出
    FILE* pFile;
    errno_t err = freopen_s(&pFile, "CONOUT$", "w", stdout);
    if (err != 0) {
        // 处理错误
        OutputDebugStringA("Failed to redirect stdout\n");
    }

    // 重定向标准错误
    err = freopen_s(&pFile, "CONOUT$", "w", stderr);
    if (err != 0) {
        OutputDebugStringA("Failed to redirect stderr\n");
    }

    // 设置控制台编码为 UTF-8
    SetConsoleOutputCP(CP_UTF8);
    

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY62, szWindowClass, MAX_LOADSTRING);
   
    //注册窗口类
    RegisterClass_Main(hInstance);
    RegisterClass_Menu(hInstance);
    RegisterClass_Play(hInstance);
    RegisterClass_Loading(hInstance);
    RegisterClass_Answer(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY62));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//应用程序初始化。
//在全局变量中保存实例句柄并创建和显示主程序窗口。
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   hMain = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if ((!hMain))
   {
      return FALSE;
   }

   ShowWindow(hMain, nCmdShow);
   UpdateWindow(hMain);

   return TRUE;
}


// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// 注册主窗口类。
ATOM RegisterClass_Main(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MainWndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY62));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY62);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


// 注册菜单窗口类。
ATOM RegisterClass_Menu(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MenuWndProc;  // 自定义窗口过程
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = 0;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = szWindowClass_MainMenu;
    wcex.hIconSm = 0;
    return RegisterClassExW(&wcex);
}

// 注册游玩界面窗口类
ATOM RegisterClass_Play(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = PlayWndProc;    // 自定义窗口过程
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = 0;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = szWindowClass_Play;
    wcex.hIconSm = 0;
    return RegisterClassExW(&wcex);
}

// 注册加载窗口类。
ATOM RegisterClass_Loading(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = LoadingWndProc;  // 自定义窗口过程
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = 0;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = szWindowClass_Loading;
    wcex.hIconSm = 0;
    return RegisterClassExW(&wcex);
}

// 注册答案展示窗口类
ATOM RegisterClass_Answer(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = AnswerWndProc;    // 自定义窗口过程
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY62)); // 使用应用图标
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = hBrush_Background; // 使用相同的背景色
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = szWindowClass_Answer;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    return RegisterClassExW(&wcex);
}