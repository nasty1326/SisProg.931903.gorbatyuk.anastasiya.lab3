
#include "framework.h"
#include "Main.h"
#include <math.h>

#define MAX_LOADSTRING 100

HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];           

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SYSTEMLAB3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SYSTEMLAB3));

    MSG msg;

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

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SYSTEMLAB3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SYSTEMLAB3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


enum class Function
{
    Sin,
    Cos,
    Tan,
    Ctg
};

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    const int POINTS_AMOUNT = 1000;
    const double TWOPI = 2 * 3.14159;

    static int cxClient, cyClient;
    static POINT points[POINTS_AMOUNT];
	static Function currentFunction = Function::Sin;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_FUNCTIONS_SIN:
                InvalidateRect(hWnd, NULL, true);
                currentFunction = Function::Sin;
                UpdateWindow(hWnd);
                break;
            case ID_FUNCTIONS_COS:
                InvalidateRect(hWnd, NULL, true);
                currentFunction = Function::Cos;
                UpdateWindow(hWnd);
                break;
            case ID_FUNCTIONS_TAN:
                InvalidateRect(hWnd, NULL, true);
                currentFunction = Function::Tan;
                UpdateWindow(hWnd);
                break;
            case ID_FUNCTIONS_CTG:
                InvalidateRect(hWnd, NULL, true);
                currentFunction = Function::Ctg;
                UpdateWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
			PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            switch (currentFunction)
            {
            case Function::Sin:
                MoveToEx(hdc, 0, cyClient / 2, NULL);
                LineTo(hdc, cxClient, cyClient / 2);

                for (int i = 0; i < POINTS_AMOUNT; i++)
                {
                    points[i].x = i * cxClient / POINTS_AMOUNT;
                    points[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI * i / POINTS_AMOUNT)));
                }
                Polyline(hdc, points, POINTS_AMOUNT);
                break;
            case Function::Cos:
                MoveToEx(hdc, 0, cyClient / 2, NULL);
                LineTo(hdc, cxClient, cyClient / 2);

                for (int i = 0; i < POINTS_AMOUNT; i++)
                {
                    points[i].x = i * cxClient / POINTS_AMOUNT;
                    points[i].y = (int)(cyClient / 2 * (1 - cos(TWOPI * i / POINTS_AMOUNT)));
                }

                Polyline(hdc, points, POINTS_AMOUNT);
                break;
            case Function::Tan:
                MoveToEx(hdc, 0, cyClient / 2, NULL);
                LineTo(hdc, cxClient, cyClient / 2);

                for (int i = 0; i < POINTS_AMOUNT; i++)
                {
                    points[i].x = i * cxClient / POINTS_AMOUNT;
                    points[i].y = (int)(cyClient / 2 * (1 - tan(TWOPI * i / POINTS_AMOUNT)));
                }

                Polyline(hdc, points, POINTS_AMOUNT);
                break;
            case Function::Ctg:
                MoveToEx(hdc, 0, cyClient / 2, NULL);
                LineTo(hdc, cxClient, cyClient / 2);

                for (int i = 0; i < POINTS_AMOUNT; i++)
                {
                    points[i].x = i * cxClient / POINTS_AMOUNT;
                    points[i].y = (int)(cyClient / 2 * (1 - 1 / tan(TWOPI * i / POINTS_AMOUNT)));
                }

                Polyline(hdc, points, POINTS_AMOUNT);
                break;
            }
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_SIZE:
		{
			cxClient = LOWORD(lParam);
			cyClient = HIWORD(lParam);
            return 0;
		}
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
