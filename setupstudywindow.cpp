#include "setupstudywindow.h"
#include "ui_setupstudywindow.h"

#include "settings.h"
#include "studywindow.h"

#include <QMessageBox>
#include <QStandardItemModel>


SetupStudyWindow::SetupStudyWindow(DataBase *_db, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetupStudyWindow)
    , db(_db)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    Configurator &config = Configurator::Instance();
    ui->wordsCountBox->setMinimum(config.GetWordsCountPerSession());
    ui->wordsCountBox->setValue(config.GetWordsCountPerSession());
    ui->allTopicsCheckBox->setChecked(true);
    ui->topicListView->setVisible(false);

    QSet<QString> topics;
    db->GetTopicsList(topics);
    QStandardItemModel *model = new QStandardItemModel(topics.size(), 1);
    int rowNumber = 0;
    for (const auto& topic : topics) {
        QStandardItem *item = new QStandardItem(topic);
        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item->setData(Qt::Unchecked, Qt::CheckStateRole);
        model->setItem(rowNumber, 0, item);
        ++rowNumber;
    }
    ui->topicListView->setModel(model);
}

SetupStudyWindow::~SetupStudyWindow() {
    delete ui;
}

void SetupStudyWindow::on_continueButton_clicked() {
    bool ruToDeDirection = ui->ruToDeButton->isChecked();
    size_t wordsPerSession = ui->wordsCountBox->value();
    QStringList topicsList;
    if (ui->allTopicsCheckBox->isChecked()) {
        topicsList << "ALLES";
    } else {
        QStandardItemModel *model = static_cast<QStandardItemModel*>(ui->topicListView->model());
        for (int rowNumber = 0; rowNumber < model->rowCount(); ++rowNumber) {
            QStandardItem *curItem = model->item(rowNumber, 0);
            if (curItem->checkState() == Qt::Checked) {
                topicsList << "'" + curItem->text() + "'";
            }
        }
    }
    if (topicsList.size() == 0) {
        QMessageBox msgBox;
        msgBox.setText(QString("You should chose at least one topic!"));
        msgBox.exec();
        return;
    }

    this->setVisible(false);
    StudyWindow study_form(db, ruToDeDirection, wordsPerSession, topicsList);
    study_form.Exec();
    close();
}

void SetupStudyWindow::on_allTopicsCheckBox_clicked(bool checked) {
    if (checked) {
        ui->topicListView->setVisible(false);
    } else {
        ui->topicListView->setVisible(true);
    }
}
