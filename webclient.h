#ifndef WEBCLIENT_H
#define WEBCLIENT_H

#include "ui_webclient.h"

#include <QDebug>
#include <QTcpSocket>
#include <QAbstractSocket>

class Webclient : public QWidget, private Ui::Webclient
{
    Q_OBJECT

public:
    explicit Webclient(QWidget *parent = nullptr);

private slots:
    void go_button_clicked();

private:

    void connected();
    void readyRead();
    void printdisplayResult(QString webpage);

    QTcpSocket * m_socket = nullptr;
    QString m_hostname;
    const unsigned char m_port = 80;
};

#endif // WEBCLIENT_H
