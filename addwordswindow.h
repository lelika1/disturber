#ifndef ADDWORDSWINDOW_H
#define ADDWORDSWINDOW_H

#include "database.h"

#include <QKeyEvent>
#include <QDialog>


namespace Ui {
class AddWordsWindow;
}

class AddWordsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddWordsWindow(DataBase *_db, QDialog *parent = 0);
    ~AddWordsWindow();

    void Exec();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_addButton_clicked();

private:
    Ui::AddWordsWindow *ui;
    DataBase *db;
    QSet<QString> topics;
};

#endif // ADDWORDSWINDOW_H
