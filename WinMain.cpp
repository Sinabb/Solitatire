#include <Windows.h>
#include <gdiplus.h>
#include <list>
#include "Card.h"

#pragma comment (lib, "Gdiplus.lib")

using namespace Gdiplus;

const wchar_t gClassName[] = L"SolitaireMyWindowClass";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

// Test
std::list<solitaire::Card> myDeck;

int WINAPI WinMain(_In_ HINSTANCE hinstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nshowcmd)
{
    GdiplusStartupInput gsi;
    ULONG_PTR token;
    GdiplusStartup(&token, &gsi, nullptr);

    // Test
    myDeck.push_back(solitaire::Card(solitaire::Type::Bear, 0, 0));
    myDeck.push_back(solitaire::Card(solitaire::Type::Dragon, 150, 0));
    myDeck.push_back(solitaire::Card(solitaire::Type::Wolf, 300, 0));

    WNDCLASSEX wc{};
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = gClassName;
    wc.hInstance = hinstance;
    wc.lpfnWndProc = WindowProc;
    wc.cbSize = sizeof(WNDCLASSEX);

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(nullptr, L"Failed to register", L"Error", MB_OK);
        return 0;
    }

    RECT wr = { 0,0,1024,768 };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    HWND hwnd = CreateWindowEx
    (
        0,
        gClassName,
        L"Solitatire Game",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        wr.right - wr.left,
        wr.bottom - wr.top,
        NULL,
        NULL,
        hinstance,
        NULL
    );

    if (hwnd == nullptr)
    {
        MessageBox(nullptr, L"Failed to create", L"Error", MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nshowcmd);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    myDeck.clear();

    GdiplusShutdown(token);
    return static_cast<int>(msg.wParam);

}

void OnPAint(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    Graphics graphics(hdc);

    // Test
    for (auto& card : myDeck)
    {
        card.Flip(true);

        card.Draw(graphics);
    }


    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
    {
        OnPAint(hwnd);
        break;
    }
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
        break;
    }
    return 0;
}

