#ifndef TIMER_VIVAT_H
#define TIMER_VIVAT_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
namespace Ui {
class Timer_vivat;
}

class Timer_vivat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Timer_vivat(QWidget *parent = 0);
    ~Timer_vivat();
protected:
    void keyPressEvent(QKeyEvent *event);
private slots:
    void on_pushButton_clicked();
    void slotTimerAlarm();

    void on_action_3_triggered();

    void on_action_2_triggered();

    void on_action_4_triggered();

    void on_pushButton_2_clicked();

    void on_action_triggered();

private:
    Ui::Timer_vivat *ui;
    QTimer *timer;
};

#endif // TIMER_VIVAT_H
