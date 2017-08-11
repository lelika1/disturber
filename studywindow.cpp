#include "studywindow.h"
#include "ui_studywindow.h"

StudyWindow::StudyWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudyWindow)
    , ruToDeDirection(true)
{
    ui->setupUi(this);

    ui->toWordEdit->setFocus();
    ui->fromLabel->setText("Russian word");
    ui->toLabel->setText("German word");

    ui->ru_deButton->setChecked(true);
    ui->de_ruButton->setChecked(false);

    ui->printAeButton->setEnabled(true);
    ui->printUeButton->setEnabled(true);
    ui->printOeButton->setEnabled(true);
    ui->printSsButton->setEnabled(true);

    ui->fromWordEdit->setText("русский -> немецкий");

    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint );
}

StudyWindow::~StudyWindow()
{
    delete ui;
}

void StudyWindow::on_printAeButton_clicked() {
    if (ruToDeDirection) {
        ui->toWordEdit->insert(ui->printAeButton->text().simplified());
        ui->toWordEdit->setFocus();
    }
}

void StudyWindow::on_printOeButton_clicked()
{
    if (ruToDeDirection) {
        ui->toWordEdit->insert(ui->printOeButton->text().simplified());
        ui->toWordEdit->setFocus();
    }
}

void StudyWindow::on_printUeButton_clicked()
{
    if (ruToDeDirection) {
        ui->toWordEdit->insert(ui->printUeButton->text().simplified());
        ui->toWordEdit->setFocus();
    }
}

void StudyWindow::on_printSsButton_clicked()
{
    if (ruToDeDirection) {
        ui->toWordEdit->insert(ui->printSsButton->text().simplified());
        ui->toWordEdit->setFocus();
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
    ruToDeDirection = true;

    ui->toWordEdit->setFocus();
    ui->fromLabel->setText("Russian word");
    ui->toLabel->setText("German word");

    ui->printAeButton->setEnabled(true);
    ui->printUeButton->setEnabled(true);
    ui->printOeButton->setEnabled(true);
    ui->printSsButton->setEnabled(true);

    ui->fromWordEdit->setText("русский -> немецкий");
}

void StudyWindow::on_de_ruButton_clicked()
{
    ruToDeDirection = false;

    ui->toWordEdit->setFocus();
    ui->fromLabel->setText("German word");
    ui->toLabel->setText("Russian word");

    ui->printAeButton->setEnabled(false);
    ui->printUeButton->setEnabled(false);
    ui->printOeButton->setEnabled(false);
    ui->printSsButton->setEnabled(false);

    ui->fromWordEdit->setText("deutsch -> russisch");
}

