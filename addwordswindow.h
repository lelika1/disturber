#ifndef ADDWORDSWINDOW_H
#define ADDWORDSWINDOW_H

#include "database.h"

#include <QKeyEvent>
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

    void Show();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_addButton_clicked();

private:
    Ui::AddWordsWindow *ui;
    DataBase *db;
};

#endif // ADDWORDSWINDOW_H
