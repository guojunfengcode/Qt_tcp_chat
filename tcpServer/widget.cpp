#include "widget.h"
#include <QByteArray>
#include <QDebug>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    text = new QPlainTextEdit;
    btn  = new QPushButton(tr("启动"));
    layout = new QVBoxLayout(this);

    layout->addWidget(text);
    layout->addWidget(btn);
    isListening = false;

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(btnClickSlot()));
}

Widget::~Widget()
{

}

void Widget::newConnection()
{
    if(!server.hasPendingConnections())
        return;

    qDebug() << "[server]有新的连接";
    socket = server.nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(tcpData()));
}

void Widget::tcpData()
{
    qDebug() << "[server]收到数据";
    QByteArray data = socket->readAll();
    qDebug() << data;
    text->appendPlainText(QString::fromStdString(data.toStdString()));
}

void Widget::btnClickSlot()
{
    if(isListening)
    {
        socket->close();
        btn->setText(tr("启动"));
        isListening = false;
    }
    else 
    {
        if(server.listen(QHostAddress::Any, 50003))
        {
            connect(&server, SIGNAL(newConnection()), this, SLOT(newConnection()));
            btn->setText(tr("断开"));
            isListening = true;
        }
        else
        {
            QMessageBox::information(this, tr("启动服务器失败"), server.errorString(), QMessageBox::Ok);
        }
    }
}

