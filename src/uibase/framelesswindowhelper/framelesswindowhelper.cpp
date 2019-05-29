#include <QQuickItem>

#include "framelesswindowhelper.h"
#include "windowhandler.h"

FramelessWindowHelper::FramelessWindowHelper(QObject *parent) :
    QObject(parent)
{
}

FramelessWindowHelper::~FramelessWindowHelper()
{
    if (m_window) {
        m_window->removeEventFilter(this);
    }
    if (m_handler) {
        delete m_handler;
        m_handler = Q_NULLPTR;
    }
}

void FramelessWindowHelper::classBegin()
{

}

void FramelessWindowHelper::componentComplete()
{
    // find root window
    auto obj = parent();
    while (Q_NULLPTR != obj) {
        if (obj->inherits("QQuickRootItem")) {
            if (auto rootItem = qobject_cast<QQuickItem *>(obj)) {
                if (auto window = rootItem->window()) {
                    if (m_window != window) {
                        window->installEventFilter(this);                        
                        m_window = window;
                        m_handler = new WindowHandler(window);
                    }
                    break;                    
                }
            }
        }

        obj = obj->parent();
    }
}

bool FramelessWindowHelper::eventFilter(QObject *watched, QEvent *event)
{
    switch (event->type()) {    
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease:
    case QEvent::Leave:
    {        
        if (m_handler) {
            m_handler->handleEvent(event);
            if (m_handler->isResizing()) {
                return true;
            }
        }        
    }
        break;   
    default:
        break;
    }
    return QObject::eventFilter(watched, event);
}
