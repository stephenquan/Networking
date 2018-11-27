#include "Networking.h"
#include "NetworkAccessManager.h"
#include "NetworkReply.h"
#include "SslSocket.h"
#include <QCoreApplication>

const char* Networking::kTypeName = "Networking";
const char* Networking::kPropertyNetworking = "networking";
const char* Networking::kPropertyNetworkAccessManagers = "networkAccessManagers";
const char* Networking::kMethodClearAccessCache = "clearAccessCache";

Networking::Networking(QObject* parent) :
    QObject(parent)
{
    QCoreApplication::instance()->setProperty(kPropertyNetworking, QVariant::fromValue<QObject*>(dynamic_cast<QObject*>(this)));
}

void Networking::registerTypes(const char* uri, int versionMajor, int versionMinor)
{
    qmlRegisterSingletonType<Networking>(uri, versionMajor, versionMinor, kTypeName, singletonProvider);
    NetworkAccessManager::registerTypes(uri, versionMajor, versionMinor);
    NetworkReply::registerTypes(uri, versionMajor, versionMinor);
    SslSocket::registerTypes(uri, versionMajor, versionMinor);
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
