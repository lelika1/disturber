#include "studywindow.h"
#include "ui_studywindow.h"
#include "teacher.h"

#include <QMessageBox>

StudyWindow::StudyWindow(DataBase *db, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StudyWindow)
    , db_(db)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

StudyWindow::~StudyWindow() {
    delete ui;
}

void StudyWindow::Show() {
    teacher_.reset(new Teacher(db_));

    if (UpdateUI()) {
        this->show();
        return;
    }

    QMessageBox msgBox;
    msgBox.setText(QString("Dictionary is currently empty!"));
    msgBox.exec();
    teacher_ = nullptr;
}

void StudyWindow::on_checkButton_clicked() {
    QString currentAnswer = ui->toWordEdit->text().simplified();

    QString correctAnswer;
    if (!teacher_->CheckResult(currentAnswer, correctAnswer)) {
        ui->toWordEdit->setFocusOnEdit();
        QMessageBox msgBox;
        msgBox.setText(QString("Wrong! Correct translation: %1").arg(correctAnswer));
        msgBox.exec();
        return;
    }
    if (UpdateUI()) {
        return;
    }
    QMessageBox msgBox;
    msgBox.setText(QString("Words per current study finished!"));
    msgBox.exec();
    teacher_ = nullptr;
    close();
}

void StudyWindow::on_ru_deButton_clicked() {
    teacher_->SetRuToDe(true);
    UpdateUI();
}

void StudyWindow::on_de_ruButton_clicked() {
    teacher_->SetRuToDe(false);
    UpdateUI();
}

bool StudyWindow::UpdateUI() {
    bool ruToDe = teacher_->RuToDe();
    const QString *word = teacher_->GetWord();
    if (word == nullptr) {
        return false;
    }

    ui->ru_deButton->setChecked(ruToDe);
    ui->de_ruButton->setChecked(!ruToDe);
    ui->toWordEdit->setButtonsVisable(ruToDe);

    ui->fromWordLabel->setText(*word);
    ui->toWordEdit->setText("");
    ui->toWordEdit->setFocusOnEdit();

    if (ruToDe) {
        ui->fromLabel->setText("Russian word");
        ui->toLabel->setText("German word");
    } else {
        ui->fromLabel->setText("German word");
        ui->toLabel->setText("Russian word");
    }
    return true;
}

