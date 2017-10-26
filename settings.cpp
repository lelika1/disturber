#include "settings.h"
#include "ui_settings.h"

#include <QFileInfo>

#include <fstream>
#include <string>


void Configurator::LoadConfigFromFile(const QString &path) {
    configPath = path;
    QFileInfo checkFile(configPath);
    if (checkFile.exists() && checkFile.isFile()) {
        std::ifstream in(configPath.toStdString().c_str());
        in >> periodBetweenTrainings;
        in >> wordsPerTraining;
        in >> successRate;
        in >> percentageOfOldWords;
        in.close();
    } else {
        SaveConfigToFile();
    }
}

void Configurator::SaveConfigToFile() {
    std::ofstream out(configPath.toStdString());
    out << periodBetweenTrainings << std::endl;
    out << wordsPerTraining << std::endl;
    out << successRate << std::endl;
    out << percentageOfOldWords << std::endl;
    out.close();
}

Configurator::Configurator()
    : periodBetweenTrainings(60)
    , wordsPerTraining(10)
    , successRate(3)
    , percentageOfOldWords(30)
{}


Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings() {
    delete ui;
}

void Settings::Show() {
    Configurator &config = Configurator::Instance();
    ui->timePeriodBox->setValue(config.GetPeriodBetweenTrainigs());
    ui->wordsCountBox->setValue(config.GetWordsCountPerTraining());
    ui->successRateBox->setValue(config.GetSuccessRate());
    ui->oldWordsPercentageBox->setValue(config.GetPercentOfOldWordsPerTraining());
    show();
}

void Settings::on_saveButton_clicked() {
    Configurator &config = Configurator::Instance();
    config.SetPeriodBetweenTrainigs(static_cast<size_t>(ui->timePeriodBox->value()));
    config.SetWordsCountPerTraining(static_cast<size_t>(ui->wordsCountBox->value()));
    config.SetSuccessRate(static_cast<size_t>(ui->successRateBox->value()));
    config.SetPercentOfOldWordsPerTraining(static_cast<size_t>(ui->oldWordsPercentageBox->value()));
    config.SaveConfigToFile();
    close();
}
