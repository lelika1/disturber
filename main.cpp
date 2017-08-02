#include "database.h"
#include "startwindow.h"

#include <QApplication>
#include <QDesktopWidget>

#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
    while (true) {
        std::cout << " !!!! " << std::endl;
        QApplication a(argc, argv);
        DataBase db("dictionary.db");
        StartWindow w(&db);
        QRect wGeom = w.geometry();
        QDesktopWidget *desktop = QApplication::desktop();
        w.setGeometry(QRect((desktop->screenGeometry().width() -  wGeom.width())/2,
                            (desktop->screenGeometry().height()- wGeom.height())/2,
                             wGeom.width(), wGeom.height()));
        w.show();
        a.exec();
        usleep(20 * 60 * 1000000);
    }
    return 0;
}
