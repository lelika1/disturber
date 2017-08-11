#include "database.h"
#include "startwindow.h"

#include <QApplication>
#include <QDesktopWidget>

#include <unistd.h>

int main(int argc, char *argv[])
{
    try {
        DataBase db("dictionary.db");
        QApplication a(argc, argv);
        StartWindow w(&db);
        QRect wGeom = w.geometry();
        QDesktopWidget *desktop = QApplication::desktop();
        w.setGeometry(QRect((desktop->screenGeometry().width() -  wGeom.width())/2,
                            (desktop->screenGeometry().height()- wGeom.height())/2,
                             wGeom.width(), wGeom.height()));

        while (true) {
            w.show();
            a.exec();
            usleep(20 * 60 * 1000000);
        }
    } catch(DBCreateException ex) {
        qDebug() << ex.what();
    }

    return 0;
}
