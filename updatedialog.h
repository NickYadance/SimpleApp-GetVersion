#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include <QTcpSocket>
#include <QTextStream>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>
#include <QByteArray>

namespace Ui {
class updateDialog;
}

class updateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit updateDialog(QWidget *parent = 0);
    ~updateDialog();

    static const QString confName ;
    void parseConf();
    void checkUpdate();
    void closeEvent(QCloseEvent *event);
private:
    Ui::updateDialog *ui;
    QTcpSocket *socket ;
    QString     serverIp;
    int         serverPort;
    QString     clientVersion;
private slots:
    void    Read();
    void    Disconnect();
    void    Error(QAbstractSocket::SocketError socketError);
};

#endif // UPDATEDIALOG_H
