#include <memory>
// ##########################################################
//                             Platform Globals
// ##########################################################
static bool running = true;

// ##########################################################
//                             Platform Functions
// ##########################################################
bool platform_create_window(int width, int height,char* title);
void platform_update_window();
// ##########################################################
//                             Windows Platform
// ##########################################################
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>

// ##########################################################
//                             Windows Globals
// ##########################################################

static HWND window;
// ##########################################################
//                             Platform Implementations
// ##########################################################

LRESULT CALLBACK windows_window_callback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {
    LRESULT result=0;
    switch (msg) {
        case WM_CLOSE: {
            running=false;
            break;
        }
        default:
        {
            result=DefWindowProcA(window, msg, wParam, lParam);
        }
    }
    return result;
}
bool platform_create_window(int width, int height,char* title)
{
    HINSTANCE instance=GetModuleHandleA(0);
    WNDCLASSA wc={};
    wc.hInstance=instance;
    wc.hIcon=LoadIconA(0,IDI_APPLICATION);
    wc.hCursor=LoadCursorA(0,IDC_ARROW);//this means we decide the look of the cursor
    wc.lpszClassName=title;//this is not a title, is just an unique identifier
    wc.lpfnWndProc=windows_window_callback;//Callback for input into the window
    if (!RegisterClassA(&wc)) {
        return false;
    }
    window=CreateWindowExA(0,title,title,WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100,width,height,NULL,NULL,instance,NULL);
    if (!window) {
        return false;
    }
    ShowWindow(window,SW_SHOW);
    return true;
}
void platform_update_window() {
    MSG msg;
    while (PeekMessageA(&msg,window,0,0,PM_REMOVE)) {
            TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}
#endif
int main() {
    platform_create_window(1200,720,"Local Chess");
    while (running) {
        //Update
        platform_update_window();
    }
    return 0;
}