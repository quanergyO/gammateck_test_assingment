#include "infowidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>

InfoWidget::InfoWidget(QWidget *parent)
    : QWidget(parent)
{
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(6);
    tableWidget->setHorizontalHeaderLabels({"ID", "Type", "Position", "Region", "Hide", "Remove"});
    tableWidget->horizontalHeader()->setStretchLastSection(true);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    tableWidget->setSelectionMode(QTableWidget::NoSelection);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tableWidget);
    setLayout(layout);
}

InfoWidget::~InfoWidget()
{
}

void InfoWidget::addFigureInfo(const Figure *figure)
{
    std::cout << "addFigureInfo" << std::endl;
    int row = tableWidget->rowCount();
    tableWidget->insertRow(row);
    QTableWidgetItem *idItem = new QTableWidgetItem(QString::number(row));
    QTableWidgetItem *typeItem = new QTableWidgetItem(getFigureType(figure));
    QTableWidgetItem *positionItem = new QTableWidgetItem(getPositionString(figure));
    QTableWidgetItem *regionItem = new QTableWidgetItem(getRegionString(figure));
    std::cout << idItem->text().toStdString() << ' ' << typeItem->text().toStdString() << ' '
              << positionItem->text().toStdString() << ' ' << regionItem->text().toStdString() << std::endl;

    tableWidget->setItem(row, 0, idItem);
    tableWidget->setItem(row, 1, typeItem);
    tableWidget->setItem(row, 2, positionItem);
    tableWidget->setItem(row, 3, regionItem);

    QPushButton *deleteButton = new QPushButton("Удалить");
    deleteButton->setFlat(true);
    connect(deleteButton, &QPushButton::clicked, this, [this, row]() {
        std::cout << "deleted row: " << row << std::endl;
        emit deleteFigure(row);
        tableWidget->removeRow(row);
    });
    tableWidget->setCellWidget(row, 5, deleteButton);
}

QString InfoWidget::getPositionString(const Figure *figure)
{
    std::cout << "getPositionString" << std::endl;
    static QString position = "";
    switch (figure->type()) {
    case FigureType::FigureType_Rect: {
        auto data = (const RectData *)figure;
        position = QString("(%1, %2)").arg(data->x()).arg(data->y());
        break;
    }
    case FigureType::FigureType_Ellipse: {
        auto data = (const EllipseData *)figure->payload();
        position = QString("(%1, %2)").arg(data->x()).arg(data->y());
        break;
    }
    case FigureType::FigureType_Triangle: {
        auto data = (const TriangleData *)figure->payload();
        position = QString("(%1, %2)").arg(data->x1()).arg(data->y1());
        break;
    }
    case FigureType::FigureType_Line: {
        auto data = (const LineData *)figure->payload();
        position = QString("(%1, %2)").arg(data->x1()).arg(data->y1());
        break;
    }
    }
    std::cout << "END" << std::endl;
    return position;
}

QString InfoWidget::getRegionString(const Figure *figure)
{
    std::cout << "getRegionString" << std::endl;
    switch (figure->type()) {
    case FigureType::FigureType_Rect: {
        auto data = (const RectData *)figure->payload();
        return QString("(%1, %2)").arg(data->width()).arg(data->height());
    }
    case FigureType::FigureType_Ellipse: {
        auto data = (const EllipseData *)figure->payload();
        return QString("(%1, %2)").arg(data->r1()).arg(data->r2());
    }
    case FigureType::FigureType_Triangle: {
        auto data = (const TriangleData *)figure->payload();
        return QString("(%1, %2, %3)").arg(data->x1()).arg(data->x2()).arg(data->x3());
    }
    case FigureType::FigureType_Line: {
        auto data = (const LineData *)figure->payload();
        return QString("(%1, %2)").arg(data->x1()).arg(data->y1());
    }
    default:
        return "";
    }
}

QString InfoWidget::getFigureType(const Figure *figure)
{
    switch (figure->type()) {
    case FigureType::FigureType_Rect: {
        return QString("Rect");
    }
    case FigureType::FigureType_Ellipse: {
        return QString("Ellipse");
    }
    case FigureType::FigureType_Triangle: {
        return QString("Triangle");
    }
    case FigureType::FigureType_Line: {
        return QString("Line");
    }
    default:
        return "";
    }
}
