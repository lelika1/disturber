#include "database.h"
#include "settings.h"

#include "startwindow.h"

#include <QApplication>
#include <QDesktopWidget>

#include <unistd.h>
#include <memory>

int main(int argc, char *argv[]) {
        QApplication a(argc, argv);

        Configurator &config = Configurator::Instance();
        config.LoadConfigFromFile("config");

        std::unique_ptr<DataBase> db;
        try {
            db.reset(new DataBase("dictionary.db"));
        } catch(DBCreateException ex) {
            qDebug() << ex.what();
            return 1;
        }

        StartWindow w(db.get());
        QRect wGeom = w.geometry();
        QDesktopWidget *desktop = QApplication::desktop();
        w.setGeometry(QRect((desktop->screenGeometry().width() -  wGeom.width())/2,
                            (desktop->screenGeometry().height()- wGeom.height())/2,
                             wGeom.width(), wGeom.height()));

        while (true) {
            w.show();
            a.exec();
            usleep(config.GetPeriodBetweenSessions() * 60 * 1000000);
        }

    return 0;
}
