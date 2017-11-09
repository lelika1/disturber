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
        in >> periodBetweenSessions;
        in >> wordsPerSession;
        in >> successRate;
        in >> percentageOfOldWords;
        in.close();
    } else {
        SaveConfigToFile();
    }
}

void Configurator::SaveConfigToFile() {
    std::ofstream out(configPath.toStdString());
    out << periodBetweenSessions << std::endl;
    out << wordsPerSession << std::endl;
    out << successRate << std::endl;
    out << percentageOfOldWords << std::endl;
    out.close();
}

Configurator::Configurator()
    : periodBetweenSessions(60)
    , wordsPerSession(10)
    , successRate(3)
    , percentageOfOldWords(30)
{}


Settings::Settings(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
}

Settings::~Settings() {
    delete ui;
}

void Settings::Exec() {
    Configurator &config = Configurator::Instance();
    ui->timePeriodBox->setValue(config.GetPeriodBetweenSessions());
    ui->wordsCountBox->setValue(config.GetWordsCountPerSession());
    ui->successRateBox->setValue(config.GetSuccessRate());
    ui->oldWordsPercentageBox->setValue(config.GetPercentOfOldWordsPerSession());
    exec();
}

void Settings::on_saveButton_clicked() {
    Configurator &config = Configurator::Instance();
    config.SetPeriodBetweenSessions(static_cast<size_t>(ui->timePeriodBox->value()));
    config.SetWordsCountPerSession(static_cast<size_t>(ui->wordsCountBox->value()));
    config.SetSuccessRate(static_cast<size_t>(ui->successRateBox->value()));
    config.SetPercentOfOldWordsPerSession(static_cast<size_t>(ui->oldWordsPercentageBox->value()));
    config.SaveConfigToFile();
    close();
}
