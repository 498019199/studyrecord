#include <core/WinApp.h>
#include <core/D3D11RenderEngine.h>
#include <core/D3D11RenderMesh.h>
#include <core/Timer.h>
#include <core/Context.h>
#include <core/D3D11Util.h>
#include <core/SceneManager.h>

WinAPP::WinAPP()
{
}

WinAPP::~WinAPP()
{
}

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
		wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(BLACK_BRUSH));
		wc.lpszMenuName  = nullptr;
		wc.hIconSm = nullptr;
		wc.lpszClassName = wname.c_str();
		if( !::RegisterClassExW(&wc) )
		{
			// 获取错误码
			DWORD errorCode = GetLastError();
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
	}

	RECT rc;
	::GetClientRect(hwnd_, &rc);
	left_ = rc.left;
	top_ = rc.top;
	width_ = rc.right - rc.left;
	height_ = rc.bottom - rc.top;

	::SetWindowLongPtrW(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

	::ShowWindow(hwnd_, SW_SHOW);
	::UpdateWindow(hwnd_);

	return true;
}

bool WinAPP::InitDevice(HWND hwnd, const RenderSettings& settings)
{
    device_ = new D3D11RenderEngine(hwnd, settings);
	if(device_)
	{
		Context::Instance().RenderEngineInstance(*device_);
		return true;    
	}

	return false;
}

// 更新状态
void WinAPP::CalculateFrameStats()
{
	++ total_num_frames_;

	// measure statistics
	frame_time_ = static_cast<float>(timer_.elapsed());
	++ num_frames_;
	accumulate_time_ += frame_time_;
	app_time_ += frame_time_;

	// check if new second
	if (accumulate_time_ > 1)
	{
		// new second - not 100% precise
		fps_ = num_frames_ / accumulate_time_;

		accumulate_time_ = 0;
		num_frames_  = 0;
	}

	timer_.restart();
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

			if( !is_paused )
			{
				CalculateFrameStats();
				Context::Instance().SceneMgr().UpdateScene(frame_time_);	
				device_->OnRender();
			}
			else
			{
				Sleep(100);
			}
        }
    }

	return (int)msg.wParam;
}
