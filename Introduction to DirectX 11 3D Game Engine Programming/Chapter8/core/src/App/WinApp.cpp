#include <core/WinApp.h>
#include <core/Timer.h>
#include <core/Context.h>
#include <core/World.h>

#include "../D3D11/D3D11RenderEngine.h"
#include "../D3D11/D3D11Util.h"

#define CHPATER_USE_IMGUISE 1
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

namespace RenderWorker
{

bool InitImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // 允许键盘控制
    io.ConfigWindowsMoveFromTitleBarOnly = true;              // 仅允许标题拖动

    // 设置Dear ImGui风格
    ImGui::StyleColorsDark();

    // 设置平台/渲染器后端
    ImGui_ImplWin32_Init(Context::Instance().AppInstance().GetHWND());
	const auto& d3d11_re = checked_cast<const D3D11RenderEngine&>(Context::Instance().RenderEngineInstance());
    auto re = d3d11_re.D3DDevice();
    auto ctx = d3d11_re.D3DDeviceImmContext();
    ImGui_ImplDX11_Init(re, ctx);
    return true;
}

WinAPP::WinAPP()
{
}

WinAPP::~WinAPP()
{
}

LRESULT WinAPP::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;
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
    auto re = new D3D11RenderEngine(hwnd, settings);
	if(re)
	{
		Context::Instance().RenderEngineInstance(*re);
		return true;    
	}

	InitImGui();
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

				// 这里添加
                ImGui_ImplDX11_NewFrame();     
                ImGui_ImplWin32_NewFrame();
                ImGui::NewFrame();
                // --------
				
				ImguiUpdate(frame_time_);

			    // 可以在这之前调用ImGui的UI部分
				// Direct3D 绘制部分
				Context::Instance().WorldInstance().UpdateScene(frame_time_);	

				// 下面这句话会触发ImGui在Direct3D的绘制
    			// 因此需要在此之前将后备缓冲区绑定到渲染管线上
    			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

				const auto& d3d11_re = checked_cast<const D3D11RenderEngine&>(Context::Instance().RenderEngineInstance());
				d3d11_re.SwitchChain();
			}
			else
			{
				Sleep(100);
			}
        }
    }

	return (int)msg.wParam;
}


void WinAPP::ImguiUpdate(float dt)
{
	static bool animateCube = true, customColor = false;
    static float phi = 0.0f, theta = 0.0f;
    phi += 0.3f * dt, theta += 0.37f * dt;

	auto& wd = Context::Instance().WorldInstance();
    wd.vs_cb_.world = MathWorker::Transpose(MathWorker::MatrixRotateX(phi) * MathWorker::MatrixRotateY(theta));
	wd.vs_cb_.worldInvTranspose = MathWorker::Transpose(MathWorker::MatrixInverse(wd.vs_cb_.world));

	// ImGui::ShowAboutWindow();
	// ImGui::ShowDemoWindow();
	// ImGui::ShowUserGuide();
	// 获取IO事件
    ImGuiIO& io = ImGui::GetIO();

	if (ImGui::Begin("Lighting"))
	{
    	ImGui::SameLine(0.0f, 25.0f);                       // 下一个控件在同一行往右25像素单位

		ImGui::Checkbox("WireFrame Mode", &wd.is_wireframe_mode_);
		// 不允许在操作UI时操作物体
    	if (!ImGui::IsAnyItemActive())
		{
			 // 鼠标左键拖动平移
        	if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
			{

			}
			// 鼠标右键拖动旋转
        	else if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
			{

			}
			// 鼠标滚轮缩放
        	else if (io.MouseWheel != 0.0f)
			{

			}
			// 是否刚按下W键
			else if(ImGui::IsKeyPressed(ImGuiKey_W))
			{

			}
		}
	}

    ImGui::End();
    ImGui::Render();
}

}