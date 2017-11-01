#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

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

private slots:
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::ResultsWindow *ui;
};

#endif // RESULTSWINDOW_H
