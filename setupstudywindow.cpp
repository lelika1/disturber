#include "setupstudywindow.h"
#include "ui_setupstudywindow.h"

#include "settings.h"
#include "studywindow.h"


SetupStudyWindow::SetupStudyWindow(DataBase *_db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetupStudyWindow)
    , db(_db)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    Configurator &config = Configurator::Instance();
    ui->wordsCountBox->setMinimum(config.GetWordsCountPerTraining());
    ui->wordsCountBox->setValue(config.GetWordsCountPerTraining());
    QSet<QString> topics;
    db->GetTopicsList(topics);
    ui->topicComboBox->addItem("ALLES");
    for (const auto& topic : topics) {
        ui->topicComboBox->addItem(topic);
    }
}

SetupStudyWindow::~SetupStudyWindow() {
    delete ui;
}

void SetupStudyWindow::Exec() {
    QSortFilterProxyModel *topicProxy = new QSortFilterProxyModel(ui->topicComboBox);
    topicProxy->setSourceModel(ui->topicComboBox->model());
    ui->topicComboBox->model()->setParent(topicProxy);
    ui->topicComboBox->setModel(topicProxy);
    ui->topicComboBox->model()->sort(0);
    this->exec();
}

void SetupStudyWindow::on_continueButton_clicked() {
    bool ruToDeDirection = ui->ruToDeButton->isChecked();
    size_t wordsPerTraining = ui->wordsCountBox->value();
    QString topic = ui->topicComboBox->currentText();
    this->setVisible(false);
    StudyWindow study_form(db, ruToDeDirection, wordsPerTraining, topic);
    study_form.Exec();
    close();
}
