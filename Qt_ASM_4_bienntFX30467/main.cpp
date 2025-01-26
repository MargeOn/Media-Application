#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "player.h"
#include <QQmlContext>
#include "playlistmodel.h"
#include "translation.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    qRegisterMetaType<QMediaPlaylist*>("QMediaPlaylist*");
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Translation translator(&app);
    translator.setCurrentLanguage(Translation::UnitedStates);
    Player player;

    engine.rootContext()->setContextProperty("playerModel",player.m_playlistModel);
    engine.rootContext()->setContextProperty("player",player.m_player);
    engine.rootContext()->setContextProperty("utility",&player);
    engine.rootContext()->setContextProperty("translator",&translator);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
