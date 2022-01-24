#include <thread>

#include "webclient.h"

Webclient::Webclient(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    connect(hostnameEntry, &QLineEdit::returnPressed, this, &Webclient::go_button_clicked);

    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &Webclient::connected);
    connect(m_socket, &QTcpSocket::readyRead, this, &Webclient::readyRead);

}

void Webclient::printdisplayResult(QString webpage)
{
    displayResult->clear();
    displayResult->setText(webpage);
}

void Webclient::go_button_clicked()
{
    if (!hostnameEntry->text().isEmpty())
    {
        m_hostname = hostnameEntry->text();
        printdisplayResult("Input:" + m_hostname);
        m_socket->connectToHost(m_hostname, m_port);
        if (!m_socket->waitForConnected(5000))
        {
            printdisplayResult("Connection failed!\n");
            printdisplayResult("Can't open the page " + m_hostname + " beacuse the server could not be found.");
            m_socket->reset();
        }
    }
    else
        printdisplayResult("Please enter another adress.");
}

void Webclient::connected()
{
    m_socket->write(QString("GET / HTTP/1.1\r\nHost:" + m_hostname + "\r\n\r\n").toLocal8Bit());
}

void Webclient::readyRead()
{
    printdisplayResult(m_socket->readAll());
    m_socket->disconnectFromHost();
}
