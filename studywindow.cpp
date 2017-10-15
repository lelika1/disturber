#include "studywindow.h"
#include "ui_studywindow.h"

#include <QMessageBox>

StudyWindow::StudyWindow(DataBase *db, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudyWindow)
    , ruToDeDirection(true)
    , teacher(db)
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

    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint );
}

StudyWindow::~StudyWindow()
{
    delete ui;
}

void StudyWindow::Show() {
    if (!teacher.InitStudy()) {
        QMessageBox msgBox;
        msgBox.setText(QString("Dictionary is currently empty!"));
        msgBox.exec();
    } else {
        QString originalWord;
        teacher.GetNewPair(ruToDeDirection, originalWord);
        ui->fromWordLabel->setText(originalWord);
        ui->toWordEdit->setText("");
        this->show();
    }
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

void StudyWindow::on_checkButton_clicked()
{
    QString correctAnswer;
    if (!teacher.CheckResult(ruToDeDirection, ui->toWordEdit->text().simplified(), correctAnswer)) {
        QMessageBox msgBox;
        msgBox.setText(QString("Wrong! Correct translation: %1").arg(correctAnswer));
        msgBox.exec();
    } else {
        QString originalWord;
        if (!teacher.GetNewPair(ruToDeDirection, originalWord)) {
            QMessageBox msgBox;
            msgBox.setText(QString("Words per current study finished!"));
            msgBox.exec();
            teacher.UpdateDBAfterStudy();
            close();
            return;
        }
        ui->fromWordLabel->setText(originalWord);
    }

    ui->toWordEdit->setText("");
}

void StudyWindow::on_ru_deButton_clicked()
{
    ruToDeDirection = true;
    QString originalWord;
    if (!teacher.GetNewPair(ruToDeDirection, originalWord)) {
        QMessageBox msgBox;
        msgBox.setText(QString("Words per current study finished!"));
        msgBox.exec();
        teacher.UpdateDBAfterStudy();
        close();
        return;
    }
    ui->fromWordLabel->setText(originalWord);
    ui->toWordEdit->setText("");

    ui->toWordEdit->setFocus();
    ui->fromLabel->setText("Russian word");
    ui->toLabel->setText("German word");

    ui->printAeButton->setEnabled(true);
    ui->printUeButton->setEnabled(true);
    ui->printOeButton->setEnabled(true);
    ui->printSsButton->setEnabled(true);
}

void StudyWindow::on_de_ruButton_clicked()
{
    ruToDeDirection = false;
    QString originalWord;
    if (!teacher.GetNewPair(ruToDeDirection, originalWord)) {
        QMessageBox msgBox;
        msgBox.setText(QString("Words per current study finished!"));
        teacher.UpdateDBAfterStudy();
        msgBox.exec();
        close();
        return;
    }
    ui->fromWordLabel->setText(originalWord);
    ui->toWordEdit->setText("");

    ui->toWordEdit->setFocus();
    ui->fromLabel->setText("German word");
    ui->toLabel->setText("Russian word");

    ui->printAeButton->setEnabled(false);
    ui->printUeButton->setEnabled(false);
    ui->printOeButton->setEnabled(false);
    ui->printSsButton->setEnabled(false);
}

