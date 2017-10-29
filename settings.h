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

    size_t GetPeriodBetweenTrainigs() { return periodBetweenTrainings; }
    void SetPeriodBetweenTrainigs(size_t period) { periodBetweenTrainings = period; }

    size_t GetWordsCountPerTraining() { return wordsPerTraining; }
    void SetWordsCountPerTraining(size_t count) { wordsPerTraining = count; }

    size_t GetSuccessRate() { return successRate; }
    void SetSuccessRate(size_t rate) { successRate = rate; }

    size_t GetPercentOfOldWordsPerTraining() { return percentageOfOldWords; }
    void SetPercentOfOldWordsPerTraining(size_t percent) { percentageOfOldWords = percent; }

private:
    size_t periodBetweenTrainings;
    size_t wordsPerTraining;
    size_t successRate;
    size_t percentageOfOldWords;
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
