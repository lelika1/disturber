#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

class Configurator {
public:
    static Configurator& Instance()
    {
        static Configurator *config = new Configurator;
        return *config;
    }


    Configurator(Configurator const&) = delete;
    Configurator& operator= (Configurator const&) = delete;

public:
    void LoadConfigFromFile(const QString &path);
    void SaveConfigToFile();

    size_t GetPeriodBetweenSessions() { return periodBetweenSessions; }
    void SetPeriodBetweenSessions(size_t period) { periodBetweenSessions = period; }

    size_t GetWordsCountPerSession() { return wordsPerSession; }
    void SetWordsCountPerSession(size_t count) { wordsPerSession = count; }

    size_t GetSuccessRate() { return successRate; }
    void SetSuccessRate(size_t rate) { successRate = rate; }

    size_t GetPercentOfOldWordsPerSession() { return percentageOfOldWords; }
    void SetPercentOfOldWordsPerSession(size_t percent) { percentageOfOldWords = percent; }

    size_t GetSampleExpantion() { return sampleExpansion; }
    void SetSampleExpansion(size_t expansion) { sampleExpansion = expansion; }

private:
    size_t periodBetweenSessions;
    size_t wordsPerSession;
    size_t successRate;
    size_t percentageOfOldWords;
    size_t sampleExpansion;
    QString configPath;

private:
    Configurator();
};

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QDialog *parent = 0);
    ~Settings();

    void Exec();

private slots:
    void on_saveButton_clicked();

private:
    Ui::Settings *ui;
};
#endif // SETTINGS_H
