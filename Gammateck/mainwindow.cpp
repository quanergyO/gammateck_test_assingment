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
    , renderWidget(new RenderWidget(this))
    , infoWidget(new InfoWidget(this))
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
    auto test = GetFigure(data.constData());

    std::string isNull = (figure == nullptr) ? "null" : "not null";
    std::cout << "Deserialize " << isNull << std::endl;

    if (figure != nullptr) {
        renderWidget->addFigure(test);
        infoWidget->addFigureInfo(test);
    }

}

void MainWindow::createMenu()
{
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *viewMenu = menuBar->addMenu("Меню");

    QAction *renderAction = viewMenu->addAction("Отрисовка");
    connect(renderAction, &QAction::triggered, [this]() {
        setCentralWidget(renderWidget);
    });

    QAction *infoAction = viewMenu->addAction("Информация");
    connect(infoAction, &QAction::triggered, [this]() {
        setCentralWidget(infoWidget);
    });

    setMenuBar(menuBar);
}
