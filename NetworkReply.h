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
        NetworkReplyAttributeUnknown                        = -1,
        NetworkReplyAttributeHttpStatusCode                 = QNetworkRequest::Attribute::HttpStatusCodeAttribute,
        NetworkReplyAttributeHttpReasonPhrase               = QNetworkRequest::Attribute::HttpReasonPhraseAttribute,
        NetworkReplyAttributeRedirectionTarget              = QNetworkRequest::Attribute::RedirectionTargetAttribute,
        NetworkReplyAttributeConnectionEncrypted            = QNetworkRequest::Attribute::ConnectionEncryptedAttribute,
        NetworkReplyAttributeCacheLoadControl               = QNetworkRequest::Attribute::CacheLoadControlAttribute,
        NetworkReplyAttributeCacheSaveControl               = QNetworkRequest::Attribute::CacheSaveControlAttribute,
        NetworkReplyAttributeSourceIsFromCache              = QNetworkRequest::Attribute::SourceIsFromCacheAttribute,
        NetworkReplyAttributeDoNotBufferUploadData          = QNetworkRequest::Attribute::DoNotBufferUploadDataAttribute,
        NetworkReplyAttributeHttpPipeliningAllowed          = QNetworkRequest::Attribute::HttpPipeliningAllowedAttribute,
        NetworkReplyAttributeHttpPipeliningWasUsed          = QNetworkRequest::Attribute::HttpPipeliningWasUsedAttribute,
        NetworkReplyAttributeCustomVerb                     = QNetworkRequest::Attribute::CustomVerbAttribute,
        NetworkReplyAttributeCookieLoadControl              = QNetworkRequest::Attribute::CookieLoadControlAttribute,
        NetworkReplyAttributeAuthenticationReuse            = QNetworkRequest::Attribute::AuthenticationReuseAttribute,
        NetworkReplyAttributeCookieSaveControl              = QNetworkRequest::Attribute::CookieSaveControlAttribute,
        NetworkReplyAttributeBackgroundRequest              = QNetworkRequest::Attribute::BackgroundRequestAttribute,
        NetworkReplyAttributeSpdyAllowed                    = QNetworkRequest::Attribute::SpdyAllowedAttribute,
        NetworkReplyAttributeSpdyWasUsed                    = QNetworkRequest::Attribute::SpdyWasUsedAttribute,
        NetworkReplyAttributeEmitAllUploadProgressSignals   = QNetworkRequest::Attribute::EmitAllUploadProgressSignalsAttribute,
        NetworkReplyAttributeFollowRedirects                = QNetworkRequest::Attribute::FollowRedirectsAttribute,
        NetworkReplyAttributeHTTP2Allowed                   = QNetworkRequest::Attribute::HTTP2AllowedAttribute,
        NetworkReplyAttributeHTTP2WasUsed                   = QNetworkRequest::Attribute::HTTP2WasUsedAttribute,
        NetworkReplyAttributeOriginalContentLength          = QNetworkRequest::Attribute::OriginalContentLengthAttribute,
        NetworkReplyAttributeRedirectPolicy                 = QNetworkRequest::Attribute::RedirectPolicyAttribute,
#if QT_VERSION >= QT_VERSION_CHECK(5, 11, 0)
        NetworkReplyAttributeHttp2Direct                    = QNetworkRequest::Attribute::Http2DirectAttribute,
#endif
    };

    Q_ENUM(Attribute)

    enum StatusCode
    {
        StatusCodeContinue                      = 100,
        StatusCodeSwitchingProtocols            = 101,

        StatusCodeOK                            = 200,
        StatusCodeCreated                       = 201,
        StatusCodeAccepted                      = 202,
        StatusCodeNonAuthoritativeInformation   = 203,
        StatusCodeNoContent                     = 204,
        StatusCodeResetContent                  = 205,
        StatusCodePartialContent                = 206,

        StatusCodeMultipleChoices               = 300,
        StatusCodeMovedPermanently              = 301,
        StatusCodeFound                         = 302,
        StatusCodeSeeOther                      = 303,
        StatusCodeNotModified                   = 304,
        StatusCodeUseProxy                      = 305,
        StatusCodeTemporaryRedirect             = 307,

        StatusCodeBadRequest                    = 400,
        StatusCodeUnauthorized                  = 401,
        StatusCodePaymentRequired               = 402,
        StatusCodeForbidden                     = 403,
        StatusCodeNotFound                      = 404,
        StatusCodeMethodNotAllowed              = 405,
        StatusCodeNotAcceptable                 = 406,
        StatusCodeProxyAuthenticationRequired   = 407,
        StatusCodeRequestTimeout                = 408,
        StatusCodeConflict                      = 409,
        StatusCodeGone                          = 410,
        StatusCodeLengthRequired                = 411,
        StatusCodePreconditionFailed            = 412,
        StatusCodeRequestEntityTooLarge         = 413,
        StatusCodeRequestURITooLong             = 414,
        StatusCodeUnsupportedMediaType          = 415,
        StatusCodeRequestedRangeNotSuitable     = 416,
        StatusCodeExpectationFailed             = 417,

        StatusCodeInternalServerError           = 500,
        StatusCodeNotImplemented                = 501,
        StatusCodeBadGateway                    = 502,
        StatusCodeServiceUnavailable            = 503,
        StatusCodeGatewayTimeout                = 504,
        StatusCodeHTTPVersionNotSupported       = 505
    };

    Q_ENUM(StatusCode)


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
