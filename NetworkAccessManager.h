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

public:
    NetworkAccessManager(QObject* parent = nullptr);
    NetworkAccessManager(QQmlEngine *engine, QJSEngine *scriptEngine, QObject* parent = nullptr);

    Q_INVOKABLE NetworkReply* get(const QUrl& url);
    Q_INVOKABLE void clearAccessCache();
    Q_INVOKABLE void clearConnectionCache();

signals:
    void finished(NetworkReply* reply);
    void sslErrors(NetworkReply* reply, const QVariantList& errors);

public:
    static void registerTypes(const char *uri, int versionMajor = 1, int versionMinor = 0);

protected slots:
    void onFinished(QNetworkReply*);
    void onSslErrors(QNetworkReply* reply, const QList<QSslError>& errors);

protected:
    QNetworkAccessManager* m_manager;
    QQmlEngine* m_engine;

    void connectSignals();
    void disconnectSignals();

    QNetworkAccessManager* manager();
    QStringList supportedSchemes();

    static QObject *singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

};

#endif
