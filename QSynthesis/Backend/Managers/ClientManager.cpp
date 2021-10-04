#include "ClientManager.h"
#include "mainwindow.h"

#include <QApplication>

ClientManager::ClientManager(QObject *parent) : QObject(parent) {
    ServerName = "QSynthesis_Server";

    connect(&client, &QLocalSocket::connected, this, &ClientManager::handleConnectSuccess);
    connect(&client, &QLocalSocket::errorOccurred, this, &ClientManager::handleConnectError);

    connect(&server, &QLocalServer::newConnection, this, &ClientManager::handleNewClient);
}

bool ClientManager::tryCallServer() {
    code = 0;

    client.connectToServer(ServerName);
    while (code == 0) {
    }

    return code == 1;
}

void ClientManager::handleConnectSuccess() {
    QChar quote = '\"';
    client.write(QString(quote + qApp->arguments().join(quote + ' ') + quote).toUtf8());
    client.disconnectFromServer();
    client.waitForDisconnected();
    code = 1;
}

void ClientManager::handleConnectError(QLocalSocket::LocalSocketError e) {
    if (e != QLocalSocket::ServerNotFoundError) {
        code = 1;
    } else {
        code = -1;
    }

    client.close();
}

bool ClientManager::startAsServer() {
    if (!server.listen(ServerName)) {
        return false;
    }
    return true;
}

void ClientManager::handleNewClient() {
    for (QLocalSocket *client = server.nextPendingConnection(); client;
         client = server.nextPendingConnection()) {
        connect(client, &QLocalSocket::readyRead, this, &ClientManager::readFromClient);
    }
}

void ClientManager::readFromClient() {
    QLocalSocket *client = qobject_cast<QLocalSocket *>(sender());
    QString message = QString::fromUtf8(client->readAll());

    QChar quote = '\"';
    QStringList cmds = message.mid(1, message.size() - 2).split(quote + ' ');

    if (qRoot) {
        qRoot->fromCommandLine(cmds);
        qRoot->showNormal();
    }
}
