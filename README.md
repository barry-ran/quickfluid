# quickfluid
基于fluid快速构建qml应用

# TODO
- qml无边框方案分析：
    - qquickview
    - 不考虑（最大化闪烁）[Qml-Frameless-application-framework](https://github.com/qq574582775/Qml-Frameless-application-framework) 纯qml实现鼠标事件处理移动窗体（FramelessWindow + ContentWindow），最大化有闪烁问题
    - 不考虑（拖动过程中鼠标样式变化频繁）[FramelessWindow](https://github.com/shenjing023/FramelessWindow) 同上，没有闪烁问题
    - 不考虑 [MyCloudMusic](https://github.com/shenjing023/MyCloudMusic) QWidget嵌入QQuickWidget，QQuickWidget加载的qml来显示界面，FramelessHelper在QWidget中installEventFilter安装事件过滤器处理鼠标事件
    - 不考虑（只支持windows可考虑，使用windows本地消息实现，几乎完美，其他方案拖动左侧的时候，无法保证右侧不晃动） [FramelessHelper](https://github.com/qtdevs/FramelessHelper) 比较完善的方案，qwidget和qml都支持，支持windows特性，但是只支持windows
    - 采用 [FramlessWindowHelper](https://github.com/lowbees/FramlessWindowHelper) c++代码向qml中注册一个qml对象，c++代码遍历parent找到window，installeventfilter处理事件
    
- qml使用http请求可考虑[HttpRequest](https://github.com/qyvlik/HttpRequest)
- 文件下载可以考虑[QuickDownload](https://github.com/Larpon/QuickDownload)
- [窗体阴影](https://stackoverflow.com/questions/18754057/shadow-for-qml-frameless-windows)
