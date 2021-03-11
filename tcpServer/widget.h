#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

#include <QPlainTextEdit>
#include <QPushButton>
#include <QLayout>
#include <QToolBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QTcpServer server;
    QTcpSocket *socket;

protected slots:
    void newConnection();
    void tcpData();
    void btnClickSlot();
    void btnClickSlotClose();
private:
    QPlainTextEdit *text;
    QPushButton *btn;
    QVBoxLayout *layout;
    bool isListening;
    QToolBox *toolBox;

    static int clientNum;
};

#endif // WIDGET_H
