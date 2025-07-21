#include <stdio.h>
#include <windows.h>

typedef HWND Window;
typedef LPARAM Register;
typedef MSG Event;

#define GetXWindow(data) ((short)(data))
#define GetYWindow(data) ((int)((data) >> 16))

int isPressed(int key){
    return GetAsyncKeyState(key) & 0x8000;
}

int wasPressed(int key){
    return GetAsyncKeyState(key) & 0x0001;
}

Register CALLBACK procedure(Window window, unsigned code, size_t mem, Register data) {
    switch (code) {
        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            return 0;
        case WM_LBUTTONUP:
            return 0;
        case WM_LBUTTONDOWN:
            printf("Click on (%i, %i)\n", GetXWindow(data), GetYWindow(data));
            return 0;
        case WM_RBUTTONUP:
            return 0;
        case WM_RBUTTONDOWN:
            return 0;
        case WM_MOUSEMOVE:
            return 0;
        case WM_KILLFOCUS:
            puts("Out of focus");
        case WM_SETCURSOR:
            if (LOWORD(data) == HTCLIENT) {
                SetCursor(LoadCursor(0, IDC_ARROW));
                return 0;
            }
            return 0;
        case WM_PAINT:{
            PAINTSTRUCT painter;
            HDC hdc = BeginPaint(window, &painter);
            HPEN hPen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
            HBRUSH hBrush = CreateSolidBrush(RGB(200, 200, 255));
            SelectObject(hdc, hPen);
            SelectObject(hdc, hBrush);
            Rectangle(hdc, 0, 0, 100, 100);
            DeleteObject(hPen);
            DeleteObject(hBrush);

            TextOut(hdc, 10, 10, "Hello, Windows!", 15);
            EndPaint(window, &painter);
            return 0;
        }
        default:
            return DefWindowProc(window, code, mem, data);
    }
}

#define windowStyle WS_TILEDWINDOW

int main(){

    const char objName[]  = "Window Holder";
    HINSTANCE instance = GetModuleHandle(NULL);

    WNDCLASS windowFrame = {};
    windowFrame.lpfnWndProc = procedure;
    windowFrame.hInstance = instance;
    windowFrame.lpszClassName = objName;

    HCURSOR cursor = LoadCursor(instance, IDC_HAND);

    RegisterClass(&windowFrame);

    HWND window = CreateWindowEx(
        0,
        objName,
        "AI manager",
        windowStyle,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        0,
        0,
        instance,
        0
    );

    ShowWindow(window, SW_SHOWNORMAL);

    MSG event;
    while (GetMessage(&event, NULL, 0, 0)) {

        if (wasPressed(VK_ESCAPE)) {
            DestroyWindow(window);
        }

        TranslateMessage(&event);
        DispatchMessage(&event);
        UpdateWindow(window);

        Sleep(10);
    }

    DestroyWindow(window);
    UnregisterClass(objName, instance);

    puts("Program exit");
}
