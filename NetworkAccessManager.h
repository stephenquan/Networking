#ifndef __NetworkAccessManager__
#define __NetworkAccessManager__

#include <QObject>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QQmlEngine>
#include <QJSEngine>
#include <QSslError>
#include <QList>

class NetworkReply;

class NetworkAccessManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList supportedSchemes READ supportedSchemes)
    Q_PROPERTY(NetworkAccessibility networkAccessible READ networkAccessible NOTIFY networkAccessibleChanged)

public:
    enum NetworkAccessibility
    {
        NetworkAccessibilityUnknown = QNetworkAccessManager::UnknownAccessibility,
        NetworkAccessibilityFalse   = QNetworkAccessManager::NotAccessible,
        NetworkAccessibilityTrue    = QNetworkAccessManager::Accessible
    };

    Q_ENUM(NetworkAccessibility)

public:
    NetworkAccessManager(QObject* parent = nullptr);
    NetworkAccessManager(QQmlEngine *engine, QJSEngine *scriptEngine, QObject* parent = nullptr);

    Q_INVOKABLE void get(const QUrl& url, NetworkReply* reply);
    Q_INVOKABLE void head(const QUrl& url, NetworkReply* reply);
    Q_INVOKABLE void deleteResource(const QUrl& url, NetworkReply* reply);
    Q_INVOKABLE void post(const QUrl& url, NetworkReply* reply, const QVariant& data = QVariant());
    Q_INVOKABLE void put(const QUrl& url, NetworkReply* reply, const QVariant& data = QVariant());
    Q_INVOKABLE void clearAccessCache();
    Q_INVOKABLE void clearConnectionCache();

public:
    static char const* kTypeName;

signals:
    void finished(NetworkReply* reply);
    void sslErrors(NetworkReply* reply, const QVariantList& errors);
    void networkAccessibleChanged(NetworkAccessibility accessible);

public:
    static QObject *singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);
    static bool validateArg(const QUrl& url);
    static bool validateArg(NetworkReply* reply);
    static void setNetworkReply(NetworkReply* reply, QNetworkReply* _reply);
    void post(const QUrl& url, NetworkReply* reply, const QByteArray& data);
    void put(const QUrl& url, NetworkReply* reply, const QByteArray& data);

protected slots:
    void onProxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void onAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void onFinished(QNetworkReply*);
    void onEncrypted(QNetworkReply *reply);
    void onSslErrors(QNetworkReply* reply, const QList<QSslError>& errors);
    void onPreSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
    void onNetworkSessionConnected();
    void onNetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible);

protected:
    QNetworkAccessManager* m_manager;
    QQmlEngine* m_engine;

    void connectSignals();
    void disconnectSignals();

    QNetworkAccessManager* manager();
    QStringList supportedSchemes();
    NetworkAccessibility networkAccessible();

};

#endif
