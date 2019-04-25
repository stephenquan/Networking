#include "Networking.h"
#include "NetworkAccessManager.h"
#include "NetworkReply.h"
#include "SslSocket.h"
#include <QCoreApplication>

#define URI "com.stephenquan.networking"

const char* Networking::kTypeName = "Networking";
const char* Networking::kPropertyNetworking = "networking";
const char* Networking::kPropertyNetworkAccessManagers = "networkAccessManagers";
const char* Networking::kMethodClearAccessCache = "clearAccessCache";

Networking::Networking(QObject* parent) :
    QObject(parent)
{
    QCoreApplication::instance()->setProperty(kPropertyNetworking, QVariant::fromValue<QObject*>(dynamic_cast<QObject*>(this)));
}

void Networking::registerTypes()
{
    qmlRegisterSingletonType<Networking>(URI, 1, 0, "Networking", Networking::singletonProvider);
    qmlRegisterSingletonType<NetworkAccessManager>(URI, 1, 0, "NetworkAccessManager", NetworkAccessManager::singletonProvider);
    qmlRegisterType<NetworkAccessManager>(URI, 1, 0, "NetworkAccessManager");
    //qmlRegisterUncreatableType<NetworkReply>(URI, 1, 0, "NetworkReply", QStringLiteral("Cannot create NetworkReply"));
    qmlRegisterType<NetworkReply>(URI, 1, 0, "NetworkReply");
    qmlRegisterSingletonType<SslSocket>(URI, 1, 0, "SslSocket", SslSocket::singletonProvider);
    qmlRegisterUncreatableType<SslSocket>(URI, 1, 0, "SslSocket", QStringLiteral("Cannot create SslSocket"));
}

QObject *Networking::singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new Networking();
}

void Networking::clearAccessCache()
{
    QObject* managers = networkAccessManagers();
    if (!managers)
    {
        return;
    }

    QMetaObject::invokeMethod(managers, kMethodClearAccessCache);
}

QObject* Networking::networkAccessManagers()
{
    QList<QNetworkAccessManager*> managers;

    QVariant varManagers = QCoreApplication::instance()->property(kPropertyNetworkAccessManagers);
    if (!varManagers.isValid() || varManagers.isNull())
    {
        return nullptr;
    }

    if (!varManagers.canConvert<QObject*>())
    {
        return nullptr;
    }

    return varManagers.value<QObject*>();
}
