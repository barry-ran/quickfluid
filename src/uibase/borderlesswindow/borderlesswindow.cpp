#include <QQuickItem>

#include <Windowsx.h>
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "user32.lib")

#include "borderlesswindow.h"

BorderlessWindow::BorderlessWindow(QWindow *parent) : QQuickWindow(parent)
{
    setFlags(flags() | Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    updateResizeable(m_resizeable);
}

BorderlessWindow::BorderlessWindow(QQuickRenderControl *renderControl) : QQuickWindow(renderControl)
{

}

void BorderlessWindow::setTitleHeight(int value)
{
    if (value != m_titleHeight) {
        m_titleHeight = value;
        emit titleHeightChanged();
    }
}

int BorderlessWindow::titleHeight() const
{
    return m_titleHeight;
}

void BorderlessWindow::setResizeable(bool resizeable)
{
    if (resizeable != m_resizeable) {
        m_resizeable = resizeable;
        updateResizeable(m_resizeable);
        emit resizeableChanged();
    }
}

void BorderlessWindow::updateResizeable(bool resizeable)
{
    bool visible = isVisible();
    if (resizeable){
        setFlags(flags() | Qt::WindowMaximizeButtonHint);
//        setWindowFlag(Qt::WindowMaximizeButtonHint);

        //此行代码可以带回Aero效果，同时也带回了标题栏和边框,在nativeEvent()会再次去掉标题栏
        //
        //this line will get titlebar/thick frame/Aero back, which is exactly what we want
        //we will get rid of titlebar and thick frame again in nativeEvent() later
        HWND hwnd = (HWND)this->winId();
        DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
        ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    }else{
        setFlags(flags() & ~Qt::WindowMaximizeButtonHint);
//        setWindowFlag(Qt::WindowMaximizeButtonHint,false);

        HWND hwnd = (HWND)this->winId();
        DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
        ::SetWindowLong(hwnd, GWL_STYLE, style & ~WS_MAXIMIZEBOX & ~WS_CAPTION);
    }

    //保留一个像素的边框宽度，否则系统不会绘制边框阴影
    //
    //we better left 1 piexl width of border untouch, so OS can draw nice shadow around it
    const MARGINS shadow = { 1, 1, 1, 1 };
    DwmExtendFrameIntoClientArea(HWND(winId()), &shadow);

    setVisible(visible);
}

bool BorderlessWindow::resizeable() const
{
    return m_resizeable;
}

bool BorderlessWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    //Workaround for known bug -> check Qt forum : https://forum.qt.io/topic/93141/qtablewidget-itemselectionchanged/13
    #if (QT_VERSION == QT_VERSION_CHECK(5, 11, 1))
    MSG* msg = *reinterpret_cast<MSG**>(message);
    #else
    MSG* msg = reinterpret_cast<MSG*>(message);
    #endif

    switch (msg->message)
    {
    case WM_NCCALCSIZE:
    {
        NCCALCSIZE_PARAMS& params = *reinterpret_cast<NCCALCSIZE_PARAMS*>(msg->lParam);
        if (params.rgrc[0].top != 0) {
            params.rgrc[0].top -= 1;
        }
        //this kills the window frame and title bar we added with WS_THICKFRAME and WS_CAPTION
        *result = WVR_REDRAW;
        return true;
    }
    case WM_NCHITTEST:
    {
        *result = 0;

        const LONG borderWidth = m_borderWidth;
        RECT winrect;
        GetWindowRect(HWND(winId()), &winrect);

        long x = GET_X_LPARAM(msg->lParam);
        long y = GET_Y_LPARAM(msg->lParam);

        if(m_resizeable)
        {
            bool resizeWidth = minimumWidth() != maximumWidth();
            bool resizeHeight = minimumHeight() != maximumHeight();

            if(resizeWidth)
            {
                //left border
                if (x >= winrect.left && x < winrect.left + borderWidth)
                {
                    *result = HTLEFT;
                }
                //right border
                if (x < winrect.right && x >= winrect.right - borderWidth)
                {
                    *result = HTRIGHT;
                }
            }
            if(resizeHeight)
            {
                //bottom border
                if (y < winrect.bottom && y >= winrect.bottom - borderWidth)
                {
                    *result = HTBOTTOM;
                }
                //top border
                if (y >= winrect.top && y < winrect.top + borderWidth)
                {
                    *result = HTTOP;
                }
            }
            if(resizeWidth && resizeHeight)
            {
                //bottom left corner
                if (x >= winrect.left && x < winrect.left + borderWidth &&
                        y < winrect.bottom && y >= winrect.bottom - borderWidth)
                {
                    *result = HTBOTTOMLEFT;
                }
                //bottom right corner
                if (x < winrect.right && x >= winrect.right - borderWidth &&
                        y < winrect.bottom && y >= winrect.bottom - borderWidth)
                {
                    *result = HTBOTTOMRIGHT;
                }
                //top left corner
                if (x >= winrect.left && x < winrect.left + borderWidth &&
                        y >= winrect.top && y < winrect.top + borderWidth)
                {
                    *result = HTTOPLEFT;
                }
                //top right corner
                if (x < winrect.right && x >= winrect.right - borderWidth &&
                        y >= winrect.top && y < winrect.top + borderWidth)
                {
                    *result = HTTOPRIGHT;
                }
            }
        }

        if (0 != *result) {
            return true;
        }

        //*result still equals 0, that means the cursor locate OUTSIDE the frame area
        //but it may locate in titlebar area
        if (0 == m_titleHeight) {
            return false;
        }

        //support highdpi
        double dpr = this->effectiveDevicePixelRatio();
        QPoint pos = mapFromGlobal(QPointF(x / dpr, y / dpr).toPoint());
        QRect title = QRect(0, 0, width(), m_titleHeight);
        if (title.contains(pos)) {
            *result = HTCAPTION;
            return true;
        }
    } //end case WM_NCHITTEST
    }

    return QQuickWindow::nativeEvent(eventType, message, result);
}
