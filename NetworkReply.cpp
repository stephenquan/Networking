#include "NetworkReply.h"
#include <QNetworkReply>

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

    setReply(reply);
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

void NetworkReply::setReply(QNetworkReply* reply)
{
    if (m_reply)
    {
        disconnectSignals();
        m_reply = nullptr;
    }

    if (!reply)
    {
        return;
    }

    m_reply = reply;

    connectSignals();
}

void NetworkReply::registerTypes(const char* uri, int versionMajor, int versionMinor)
{
    qmlRegisterUncreatableType<NetworkReply>(uri, versionMajor, versionMinor, "NetworkReply", QStringLiteral("Cannot create NetworkReply"));
}

void NetworkReply::connectSignals()
{

}

void NetworkReply::disconnectSignals()
{

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
