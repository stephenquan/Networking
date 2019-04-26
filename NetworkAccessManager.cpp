#include "NetworkAccessManager.h"
#include "NetworkReply.h"
#include <QQmlEngine>
#include <QNetworkRequest>
#include <QNetworkProxy>
#include <QAuthenticator>
#include <QDebug>

const char* NetworkAccessManager::kTypeName = "NetworkAccessManager";

NetworkAccessManager::NetworkAccessManager(QObject* parent) :
    QObject(parent),
    m_manager(nullptr),
    m_engine(nullptr)
{
    qDebug() << Q_FUNC_INFO;
}

NetworkAccessManager::NetworkAccessManager(QQmlEngine *engine, QJSEngine *scriptEngine, QObject* parent) :
    QObject(parent),
    m_manager(nullptr),
    m_engine(engine)
{
    qDebug() << Q_FUNC_INFO;
    Q_UNUSED(scriptEngine)
}

QNetworkAccessManager* NetworkAccessManager::manager()
{
    qDebug() << Q_FUNC_INFO;

    if (m_manager)
    {
        return m_manager;
    }

    if (!m_engine)
    {
        m_engine = qmlEngine(this);
    }

    m_manager = m_engine->networkAccessManager();
    connectSignals();
    return m_manager;
}

void NetworkAccessManager::get(const QUrl& url, NetworkReply* reply)
{
    qDebug() << Q_FUNC_INFO << url;

    if (!validateArg(url)) return;
    if (!validateArg(reply)) return;

    QNetworkRequest req(url);
    QNetworkReply* _reply = manager()->get(req);
    setNetworkReply(reply, _reply);
}

void NetworkAccessManager::head(const QUrl& url, NetworkReply* reply)
{
    qDebug() << Q_FUNC_INFO << url;

    if (!validateArg(url)) return;
    if (!validateArg(reply)) return;

    QNetworkRequest req(url);
    QNetworkReply* _reply = manager()->head(req);
    setNetworkReply(reply, _reply);
}

void NetworkAccessManager::deleteResource(const QUrl& url, NetworkReply* reply)
{
    qDebug() << Q_FUNC_INFO << url;

    if (!validateArg(url)) return;
    if (!validateArg(reply)) return;

    QNetworkRequest req(url);
    QNetworkReply* _reply = manager()->deleteResource(req);
    setNetworkReply(reply, _reply);
}

void NetworkAccessManager::post(const QUrl& url, NetworkReply* reply, const QVariant& data)
{
    qDebug() << Q_FUNC_INFO << url << data;

    if (data.isNull())
    {
        post(url, reply, QByteArray());
        return;
    }

    if (data.type() == QVariant::String)
    {
        post(url, reply, data.toString().toUtf8());
        return;
    }

    if (data.canConvert<QByteArray>())
    {
        post(url, reply, data.toByteArray());
        return;
    }

    qWarning(" not supported (yet)");
}

void NetworkAccessManager::post(const QUrl& url, NetworkReply* reply, const QByteArray& data)
{
    qDebug() << Q_FUNC_INFO << url << data;

    if (!validateArg(url)) return;
    if (!validateArg(reply)) return;

    QNetworkRequest req(url);
    QNetworkReply* _reply = manager()->post(req, data);
    setNetworkReply(reply, _reply);
}

void NetworkAccessManager::put(const QUrl& url, NetworkReply* reply, const QVariant& data)
{
    qDebug() << Q_FUNC_INFO << url << data;

    if (data.isNull())
    {
        put(url, reply, QByteArray());
        return;
    }

    if (data.type() == QVariant::String)
    {
        put(url, reply, data.toString().toUtf8());
        return;
    }

    if (data.canConvert<QByteArray>())
    {
        put(url, reply, data.toByteArray());
        return;
    }

    qWarning(" not supported (yet)");
}

void NetworkAccessManager::put(const QUrl& url, NetworkReply* reply, const QByteArray& data)
{
    qDebug() << Q_FUNC_INFO << url << data;

    if (!validateArg(url)) return;
    if (!validateArg(reply)) return;

    QNetworkRequest req(url);
    QNetworkReply* _reply = manager()->put(req, data);
    setNetworkReply(reply, _reply);
}

void NetworkAccessManager::clearAccessCache()
{
    if (!m_manager)
    {
        return;
    }

    m_manager->clearAccessCache();
}

void NetworkAccessManager::clearConnectionCache()
{
    if (!m_manager)
    {
        return;
    }

    m_manager->clearConnectionCache();
}

void NetworkAccessManager::connectSignals()
{
    qDebug() << Q_FUNC_INFO;
    connect(m_manager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &NetworkAccessManager::onProxyAuthenticationRequired);
    connect(m_manager, &QNetworkAccessManager::authenticationRequired, this, &NetworkAccessManager::onAuthenticationRequired);
    connect(m_manager, &QNetworkAccessManager::finished, this, &NetworkAccessManager::onFinished);
    connect(m_manager, &QNetworkAccessManager::encrypted, this, &NetworkAccessManager::onEncrypted);
    connect(m_manager, &QNetworkAccessManager::sslErrors, this, &NetworkAccessManager::onSslErrors);
    connect(m_manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &NetworkAccessManager::onPreSharedKeyAuthenticationRequired);
    connect(m_manager, &QNetworkAccessManager::networkSessionConnected, this, &NetworkAccessManager::onNetworkSessionConnected);
    connect(m_manager, &QNetworkAccessManager::networkAccessibleChanged, this, &NetworkAccessManager::onNetworkAccessibleChanged);
}

void NetworkAccessManager::disconnectSignals()
{
    qDebug() << Q_FUNC_INFO;
    disconnect(m_manager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &NetworkAccessManager::onProxyAuthenticationRequired);
    disconnect(m_manager, &QNetworkAccessManager::authenticationRequired, this, &NetworkAccessManager::onAuthenticationRequired);
    disconnect(m_manager, &QNetworkAccessManager::finished, this, &NetworkAccessManager::onFinished);
    disconnect(m_manager, &QNetworkAccessManager::encrypted, this, &NetworkAccessManager::onEncrypted);
    disconnect(m_manager, &QNetworkAccessManager::sslErrors, this, &NetworkAccessManager::onSslErrors);
    disconnect(m_manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &NetworkAccessManager::onPreSharedKeyAuthenticationRequired);
    disconnect(m_manager, &QNetworkAccessManager::networkSessionConnected, this, &NetworkAccessManager::onNetworkSessionConnected);
    disconnect(m_manager, &QNetworkAccessManager::networkAccessibleChanged, this, &NetworkAccessManager::onNetworkAccessibleChanged);
}

void NetworkAccessManager::onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    qDebug() << Q_FUNC_INFO << proxy.hostName() << authenticator;
}

void NetworkAccessManager::onAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    qDebug() << Q_FUNC_INFO << reply << authenticator;
}

void NetworkAccessManager::onFinished(QNetworkReply* reply)
{
    qDebug() << Q_FUNC_INFO << reply;
    NetworkReply* qmlReply = NetworkReply::create(reply);
    emit finished(qmlReply);
    reply->deleteLater();
}

void NetworkAccessManager::onEncrypted(QNetworkReply *reply)
{
    qDebug() << Q_FUNC_INFO << reply;
}

void NetworkAccessManager::onSslErrors(QNetworkReply* reply, const QList<QSslError>& errors)
{
    qDebug() << Q_FUNC_INFO << reply;
    QVariantList qmlErrors;
    foreach (QSslError error, errors)
    {
        QVariantMap qmlError;
        qmlError["error"] = error.error();
        qmlError["errorString"] = error.errorString();
        qmlErrors.append(qmlError);
    }
    NetworkReply* qmlReply = NetworkReply::create(reply);
    emit sslErrors(qmlReply, qmlErrors);
}

void NetworkAccessManager::onPreSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    qDebug() << Q_FUNC_INFO << reply << authenticator;
}

void NetworkAccessManager::onNetworkSessionConnected()
{
    qDebug() << Q_FUNC_INFO;
}

void NetworkAccessManager::onNetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{
    qDebug() << Q_FUNC_INFO << accessible;
    emit networkAccessibleChanged(static_cast<NetworkAccessibility>(accessible));
}

QObject *NetworkAccessManager::singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    return new NetworkAccessManager(engine, scriptEngine);
}

QStringList NetworkAccessManager::supportedSchemes()
{
    return manager()->supportedSchemes();
}

NetworkAccessManager::NetworkAccessibility NetworkAccessManager::networkAccessible()
{
    QNetworkAccessManager* _manager = manager();

    return static_cast<NetworkAccessibility>(_manager->networkAccessible());
}

bool NetworkAccessManager::validateArg(const QUrl& url)
{
    if (!url.isEmpty() && url.isValid()) return true;
    qCritical("invalid url argument");
    return false;
}


bool NetworkAccessManager::validateArg(NetworkReply* reply)
{
    if (reply) return true;
    qCritical("invalid NetworkReply argument");
    return false;
}

void NetworkAccessManager::setNetworkReply(NetworkReply* reply, QNetworkReply* _reply)
{
    if (!_reply)
    {
        qCritical("unexpected empty QNetworkReply");
        return;
    }

    reply->assign(_reply);
}
