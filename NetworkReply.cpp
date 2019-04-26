#include "NetworkReply.h"
#include <QNetworkReply>

const char* NetworkReply::kTypeName = "NetworkReply";

NetworkReply::NetworkReply(QObject* parent) :
    QObject(parent),
    m_reply(nullptr)
{
    qDebug() << Q_FUNC_INFO;
}

NetworkReply::NetworkReply(QNetworkReply* reply, QObject* parent) :
    QObject(parent),
    m_reply(nullptr)
{
    qDebug() << Q_FUNC_INFO << reply;

    assign(reply);
}

NetworkReply::~NetworkReply()
{
    qDebug() << Q_FUNC_INFO;
}

NetworkReply* NetworkReply::create(QNetworkReply* reply, QQmlEngine::ObjectOwnership ownership)
{
    NetworkReply* qmlReply = new NetworkReply(reply);
    QQmlEngine::setObjectOwnership(qmlReply, ownership);
    return qmlReply;
}

void NetworkReply::assign(QNetworkReply* reply)
{
    if (m_reply)
    {
        disconnectSignals();
        m_reply->deleteLater();
        m_reply = nullptr;
    }

    if (!reply)
    {
        return;
    }

    m_reply = reply;

    connectSignals();
}

void NetworkReply::assign(QObject* reply)
{
    qDebug() << Q_FUNC_INFO << reply;

    NetworkReply* _reply = dynamic_cast<NetworkReply*>(reply);
    if (_reply)
    {
        assign(_reply);
        return;
    }
}

void NetworkReply::assign(NetworkReply* reply)
{
    qDebug() << Q_FUNC_INFO << reply;
    assign(reply->m_reply);
}

void NetworkReply::clear()
{
    if (!m_reply)
    {
        return;
    }

    disconnectSignals();
    m_reply->deleteLater();
    m_reply = nullptr;
}

void NetworkReply::connectSignals()
{
    connect(m_reply, &QNetworkReply::metaDataChanged, this, &NetworkReply::onMetaDataChanged);
    connect(m_reply, &QNetworkReply::finished, this, &NetworkReply::onFinished);
    connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    connect(m_reply, &QNetworkReply::sslErrors, this, &NetworkReply::onSslErrors);
    connect(m_reply, &QNetworkReply::preSharedKeyAuthenticationRequired, this, &NetworkReply::onPreSharedKeyAuthenticationRequired);
    connect(m_reply, &QNetworkReply::redirected, this, &NetworkReply::onRedirected);
    connect(m_reply, &QNetworkReply::redirectAllowed, this, &NetworkReply::onRedirectAllowed);
    connect(m_reply, &QNetworkReply::uploadProgress, this, &NetworkReply::onUploadProgress);
    connect(m_reply, &QNetworkReply::downloadProgress, this, &NetworkReply::onDownloadProgress);
}

void NetworkReply::disconnectSignals()
{
    disconnect(m_reply, &QNetworkReply::metaDataChanged, this, &NetworkReply::onMetaDataChanged);
    disconnect(m_reply, &QNetworkReply::finished, this, &NetworkReply::onFinished);
    disconnect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
    disconnect(m_reply, &QNetworkReply::sslErrors, this, &NetworkReply::onSslErrors);
    disconnect(m_reply, &QNetworkReply::preSharedKeyAuthenticationRequired, this, &NetworkReply::onPreSharedKeyAuthenticationRequired);
    disconnect(m_reply, &QNetworkReply::redirected, this, &NetworkReply::onRedirected);
    disconnect(m_reply, &QNetworkReply::redirectAllowed, this, &NetworkReply::onRedirectAllowed);
    disconnect(m_reply, &QNetworkReply::uploadProgress, this, &NetworkReply::onUploadProgress);
    disconnect(m_reply, &QNetworkReply::downloadProgress, this, &NetworkReply::onDownloadProgress);
}

QVariant NetworkReply::attribute(Attribute code) const
{
    if (!m_reply)
    {
        return QVariant();
    }

    return m_reply->attribute(static_cast<QNetworkRequest::Attribute>(code));
}

QString NetworkReply::readAll()
{
    if (!m_reply)
    {
        return QString();
    }

    QByteArray bytes = m_reply->readAll();
    QString response = QString::fromUtf8(bytes);
    qDebug() << Q_FUNC_INFO << response;
    return response;
}

void NetworkReply::onMetaDataChanged()
{
    qDebug() << Q_FUNC_INFO;
    emit rawHeadersChanged();
}

void NetworkReply::onFinished()
{
    qDebug() << Q_FUNC_INFO;

    emit rawHeadersChanged();
    emit finished();
}

void NetworkReply::onError(QNetworkReply::NetworkError error)
{
    qDebug() << Q_FUNC_INFO << error;
    emit rawHeadersChanged();
}

void NetworkReply::onEncrypted()
{
    qDebug() << Q_FUNC_INFO;
}

void NetworkReply::onSslErrors(const QList<QSslError> &errors)
{
    qDebug() << Q_FUNC_INFO << errors;
}

void NetworkReply::onPreSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator)
{
    qDebug() << Q_FUNC_INFO << authenticator;
}

void NetworkReply::onRedirected(const QUrl &url)
{
    qDebug() << Q_FUNC_INFO << url;
    emit rawHeadersChanged();
}

void NetworkReply::onRedirectAllowed()
{
    qDebug() << Q_FUNC_INFO;
}

void NetworkReply::onUploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug() << Q_FUNC_INFO << bytesSent << bytesTotal;
}

void NetworkReply::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << Q_FUNC_INFO << bytesReceived << bytesTotal;
}

QVariantMap NetworkReply::rawHeaders()
{
    qDebug() << Q_FUNC_INFO;

    QVariantMap map;
    if (!m_reply) return map;

    foreach (auto key, m_reply->rawHeaderList())
    {
        map[QString::fromUtf8(key)] = QString::fromUtf8(m_reply->rawHeader(key));
    }

    return map;
}
