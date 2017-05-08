#include "mainwindow.h"
#include <QApplication>
#include "updatedialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    updateDialog *update_dialog = new updateDialog(&w);
    if ( update_dialog->exec() == QDialog::Accepted )
    {
        w.setVersion();
        w.show();
        return a.exec();
    }
    else
    {
        a.quit();
    }
}
