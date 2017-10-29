#ifndef DICTIONARYWINDOW_H
#define DICTIONARYWINDOW_H

#include "database.h"
#include <QDialog>

#include <memory>

namespace Ui {

class DictionaryWindow;

} // namespace Ui


class DictionaryWindow : public QDialog {
    Q_OBJECT

public:
    explicit DictionaryWindow(DataBase *_db, QDialog *parent = 0);
    ~DictionaryWindow();

public:
    void Exec();

private slots:
    void on_findEdit_textChanged(const QString &arg1);
    void on_deleteWordsButton_clicked();
    void on_addWordsButton_clicked();

private:
    Ui::DictionaryWindow *ui;
    DataBase *db;
    std::unique_ptr<QSqlTableModel> sql_model;
};

#endif // DICTIONARYWINDOW_H
