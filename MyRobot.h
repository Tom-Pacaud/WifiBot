#ifndef MYROBOT_H
#define MYROBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QWidget>
#include <QWebEngineView>
#include <QWidget>
#include <QKeyEvent>

class MyRobot : public QObject {
    Q_OBJECT
public:
    explicit MyRobot(QObject *parent = 0);
    void doConnect();
    void disConnect();
    void gotoGauche();
    void gotoDroite();
    void gogogo();
    void nonono();
    void crctosend();
    void stop();
    QByteArray DataToSend;
    QByteArray DataReceived;
    QMutex Mutex;
    char crc;

signals:
    void updateUI(const QByteArray Data);
public slots:
    void connected();
    void disconnected();
    void bytesWritten(qint64 bytes);
    void readyRead();
    void MyTimerSlot();

private:
    QTcpSocket *socket;
    QTimer *TimerEnvoi;
};

#endif // MYROBOT_H
