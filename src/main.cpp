#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQuick/QQuickWindow>
#include <QtCore/QDebug>

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    foreach (QScreen *pScreen, QGuiApplication::screens())
    {
        pScreen->setOrientationUpdateMask(Qt::LandscapeOrientation | Qt::PortraitOrientation |
                                          Qt::InvertedLandscapeOrientation | Qt::InvertedPortraitOrientation);
    }

    QQmlEngine engine;
    QQmlComponent component(&engine);
    QQuickWindow::setDefaultAlphaBuffer(true);
    component.loadUrl(QUrl("qrc:///qworship/qml/qworship.qml"));
    if (component.isReady())
        component.create();
    else
        qWarning() << component.errorString();

//    view.setResizeMode(QQuickView::SizeRootObjectToView);
//    view.setSource(QUrl("qrc:///qworship/qml/qworship.qml"));
//    view.show();

    return app.exec();
}
