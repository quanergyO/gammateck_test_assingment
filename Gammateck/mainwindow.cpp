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
    , stackedLayout(new QStackedLayout(this))
    , model(new FigureModel(this))
    , renderWidget(new RenderWidget(model, this))
    , infoWidget(new InfoWidget(model, this))
    , dataReceiver(new DataReceiver(this))
    , dataReceiverThread(new QThread(this))
{
    ui->setupUi(this);
    setCentralWidget(renderWidget);

    createMenu();



    dataReceiver->moveToThread(dataReceiverThread);

    connect(dataReceiverThread, &QThread::started, dataReceiver, &DataReceiver::startReceiving);
    connect(dataReceiver, &DataReceiver::figureReceived, this, &MainWindow::onFigureReceived);
    connect(dataReceiverThread, &QThread::finished, dataReceiverThread, &QThread::deleteLater);
    dataReceiverThread->start();
}

MainWindow::~MainWindow()
{
    dataReceiver->stopReceiving();
    dataReceiverThread->quit();
    dataReceiverThread->wait();
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
        stackedLayout->setCurrentIndex(0);
    });

    QAction *infoAction = viewMenu->addAction(tr("Информация"));
    connect(infoAction, &QAction::triggered, [this]() {
        stackedLayout->setCurrentIndex(1);
    });

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(renderWidget);
    stackedLayout->addWidget(infoWidget);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(stackedLayout);

    setCentralWidget(centralWidget);
    setMenuBar(menuBar);
}
