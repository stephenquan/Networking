
message("Networking.pri")

QT += network

SOURCES += \
        $$PWD/Networking.cpp \
        $$PWD/NetworkAccessManager.cpp \
        $$PWD/NetworkReply.cpp \
        $$PWD/SslSocket.cpp

HEADERS += \
        $$PWD/Networking.h \
        $$PWD/NetworkAccessManager.h \
        $$PWD/NetworkReply.h \
        $$PWD/SslSocket.h

android: {
    OPENSSL_PATH=$$(HOME)/openssl/armv7/openssl-1.0.2p
    ANDROID_EXTRA_LIBS += \
        $${OPENSSL_PATH}/libcrypto.so \
        $${OPENSSL_PATH}/libssl.so
}
