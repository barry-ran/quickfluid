#ifndef BORDERLESSWINDOW_H
#define BORDERLESSWINDOW_H

#include <QQuickWindow>

// https://github.com/Bringer-of-Light/Qt-Nice-Frameless-Window，qml bug
// https://github.com/lowbees/FramlessWindowHelper same bug

class BorderlessWindow : public QQuickWindow
{
    Q_OBJECT
    Q_PROPERTY(int titleHeight READ titleHeight WRITE setTitleHeight NOTIFY titleHeightChanged)
    Q_PROPERTY(bool resizeable READ resizeable WRITE setResizeable NOTIFY resizeableChanged)

public:
    explicit BorderlessWindow(QWindow *parent = nullptr);
    explicit BorderlessWindow(QQuickRenderControl *renderControl);

    void setTitleHeight(int value);
    int titleHeight() const;
    void setResizeable(bool resizeable);
    bool resizeable() const;

signals:
    void titleHeightChanged();
    void resizeableChanged();

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

private:
    void updateResizeable(bool resizeable);

private:
    int m_titleHeight = 36;
    int m_borderWidth = 5;
    bool m_resizeable = true;
};

#endif // BORDERLESSWINDOW_H
