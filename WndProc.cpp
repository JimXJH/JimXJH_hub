#include"MyWnd.h"
using namespace std;

#include <windows.h>
#include<string>
#include<iostream>
#include"CommCtrl.h"


// 主窗口的窗口过程
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // 创建子窗口

        //菜单窗口
        
        hMenu = CreateWindowEx(
            0,
            szWindowClass_MainMenu,       // 使用自定义类名
            L"",
            WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
            0, 0, 0, 0,        // 初始位置大小由WM_SIZE设置
            hWnd,
            NULL,
            hInst,
            NULL
        );

        //游玩窗口
        hPlay = CreateWindowEx
        (
            0,
            szWindowClass_Play,    // 使用新注册的类名
            L"",
            WS_CHILD | WS_CLIPCHILDREN,
            0, 0, 0, 0,                // 初始位置和大小由WM_SIZE设置
            hWnd,                     
            NULL,
            hInst,
            NULL
        );


        //加载界面窗口
        hLoading= CreateWindowEx
        (
            0,
            szWindowClass_Loading,    // 使用新注册的类名
            L"",
            WS_CHILD | WS_CLIPCHILDREN,
            0, 0, 0, 0,                // 初始位置和大小由WM_SIZE设置
            hWnd,
            NULL,
            hInst,
            NULL
        );

        break;
    }
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    }
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        // 调整子窗口大小覆盖整个客户区

        //菜单窗口
        if (hMenu) {
            SetWindowPos(
                hMenu,
                HWND_BOTTOM,
                0, 0,
                width, height,
                SWP_NOZORDER | SWP_NOACTIVATE
            );
        }

        //游玩窗口
        if (hPlay) 
        {
            SetWindowPos(
                hPlay,
                HWND_TOP,
                0, 0,
                width, height,
                SWP_NOZORDER | SWP_NOACTIVATE
            );
        }

        //加载界面窗口
        if (hLoading)
        {
            SetWindowPos(
                hLoading,
                HWND_TOP,
                0, 0,
                width, height,
                SWP_NOZORDER | SWP_NOACTIVATE
            );
        }

        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:

        // 清理答案窗口
        if (hAnswer != NULL) {
            DestroyWindow(hAnswer);
            hAnswer = NULL;
        }

        // 释放字体资源
        if (g_hTextFont != NULL) {
            DeleteObject(g_hTextFont);
            g_hTextFont = NULL;
        }

        //释放颜色控件
        if (hBrush_Background != NULL) {
            DeleteObject(hBrush_Background);
            hBrush_Background = NULL;
        }

        for (auto& pair : hBrushes_Plate)
        {
            if (pair.second != NULL)
            {
                DeleteObject(pair.second);
            }
        }

        //退出程序（唯一出口）
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 菜单窗口的窗口过程
LRESULT CALLBACK MenuWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
    {
        hTextWnd_hMenu_1 = CreateWindowEx(
            0,                          // 扩展样式（无特殊样式）
            L"STATIC",                  // 类名（静态控件）
            L"锯齿数独游戏（随机出题）",         // 窗口文本内容
            WS_CHILD | WS_VISIBLE | SS_SIMPLE | WS_DLGFRAME | SS_CENTER, // 样式：子窗口、可见、简单文本、不可变粗边框、文本(水平)居中
            0,                          // x坐标（相对于父窗口左上角）
            0,                          // y坐标（相对于父窗口左上角）
            0,                        // 宽度
            0,                         // 高度
            hWnd,                   // 父窗口句柄（主窗口）
            NULL,                       // 菜单句柄（无）
            hInst,                  // 应用程序实例句柄
            NULL                        // 额外参数（无）
        );

        //设置字体
        SendMessage(hTextWnd_hMenu_1, WM_SETFONT, (WPARAM)g_hTextFont, TRUE);

        hButton_ChooseSize_5 = CreateWindowEx(
            WS_EX_CLIENTEDGE,        // 扩展窗口样式（可选立体边框）
            L"BUTTON",               // 预定义的按钮类名
            L"5 * 5",             // 按钮显示的文本
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // 窗口样式 + 按钮类型
            0,                       // 水平位置（相对父窗口）
            0,                       // 垂直位置（相对父窗口）
            0,                   // 按钮宽度
            0,                  // 按钮高度
            hWnd,              // 父窗口句柄
            (HMENU)ID_Button_ChooseSize_5,       // 控件ID（用于消息处理）
            hInst,               // 应用程序实例句柄
            NULL                     // 通常为NULL
        );

        hButton_ChooseSize_6 = CreateWindowEx(
            WS_EX_CLIENTEDGE,        // 扩展窗口样式（可选立体边框）
            L"BUTTON",               // 预定义的按钮类名
            L"6 * 6",             // 按钮显示的文本
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // 窗口样式 + 按钮类型
            0,                       // 水平位置（相对父窗口）
            0,                       // 垂直位置（相对父窗口）
            0,                   // 按钮宽度
            0,                  // 按钮高度
            hWnd,              // 父窗口句柄
            (HMENU)ID_Button_ChooseSize_6,       // 控件ID（用于消息处理）
            hInst,               // 应用程序实例句柄
            NULL                     // 通常为NULL
        );

        hButton_ChooseSize_7 = CreateWindowEx(
            WS_EX_CLIENTEDGE,        // 扩展窗口样式（可选立体边框）
            L"BUTTON",               // 预定义的按钮类名
            L"7 * 7",             // 按钮显示的文本
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // 窗口样式 + 按钮类型
            0,                       // 水平位置（相对父窗口）
            0,                       // 垂直位置（相对父窗口）
            0,                   // 按钮宽度
            0,                  // 按钮高度
            hWnd,              // 父窗口句柄
            (HMENU)ID_Button_ChooseSize_7,       // 控件ID（用于消息处理）
            hInst,               // 应用程序实例句柄
            NULL                     // 通常为NULL
        );

        hButton_ChooseSize_8 = CreateWindowEx(
            WS_EX_CLIENTEDGE,        // 扩展窗口样式（可选立体边框）
            L"BUTTON",               // 预定义的按钮类名
            L"8 * 8",             // 按钮显示的文本
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // 窗口样式 + 按钮类型
            0,                       // 水平位置（相对父窗口）
            0,                       // 垂直位置（相对父窗口）
            0,                   // 按钮宽度
            0,                  // 按钮高度
            hWnd,              // 父窗口句柄
            (HMENU)ID_Button_ChooseSize_8,       // 控件ID（用于消息处理）
            hInst,               // 应用程序实例句柄
            NULL                     // 通常为NULL
        );

        hButton_ChooseSize_9 = CreateWindowEx(
            WS_EX_CLIENTEDGE,        // 扩展窗口样式（可选立体边框）
            L"BUTTON",               // 预定义的按钮类名
            L"9 * 9",             // 按钮显示的文本
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, // 窗口样式 + 按钮类型
            0,                       // 水平位置（相对父窗口）
            0,                       // 垂直位置（相对父窗口）
            0,                   // 按钮宽度
            0,                  // 按钮高度
            hWnd,              // 父窗口句柄
            (HMENU)ID_Button_ChooseSize_9,       // 控件ID（用于消息处理）
            hInst,               // 应用程序实例句柄
            NULL                     // 通常为NULL
        );
    }
    case WM_SIZE: 
    {
        RECT rcClient;
        GetClientRect(hWnd, &rcClient);
        int clientWidth = rcClient.right - rcClient.left;
        int clientHeight = rcClient.bottom - rcClient.top;

        // 布局参数
        const int BUTTON_WIDTH = 180;
        const int BUTTON_HEIGHT = 50;
        const int BUTTON_SPACING = 20;  // 按钮间距
        const int TOTAL_BUTTONS = 5;     // 5个按钮

        // 计算总内容高度（所有按钮高度+间距）
        int totalContentHeight = TOTAL_BUTTONS * BUTTON_HEIGHT + (TOTAL_BUTTONS - 1) * BUTTON_SPACING;

        // 起始Y坐标（垂直居中）
        int startY = (clientHeight - totalContentHeight) / 2;
        if (startY < 20) startY = 20;  // 保持最小上边距

        // 统一调整所有按钮位置
        int buttonPositions[] = {
            startY,
            startY + BUTTON_HEIGHT + BUTTON_SPACING,
            startY + 2 * (BUTTON_HEIGHT + BUTTON_SPACING),
            startY + 3 * (BUTTON_HEIGHT + BUTTON_SPACING),
            startY + 4 * (BUTTON_HEIGHT + BUTTON_SPACING)
        };

        // 调整所有按钮位置
        HWND buttons[] = {
            hButton_ChooseSize_5,
            hButton_ChooseSize_6,
            hButton_ChooseSize_7,
            hButton_ChooseSize_8,
            hButton_ChooseSize_9
        };

        for (int i = 0; i < 5; i++) {
            SetWindowPos(
                buttons[i],
                NULL,
                (clientWidth - BUTTON_WIDTH) / 2,  // 水平居中
                buttonPositions[i],
                BUTTON_WIDTH,
                BUTTON_HEIGHT,
                SWP_NOZORDER | SWP_NOACTIVATE
            );
        }

        // 调整标题文本位置（保持原有逻辑微调）
        SetWindowPos(
            hTextWnd_hMenu_1,
            NULL,
            (clientWidth - 280) / 2,  // 水平居中
            20,                        // 固定上边距
            310,
            40,
            SWP_NOZORDER | SWP_NOACTIVATE
        );
        break;
    }
    case WM_COMMAND:
    {
        int wMenuId = LOWORD(wParam);

        if ((wMenuId > 1004) && (wMenuId < 1010))
        {
            line_wnd_priv = wMenuId - 1000;
        }

        if (line_wnd_priv)
        {
            //隐藏菜单窗口
            ShowWindow(hMenu, SW_HIDE);

            //单开final_func()线程
            //
            // 创建线程参数
            struct ThreadParams {
                int line_size;
                std::vector<std::vector<int>>* p_area;
                std::vector<std::vector<int>>* p_ori;
                std::vector<std::vector<int>>* p_ans;
                std::map<std::pair<int,int>,int>* p_map;
                HWND hWnd;
            };

            ThreadParams* params = new ThreadParams{
                line_wnd_priv,
                &v_area_plate,
                &v_ori_plate,
                &v_ans_plate,
                &map_area_plate,
                hPlay
            };

            // 创建线程
            CreateThread(
                NULL,
                0,
                [](LPVOID lpParam) -> DWORD {
                    ThreadParams* p = static_cast<ThreadParams*>(lpParam);
                    final_func(p->line_size, *(p->p_area), *(p->p_ori), *(p->p_ans),*(p->p_map));

                    // 发送完成消息（发送至hPlay）
                    PostMessage(p->hWnd, WM_THREAD_COMPLETE_Build_Plate, 0, 0);
                    delete p;
                    return 0;
                },
                params,
                0,
                NULL
            );

            ShowWindow(hLoading, SW_SHOW);
        }

        break;
    }
    case WM_ERASEBKGND:
        return 1;  // 避免闪烁，由WM_PAINT统一绘制

    case WM_DRAWITEM:
    {
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        //纯色背景
        FillRect(hdc, &ps.rcPaint, hBrush_Background);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_CTLCOLORSTATIC:// 静态文本控件 设置背景色
    {
        break;
    }
    case WM_CTLCOLORBTN:// 按钮控件 设置背景色
    {
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//游玩窗口的窗口过程
LRESULT CALLBACK PlayWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // 静态变量
    static HFONT hCellFont;        // 盘面按钮字体
    static int lastSquareSize;     // 记录上次格子大小
    static HFONT hButtonFont;      // 数字按钮字体
    static int lastButtonHeight;   // 记录上次按钮高度
    static HFONT hShowAnswerFont;  // 显示答案按钮字体
    static int lastShowAnswerButtonHeight; // 记录显示答案按钮的上次高度

    switch (message)
    {
    case WM_CREATE:
    {
        //初始化静态遍量
        hCellFont = NULL;
        lastSquareSize = 0;
        hButtonFont = NULL;
        lastButtonHeight = 0;
        hShowAnswerFont = NULL;
        lastShowAnswerButtonHeight = 0;

        //初始化颜色图
        hBrushes_Plate[1] = CreateSolidBrush(RGB(70, 130, 180));
        hBrushes_Plate[2] = CreateSolidBrush(RGB(0, 0, 55));
        hBrushes_Plate[3] = CreateSolidBrush(RGB(224, 247, 250));
        hBrushes_Plate[4] = CreateSolidBrush(RGB(0, 35, 102));
        hBrushes_Plate[5] = CreateSolidBrush(RGB(173, 216, 230));
        hBrushes_Plate[6] = CreateSolidBrush(RGB(25, 25, 112));
        hBrushes_Plate[7] = CreateSolidBrush(RGB(135, 206, 235));
        hBrushes_Plate[8] = CreateSolidBrush(RGB(65, 105, 225));
        hBrushes_Plate[9] = CreateSolidBrush(RGB(100, 149, 237));

        //创建盘面展示窗口组
        hWndPlate = vector<vector<HWND>>(9, vector<HWND>(9, NULL));

        // 创建按钮控件组
        hBtnPlate = vector<vector<HWND>>(9, vector<HWND>(9, NULL));

        // 创建盘面窗口和按钮控件
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                hWndPlate[i][j] = CreateWindowEx
                (
                    0,
                    L"STATIC",
                    L"0",
                    WS_CHILD | SS_CENTER | WS_BORDER,
                    0,0,0,0,
                    hWnd,
                    NULL,
                    hInst,
                    NULL);

                // 设置区域属性（临时值，后续会更新）
                // 存储格子所属的区域（map_area_plate对应的值）
                SetProp(hWndPlate[i][j], L"SUDOKU_AREA", (HANDLE)0);
                // 设置行列属性
                SetProp(hWndPlate[i][j], L"SUDOKU_ROW", (HANDLE)(INT_PTR)i);
                SetProp(hWndPlate[i][j], L"SUDOKU_COL", (HANDLE)(INT_PTR)j);
                // 设置文本类型属性（临时值，后续会更新）
                // 0，空格子（无文本）；1，盘面已知数字（紫色字）；2，有填数且无明显错误（绿色字）；3，有填数且有明显错误（红色字）
                SetProp(hWndPlate[i][j], L"SUDOKU_TEXT", (HANDLE)(INT_PTR)0);

                // 创建透明按钮（覆盖在静态控件上）
                hBtnPlate[i][j] = CreateWindow(
                    L"BUTTON",
                    L"",
                    WS_CHILD | BS_OWNERDRAW,
                    0, 0, 0, 0,
                    hWnd,
                    (HMENU)(3000 + 10 * i + j), // ID = 3000 + 10*i + j
                    hInst,
                    NULL);

                // 设置按钮为透明
                SetWindowLong(hBtnPlate[i][j], GWL_EXSTYLE,
                    GetWindowLong(hBtnPlate[i][j], GWL_EXSTYLE) | WS_EX_TRANSPARENT);

                // 子类化按钮以处理 WM_ERASEBKGND
                SetWindowSubclass(hBtnPlate[i][j], TransparentButtonProc, 0, 0);
            }
        }

        // 创建数字按钮 1-9
        for (int i = 0; i < 9; i++) {
            wchar_t buttonText[10];
            wsprintf(buttonText, L"%d", i + 1);
            hNumButtons[i] = CreateWindow(
                L"BUTTON",
                buttonText,
                WS_CHILD | BS_PUSHBUTTON,
                0, 0, 0, 0,  // 位置大小将在WM_SIZE中设置
                hWnd,
                (HMENU)(4001 + i),  // ID从4001开始
                hInst,
                NULL
            );
        }

        // 创建擦除按钮
        hEraseButton = CreateWindow(
            L"BUTTON",
            L"擦除",
            WS_CHILD | BS_PUSHBUTTON,
            0, 0, 0, 0,  // 位置大小将在WM_SIZE中设置
            hWnd,
            (HMENU)4010,  // ID=4010
            hInst,
            NULL
        );

        // 创建显示答案按钮
        hShowAnswerButton = CreateWindow(
            L"BUTTON",
            L"显示答案",
            WS_CHILD | BS_PUSHBUTTON,
            0, 0, 0, 0,  // 位置大小将在WM_SIZE中设置
            hWnd,
            (HMENU)ID_Button_ShowAnswer,
            hInst,
            NULL
        );

        //退出按钮
        hBackToMenu_hPlay = CreateWindowEx
        (
            0,
            L"BUTTON",
            L"退出",
            WS_CHILD | SS_CENTER | WS_BORDER | WS_VISIBLE,
            0,
            0,
            0,
            0,
            hWnd,
            (HMENU)ID_Button_BackToMenu_Play,
            hInst,
            NULL
        );
        break;
    }
    case WM_SIZE:
    {
        RECT rcClient;
        GetClientRect(hWnd, &rcClient);
        int clientWidth = rcClient.right - rcClient.left;
        int clientHeight = rcClient.bottom - rcClient.top;

        if (clientWidth <= 0 || clientHeight <= 0 || line_wnd_priv <= 0) {
            break; // 避免无效计算
        }

        // === 左侧盘面区域 (占2/3宽度) ===
        const int boardWidth = clientWidth * 2 / 3;
        const int totalSize = min(clientHeight - 40, boardWidth);
        const int squareSize = totalSize / line_wnd_priv;
        const int startY = 20;
        int startX = (boardWidth - totalSize) / 2;  // 在左侧区域居中

        int currentSize = (line_wnd_priv <= 0) ? 9 : line_wnd_priv; // 默认显示9x9

        // === 动态调整字体大小 ===
        if (squareSize != lastSquareSize) 
        {
            // 删除旧字体
            if (hCellFont != NULL) 
            {
                DeleteObject(hCellFont);
                hCellFont = NULL;
            }

            // 创建新字体（大小为格子的70%）
            int fontSize = (squareSize * 70) / 100;
            hCellFont = CreateFont(
                fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
            lastSquareSize = squareSize;
        }

        if (hCellFont != NULL)
        {
            // 应用到所有格子控件
            for (int i = 0; i < currentSize; i++) {
                for (int j = 0; j < currentSize; j++) {
                    if (hWndPlate[i][j] != NULL) {
                        SendMessage(hWndPlate[i][j], WM_SETFONT, (WPARAM)hCellFont, TRUE);
                    }
                }
            }
        }

        // === 字体调整结束 ===

        // 调整静态控件和按钮的位置和大小
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if ((i < currentSize) && (j < currentSize))
                {
                    // 设置静态控件
                    SetWindowPos
                    (
                        hWndPlate[i][j],
                        NULL,
                        startX + j * squareSize,
                        startY + i * squareSize,
                        squareSize,
                        squareSize,
                        SWP_NOZORDER | SWP_NOACTIVATE
                    );
                    ShowWindow(hWndPlate[i][j], SW_SHOW);

                    // 设置按钮（覆盖在静态控件上）
                    SetWindowPos(
                        hBtnPlate[i][j],
                        HWND_TOP,  // 确保按钮在最上层
                        startX + j * squareSize,
                        startY + i * squareSize,
                        squareSize,
                        squareSize,
                        SWP_NOZORDER | SWP_NOACTIVATE
                    );
                    ShowWindow(hBtnPlate[i][j], SW_SHOW);
                }
                else
                {
                    ShowWindow(hWndPlate[i][j], SW_HIDE);
                    ShowWindow(hBtnPlate[i][j], SW_HIDE);
                }
            }
        }


        // === 右侧按钮区域 (占1/3宽度) ===
        const int buttonAreaWidth = clientWidth - boardWidth;  // 使用精确计算
        const int buttonAreaStartX = boardWidth;

        // 计算按钮宽度（考虑边距和间距）
        const int maxButtonsPerRow = 3; // 每行最多3个按钮
        const int buttonSpacing = 15;   // 按钮间距
        const int sideMargin = 20;      // 左右边距

        // 计算最大可用宽度（考虑边距和间距）
        int maxAvailableWidth = buttonAreaWidth - 2 * sideMargin - (maxButtonsPerRow - 1) * buttonSpacing;
        int buttonWidth = maxAvailableWidth / maxButtonsPerRow;

        // 限制按钮宽度范围（80-120像素）
        buttonWidth = min(120, max(80, buttonWidth));
        const int buttonHeight = 60;  // 固定按钮高度

        // 计算行数
        int numRows = (line_wnd_priv + maxButtonsPerRow - 1) / maxButtonsPerRow;

        // 数字按钮区域高度
        int buttonAreaHeight = numRows * buttonHeight + (numRows - 1) * buttonSpacing;

        // 起始Y坐标（垂直居中）
        int buttonStartY = (clientHeight - buttonAreaHeight - buttonHeight * 2 - buttonSpacing * 2) / 2;
        if (buttonStartY < 20) buttonStartY = 20;

        // === 动态调整按钮字体大小 ===
        if (buttonHeight != lastButtonHeight)
        {
            // 删除旧字体
            if (hButtonFont != NULL)
            {
                DeleteObject(hButtonFont);
                hButtonFont = NULL;
            }

            // 创建新字体（大小为按钮高度的60%）
            int fontSize = (buttonHeight * 60) / 100;
            hButtonFont = CreateFont(
                fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
            lastButtonHeight = buttonHeight;
        }

        // 设置数字按钮
        for (int i = 0; i < line_wnd_priv; i++)
        {
            // 计算行和列索引
            int row = i / maxButtonsPerRow;
            int col = i % maxButtonsPerRow;

            // 计算位置（考虑边距）
            int xPos = buttonAreaStartX + sideMargin + col * (buttonWidth + buttonSpacing);
            int yPos = buttonStartY + row * (buttonHeight + buttonSpacing);

            SetWindowPos(
                hNumButtons[i],
                NULL,
                xPos,
                yPos,
                buttonWidth,
                buttonHeight,
                SWP_NOZORDER | SWP_NOACTIVATE
            );

            // 设置按钮字体
            if (hButtonFont != NULL) {
                SendMessage(hNumButtons[i], WM_SETFONT, (WPARAM)hButtonFont, TRUE);
            }

            ShowWindow(hNumButtons[i], SW_SHOW);
        }

        // 隐藏未使用的数字按钮
        for (int i = line_wnd_priv; i < 9; i++) {
            ShowWindow(hNumButtons[i], SW_HIDE);
        }

        // 设置擦除按钮（在数字按钮下方）
        SetWindowPos(
            hEraseButton,
            NULL,
            buttonAreaStartX + (buttonAreaWidth - buttonWidth) / 2,
            buttonStartY + numRows * (buttonHeight + buttonSpacing) + buttonSpacing, // 放在数字按钮下方
            buttonWidth,
            buttonHeight,
            SWP_NOZORDER | SWP_NOACTIVATE
        );

        // 设置擦除按钮字体
        if (hButtonFont != NULL) {
            SendMessage(hEraseButton, WM_SETFONT, (WPARAM)hButtonFont, TRUE);
        }

        ShowWindow(hEraseButton, SW_SHOW);

        // 动态调整显示答案按钮字体大小
        if (buttonHeight != lastShowAnswerButtonHeight)
        {
            // 删除旧字体
            if (hShowAnswerFont != NULL)
            {
                DeleteObject(hShowAnswerFont);
                hShowAnswerFont = NULL;
            }

            // 创建新字体（大小为按钮高度的50%）
            int fontSize = (buttonHeight * 50) / 100; // 从60%改为50%
            hShowAnswerFont = CreateFont(
                fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
            lastShowAnswerButtonHeight = buttonHeight;
        }

        // 设置显示答案按钮（在擦除按钮下方）
        SetWindowPos(
            hShowAnswerButton,
            NULL,
            buttonAreaStartX + (buttonAreaWidth - buttonWidth) / 2,
            buttonStartY + numRows * (buttonHeight + buttonSpacing) + buttonSpacing * 2 + buttonHeight, // 放在擦除按钮下方
            buttonWidth,
            buttonHeight,
            SWP_NOZORDER | SWP_NOACTIVATE
        );

        // 设置按钮字体 (使用单独字体)
        if (hShowAnswerFont != NULL) {
            SendMessage(hShowAnswerButton, WM_SETFONT, (WPARAM)hShowAnswerFont, TRUE);
        }
        ShowWindow(hShowAnswerButton, SW_SHOW);


        //设置退出按钮
        const int BUTTON_WIDTH = 80;
        const int BUTTON_HEIGHT = 30;
        SetWindowPos(
            hBackToMenu_hPlay,
            NULL,
            clientWidth - BUTTON_WIDTH - 10,  // 距离右侧10像素
            10,                              // 距离顶部10像素
            BUTTON_WIDTH,
            BUTTON_HEIGHT,
            SWP_NOZORDER | SWP_NOACTIVATE
        );

        break;
    }
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        HWND hWndCtrl = (HWND)lParam;

        // 获取行列
        int i = (int)(INT_PTR)GetProp(hWndCtrl, L"SUDOKU_ROW");
        int j = (int)(INT_PTR)GetProp(hWndCtrl, L"SUDOKU_COL");

        int text_type = (int)(INT_PTR)GetProp(hWndCtrl, L"SUDOKU_TEXT");
        // 高亮状态使用橙色背景
        if (v_highlight[i][j]) {
            switch (text_type)
            {
            case 0:
                break;
            case 1:
                SetTextColor(hdcStatic, RGB(128, 0, 128));// 设置静态文本颜色
                break;
            case 2:
                SetTextColor(hdcStatic, RGB(50, 205, 50));// 设置正确文本颜色
                break;
            case 3:
                SetTextColor(hdcStatic, RGB(255, 69, 0));// 设置错误文本颜色
                break;
            }

            SetBkMode(hdcStatic, TRANSPARENT);

            if ((i == lastClicked_i) && (j == lastClicked_j))
            {
                return (LRESULT)hHighlightBrush_1;
            }
            else
            {
                return (LRESULT)hHighlightBrush_2;
            }
        }

        // 获取区域属性
        INT_PTR area = (INT_PTR)GetProp(hWndCtrl, L"SUDOKU_AREA");

        // 正常状态使用区域颜色背景
        if (area >= 1 && area <= 9 && hBrushes_Plate.find(area) != hBrushes_Plate.end())
        {
            switch (text_type)
            {
            case 0:
                break;
            case 1:
                SetTextColor(hdcStatic, RGB(128, 0, 128));// 设置静态文本颜色
                break;
            case 2:
                SetTextColor(hdcStatic, RGB(50, 205, 50));// 设置正确文本颜色
                break;
            case 3:
                SetTextColor(hdcStatic, RGB(255, 69, 0));// 设置错误文本颜色
                break;
            }
            SetBkMode(hdcStatic, TRANSPARENT);     // 设置背景透明
            return (LRESULT)hBrushes_Plate[area];  // 返回区域对应的画刷
        }
        break;
    }
    case WM_DRAWITEM: // 处理透明按钮绘制
    {
        DRAWITEMSTRUCT* pDraw = (DRAWITEMSTRUCT*)lParam;
        if (pDraw->CtlType == ODT_BUTTON)
        {
            // 透明背景 - 什么都不做
            return TRUE;
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 纯色背景
        FillRect(hdc, &ps.rcPaint, hBrush_Background);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_THREAD_COMPLETE_Build_Plate:
    {
        //初始化动态数字盘
        v_dynamic_plate = v_ori_plate;

        // 重置高亮状态
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                v_highlight[i][j] = false;
            }
        }
        lastClicked_i = -1;
        lastClicked_j = -1;


        for (int i = 0; i < line_wnd_priv; i++) {
            for (int j = 0; j < line_wnd_priv; j++) {
                cout << v_ori_plate[i][j] << " ";
            }
            cout << endl;
        }

        // 设置数独盘面文本
        for (int i = 0; i < line_wnd_priv; i++) {
            for (int j = 0; j < line_wnd_priv; j++) {
                if (hWndPlate[i][j] != NULL) 
                {
                    wchar_t wstr[2] = { 0 };// 初始化宽字符缓冲区
                    int n = v_ori_plate[i][j];
                    if (n != 0) {
                        wstr[0] = L'0' + static_cast<wchar_t>(n);// 数字转宽字符
                        SetProp(hWndPlate[i][j], L"SUDOKU_TEXT", (HANDLE)(INT_PTR)1);// 更新文本类型属性
                    }
                    else
                    {
                        SetProp(hWndPlate[i][j], L"SUDOKU_TEXT", (HANDLE)(INT_PTR)0);
                    }
                    SetWindowText(hWndPlate[i][j], wstr);

                    // 更新区域属性
                    auto it = map_area_plate.find({ i, j });
                    if (it != map_area_plate.end()) {
                        SetProp(hWndPlate[i][j], L"SUDOKU_AREA", (HANDLE)(INT_PTR)it->second);
                    }
                }
            }
        }

        cout << endl;
        for (int i = 0; i < line_wnd_priv; i++) {
            for (int j = 0; j < line_wnd_priv; j++) {
                cout << (int)(INT_PTR)GetProp(hWndPlate[i][j], L"SUDOKU_TEXT") << " ";
            }
            cout << endl;
        }

        //手动触发WM_SIZE
        RECT rc;
        GetClientRect(hMain, &rc);
        SendMessage(hWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(rc.right, rc.bottom));

        ShowWindow(hLoading, SW_HIDE);
        ShowWindow(hPlay, SW_SHOW);

        break;
    }
    case WM_ERASEBKGND:
        return 1;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        // 盘面按钮处理 (ID范围 3000-3088)
        if (wmId >= 3000 && wmId <= 3088)
        {
            // 解析行号和列号
            int idOffset = wmId - 3000;
            int i = idOffset / 10;
            int j = idOffset % 10;

            // 点击的是高亮按钮
            if (v_highlight[i][j])
            {
                // 重置所有高亮
                for (int x = 0; x < line_wnd_priv; x++) {
                    for (int y = 0; y < line_wnd_priv; y++)
                    {
                        v_highlight[x][y] = false;
                        InvalidateRect(hWndPlate[x][y], NULL, TRUE);
                    }
                }

                lastClicked_i = -1;
                lastClicked_j = -1;
            }
            // 点击的是非高亮按钮
            else
            {
                // 重置所有高亮
                for (int x = 0; x < line_wnd_priv; x++) {
                    for (int y = 0; y < line_wnd_priv; y++)
                    {
                        v_highlight[x][y] = false;
                        InvalidateRect(hWndPlate[x][y], NULL, TRUE);
                    }
                }
                // 处理有数字的格子
                if (v_dynamic_plate[i][j] != 0)
                {
                    int num = v_dynamic_plate[i][j];
                    // 设置新的高亮
                    for (int x = 0; x < line_wnd_priv; x++) {
                        for (int y = 0; y < line_wnd_priv; y++) {
                            if (v_dynamic_plate[x][y] == num) {
                                v_highlight[x][y] = true;
                                InvalidateRect(hWndPlate[x][y], NULL, TRUE);
                            }
                        }
                    }
                    lastClicked_i = i;
                    lastClicked_j = j;
                }
                // 处理空格子
                else
                {
                    lastClicked_i = i;
                    lastClicked_j = j;

                    // 设置新的高亮
                    // 行高亮
                    for (int row = 0;row < line_wnd_priv;row++)
                    {
                        v_highlight[row][j] = true;
                        InvalidateRect(hWndPlate[row][j], NULL, TRUE);
                    }
                    // 列高亮
                    for (int col = 0;col < line_wnd_priv;col++)
                    {
                        v_highlight[i][col] = true;
                        InvalidateRect(hWndPlate[i][col], NULL, TRUE);
                    }
                    // 区域高亮
                    int area_code = map_area_plate.find({ i,j })->second;
                    for (auto it = map_area_plate.begin();it != map_area_plate.end();it++)
                    {
                        if (it->second == area_code)
                        {
                            v_highlight[it->first.first][it->first.second] = true;
                            InvalidateRect(hWndPlate[it->first.first][it->first.second], NULL, TRUE);
                        }
                    }
                }
            }
        }
        // 数字按钮处理 (ID 4001-4009)
        else if (wmId >= 4001 && wmId <= 4009) 
        {
            int num = wmId - 4000;  // 获取按钮对应的数字

            cout << "lastClicked: (" << lastClicked_i << ", " << lastClicked_j << ")"; 
            if ((lastClicked_i != -1) && (lastClicked_j != -1))
            {
                cout << "--- SUDOKU_TEXT = " << (int)(INT_PTR)GetProp(hWndPlate[lastClicked_i][lastClicked_j], L"SUDOKU_TEXT");
            }
            cout << endl;

            // 没有选中格子或选中的是原始数字
            if (lastClicked_i == -1 || (int)(INT_PTR)GetProp(hWndPlate[lastClicked_i][lastClicked_j], L"SUDOKU_TEXT") == 1) 
            {
                // 重置高亮；高亮所有相同数字的格子
                for (int i = 0; i < line_wnd_priv; i++) 
                {
                    for (int j = 0; j < line_wnd_priv; j++) 
                    {
                        if (v_dynamic_plate[i][j] == num) 
                        {
                            v_highlight[i][j] = true;
                            InvalidateRect(hWndPlate[i][j], NULL, TRUE);
                        }
                        else 
                        {
                            v_highlight[i][j] = false;
                            InvalidateRect(hWndPlate[i][j], NULL, TRUE);
                        }
                    }
                }
                lastClicked_i = -1;
                lastClicked_j = -1;
            }
            else // 选中了可修改格子
            {
                int i = lastClicked_i;
                int j = lastClicked_j;

                // 更新格子内容和状态
                v_dynamic_plate[i][j] = num;
                wchar_t wstr[2] = { L'0' + static_cast<wchar_t>(num), 0 };
                SetWindowText(hWndPlate[i][j], wstr);

                // 检查冲突
                bool hasConflict = false;
                // 检查行
                for (int col = 0; col < line_wnd_priv; col++) {
                    if (col != j && v_dynamic_plate[i][col] == num) {
                        hasConflict = true;
                        break;
                    }
                }
                // 检查列
                if (!hasConflict) {
                    for (int row = 0; row < line_wnd_priv; row++) {
                        if (row != i && v_dynamic_plate[row][j] == num) {
                            hasConflict = true;
                            break;
                        }
                    }
                }
                // 检查区域
                if (!hasConflict) {
                    auto it = map_area_plate.find({ i, j });
                    if (it != map_area_plate.end()) {
                        int area = it->second;
                        for (int row = 0; row < line_wnd_priv; row++) {
                            for (int col = 0; col < line_wnd_priv; col++) {
                                if ((row != i || col != j) &&
                                    map_area_plate[{row, col}] == area &&
                                    v_dynamic_plate[row][col] == num) {
                                    hasConflict = true;
                                    break;
                                }
                            }
                            if (hasConflict) break;
                        }
                    }
                }

                // 设置文本类型属性
                SetProp(hWndPlate[i][j], L"SUDOKU_TEXT", (HANDLE)(INT_PTR)(hasConflict ? 3 : 2));

                // 重置所有高亮
                for (int x = 0; x < line_wnd_priv; x++) {
                    for (int y = 0; y < line_wnd_priv; y++)
                    {
                        v_highlight[x][y] = false;
                        InvalidateRect(hWndPlate[x][y], NULL, TRUE);
                    }
                }

                //设置单格高亮
                v_highlight[i][j] = true;
                InvalidateRect(hWndPlate[i][j], NULL, TRUE);

                lastClicked_i = i;
                lastClicked_j = j;
            }
        }
        // 擦除按钮处理 (ID 4010)
        else if (wmId == 4010) 
        {
            if (lastClicked_i != -1 && lastClicked_j != -1) {
                int textType = (int)(INT_PTR)GetProp(hWndPlate[lastClicked_i][lastClicked_j], L"SUDOKU_TEXT");

                // 只处理玩家填写的格子
                if (textType == 2 || textType == 3) {
                    // 清除格子内容
                    v_dynamic_plate[lastClicked_i][lastClicked_j] = 0;
                    SetWindowText(hWndPlate[lastClicked_i][lastClicked_j], L"");
                    SetProp(hWndPlate[lastClicked_i][lastClicked_j], L"SUDOKU_TEXT", (HANDLE)(INT_PTR)0);

                    // 刷新
                    InvalidateRect(hWndPlate[lastClicked_i][lastClicked_j], NULL, TRUE);
                    lastClicked_i = -1;
                    lastClicked_j = -1;
                }
            }
        }
        // 显示答案按钮处理 (ID 4011)
        else if (wmId == ID_Button_ShowAnswer)
        {
            if (hAnswer == NULL || !IsWindowVisible(hAnswer))
            {
                // 如果答案窗口尚未创建，则创建
                if (hAnswer == NULL)
                {
                    hAnswer = CreateWindowEx(
                        WS_EX_APPWINDOW | WS_EX_WINDOWEDGE, // 标准窗口边框
                        szWindowClass_Answer,
                        L"数独答案",
                        WS_OVERLAPPEDWINDOW | WS_VISIBLE, // 包含标题栏、边框等
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        500, 500, // 初始大小
                        hMain, // 父窗口
                        NULL,
                        hInst,
                        NULL
                    );
                }

                // 设置答案盘面的内容
                if (hAnswer != NULL)
                {
                    for (int i = 0; i < line_wnd_priv; i++)
                    {
                        for (int j = 0; j < line_wnd_priv; j++)
                        {
                            if (hWndAnswerPlate[i][j] != NULL)
                            {
                                wchar_t wstr[2] = { 0 };
                                int num = v_ans_plate[i][j];
                                if (num != 0) {
                                    wstr[0] = L'0' + static_cast<wchar_t>(num);
                                }
                                SetWindowText(hWndAnswerPlate[i][j], wstr);
                            }
                        }
                    }

                    // 更新窗口大小
                    RECT rc;
                    GetClientRect(hAnswer, &rc);
                    SendMessage(hAnswer, WM_SIZE, SIZE_RESTORED, MAKELPARAM(rc.right, rc.bottom));

                    ShowWindow(hAnswer, SW_SHOW);
                    SetWindowText(hShowAnswerButton, L"隐藏答案");
                }
            }
            else
            {
                // 隐藏答案窗口
                ShowWindow(hAnswer, SW_HIDE);
                SetWindowText(hShowAnswerButton, L"显示答案");
            }
        }
        // 退出按钮处理
        else if (wmId == ID_Button_BackToMenu_Play)
        {
            ShowWindow(hPlay, SW_HIDE);
            ShowWindow(hMenu, SW_SHOW);

            // 重置高亮状态
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    v_highlight[i][j] = false;
                }
            }
            lastClicked_i = -1;
            lastClicked_j = -1;
        }
        else
        {

        }
        break;
    }
    case WM_DESTROY:
    {
        // 清理所有静态控件的区域属性
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (hWndPlate[i][j] != NULL) {
                    RemoveProp(hWndPlate[i][j], L"SUDOKU_AREA");
                    RemoveProp(hWndPlate[i][j], L"SUDOKU_ROW");
                    RemoveProp(hWndPlate[i][j], L"SUDOKU_COL");
                    RemoveProp(hWndPlate[i][j], L"SUDOKU_TEXT");
                }
            }
        }

        // 清理字体资源
        if (hCellFont != NULL) {
            DeleteObject(hCellFont);
            hCellFont = NULL;
        }
        if (hButtonFont != NULL) {
            DeleteObject(hButtonFont);
            hButtonFont = NULL;
        }
        if (hShowAnswerFont != NULL) {
            DeleteObject(hShowAnswerFont);
            hShowAnswerFont = NULL;
        }

        // 清理按钮
        for (int i = 0; i < 9; i++) {
            if (hNumButtons[i]) {
                DestroyWindow(hNumButtons[i]);
            }
        }
        if (hEraseButton) {
            DestroyWindow(hEraseButton);
        }

        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//加载界面窗口的窗口过程
LRESULT CALLBACK LoadingWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hTextWnd_hLoading_1 = CreateWindowEx
        (
            0,
            L"STATIC",
            L"加载中，请稍候",
            WS_CHILD | SS_CENTER | WS_BORDER | WS_VISIBLE,
            0,
            0,
            0,
            0,
            hWnd,
            NULL,
            hInst,
            NULL
        );
        //设置字体
        SendMessage(hTextWnd_hLoading_1, WM_SETFONT, (WPARAM)g_hTextFont, TRUE);

        //取消按钮
        hBackToMenu_hLoading = CreateWindowEx(
            0,
            L"BUTTON",
            L"取消",
            WS_CHILD | SS_CENTER | WS_BORDER | WS_VISIBLE,
            0,
            0,
            0,
            0,
            hWnd,
            (HMENU)ID_Button_Cancel_Loading,  // 添加ID
            hInst,
            NULL
        );

        break;
    }
    case WM_SIZE:
    {
        RECT rcClient;
        GetClientRect(hWnd, &rcClient);
        int clientWidth = rcClient.right - rcClient.left;
        int clientHeight = rcClient.bottom - rcClient.top;

        // 加载文本位置 (水平居中，垂直方向1/3处)
        const int TEXT_WIDTH = 300;
        const int TEXT_HEIGHT = 40;
        SetWindowPos(
            hTextWnd_hLoading_1,
            NULL,
            (clientWidth - TEXT_WIDTH) / 2,
            clientHeight / 3,
            TEXT_WIDTH,
            TEXT_HEIGHT,
            SWP_NOZORDER | SWP_NOACTIVATE
        );

        // 取消按钮位置 (水平居中，在文本下方)
        const int BUTTON_WIDTH = 100;
        const int BUTTON_HEIGHT = 30;
        SetWindowPos(
            hBackToMenu_hLoading,
            NULL,
            (clientWidth - BUTTON_WIDTH) / 2,
            clientHeight / 3 + TEXT_HEIGHT + 20, // 文本下方20像素
            BUTTON_WIDTH,
            BUTTON_HEIGHT,
            SWP_NOZORDER | SWP_NOACTIVATE
        );
        break;

        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 纯色背景
        FillRect(hdc, &ps.rcPaint, hBrush_Background);



        EndPaint(hWnd, &ps);
        break;
    }
    case WM_ERASEBKGND:
        return 1;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case ID_Button_Cancel_Loading:
            // 取消按钮被点击
            ShowWindow(hLoading, SW_HIDE);
            ShowWindow(hMenu, SW_SHOW);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }


        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


//答案展示窗口的窗口过程
LRESULT CALLBACK AnswerWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HFONT hCellFont = NULL;      // 盘面按钮字体
    static int lastSquareSize = 0;       // 记录上次格子大小

    switch (message)
    {
    case WM_CREATE:
    {
        // 创建盘面展示窗口组
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                hWndAnswerPlate[i][j] = CreateWindowEx(
                    0,
                    L"STATIC",
                    L"0",
                    WS_CHILD | SS_CENTER | WS_BORDER,
                    0, 0, 0, 0,
                    hWnd,
                    NULL,
                    hInst,
                    NULL);

                // 设置区域属性
                auto it = map_area_plate.find({ i, j });
                if (it != map_area_plate.end()) {
                    SetProp(hWndAnswerPlate[i][j], L"SUDOKU_AREA", (HANDLE)(INT_PTR)it->second);
                }

                // 设置行/列属性
                SetProp(hWndAnswerPlate[i][j], L"SUDOKU_ROW", (HANDLE)(INT_PTR)i);
                SetProp(hWndAnswerPlate[i][j], L"SUDOKU_COL", (HANDLE)(INT_PTR)j);
            }
        }
        break;
    }
    case WM_SIZE:
    {
        RECT rcClient;
        GetClientRect(hWnd, &rcClient);
        int clientWidth = rcClient.right - rcClient.left;
        int clientHeight = rcClient.bottom - rcClient.top;

        if (clientWidth <= 0 || clientHeight <= 0 || line_wnd_priv <= 0) {
            break; // 避免无效计算
        }

        // === 盘面区域 ===
        const int totalSize = min(clientHeight - 40, clientWidth - 40);
        const int squareSize = totalSize / line_wnd_priv;
        const int startY = 20;
        const int startX = (clientWidth - totalSize) / 2;

        // === 动态调整字体大小 ===
        if (squareSize != lastSquareSize)
        {
            // 删除旧字体
            if (hCellFont != NULL)
            {
                DeleteObject(hCellFont);
                hCellFont = NULL;
            }

            // 创建新字体（大小为格子的70%）
            int fontSize = (squareSize * 70) / 100;
            hCellFont = CreateFont(
                fontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
            lastSquareSize = squareSize;
        }

        // 调整静态控件位置
        for (int i = 0; i < line_wnd_priv; i++)
        {
            for (int j = 0; j < line_wnd_priv; j++)
            {
                if (hWndAnswerPlate[i][j] != NULL)
                {
                    SetWindowPos(
                        hWndAnswerPlate[i][j],
                        NULL,
                        startX + j * squareSize,
                        startY + i * squareSize,
                        squareSize,
                        squareSize,
                        SWP_NOZORDER | SWP_NOACTIVATE
                    );

                    if (hCellFont != NULL) {
                        SendMessage(hWndAnswerPlate[i][j], WM_SETFONT, (WPARAM)hCellFont, TRUE);
                    }

                    ShowWindow(hWndAnswerPlate[i][j], SW_SHOW);
                }
            }
        }
        break;
    }
    case WM_CTLCOLORSTATIC:
    {
        HDC hdcStatic = (HDC)wParam;
        HWND hWndCtrl = (HWND)lParam;

        // 获取区域属性
        INT_PTR area = (INT_PTR)GetProp(hWndCtrl, L"SUDOKU_AREA");

        // 获取行列属性
        int row = (int)(INT_PTR)GetProp(hWndCtrl, L"SUDOKU_ROW");
        int col = (int)(INT_PTR)GetProp(hWndCtrl, L"SUDOKU_COL");

        // 根据原始盘面决定文字颜色
        COLORREF textColor;
        if (row < v_ori_plate.size() && col < v_ori_plate[0].size()) {
            // 原始盘面有数字：紫色
            if (v_ori_plate[row][col] != 0) {
                textColor = RGB(128, 0, 128);
            }
            // 原始盘面无数字：绿色
            else {
                textColor = RGB(50,205,50);
            }
        }
        else {
            // 默认紫色
            textColor = RGB(128, 0, 128);
        }

        // 设置文字颜色
        SetTextColor(hdcStatic, textColor);

        // 使用区域颜色背景
        if (area >= 1 && area <= 9 && hBrushes_Plate.find(area) != hBrushes_Plate.end())
        {
            SetBkMode(hdcStatic, TRANSPARENT);     // 设置背景透明
            return (LRESULT)hBrushes_Plate[area];  // 返回区域对应的画刷
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        // 纯色背景
        FillRect(hdc, &ps.rcPaint, hBrush_Background);

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hWnd); // 处理关闭消息
        break;
    case WM_DESTROY:
    {
        // 清理所有静态控件的区域属性
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (hWndAnswerPlate[i][j] != NULL) {
                    RemoveProp(hWndAnswerPlate[i][j], L"SUDOKU_AREA");
                    RemoveProp(hWndAnswerPlate[i][j], L"SUDOKU_ROW");
                    RemoveProp(hWndAnswerPlate[i][j], L"SUDOKU_COL");
                }
            }
        }

        // 清理字体资源
        if (hCellFont != NULL) {
            DeleteObject(hCellFont);
            hCellFont = NULL;
        }

        // 重置字体大小记录 
        lastSquareSize = 0;  // 确保下次创建窗口时重新计算字体

        // 重置全局hAnswer并更新按钮文本
        if (hAnswer == hWnd) {
            hAnswer = NULL;
            // 更新游玩窗口的按钮文本
            if (hPlay && IsWindow(hPlay)) {
                HWND hButton = GetDlgItem(hPlay, ID_Button_ShowAnswer);
                if (hButton) {
                    SetWindowText(hButton, L"显示答案");
                }
            }
        }
        break;
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}