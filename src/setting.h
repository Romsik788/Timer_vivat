#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = 0);
    ~setting();
private:
    Ui::setting *ui;

protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_lineEdit_textEdited();
    void on_lineEdit_2_textEdited();
    void closeEvent(QCloseEvent *event);
};
#endif // SETTING_H
