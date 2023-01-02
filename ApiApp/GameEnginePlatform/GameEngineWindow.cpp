#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>

// LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM)

HWND GameEngineWindow::hWnd = nullptr;

LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
        // 내 윈도우가 선택되었다.
    case WM_SETFOCUS:
    {
        int a = 0;
        break;
    }
    case WM_ACTIVATE:
    {
        int a = 0;
        break;
    }
    case WM_KILLFOCUS:
    {
        int a = 0;
        break;
    }
    case WM_DESTROY:
    {
        // Message함수가 0을 리턴하게 만들어라.
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return 0;
}

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
}


void GameEngineWindow::WindowCreate(HINSTANCE _hInstance, const std::string_view& _TitleName)
{
    // 윈도우를 찍어낼수 있는 class를 만들어내는 것이다.
    // 나는 이러이러한 윈도우를 만들어줘...
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    // 넣어주지 않으면 윈도우 기본Icon이 됩니다.
    wcex.hIcon = nullptr;//LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 흰색 
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "GameEngineWindowDefault";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // 윈도우에게 이런 내용을 window클래스를 GameEngineWindowDefault라는 이름으로 등록해줘.
    // 나중에 윈도우 만들때 쓸꺼냐.
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("윈도우 클래스 등록에 실패했습니다.");
        return;
    }

    // hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    // 1000번 프로그램이 윈도우를 띄워달라고 요청했다.
    // 윈도우는 다시 특정 숫자이라는 윈도우가 만들어졌다고 우리에게 알려주는데.
    // 특정 숫자로 인식되는 우리의 윈도우에게 크기변경 떠라

    hWnd = CreateWindow("GameEngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (!hWnd)
    {
        MsgAssert("윈도우 클래스 생성에 실패했습니다.");
        return;
    }

    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);

    return;
}

int GameEngineWindow::WindowLoop()
{
    // 단축키인데. 안써도 문제가 되지는 않는다.
    // HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 동기 함수가 종료될때까지 프로그램이 멈춘다.

    // 기본 메시지 루프입니다:
    // GetMessage는 내 윈도우에 무슨일이 생기는지 체크해줘.
    // GetMessage는 윈도우의 특별한 일이 생길대까지 멈추는 함수인겁니다.
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        //if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
        //{
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        //}
    }

    return (int)msg.wParam;
}

void GameEngineWindow::WindowSize(float4 _Size)
{

}
void GameEngineWindow::WindowPos(float4 _Pos)
{

}