#ifndef __SslSocket__
#define __SslSocket__

#include <QObject>
#include <QSslSocket>
#include <QQmlEngine>
#include <QUrl>

class SslSocket: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool supportsSsl READ supportsSsl)
    Q_PROPERTY(long sslLibraryBuildVersionNumber READ sslLibraryBuildVersionNumber)
    Q_PROPERTY(QString sslLibraryBuildVersionString READ sslLibraryBuildVersionString)
    Q_PROPERTY(long sslLibraryVersionNumber READ sslLibraryVersionNumber)
    Q_PROPERTY(QString sslLibraryVersionString READ sslLibraryVersionString)

public:
    enum EncodingFormat
    {
        EncodingFormatPem = QSsl::Pem,
        EncodingFormatDer = QSsl::Der
    };

    Q_ENUM(EncodingFormat)

    enum PatternSyntax
    {
        PatternSyntaxRegExp         = QRegExp::RegExp,
        PatternSyntaxWildcard       = QRegExp::Wildcard,
        PatternSyntaxFixedString    = QRegExp::FixedString,
        PatternSyntaxRegExp2        = QRegExp::RegExp2,
        PatternSyntaxWildcardUnix   = QRegExp::WildcardUnix,
        PatternSyntaxW3CXmlSchema11 = QRegExp::W3CXmlSchema11
    };

    Q_ENUM(PatternSyntax)

public:
    SslSocket(QObject* parent = nullptr);
    SslSocket(QSslSocket* socket, QObject* parent = nullptr);
    virtual ~SslSocket();

    Q_INVOKABLE bool addDefaultCaCertificates(const QString& path, EncodingFormat format = EncodingFormatPem, PatternSyntax patternSyntax = PatternSyntaxWildcard);

public:
    static const char* typeName;

    void setSocket(QSslSocket* socket);

    static SslSocket* create(QSslSocket*, QQmlEngine::ObjectOwnership ownership = QQmlEngine::JavaScriptOwnership);
    static void registerTypes(const char* uri, int versionMajor = 1, int versionMinor = 0);

protected:
    QSslSocket* m_socket;

    void connectSignals();
    void disconnectSignals();

    static QObject *singletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine);

    static bool supportsSsl() { return QSslSocket::supportsSsl(); }
    static long sslLibraryBuildVersionNumber() { return QSslSocket::sslLibraryBuildVersionNumber(); }
    static QString sslLibraryBuildVersionString() { return QSslSocket::sslLibraryBuildVersionString(); }
    static long sslLibraryVersionNumber() { return QSslSocket::sslLibraryVersionNumber(); }
    static QString sslLibraryVersionString() { return QSslSocket::sslLibraryVersionString(); }

};

#endif
