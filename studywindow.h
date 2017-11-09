#ifndef STUDYWINDOW_H
#define STUDYWINDOW_H

#include "database.h"
#include "teacher.h"
#include <memory>

#include <QKeyEvent>
#include <QDialog>

namespace Ui {
class StudyWindow;
}

class StudyWindow : public QDialog
{
    Q_OBJECT

public:
    StudyWindow(DataBase *db, bool ruToDeDirection, size_t wordsPerTraining, const QStringList &topicsList, QDialog *parent = 0);
    ~StudyWindow();

    void Exec();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_checkButton_clicked();

private:
    // Returns true if there is at least one pair of words left for studying.
    bool UpdateUI();

private:
    Ui::StudyWindow *ui;
    DataBase *db_;

    std::unique_ptr<Teacher> teacher_;
};

#endif // STUDYWINDOW_H
