#ifndef FRAMELESSWINDOWHELPER_H
#define FRAMELESSWINDOWHELPER_H

#include <QObject>
#include <QQuickWindow>
#include <QQmlParserStatus>
#include <QPointer>

class WindowHandler;

class FramelessWindowHelper : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
public:
    explicit FramelessWindowHelper(QObject *parent = Q_NULLPTR);
    ~FramelessWindowHelper() override;
    
public:
    void classBegin() Q_DECL_FINAL;
    void componentComplete() Q_DECL_FINAL;    

public:
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    QPointer<QObject> m_window;
    WindowHandler* m_handler = Q_NULLPTR;
};

#endif // FRAMELESSWINDOWHELPER_H
