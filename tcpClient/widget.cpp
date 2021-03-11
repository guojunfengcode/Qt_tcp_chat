#include "widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    lineEdit = new QLineEdit;
     btn = new QPushButton(tr("发送"));

     layout = new QHBoxLayout(this);
     layout->addWidget(lineEdit);
     layout->addWidget(btn);

     socket = new QTcpSocket(this);
     socket->connectToHost("192.168.18.143", 50003);
     if(socket->waitForConnected(1000))
         qDebug() << "[客户端]连接成功";

     connect(btn, SIGNAL(clicked(bool)), this, SLOT(sendTcpData()));
}

Widget::~Widget()
{

}

void Widget::sendTcpData()
{
    int n = socket->write(lineEdit->text().toStdString().data());
    if(n == -1) {
        QMessageBox::information(this, tr("发送失败"), socket->errorString(), QMessageBox::Ok);
    } else {
        qDebug() << "已发送" << n << "个字节";
        lineEdit->clear();
    }
}
