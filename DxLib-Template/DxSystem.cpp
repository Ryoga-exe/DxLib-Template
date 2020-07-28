#include <stdio.h>
#include "DxSystem.h"

// static bool useVF, isF;

void ErrMsgBx(const TCHAR* errorMsg) {
    MessageBox( NULL, errorMsg, L"ERROR", MB_OK | MB_ICONERROR );
}
/*
int ActiveStateChangeCallbackFunction(int ActiveState, void* UserData)
{
    if (!useVF && !isF) {
        return 0;
    }
    else {
        if (ActiveState) {
            SetWindowZOrder(DX_WIN_ZTYPE_TOPMOST, TRUE);
        }
        else {
            SetWindowZOrder(DX_WIN_ZTYPE_NORMAL, FALSE);
        }

    }
    return 0;
}
*/

DxSystem::DxSystem() : m_hasInitialized(false), m_window(defaultWindowCon),
m_hasGotWindowPosition(false) {
    DxLib::SetOutApplicationLogValidFlag(FALSE);         // 一番先に行う
    DxLib::SetUseCharCodeFormat(DX_CHARCODEFORMAT_UTF8); // 上の次に行う
    // DxLib::SetActiveStateChangeCallBackFunction(ActiveStateChangeCallbackFunction, NULL);
    /* デフォ用 */
    DxLib::GetDefaultState(&m_desktopSize.width, &m_desktopSize.height, &m_window.colorDepth);
    DxLib::ChangeWindowMode(!m_window.isFullscreen);
    SetEnableSizeChange(m_window.enableSizeChange.enable, m_window.enableSizeChange.toFit);
    DxLib::SetWindowStyleMode(m_window.styleMode);
    //useVF = false; isF = false;
}
DxSystem::~DxSystem() {
    Finalize();
}
bool DxSystem::Finalize() {
    if (!m_hasInitialized) return true;
    DxLib::DxLib_End();
    m_hasInitialized = false;
    return false;
}

bool DxSystem::Initialize(const TCHAR* windowTitle) {
    if (m_hasInitialized) return true;
    DxLib::SetMainWindowText(windowTitle);

    
    SetWindowSize({ 1280, 720 });

    SetEnableSizeChange(true, false);

    SetUseVirtualFullScreenFlag(true);
    // ToggleFullscreenMode();

    if (DxInit()) return true;

    m_hasInitialized = true;
    return false;
}

bool DxSystem::DxInit() {
    if (DxLib::DxLib_Init() != 0) {
        ErrMsgBx(L"エラーが発生しました。\nウィンドウの生成に失敗しました。"); // language
        return true;
    }
    if (DxLib::SetDrawScreen(DX_SCREEN_BACK) != 0) {
        ErrMsgBx(L"エラーが発生しました。\nウィンドウの設定に失敗しました。");
        DxLib::DxLib_End();
        return true;
    }
    if (!m_hasGotWindowPosition) {
        DxLib::GetWindowPosition(&m_windowPosX, &m_windowPosY);
        m_hasGotWindowPosition = true;
    }

    return false;
}

int DxSystem::SetWindowSize(RectSize_t size) {
    m_window.size = size;
    if (!m_window.enableSizeChange.toFit || m_window.useVirtualFullscreen) {
        return DxLib::SetWindowSize(size.width, size.height);
    }
    return DxLib::SetGraphMode(size.width, size.height, m_window.colorDepth);
}

int DxSystem::SetEnableSizeChange(bool enable, bool toFit) {
    if (m_window.useVirtualFullscreen) return -1;
    if (m_window.enableSizeChange.toFit) { // true -> false
        if (!toFit) {
            DxLib::SetGraphMode(m_desktopSize.width, m_desktopSize.height, m_window.colorDepth);
            DxLib::SetWindowSize(m_window.size.width, m_window.size.height);
        }
    }
    else {  // false -> true
        if (toFit) {
            if (!m_window.useVirtualFullscreen) DxLib::SetGraphMode(m_window.size.width, m_window.size.width, m_window.colorDepth);
            DxLib::SetWindowSize(m_window.size.width, m_window.size.width);
        }
    }
    m_window.enableSizeChange = { enable, toFit };
    return DxLib::SetWindowSizeChangeEnableFlag(enable, toFit);
}

bool DxSystem::SetUseVirtualFullScreenFlag(bool useVirtualFullScreen) {
    // same (true -> true, false -> false)
    if (m_window.useVirtualFullscreen == useVirtualFullScreen) return false;
    // false -> true
    else if (!m_window.useVirtualFullscreen && useVirtualFullScreen) {
        m_window.useVirtualFullscreen = useVirtualFullScreen;
        if (m_window.isFullscreen) DxLib::ChangeWindowMode(TRUE);

        DxLib::SetGraphMode(m_desktopSize.width, m_desktopSize.height, m_window.colorDepth);

        m_window.enableSizeChange.toFit = false;

        DxLib::SetWindowSizeChangeEnableFlag(m_window.enableSizeChange.enable, FALSE);

        DxLib::SetWindowSize(m_window.size.width, m_window.size.height);

        SetFullscreenMode(m_window.isFullscreen);
    }
    // true -> false
    else {
        m_window.useVirtualFullscreen = useVirtualFullScreen;
        DxLib::SetGraphMode(m_window.size.width, m_window.size.width, m_window.colorDepth);
        DxLib::SetWindowSize(m_window.size.width, m_window.size.width);
        SetFullscreenMode(m_window.isFullscreen);
    }
    return false;
}

int DxSystem::SetWindowPosition(int posX, int posY) {
    if (m_window.isFullscreen) return -1;
    m_hasGotWindowPosition = true;
    m_windowPosX = posX; m_windowPosY = posY;
    return DxLib::SetWindowPosition(posX, posY);
}

int DxSystem::SetFullscreenMode(bool isFullscreen) {
    if (m_window.isFullscreen == isFullscreen) return 0;
    if (!m_hasGotWindowPosition) {
        m_windowPosX = (int)((m_desktopSize.width - m_window.size.width) / 2);
        m_windowPosY = (int)((m_desktopSize.height - m_window.size.height) / 2);
        m_hasGotWindowPosition = true;
    }
    m_window.isFullscreen = isFullscreen;
    if (m_window.useVirtualFullscreen) {
        if (isFullscreen) {
            DxLib::SetWindowSizeChangeEnableFlag(FALSE, FALSE);
            // DxLib::SetWindowZOrder(DX_WIN_ZTYPE_TOPMOST);
            DxLib::SetWindowSize(m_desktopSize.width, m_desktopSize.height);
            if (m_window.styleMode != 2) DxLib::SetWindowStyleMode(2);
            DxLib::SetWindowPosition(0, 0);
        }
        else {
            DxLib::SetWindowSizeChangeEnableFlag(m_window.enableSizeChange.enable, false);
            DxLib::SetWindowStyleMode(m_window.styleMode);
            DxLib::SetWindowZOrder(DX_WIN_ZTYPE_NORMAL);
            DxLib::SetWindowPosition(m_windowPosX, m_windowPosY);
            DxLib::SetWindowSize(m_window.size.width, m_window.size.height);
        }
        return 0;
    }
    return DxLib::ChangeWindowMode(!isFullscreen);
}
int DxSystem::ToggleFullscreenMode() {
    return SetFullscreenMode(!m_window.isFullscreen);
}

RectSize_t DxSystem::GetWindowSize() {
    if (m_window.useVirtualFullscreen && m_window.isFullscreen) {
        return m_desktopSize;
    }
    if (!m_window.enableSizeChange.toFit) {
        int width, height;
        DxLib::GetWindowSize(&width, &height);
        m_window.size = { width, height };
    }
    return m_window.size;
}