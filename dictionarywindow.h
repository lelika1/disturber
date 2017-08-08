#ifndef DICTIONARYWINDOW_H
#define DICTIONARYWINDOW_H

#include "database.h"
#include <QWidget>

namespace Ui {
class DictionaryWindow;
}

class DictionaryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DictionaryWindow(DataBase *_db, QWidget *parent = 0);
    ~DictionaryWindow();

public:
    void ShowTable();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_saveButton_clicked();

    void on_findButton_clicked();

    void on_revertButton_clicked();

private:
    Ui::DictionaryWindow *ui;
    DataBase *db;
    //QSqlQueryModel sql_model;
    QSqlTableModel *sql_model;
};

#endif // DICTIONARYWINDOW_H
