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
    Q_PROPERTY(QVariantMap rawHeaders READ rawHeaders NOTIFY rawHeadersChanged)

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

    enum NetworkError
    {
        NetworkErrorNoError                           = QNetworkReply::NoError,
        NetworkErrorConnectionRefusedError            = QNetworkReply::ConnectionRefusedError,
        NetworkErrorRemoteHostClosedError             = QNetworkReply::RemoteHostClosedError,
        NetworkErrorHostNotFoundError                 = QNetworkReply::HostNotFoundError,
        NetworkErrorTimeoutError                      = QNetworkReply::TimeoutError,
        NetworkErrorOperationCanceledError            = QNetworkReply::OperationCanceledError,
        NetworkErrorSslHandshakeFailedError           = QNetworkReply::SslHandshakeFailedError,
        NetworkErrorTemporaryNetworkFailureError      = QNetworkReply::TemporaryNetworkFailureError,
        NetworkErrorNetworkSessionFailedError         = QNetworkReply::NetworkSessionFailedError,
        NetworkErrorBackgroundRequestNotAllowedError  = QNetworkReply::BackgroundRequestNotAllowedError,
        NetworkErrorTooManyRedirectsError             = QNetworkReply::TooManyRedirectsError,
        NetworkErrorInsecureRedirectError             = QNetworkReply::InsecureRedirectError,
        NetworkErrorUnknownNetworkError               = QNetworkReply::UnknownNetworkError,
        NetworkErrorProxyConnectionRefusedError       = QNetworkReply::ProxyConnectionRefusedError,
        NetworkErrorProxyConnectionClosedError        = QNetworkReply::ProxyConnectionClosedError,
        NetworkErrorProxyNotFoundError                = QNetworkReply::ProxyNotFoundError,
        NetworkErrorProxyTimeoutError                 = QNetworkReply::ProxyTimeoutError,
        NetworkErrorProxyAuthenticationRequiredError  = QNetworkReply::ProxyAuthenticationRequiredError,
        NetworkErrorUnknownProxyError                 = QNetworkReply::UnknownProxyError,
        NetworkErrorContentAccessDenied               = QNetworkReply::ContentAccessDenied,
        NetworkErrorContentOperationNotPermittedError = QNetworkReply::ContentOperationNotPermittedError,
        NetworkErrorContentNotFoundError              = QNetworkReply::ContentNotFoundError,
        NetworkErrorAuthenticationRequiredError       = QNetworkReply::AuthenticationRequiredError,
        NetworkErrorContentReSendError                = QNetworkReply::ContentReSendError,
        NetworkErrorContentConflictError              = QNetworkReply::ContentConflictError,
        NetworkErrorContentGoneError                  = QNetworkReply::ContentGoneError,
        NetworkErrorUnknownContentError               = QNetworkReply::UnknownContentError,
        NetworkErrorProtocolUnknownError              = QNetworkReply::ProtocolUnknownError,
        NetworkErrorProtocolInvalidOperationError     = QNetworkReply::ProtocolInvalidOperationError,
        NetworkErrorProtocolFailure                   = QNetworkReply::ProtocolFailure,
        NetworkErrorInternalServerError               = QNetworkReply::InternalServerError,
        NetworkErrorOperationNotImplementedError      = QNetworkReply::OperationNotImplementedError,
        NetworkErrorServiceUnavailableError           = QNetworkReply::ServiceUnavailableError,
        NetworkErrorUnknownServerError                = QNetworkReply::UnknownServerError
    };

    Q_ENUM(NetworkError)

public:
    NetworkReply(QObject* parent = nullptr);
    NetworkReply(QNetworkReply* reply, QObject* parent = nullptr);
    virtual ~NetworkReply();

    Q_INVOKABLE void clear();
    Q_INVOKABLE QVariant attribute(Attribute code) const;
    Q_INVOKABLE QString readAll();
    Q_INVOKABLE void assign(QObject* reply);

signals:
    void finished();

    void rawHeadersChanged();

public:
    static const char* kTypeName;

public:
    QUrl url() const { return m_reply ? m_reply->url() : QUrl(); }
    NetworkError error() const { return m_reply ? static_cast<NetworkError>(m_reply->error()) : NetworkErrorNoError; }
    QString errorString() const { return m_reply ? m_reply->errorString() : QString(); }

    void assign(QNetworkReply* reply);
    void assign(NetworkReply* reply);
    QVariantMap rawHeaders();

    static NetworkReply* create(QNetworkReply*, QQmlEngine::ObjectOwnership ownership = QQmlEngine::JavaScriptOwnership);

protected:
    QNetworkReply* m_reply;

    void connectSignals();
    void disconnectSignals();

protected slots:
    void onMetaDataChanged();
    void onFinished();
    void onError(QNetworkReply::NetworkError error);
    void onEncrypted();
    void onSslErrors(const QList<QSslError> &errors);
    void onPreSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator *authenticator);
    void onRedirected(const QUrl &url);
    void onRedirectAllowed();
    void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

};

#endif
