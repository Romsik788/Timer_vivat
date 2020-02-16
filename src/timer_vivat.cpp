#include "timer_vivat.h"
#include "ui_timer_vivat.h"
#include "QMessageBox"
#include <windows.h>
#include "shellapi.h"
#include "QPushButton"
#include "QKeyEvent"
#include "QFontDatabase"
#include "QFont"
#include "setting.h"
#include "ui_setting.h"
#include <mmsystem.h>
#include <filereader.h>
using namespace std;
Timer_vivat::Timer_vivat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Timer_vivat)
{
    ui->setupUi(this);
    ui->label->setText("60.0");
    ui->label_2->setVisible(false);
    int id = QFontDatabase::addApplicationFont("res\\fonts\\Crystal.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont f(family);
    ui->label->setFont(QFont(f));
    ui->label->setStyleSheet("font-size: 160px; color: olive");
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
}
static bool sixtySec = true;
static bool twentySec = false;
static bool falsestart = false, keyPress = false, mainTimer = false;
Timer_vivat::~Timer_vivat()
{
    delete ui;
}
static double mSecondsToEnd, mSecondsDelay;
static int red, black;
void Timer_vivat::on_pushButton_2_clicked()
{
    timer->stop();
    QKeySequence seqRed = QKeySequence(readVal("red").c_str());
    QKeySequence seqBlack = QKeySequence(readVal("black").c_str());
    red = seqRed[0];
    black = seqBlack[0];
    ui->label->setText("60.0");
    ui->label_2->setVisible(false);
    mSecondsToEnd=600;
    mSecondsDelay=10;
    ui->pushButton->setEnabled(true);
    falsestart = true;
    twentySec = false;
    sixtySec = true;
    keyPress = false;
}
void Timer_vivat::on_pushButton_clicked()
{
    PlaySound(TEXT ("res\\sounds\\Start.wav"), nullptr, SND_FILENAME | SND_ASYNC);
    mainTimer = true;
    timer->start(100);
    ui->pushButton->setEnabled(false);
    ui->label_2->setVisible(false);
    falsestart = false;
    keyPress = false;
}
void Timer_vivat::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == red && !keyPress) //red button
    {
        if(falsestart){
            PlaySound(TEXT ("res\\sounds\\falsestart.wav"), nullptr, SND_FILENAME | SND_ASYNC);
            ui->pushButton->setEnabled(false);
            ui->label_2->setText("Фальстарт червона");
            ui->label_2->setStyleSheet(QString("font-size: 71px; color: red"));
            ui->label_2->setVisible(true);
            mainTimer = false;
            timer->start(100);
        } else
        if(twentySec){
            ui->label->setText("0");
            ui->label_2->setText("Натиснута червона кнопка");
            ui->label_2->setStyleSheet(QString("font-size: 65px; color: red"));
            ui->label_2->setVisible(true);
            mSecondsToEnd=0;
            ui->pushButton->setEnabled(false);
            twentySec = false;
        } else
        if(sixtySec)
        {
            PlaySound(TEXT ("res\\sounds\\Button.wav"), nullptr, SND_FILENAME | SND_ASYNC);
            ui->label_2->setText("Натиснута червона кнопка");
            ui->label_2->setStyleSheet(QString("font-size: 65px; color: red"));
            ui->label_2->setVisible(true);
            mSecondsToEnd=200;
            timer->stop();
            ui->pushButton->setEnabled(false);
            ui->label->setText("20.0");
            twentySec=true;
            sixtySec = false;
            keyPress = true;
            mainTimer = false;
            timer->start(100);
        }
        red=0;
    }
    if(event->key() == black && !keyPress) // black button
    {
        if(falsestart){
            PlaySound(TEXT ("res\\sounds\\falsestart.wav"), nullptr, SND_FILENAME | SND_ASYNC);
            ui->pushButton->setEnabled(false);
            ui->label_2->setText("Фальстарт чорна");
            ui->label_2->setStyleSheet(QString("font-size: 71px; color: black"));
            ui->label_2->setVisible(true);
            mainTimer = false;
            timer->start(100);
        } else
        if(twentySec){
            ui->label->setText("0");
            ui->label_2->setText("Натиснута чорна кнопка");
            ui->label_2->setStyleSheet(QString("font-size: 71px; color: black"));
            ui->label_2->setVisible(true);
            mSecondsToEnd=0;
            ui->pushButton->setEnabled(false);
            twentySec = false;
        } else
        if(sixtySec)
        {
            PlaySound(TEXT ("res\\sounds\\Button.wav"), nullptr, SND_FILENAME | SND_ASYNC);
            ui->label_2->setText("Натиснута чорна кнопка");
            ui->label_2->setStyleSheet(QString("font-size: 71px; color: black"));
            ui->label_2->setVisible(true);
            timer->stop();
            ui->pushButton->setEnabled(false);
            mSecondsToEnd=200;
            ui->label->setText("20.0");
            twentySec=true;
            sixtySec = false;
            keyPress = true;
            mainTimer = false;
            timer->start(100);
        }
        black = 0;
    }
}
void Timer_vivat::slotTimerAlarm()
{
    if (mainTimer)
    {
    --mSecondsToEnd;
        if (mSecondsToEnd >= 0)
        {
            if (mSecondsToEnd == 50) PlaySound(TEXT ("res\\sounds\\beep.wav"), nullptr, SND_FILENAME | SND_ASYNC);
            if (mSecondsToEnd == 40) PlaySound(TEXT ("res\\sounds\\beep.wav"), nullptr, SND_FILENAME | SND_ASYNC);
            if (mSecondsToEnd == 30) PlaySound(TEXT ("res\\sounds\\beep.wav"), nullptr, SND_FILENAME | SND_ASYNC);
            if (mSecondsToEnd == 20) PlaySound(TEXT ("res\\sounds\\beep.wav"), nullptr, SND_FILENAME | SND_ASYNC);
            if (mSecondsToEnd == 10) PlaySound(TEXT ("res\\sounds\\beep.wav"), nullptr, SND_FILENAME | SND_ASYNC);
            QString time = QString::number(mSecondsToEnd / 10);
            ui->label->setText(time);
        }
        else
        {
            PlaySound(TEXT ("res\\sounds\\timeout.wav"), nullptr, SND_FILENAME | SND_ASYNC);
            if (red != 0 || black != 0)
            {
            ui->label_2->setText("Час вийшов!");
            ui->label_2->setStyleSheet(QString("font-size: 71px; color: black"));
            ui->label_2->setVisible(true);
            }
            timer->stop();
            ui->pushButton->setEnabled(false);
        }
    }
    if(!mainTimer)
    {
     --mSecondsDelay;
        if (mSecondsDelay >= 0)
        {
            QString time = QString::number(mSecondsToEnd / 10);
        }
        else
        {
            timer->stop();
            mSecondsDelay = 10;
            ui->pushButton->setEnabled(true);
        }
    }
}

void Timer_vivat::on_action_3_triggered()
{
    QApplication::quit();
}

void Timer_vivat::on_action_2_triggered()
{
    QMessageBox::about(this, "Про програму", "Timer_vivat Версія 1.0\nПрограма для гри \"Віват, інтелект!\"\nПо всіх питаннях пишіть на rmalenko4@gmail.com");
}

void Timer_vivat::on_action_4_triggered()
{
    ShellExecute(nullptr, nullptr, L"WINWORD.EXE", L"res\\vivat.doc", nullptr, SW_SHOW);
}

void Timer_vivat::on_action_triggered()
{
    setting *w = new setting;
    w->show();
}
