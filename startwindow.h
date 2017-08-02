#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "addwordswindow.h"
#include "database.h"
#include "dictionarywindow.h"

#include <QMainWindow>

namespace Ui {
class StartWindow;
}

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartWindow(DataBase *_db, QWidget *parent = 0);
    ~StartWindow();

private slots:
    void on_addButton_clicked();

    void on_editButton_clicked();

private:
    Ui::StartWindow *ui;
    AddWordsWindow add_pair_form;
    DictionaryWindow dictionary_form;
    DataBase *db;
};

#endif // STARTWINDOW_H
