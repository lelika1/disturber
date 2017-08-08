#include "startwindow.h"
#include "ui_startwindow.h"

#include <QApplication>
#include <QDesktopWidget>


StartWindow::StartWindow(DataBase *_db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
    , add_pair_form(_db)
    , dictionary_form(_db)
    , db(_db)
{
    ui->setupUi(this);
    //add_pair_form = new AddWordsWindow();
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_addButton_clicked()
{
    QRect wGeom = this->geometry();
    add_pair_form.setGeometry(QRect(wGeom.x(), wGeom.y(),
                                    add_pair_form.geometry().width(),
                                    add_pair_form.geometry().height()));
    add_pair_form.show();
}

void StartWindow::on_editButton_clicked()
{
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
//    QRect wGeom = this->geometry();
    dictionary_form.setGeometry(screenGeometry);
    dictionary_form.ShowTable();
}

void StartWindow::on_studyButton_clicked()
{
    QRect wGeom = this->geometry();
    study_form.setGeometry(QRect(wGeom.x(), wGeom.y(),
                           study_form.geometry().width(),
                           study_form.geometry().height()));
    study_form.show();
}
