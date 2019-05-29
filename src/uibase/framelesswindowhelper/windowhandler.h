#ifndef WINDOWHANDLER_H
#define WINDOWHANDLER_H

#include <QRect>

class QQuickWindow;
class QEvent;
class QMouseEvent;
class QPoint;
class QCursor;

class WindowHandler
{
public:

    WindowHandler(QQuickWindow *window);

    // 事件转发
    void handleEvent(QEvent *event);

    bool isResizing() const { return m_resizing; }
    int edgeSize() const { return m_edgeSize; }
    void setEdgeSize(int size) {
        if (size > 0 && size != m_edgeSize) {
            m_edgeSize = size;
        }
    }

private:
    // 是否在边界可拉伸区域
    void checkOnEdges(const QPoint &pos);
    // 更新鼠标样式
    void updateCursorShape(const QPoint &pos);
    // 更新鼠标样式
    void changeCursorShape(Qt::CursorShape shape);
    // 更改窗口大小和位置
    void resizeWindow(const QPoint &pos);
    // 处理鼠标按下事件
    void handleMousePressEvent(QMouseEvent *e);
    // 处理鼠标移动事件
    void handleMouseMoveEvent(QMouseEvent *e);
    // 处理鼠标释放事件
    void handleMouseReleaseEvent(QMouseEvent *e);

private:
    bool m_onLeft = false;
    bool m_onTop = false;
    bool m_onRight = false;
    bool m_onBottom = false;
    bool m_onTopLeft = false;
    bool m_onTopRight = false;
    bool m_onBottomLeft = false;
    bool m_onBottomRight = false;
    bool m_onEdges = false;
    bool m_leftButtonPress = false;
    bool m_resizing = false;
    int m_edgeSize = 10;
    QQuickWindow *m_window = Q_NULLPTR;
    QRect m_oldWindowRect;
};

#endif // WINDOWHANDLER_H
