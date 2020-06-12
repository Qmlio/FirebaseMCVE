#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <firebaseauth.h>
#include <firebasedatabase.h>
int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  qmlRegisterType<qmlio::googleFirebase::FirebaseDatabase>("Error", 1, 0,
                                                           "Database");
  engine.rootContext()->setContextProperty(
      "auth", qmlio::googleFirebase::FirebaseAuth::getInstance());
  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
