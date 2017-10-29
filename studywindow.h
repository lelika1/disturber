#ifndef STUDYWINDOW_H
#define STUDYWINDOW_H

#include "database.h"
#include "teacher.h"
#include <memory>

#include <QKeyEvent>
#include <QWidget>

namespace Ui {
class StudyWindow;
}

class StudyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudyWindow(DataBase *db, QWidget *parent = 0);
    ~StudyWindow();

    void Show();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_checkButton_clicked();
    void on_ru_deButton_clicked();
    void on_de_ruButton_clicked();

private:
    // Returns true if there is at least one pair of words left for studying.
    bool UpdateUI();

private:
    Ui::StudyWindow *ui;
    DataBase *db_;

    std::unique_ptr<Teacher> teacher_;
};

#endif // STUDYWINDOW_H
