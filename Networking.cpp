#include "Networking.h"
#include "NetworkAccessManager.h"
#include "NetworkReply.h"
#include "SslSocket.h"

void Networking::registerTypes(const char* uri, int versionMajor, int versionMinor)
{
    NetworkAccessManager::registerTypes(uri, versionMajor, versionMinor);
    NetworkReply::registerTypes(uri, versionMajor, versionMinor);
    SslSocket::registerTypes(uri, versionMajor, versionMinor);
}
