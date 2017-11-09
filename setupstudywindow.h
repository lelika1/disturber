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

private slots:
    void on_continueButton_clicked();

    void on_allTopicsCheckBox_clicked(bool checked);

private:
    Ui::SetupStudyWindow *ui;
    DataBase *db;
};

#endif // SETUPWTUDYWINDOW_H
