#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

class Configurator {
public:
    static Configurator& Instance()
    {
        static Configurator config;
        return config;
    }

public:
    void LoadConfigFromFile(const QString &path);
    void SaveConfigToFile();

    int GetPeriodBetweenTrainigs() { return periodBetweenTrainings; }
    void SetPeriodBetweenTrainigs(int period) { periodBetweenTrainings = period; }

    int GetWordsCountPerTraining() { return wordsPerTraining; }
    void SetWordsCountPerTraining(int count) { wordsPerTraining = count; }

    int GetSuccessRate() { return successRate; }
    void SetSuccessRate(int rate) { successRate = rate; }

    int GetPercentOfOldWordsPerTraining() { return percentageOfOldWords; }
    void SetPercentOfOldWordsPerTraining(int percent) { percentageOfOldWords = percent; }

private:
    int periodBetweenTrainings;
    int wordsPerTraining;
    int successRate;
    int percentageOfOldWords;
    QString configPath;

private:
    Configurator();
    ~Configurator() {}

    Configurator(Configurator const&) = delete;
    Configurator& operator= (Configurator const&) = delete;
};


namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    void Show();

private slots:
    void on_saveButton_clicked();

private:
    Ui::Settings *ui;
};
#endif // SETTINGS_H
