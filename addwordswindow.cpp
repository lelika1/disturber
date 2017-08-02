#include "addwordswindow.h"
#include "ui_addwordswindow.h"

#include <QMessageBox>

AddWordsWindow::AddWordsWindow(DataBase *_db, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddWordsWindow)
    , db(_db)
{
    ui->setupUi(this);
}

AddWordsWindow::~AddWordsWindow() {
    delete ui;
}


void AddWordsWindow::on_addButton_clicked() {
    QString ru_word = ui->ruWordEdit->text().simplified();
    QString de_word = ui->deWordEdit->text().simplified();

    if (ru_word.size() == 0 || de_word.size() == 0) {
        QMessageBox msgBox;
        msgBox.setText("All words should be not empty!");
        msgBox.exec();
    } else {
        db->AddEntry(ru_word.toStdString().c_str(), de_word.toStdString().c_str());
        ui->ruWordEdit->setText("");
        ui->deWordEdit->setText("");
    }
}

void AddWordsWindow::on_printAeButton_clicked()
{
    ui->deWordEdit->insert(ui->printAeButton->text().simplified());
    ui->deWordEdit->setFocus();
}

void AddWordsWindow::on_printOeButton_clicked()
{
    ui->deWordEdit->insert(ui->printOeButton->text().simplified());
    ui->deWordEdit->setFocus();
}

void AddWordsWindow::on_printUeButton_clicked()
{
    ui->deWordEdit->insert(ui->printUeButton->text().simplified());
    ui->deWordEdit->setFocus();
}

void AddWordsWindow::on_printSsButton_clicked()
{
    ui->deWordEdit->insert(ui->printSsButton->text().simplified());
    ui->deWordEdit->setFocus();
}
