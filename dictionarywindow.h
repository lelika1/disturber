#ifndef DICTIONARYWINDOW_H
#define DICTIONARYWINDOW_H

#include "database.h"
#include <QWidget>

namespace Ui {

class DictionaryWindow;

} // namespace Ui


class DictionaryWindow : public QWidget {
    Q_OBJECT

public:
    explicit DictionaryWindow(DataBase *_db, QWidget *parent = 0);
    ~DictionaryWindow();

public:
    void ShowTable();

private slots:
    void on_deleteRowButton_clicked();

    void on_findEdit_textChanged(const QString &arg1);

private:
    Ui::DictionaryWindow *ui;
    DataBase *db;
    QSqlTableModel *sql_model;
};

#endif // DICTIONARYWINDOW_H
