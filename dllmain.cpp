#include "include.h"

void* d3d9Device[119];
BYTE EndSceneBytes[7]{ 0 };
tEndScene oEndScene = nullptr;
LPDIRECT3DDEVICE9 pDevice = nullptr;
WNDPROC oWndProc;

Engine E;

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX9_Init(pDevice);
}

bool init = false;
bool ShowMenu = true;
HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 o_pDevice)
{   


    if (GetAsyncKeyState(MENU_KB) & 1)
    {
        ShowMenu = !ShowMenu;
    }
    if (!pDevice)
        pDevice = o_pDevice;
    
    if (!init)
    {

        DXDEVICE = pDevice;
        InitImGui(pDevice);
        init = true;
    }

    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Insert)))
        ShowMenu = !ShowMenu;

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    
    ImGui::Begin("CSGO Cheese", &ShowMenu);
    ImGui::Checkbox("AutoJump", &Settings.EnableBhop);
    ImGui::Checkbox("Triggerbot", &Settings.EnableTriggerbot);
    ImGui::Separator();
    ImGui::Checkbox("No Recoil", &Settings.EnableRecoilControl);
    if (Settings.EnableRecoilControl)
    {
        ImGui::SliderFloat("Amount", &Settings.EnableRecoilControlAmount, 0.0f, 1.0f);
    }

    ImGui::Checkbox("Recoil Crosshair", &Settings.EnableRecoilCrosshair);
    if (Settings.EnableRecoilCrosshair)
    {
        ImGui::SliderInt("Thickness", &Settings.RecoilCrosshairThickness, 1, 10);
        ImGui::Checkbox("Draw Circle", &Settings.RecolCrosshairCircle);
        ImGui::Checkbox("Draw Tracer", &Settings.RecoilCrosshairLine);
        if (!Settings.RecoilCrosshairLine)
        {
            ImGui::SliderInt("Length", &Settings.RecoilCrosshairLength, 1, 50);
        }
        ImGui::ColorEdit4("Crosshair Color", (float*)&Settings.RecoulCrosshairColor);
    }
    ImGui::Separator();
    ImGui::Checkbox("Antialiasing", &Settings.Global_Antialias);

    ImGui::End();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());


    windowWidth = GetSystemMetrics(SM_CXSCREEN);
    windowHeight = GetSystemMetrics(SM_CYSCREEN);
    if (Settings.EnableRecoilCrosshair)
    {
        int len = Settings.RecoilCrosshairLength;
        int thickness = Settings.RecoilCrosshairThickness;
        if (Settings.RecolCrosshairCircle)
        {
            DrawCircle(
                RecoilCrosshairX,
                RecoilCrosshairY,
                (int)(len * 2),
                8,
                thickness,
                Settings.Global_Antialias,
                ImColor_D3D(Settings.RecoulCrosshairColor)
            );
        }
        if (Settings.RecoilCrosshairLine)
        {
            DrawLine(
                RecoilCrosshairX,
                RecoilCrosshairY,
                windowWidth / 2,
                windowHeight / 2,
                thickness,
                Settings.Global_Antialias,
                ImColor_D3D(Settings.RecoulCrosshairColor)
            );
        }
        else
        {
            DrawLine(
                RecoilCrosshairX - len,
                RecoilCrosshairY,
                RecoilCrosshairX + len,
                RecoilCrosshairY,
                thickness,
                Settings.Global_Antialias,
                ImColor_D3D(Settings.RecoulCrosshairColor)
            );
            DrawLine(
                RecoilCrosshairX,
                RecoilCrosshairY - len,
                RecoilCrosshairX,
                RecoilCrosshairY + len,
                thickness,
                Settings.Global_Antialias,
                ImColor_D3D(Settings.RecoulCrosshairColor)
            );
        }

    }

    return oEndScene(pDevice);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;
    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
    DWORD wndProcId;
    GetWindowThreadProcessId(handle, &wndProcId);

    if (GetCurrentProcessId() != wndProcId)
        return TRUE;
    window = handle;
    return FALSE;
}
HWND GetProcess()
{
    window = NULL;
    EnumWindows(EnumWindowsCallback, NULL);
    return window;
}

DWORD WINAPI MainThread(HMODULE hMod)
{
    // Hook
    if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
    {
        memcpy(EndSceneBytes, (char*)d3d9Device[42], 7);
        oEndScene = (tEndScene)TrampHook((char*)d3d9Device[42], (char*)hkEndScene, 7);
    }
    window = GetProcess();
    oWndProc = (WNDPROC)SetWindowLongPtr(window, -4, (LONG_PTR)WndProc);

    // Loop
    while (!GetAsyncKeyState(UNINJECT_KB))
    {
        Sleep(500); // Always sleep when you're in a "while" loop because you get 20% of cpu usage if you dont
    }

    // Unhook
    Patch((BYTE*)d3d9Device[42], EndSceneBytes, 7);
    FreeLibraryAndExitThread(hMod, 0);
}

BOOL __stdcall StartThread(HMODULE hModule, LPTHREAD_START_ROUTINE StartAddress)
{
    return CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, hModule, 0, 0));
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        E.Init();
        StartThread(hModule, (LPTHREAD_START_ROUTINE)MainThread);
        StartThread(hModule, (LPTHREAD_START_ROUTINE)BhopThread);
        StartThread(hModule, (LPTHREAD_START_ROUTINE)TriggerbotThread);
        StartThread(hModule, (LPTHREAD_START_ROUTINE)RecoilThread);
    default:
        break;
    }
    return TRUE;
}
