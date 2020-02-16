#include "setting.h"
#include "ui_setting.h"
#include <QPainter>
#include <QMessageBox>
#include "filereader.h"
using namespace std;
static QString red, black;
setting::setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::setting)
{
    red = QString::fromStdString(readVal("red"));
    black = QString::fromStdString(readVal("black"));
    ui->setupUi(this);
    ui->lineEdit->setText(QString("%1").arg(red));
    ui->lineEdit_2->setText(QString("%1").arg(black));
}
setting::~setting()
{
    delete ui;
}
void setting::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter_2(this);
    painter_2.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::FlatCap));
    painter_2.setBrush(QBrush(Qt::black, Qt::SolidPattern));
    painter_2.drawRect(174, 40, 31, 22);
    QPainter painter(this);
    painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap));
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawRect(174, 6, 31, 22);
}
static bool textWriteR = false, textWriteB = false;
void setting::on_lineEdit_textEdited()
{
    red = ui->lineEdit->text();
    ui->lineEdit->clear();
    red = red[1].toUpper();
    ui->lineEdit->setText(red);
    textWriteR = true;
}

void setting::on_lineEdit_2_textEdited()
{
    black = ui->lineEdit_2->text();
    ui->lineEdit_2->clear();
    black = black[1].toUpper();
    ui->lineEdit_2->setText(black);
    textWriteB = true;
}
void setting::closeEvent(QCloseEvent *event)
{
    if ((textWriteR) || (textWriteB))
    {
        saveSetting("red", red);
        saveSetting("black", black);
    }
}
