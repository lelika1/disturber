#ifndef SETUPWTUDYWINDOW_H
#define SETUPWTUDYWINDOW_H

#include "database.h"

#include <QDialog>


namespace Ui {
class SetupStudyWindow;
}

class SetupStudyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SetupStudyWindow(DataBase *_db, QWidget *parent = 0);
    ~SetupStudyWindow();

    void Exec();

private slots:
    void on_continueButton_clicked();

private:
    Ui::SetupStudyWindow *ui;
    DataBase *db;
};

#endif // SETUPWTUDYWINDOW_H
