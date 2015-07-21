#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtCore/QDebug>
#include <QtCore/QTranslator>
#include <QtCore/QLibraryInfo>

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    foreach (QScreen *pScreen, QGuiApplication::screens())
    {
        pScreen->setOrientationUpdateMask(Qt::LandscapeOrientation | Qt::PortraitOrientation |
                                          Qt::InvertedLandscapeOrientation | Qt::InvertedPortraitOrientation);
    }

    QTranslator qtTrans;
    qtTrans.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTrans);

    QTranslator appTrans;
    appTrans.load(":///lang/qworship" + QLocale::system().name());
    app.installTranslator(&appTrans);

    QQmlEngine engine;
    QQmlComponent component(&engine);
    QQuickWindow::setDefaultAlphaBuffer(true);
    QQmlContext *pContext = new QQmlContext(engine.rootContext());
    pContext->setContextProperty("screenPixelDensity", QGuiApplication::primaryScreen()->logicalDotsPerInch() *
                                 QGuiApplication::primaryScreen()->devicePixelRatio());

    component.loadUrl(QUrl("qrc:///qml/qworship.qml"));
    if (component.isReady())
        component.create(pContext);
    else
        qWarning() << component.errorString();

//    view.setResizeMode(QQuickView::SizeRootObjectToView);
//    view.setSource(QUrl("qrc:///qworship/qml/qworship.qml"));
//    view.show();

    return app.exec();
}
