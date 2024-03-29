#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "database.h"

#include <QMainWindow>

namespace Ui {

class StartWindow;

} // namespace Ui


class StartWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit StartWindow(DataBase *_db, QWidget *parent = 0);
    ~StartWindow();

private slots:
    void on_studyButton_clicked();

    void on_action_Options_triggered();
    void on_actionEdit_dictionary_triggered();
    void on_actionImport_triggered();
    void on_actionExport_triggered();

private:
    Ui::StartWindow *ui;
    DataBase *db;
};

#endif // STARTWINDOW_H
