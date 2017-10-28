#ifndef DICTIONARYWINDOW_H
#define DICTIONARYWINDOW_H

#include "database.h"
#include "addwordswindow.h"
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
    void Show();

private slots:
    void on_findEdit_textChanged(const QString &arg1);
    void on_deleteWordsButton_clicked();
    void on_addWordsButton_clicked();

private:
    Ui::DictionaryWindow *ui;
    DataBase *db;
    QSqlTableModel *sql_model;

    AddWordsWindow add_words_form;
};

#endif // DICTIONARYWINDOW_H
