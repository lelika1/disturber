#include "studywindow.h"
#include "ui_studywindow.h"
#include "studysession.h"
#include "resultswindow.h"

#include <QMessageBox>

StudyWindow::StudyWindow(DataBase *db, bool ruToDeDirection, size_t wordsPerSession, const QStringList &topicsList, QDialog *parent)
    : QDialog(parent)
    , ui(new Ui::StudyWindow)
    , db_(db)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    this->setWindowTitle(this->windowTitle() + ": " + topicsList.join("|"));
    session_.reset(new StudySession(db_, ruToDeDirection, wordsPerSession, topicsList));
}

StudyWindow::~StudyWindow() {
    session_ = nullptr;
    delete ui;
}

void StudyWindow::Exec() {
    if (UpdateUI()) {
        this->exec();
        return;
    }

    QMessageBox msgBox;
    msgBox.setText(QString("Dictionary is currently empty!"));
    msgBox.exec();
}

void StudyWindow::on_checkButton_clicked() {
    QString currentAnswer = ui->toWordEdit->text().simplified();

    QString correctAnswer;
    if (!session_->SubmitAnswer(currentAnswer, correctAnswer)) {
        ui->toWordEdit->setFocusOnEdit();
        QMessageBox msgBox;
        msgBox.setText(QString("Wrong! Correct translation: %1").arg(correctAnswer));
        msgBox.exec();
        return;
    }
    if (UpdateUI()) {
        return;
    }

    hide();
    ResultsWindow resultWindow(this);
    resultWindow.Exec(session_.get());
    // TODO(): save session
    session_ = nullptr;
    close();
}

void StudyWindow::keyPressEvent(QKeyEvent *event) {
    if ((event->key() == Qt::Key_Enter) || (event->key() == Qt::Key_Return)) {
        ui->checkButton->clicked();
    } else {
        QWidget::keyPressEvent(event);
    }
}

bool StudyWindow::UpdateUI() {
    bool ruToDe = session_->GetRuToDe();
    const QString *word = session_->GetWord();
    if (word == nullptr) {
        return false;
    }

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

