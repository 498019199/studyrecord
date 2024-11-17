#include <WinApp.h>
#include <Windows.h>

LRESULT CALLBACK WinAPP::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
    //if()
    //else
	{
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

bool WinAPP::CreateAppWindow(const RenderSettings& settings)
{
    HINSTANCE hInst = ::GetModuleHandle(nullptr);

    WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInst;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = L"D3DWndClassName";

	if( !RegisterClass(&wc) )
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, settings.width, settings.height };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width  = R.right - R.left;
	int height = R.bottom - R.top;

	hwnd_ = CreateWindowW(L"D3DWndClassName", mMainWndCaption.c_str(), 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mhAppInst, 0); 
	if( !hwnd_ )
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(hwnd_, SW_SHOW);
	UpdateWindow(hwnd_);

	return true;
}

int WinAPP::Run()
{
    MSG msg = {0};

    while(msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if(PeekMessage( &msg, 0, 0, 0, PM_REMOVE ))
		{
            TranslateMessage( &msg );
            DispatchMessage( &msg );
		}
		// Otherwise, do animation/game stuff.
		else
        {	
			//mTimer.Tick();

			//if( !mAppPaused )
			{
				//CalculateFrameStats();
				//UpdateScene(mTimer.DeltaTime());	
				//DrawScene();
			}
			//else
			{
				Sleep(100);
			}
        }
    }

	return (int)msg.wParam;
}

