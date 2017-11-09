#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include <QAbstractTableModel>
#include <QDialog>

namespace Ui {
class ResultsWindow;
}

class ResultsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResultsWindow(QWidget *parent = 0);
    ~ResultsWindow();

    void Exec(QAbstractTableModel *model);

private slots:
    void on_submitBtn_clicked();

private:
    Ui::ResultsWindow *ui;
};

#endif // RESULTSWINDOW_H
