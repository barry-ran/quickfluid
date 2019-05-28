#include "windowhandler.h"
#include <QQuickWindow>
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QGuiApplication>
#include <QDebug>

WindowHandler::WindowHandler(QQuickWindow *window) :
    m_window(window)
{
    if (m_window) {
        m_window->setFlags(m_window->flags() | Qt::FramelessWindowHint);
    }
}

void WindowHandler::handleEvent(QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress:
        handleMousePressEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::MouseMove:
        handleMouseMoveEvent(static_cast<QMouseEvent*>(event));
        break;
    case QEvent::MouseButtonRelease:
        handleMouseReleaseEvent(static_cast<QMouseEvent*>(event));
        break;
    default:
        break;
    }
}

void WindowHandler::checkOnEdges(const QPoint &pos)
{
    if (!m_window) {
        return;
    }

    int x = pos.x();
    int y = pos.y();
    int width = m_window->width();
    int height = m_window->height();

    m_onLeft = (x >= 0 && x <= m_edgeSize);
    m_onTop = (y >= 0 && y <= m_edgeSize);
    m_onRight = (x >= width - m_edgeSize && x <= width);
    m_onBottom = (y >= height - m_edgeSize && y <= height);

    m_onTopLeft = m_onTop && m_onLeft;
    m_onTopRight = m_onTop && m_onRight;
    m_onBottomLeft = m_onBottom && m_onLeft;
    m_onBottomRight = m_onBottom && m_onRight;
    m_onEdges = m_onTop || m_onLeft || m_onRight || m_onBottom;

}

void WindowHandler::updateCursorShape(const QPoint &pos)
{
    if (!m_window) {
        return;
    }
    if (m_window->visibility() == QQuickWindow::FullScreen
            || m_window->visibility() == QQuickWindow::Maximized) {
        while (QGuiApplication::overrideCursor()) {
            QGuiApplication::restoreOverrideCursor();
        }
        return;
    }

    checkOnEdges(pos);
    if (m_onTopLeft || m_onBottomRight) {
        QGuiApplication::setOverrideCursor(Qt::SizeFDiagCursor);
    } else if (m_onTopRight || m_onBottomLeft) {
        QGuiApplication::setOverrideCursor(Qt::SizeBDiagCursor);
    } else if (m_onLeft || m_onRight) {
        QGuiApplication::setOverrideCursor(Qt::SizeHorCursor);
    } else if (m_onTop || m_onBottom) {
        QGuiApplication::setOverrideCursor(Qt::SizeVerCursor);
    } else {
        // 将鼠标形状恢复
        while (QGuiApplication::overrideCursor()) {
            QGuiApplication::restoreOverrideCursor();
        }
    }
}

void WindowHandler::resizeWindow(const QPoint &pos)
{
    if (!m_window) {
        return;
    }

    QRect rc = m_oldWindowRect;
    int minWidth = m_window->minimumWidth();
    int minHeight = m_window->minimumHeight();
    int maxWidth = m_window->maximumWidth();
    int maxHeight = m_window->maximumHeight();
    int newWidth = 0;
    int newHeight = 0;

    if (m_onLeft) {
        newWidth = rc.right() - pos.x();
        newWidth = newWidth < minWidth ? minWidth : newWidth;
        newWidth = newWidth > maxWidth ? maxWidth : newWidth;
        rc.setX(rc.right() - newWidth);
    }
    if (m_onTop) {
        newHeight = rc.bottom() - pos.y();
        newHeight = newHeight < minHeight ? minHeight : newHeight;
        newHeight = newHeight > maxHeight ? maxHeight : newHeight;
        rc.setY(rc.bottom() - newHeight);
    }
    if (m_onRight) {
        newWidth = pos.x() - rc.left();
        newWidth = newWidth < minWidth ? minWidth : newWidth;
        newWidth = newWidth > maxWidth ? maxWidth : newWidth;
        rc.setWidth(newWidth);
    }
    if (m_onBottom) {
        newHeight = pos.y() - rc.top();
        newHeight = newHeight < minHeight ? minHeight : newHeight;
        newHeight = newHeight > maxHeight ? maxHeight : newHeight;
        rc.setHeight(newHeight);
    }
    m_window->setGeometry(rc);

    // 解决闪烁
    qreal opacity = m_window->opacity();
    m_window->setOpacity(opacity - 0.01);
    m_window->setOpacity(opacity);
}

void WindowHandler::handleMousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_leftButtonPress = true;
        m_oldWindowRect = m_window->frameGeometry();
        checkOnEdges(e->pos());
    }
}

void WindowHandler::handleMouseMoveEvent(QMouseEvent *e)
{
    if (m_window && m_window->visibility() == QWindow::Maximized) {
        return;
    }
    if (m_leftButtonPress) {
        if (m_onEdges) {
            m_resizing = true;
            resizeWindow(e->globalPos());
        }
    } else {
        updateCursorShape(e->pos());
    }
}

void WindowHandler::handleMouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    m_leftButtonPress = false;
    m_resizing = false;
}
