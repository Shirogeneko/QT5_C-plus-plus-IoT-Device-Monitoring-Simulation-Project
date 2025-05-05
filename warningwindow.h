#ifndef WARNINGWINDOW_H
#define WARNINGWINDOW_H

#include <QDialog>

namespace Ui {
class WarningWindow;
}

class WarningWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WarningWindow(QWidget *parent = nullptr);
    ~WarningWindow();
    void setText(QString text);
    void init();
    bool isOpen();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WarningWindow *ui;
    bool boolOpen = false;;
};

#endif // WARNINGWINDOW_H
