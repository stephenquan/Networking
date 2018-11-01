#include "SslSocket.h"
#include <QSslSocket>

const char* SslSocket::typeName = "SslSocket";

SslSocket::SslSocket(QObject* parent) :
    QObject(parent),
    m_socket(nullptr)
{
    qDebug() << Q_FUNC_INFO;
}

SslSocket::SslSocket(QSslSocket* socket, QObject* parent) :
    QObject(parent),
    m_socket(nullptr)
{
    qDebug() << Q_FUNC_INFO << socket;

    setSocket(socket);
}

SslSocket::~SslSocket()
{
    qDebug() << Q_FUNC_INFO;
}


SslSocket* SslSocket::create(QSslSocket* socket, QQmlEngine::ObjectOwnership ownership)
{
    SslSocket* qmlSocket = new SslSocket(socket);
    QQmlEngine::setObjectOwnership(qmlSocket, ownership);
    return qmlSocket;
}

void SslSocket::setSocket(QSslSocket* socket)
{
    if (m_socket)
    {
        disconnectSignals();
        m_socket = nullptr;
    }

    if (!socket)
    {
        return;
    }

    m_socket = socket;

    connectSignals();
}

void SslSocket::registerTypes(const char* uri, int versionMajor, int versionMinor)
{
    qmlRegisterSingletonType<SslSocket>(uri, versionMajor, versionMinor, typeName, singletonProvider);
    qmlRegisterUncreatableType<SslSocket>(uri, versionMajor, versionMinor, typeName, QStringLiteral("Cannot create SslSocket"));
}

void SslSocket::connectSignals()
{

}

void SslSocket::disconnectSignals()
{

}

QObject *SslSocket::singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new SslSocket(nullptr, nullptr);
}

bool SslSocket::addDefaultCaCertificates(const QString& path, EncodingFormat format, PatternSyntax patternSyntax)
{
    qDebug() << Q_FUNC_INFO << path << format;
    return QSslSocket::addDefaultCaCertificates(
        path,
        static_cast<QSsl::EncodingFormat>(format),
        static_cast<QRegExp::PatternSyntax>(patternSyntax));
}
