#include "studywindow.h"
#include "ui_studywindow.h"

StudyWindow::StudyWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudyWindow)
{
    ui->setupUi(this);
    ui->deWordEdit->setFocus();
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint );
}

StudyWindow::~StudyWindow()
{
    delete ui;
}

void StudyWindow::on_printAeButton_clicked()
{
    if (ui->deWordEdit->isEnabled()) {
        ui->deWordEdit->insert(ui->printAeButton->text().simplified());
        ui->deWordEdit->setFocus();
    }
}

void StudyWindow::on_printOeButton_clicked()
{
    if (ui->deWordEdit->isEnabled()) {
        ui->deWordEdit->insert(ui->printOeButton->text().simplified());
        ui->deWordEdit->setFocus();
    }
}

void StudyWindow::on_printUeButton_clicked()
{
    if (ui->deWordEdit->isEnabled()) {
        ui->deWordEdit->insert(ui->printUeButton->text().simplified());
        ui->deWordEdit->setFocus();
    }
}

void StudyWindow::on_printSsButton_clicked()
{
    if (ui->deWordEdit->isEnabled()) {
        ui->deWordEdit->insert(ui->printSsButton->text().simplified());
        ui->deWordEdit->setFocus();
    }
}

void StudyWindow::on_closeButton_clicked()
{

}

void StudyWindow::on_checkButton_clicked()
{

}

void StudyWindow::on_ru_deButton_clicked()
{
    ui->ruWordEdit->setEnabled(false);
    ui->deWordEdit->setEnabled(true);
    ui->deWordEdit->setFocus();

    ui->printAeButton->setEnabled(true);
    ui->printUeButton->setEnabled(true);
    ui->printOeButton->setEnabled(true);
    ui->printSsButton->setEnabled(true);
}

void StudyWindow::on_de_ruButton_clicked()
{
    ui->ruWordEdit->setEnabled(true);
    ui->deWordEdit->setEnabled(false);
    ui->ruWordEdit->setFocus();

    ui->printAeButton->setEnabled(false);
    ui->printUeButton->setEnabled(false);
    ui->printOeButton->setEnabled(false);
    ui->printSsButton->setEnabled(false);
}

