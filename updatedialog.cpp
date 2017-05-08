#include "updatedialog.h"
#include "ui_updatedialog.h"

const QString updateDialog::confName = "conf.ini";

updateDialog::updateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateDialog)
{
    ui->setupUi(this);
    ui->versionLineEdit->setEnabled(false);
    this->parseConf();
    this->checkUpdate();
}

updateDialog::~updateDialog()
{
    delete ui;
}

void updateDialog::parseConf()
{
    QSettings conf(updateDialog::confName, QSettings::IniFormat);
    serverIp = conf.value("ip").toString();
    serverPort = conf.value("port").toInt();
    clientVersion = conf.value("cv").toString();
}

void updateDialog::checkUpdate()
{
    ui->versionLineEdit->setText(clientVersion);
    socket = new QTcpSocket;
    socket->abort();
    socket->connectToHost(serverIp, serverPort);
    QObject::connect(socket, SIGNAL(readyRead()), this, SLOT(Read()));
    QObject::connect(socket, SIGNAL(disconnected()), this, SLOT(Disconnect()));
    QObject::connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(Error(QAbstractSocket::SocketError)));
}

void updateDialog::closeEvent(QCloseEvent *event)
{
    close();
}

void updateDialog::Read()
{
    char serverVersion[8] ;
    char type;

    socket->read(serverVersion, 8);
    socket->read(&type, 1);
    qDebug() << type << endl;
    if (serverVersion > clientVersion)
    {
        if (QMessageBox::Yes == QMessageBox::question(this, "版本更新", QString("有新的版本：%1").arg(serverVersion),
                                                                  QMessageBox::Yes|QMessageBox::No, QMessageBox::No))
        {
            QSettings conf(updateDialog::confName, QSettings::IniFormat);
            conf.setValue("cv", serverVersion);
            QMessageBox::about(this, "版本更新", "更新成功!");
            accept();
        }
        else
        {
            if (type=='1')   close();
            else        accept();
        }
    }
    else
    {
        ui->versionLineEdit->setText("当前版本已经是最新");
        accept();
    }
}

void updateDialog::Disconnect()
{
    socket->close();
}

void updateDialog::Error(QAbstractSocket::SocketError socketError)
{
    socket->close();
}
