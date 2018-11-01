#ifndef __NetworkReply__
#define __NetworkReply__

#include <QObject>
#include <QNetworkReply>
#include <QQmlEngine>
#include <QUrl>

class NetworkReply: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl url READ url)
    Q_PROPERTY(int error READ error)
    Q_PROPERTY(QString errorString READ errorString)

public:
    enum Attribute
    {
        NetworkReplyAttributeHttpStatusCode = QNetworkRequest::HttpStatusCodeAttribute
    };

    Q_ENUM(Attribute)

public:
    NetworkReply(QObject* parent = nullptr);
    NetworkReply(QNetworkReply* reply, QObject* parent = nullptr);
    virtual ~NetworkReply();

    Q_INVOKABLE QVariant attribute(Attribute code) const;
    Q_INVOKABLE QString readAll();

public:
    QUrl url() const { return m_reply ? m_reply->url() : QUrl(); }
    int error() const { return m_reply ? m_reply->error() : 0; }
    QString errorString() const { return m_reply ? m_reply->errorString() : QString(); }

    void setReply(QNetworkReply* reply);

    static NetworkReply* create(QNetworkReply*, QQmlEngine::ObjectOwnership ownership = QQmlEngine::JavaScriptOwnership);
    static void registerTypes(const char* uri, int versionMajor = 1, int versionMinor = 0);

protected:
    QNetworkReply* m_reply;

    void connectSignals();
    void disconnectSignals();

};

#endif
