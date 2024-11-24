#include <common/WinApp.h>

#include <string>

LRESULT WinAPP::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
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

    std::wstring  wname = L"D3DWndClassName";
    WNDCLASSEXW wc;
    wc.cbSize = sizeof(wc);
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = WndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = sizeof(this);
	wc.hInstance     = hInst;
	wc.hIcon         = nullptr;
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = wname.c_str();

	if( !::RegisterClassExW(&wc) )
	{
		::MessageBoxW(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

    if (settings.full_screen)
    {
        win_style_ = WS_POPUP;
    }
    else
    {
        win_style_ = WS_OVERLAPPEDWINDOW;
    }

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT rc = { 0, 0, static_cast<LONG>(settings.width * dpi_scale_ + 0.5f), static_cast<LONG>(settings.height * dpi_scale_ + 0.5f) };
	::AdjustWindowRect(&rc, win_style_, false);

	hwnd_ = ::CreateWindowW(wname.c_str(), wname.c_str(),  win_style_, settings.left, settings.top,
		rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInst, nullptr);
	if( !hwnd_ )
	{
		::MessageBoxW(0, L"CreateWindow Failed.", 0, 0);
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

