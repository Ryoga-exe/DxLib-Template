#pragma once
#include "DxLib.h"

struct RectSize_t {
    int width;
    int height;
};

struct EnableSizeChange_t {
    bool enable;
    bool toFit;
};

struct Window_t {
    RectSize_t size;
    EnableSizeChange_t enableSizeChange;
    int  colorDepth;
    bool isFullscreen;
    bool useVirtualFullscreen;
    int  styleMode;
};

static const Window_t defaultWindowCon = { {640, 480}, {true, true}, 32, false, false, 7 };

void ErrMsgBx(const TCHAR* errorMsg);

class DxSystem {
public:
    DxSystem();
    ~DxSystem();
    
    bool Initialize(const TCHAR* windowTitle);
    bool Finalize();

    int  SetWindowPosition(int posX, int posY);
    int  SetFullscreenMode(bool isFullscreen);
    int  ToggleFullscreenMode();
    RectSize_t GetWindowSize();
    

private:
    bool DxInit();
    int  SetWindowSize(RectSize_t size);
    int  SetEnableSizeChange(bool enable, bool toFit = true);
    bool SetUseVirtualFullScreenFlag(bool useVirtualFullScreen);

    bool m_hasInitialized;
    bool m_hasGotWindowPosition;
    Window_t   m_window;
    RectSize_t m_desktopSize;
    int m_windowPosX, m_windowPosY;
};