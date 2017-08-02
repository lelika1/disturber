#ifndef STUDYWINDOW_H
#define STUDYWINDOW_H

#include <QWidget>

namespace Ui {
class StudyWindow;
}

class StudyWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudyWindow(QWidget *parent = 0);
    ~StudyWindow();

private slots:
    void on_printAeButton_clicked();

    void on_printOeButton_clicked();

    void on_printUeButton_clicked();

    void on_printSsButton_clicked();

    void on_closeButton_clicked();

    void on_checkButton_clicked();

    void on_ru_deButton_clicked();

    void on_de_ruButton_clicked();

private:
    Ui::StudyWindow *ui;
};

#endif // STUDYWINDOW_H
