#ifndef __Networking__
#define __Networking__

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QVariantMap>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QAuthenticator>

class Networking : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString user MEMBER m_user)
    Q_PROPERTY(QString password MEMBER m_password)
    Q_PROPERTY(QString realm MEMBER m_realm)
    Q_PROPERTY(QString proxyUser MEMBER m_proxyUser)
    Q_PROPERTY(QString proxyPassword MEMBER m_proxyPassword)
    Q_PROPERTY(QString proxyRealm MEMBER m_proxyRealm)

public:
    Networking(QObject* parent = nullptr);

    static void registerTypes();
    static QObject *singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

    Q_INVOKABLE void clearAccessCache();

public:
    static const char* kTypeName;
    static const char* kPropertyNetworking;
    static const char* kPropertyNetworkAccessManagers;
    static const char* kMethodClearAccessCache;

signals:
    void networkError(const QUrl& url, int error, const QString& errorString);

protected:
    QString m_user;
    QString m_password;
    QString m_realm;
    QString m_proxyUser;
    QString m_proxyPassword;
    QString m_proxyRealm;

    static QObject* networkAccessManagers();

};

#endif
