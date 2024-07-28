#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "renderwidget.h"
#include "infowidget.h"
#include "datareceiver.h"
#include "api_generated.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new FigureModel(this))
    , renderWidget(new RenderWidget(model, this))
    , infoWidget(new InfoWidget(model, this))
    , dataReceiver(new DataReceiver(this))
{
    ui->setupUi(this);
    setCentralWidget(renderWidget);

    createMenu();

    connect(dataReceiver, &DataReceiver::figureReceived, this, &MainWindow::onFigureReceived);
    dataReceiver->startReceiving();
}

MainWindow::~MainWindow()
{
    dataReceiver->stopReceiving();
    delete ui;
}

void MainWindow::onFigureReceived(const QByteArray &data)
{
    auto figure = flatbuffers::GetRoot<Figure>(data.constData());

    if (figure != nullptr) {
        model->addFigure(figure);
    }

}

void MainWindow::createMenu()
{
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *viewMenu = menuBar->addMenu(tr("Меню"));

    QAction *renderAction = viewMenu->addAction(tr("Отрисовка"));
    connect(renderAction, &QAction::triggered, [this]() {
        setCentralWidget(renderWidget);
    });

    QAction *infoAction = viewMenu->addAction(tr("Информация"));
    connect(infoAction, &QAction::triggered, [this]() {
        setCentralWidget(infoWidget);
    });

    setMenuBar(menuBar);
}
