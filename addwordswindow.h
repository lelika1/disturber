#ifndef ADDWORDSWINDOW_H
#define ADDWORDSWINDOW_H

#include "database.h"
#include <QWidget>

namespace Ui {
class AddWordsWindow;
}

class AddWordsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AddWordsWindow(DataBase *_db, QWidget *parent = 0);
    ~AddWordsWindow();

private slots:
    void on_addButton_clicked();

    void on_printAeButton_clicked();

    void on_printOeButton_clicked();

    void on_printUeButton_clicked();

    void on_printSsButton_clicked();

private:
    Ui::AddWordsWindow *ui;
    DataBase *db;
};

#endif // ADDWORDSWINDOW_H
