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

private:
    Ui::DictionaryWindow *ui;
    DataBase *db;
};

#endif // DICTIONARYWINDOW_H
