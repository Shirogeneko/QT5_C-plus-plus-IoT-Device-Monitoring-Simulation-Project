#include "warningwindow.h"
#include "ui_warningwindow.h"

WarningWindow::WarningWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WarningWindow)
{
    ui->setupUi(this);
}

WarningWindow::~WarningWindow()
{
    delete ui;
}

void WarningWindow::init()
{
    boolOpen = true;
}

bool WarningWindow::isOpen()
{
    return boolOpen;
}

void WarningWindow::setText(QString text)
{
    ui->label->setText(text);
}

void WarningWindow::on_pushButton_clicked()
{
    boolOpen = false;
    this->close();
}
