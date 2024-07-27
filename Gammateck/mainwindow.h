#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "datareceiver.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class RenderWidget;
class InfoWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void createMenu();

private slots:
    void onFigureReceived(const QByteArray &data);


private:
    Ui::MainWindow *ui;
    RenderWidget *renderWidget;
    InfoWidget *infoWidget;
    DataReceiver *dataReceiver;
};
#endif // MAINWINDOW_H
