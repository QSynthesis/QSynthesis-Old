#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QEventLoop>
#include <QLocalServer>
#include <QLocalSocket>
#include <QMutex>
#include <QObject>

class ClientManager : public QObject {
    Q_OBJECT
public:
    ClientManager(QObject *parent = nullptr);

    QString ServerName;

public:
    bool tryCallServer();

private:
    QLocalSocket client;
    int code;

    void handleConnectSuccess();
    void handleConnectError(QLocalSocket::LocalSocketError e);

public:
    bool startAsServer();

private:
    QLocalServer server;

    void handleNewClient();
    void readFromClient();
};

#endif // CLIENTMANAGER_H
