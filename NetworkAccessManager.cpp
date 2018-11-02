#include "NetworkAccessManager.h"
#include "NetworkReply.h"
#include <QQmlEngine>
#include <QNetworkRequest>
#include <QDebug>

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

NetworkReply* NetworkAccessManager::get(const QUrl& url)
{
    qDebug() << Q_FUNC_INFO;
    QNetworkRequest req(url);
    QNetworkReply* reply = manager()->get(req);
    NetworkReply* qmlReply = NetworkReply::create(reply);
    return qmlReply;
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
    //connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    //Qconnect(m_manager, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslErrors>&)), this, SLOT(onSslErrors(QNetworkReply*, const QList<QSslErrors>&)));
    connect(m_manager, &QNetworkAccessManager::finished, this, &NetworkAccessManager::onFinished);
    connect(m_manager, &QNetworkAccessManager::sslErrors, this, &NetworkAccessManager::onSslErrors);
}

void NetworkAccessManager::disconnectSignals()
{
    qDebug() << Q_FUNC_INFO;
    //disconnect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onFinished(QNetworkReply*)));
    // disconnect(m_manager, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslErrors>&)), this, SLOT(onSslErrors(QNetworkReply*, const QList<QSslErrors>&)));
    disconnect(m_manager, &QNetworkAccessManager::finished, this, &NetworkAccessManager::onFinished);
    disconnect(m_manager, &QNetworkAccessManager::sslErrors, this, &NetworkAccessManager::onSslErrors);
}

void NetworkAccessManager::onFinished(QNetworkReply* reply)
{
    qDebug() << Q_FUNC_INFO << reply;
    NetworkReply* qmlReply = NetworkReply::create(reply);
    emit finished(qmlReply);
    reply->deleteLater();
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

void NetworkAccessManager::registerTypes(const char* uri, int versionMajor, int versionMinor)
{
    qmlRegisterSingletonType<NetworkAccessManager>(uri, versionMajor, versionMinor, "NetworkAccessManager", singletonProvider);
    qmlRegisterType<NetworkAccessManager>(uri, versionMajor, versionMinor, "NetworkAccessManager");
}

QObject *NetworkAccessManager::singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    return new NetworkAccessManager(engine, scriptEngine);
}

QStringList NetworkAccessManager::supportedSchemes()
{
    return manager()->supportedSchemes();
}
