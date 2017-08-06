#include "startwindow.h"
#include "ui_startwindow.h"

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
    QRect wGeom = this->geometry();
    dictionary_form.setGeometry(QRect(wGeom.x(), wGeom.y(),
                                dictionary_form.geometry().width(),
                                dictionary_form.geometry().height()));
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
