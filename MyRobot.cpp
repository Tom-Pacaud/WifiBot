// myrobot.cpp

#include "MyRobot.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include "mainwindow.h"

//Fonction de création du crc
short Crc16(unsigned char *Adresse_tab , unsigned char Taille_max)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity= 0;
    Crc = 0xFFFF;
    Polynome = 0xA001;
    for ( CptOctet= 0 ; CptOctet < Taille_max ; CptOctet++)
    {
        Crc ^= *( Adresse_tab + CptOctet);
        for ( CptBit = 0; CptBit <= 7 ; CptBit++)
        {
            Parity= Crc;
            Crc >>= 1;
            if (Parity%2 == true) Crc ^= Polynome;
        }
    }
    return(Crc);
}

//Constructeur de l'objet MyRobot
MyRobot::MyRobot(QObject *parent) : QObject(parent) {
    DataToSend.resize(9);
    DataToSend[0] = 0xFF;
    DataToSend[1] = 0x07;
    DataToSend[2] = 0x00;
    DataToSend[3] = 0x00;
    DataToSend[4] = 0x00;
    DataToSend[5] = 0x00;
    DataToSend[6] = 0x00;
    DataToSend[7] = 0x00;
    DataToSend[8] = 0x00;
    DataReceived.resize(21);
    TimerEnvoi = new QTimer();
    // setup signal and slot
    connect(TimerEnvoi, SIGNAL(timeout()), this, SLOT(MyTimerSlot())); //Send data to wifibot timer

    Camera=new QNetworkAccessManager();
}

//Fonction d'envoie du crc
void MyRobot::crctosend(){
    unsigned char *dat=(unsigned char *)DataToSend.data();
    short crc = Crc16(dat+1,6);
    DataToSend[7] = (char) crc;
    DataToSend[8] = (char) (crc >>8);
    DataReceived.resize(21);
    // setup signal and slot
}

//Focntion faisant avancer le robot
void MyRobot::avancer(){
    DataToSend[2] = 100;
    DataToSend[3] = 100 >> 8;
    DataToSend[4] = 100;
    DataToSend[5] = 100 >> 8;
    DataToSend[6] = 80;
    crctosend();

}

//Focntion faisant reculer le robot
void MyRobot::reculer(){
    DataToSend[2] = 100;
    DataToSend[3] = 100 >> 8;
    DataToSend[4] = 100;
    DataToSend[5] = 100 >> 8;
    DataToSend[6] = 0;
    crctosend();

}

//Focntion faisant aller le robot à droite
void MyRobot::allerDroite(){
    DataToSend[2] = 150;
    DataToSend[3] = 150 >> 8;
    DataToSend[4] = 150;
    DataToSend[5] = 150 >> 8;
    DataToSend[6] = 64;
    crctosend();
}

//Focntion faisant aller le robot à gauche
void MyRobot::allerGauche(){
    DataToSend[2] = 150;
    DataToSend[3] = 150 >> 8;
    DataToSend[4] = 150;
    DataToSend[5] = 150 >> 8;
    DataToSend[6] = 16;
    crctosend();
}

//Focntion faisant s'arrêter le robot
void MyRobot::stop(){
    DataToSend[2] = 0x00;
    DataToSend[3] = 0x00;
    DataToSend[4] = 0x00;
    DataToSend[5] = 0x00;
    DataToSend[6] = 80;
    crctosend();
}

//Fonction permettant à la caméra de tourner vers la gauche
void MyRobot::camGauche(){
    this->Camera->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200")));
}

//Fonction permettant à la caméra de tourner vers la droite
void MyRobot::camDroite(){
    this->Camera->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200")));
}

//Fonction permettant à la caméra de tourner vers le haut
void MyRobot::camHaut(){
    this->Camera->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200")));
}

//Fonction permettant à la caméra de tourner vers le bas
void MyRobot::camBas(){
    this->Camera->get(QNetworkRequest(QUrl("http://192.168.1.106:8080/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200")));
}

//Fonction de connection au robot
void MyRobot::doConnect() {
    socket = new QTcpSocket(this); // socket creation
    connect(socket, SIGNAL(connected()),this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
    qDebug() << "connecting..."; // this is not blocking call
    //socket->connectToHost("LOCALHOST", 15020);
    socket->connectToHost("192.168.1.106", 15020); // connection to wifibot
    // we need to wait...
    if(!socket->waitForConnected(5000)) {
        qDebug() << "Error: " << socket->errorString();
        return;
    }
    TimerEnvoi->start(75);

}

//Fonction de décoonection au robot
void MyRobot::disConnect() {
    TimerEnvoi->stop();
    socket->close();
}

// Fonction de débug en console

void MyRobot::connected() {
    qDebug() << "connected...";
}

void MyRobot::disconnected() {
    qDebug() << "disconnected...";
}

void MyRobot::bytesWritten(qint64 bytes) {
    qDebug() << bytes << " bytes written...";
}

void MyRobot::readyRead() { // Fonction de récupération des données des capteurs
    DataReceived = socket->readAll(); // Récupération des données
    emit updateUI(DataReceived); // Envoie des données dans le signal updateUI

}

void MyRobot::MyTimerSlot() {
    qDebug() << "Timer...";
    while(Mutex.tryLock());
    socket->write(DataToSend);
    Mutex.unlock();
}

