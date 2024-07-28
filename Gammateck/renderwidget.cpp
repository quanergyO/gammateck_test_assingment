#include "renderwidget.h"
#include <QPainter>

RenderWidget::RenderWidget(FigureModel* model, QWidget *parent)
    : QWidget(parent)
    , model(model)
{
}

RenderWidget::~RenderWidget()
{

}

void RenderWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    std::cout << "HELLO" << std::endl;

    for (int row = 0; row < model->rowCount(); ++row) {
        const DAO::Types::IFigure* figure = model->getFigure(row);

        if (const DAO::Types::Rect* rect = dynamic_cast<const DAO::Types::Rect*>(figure)) {
            drawRect(painter, rect);
        }
        else if (const DAO::Types::Ellipse* ellipse = dynamic_cast<const DAO::Types::Ellipse*>(figure)) {
            drawEllipse(painter, ellipse);
        }
        else if (const DAO::Types::Triangle* triangle = dynamic_cast<const DAO::Types::Triangle*>(figure)) {
            drawTriangle(painter, triangle);
        }
        else if (const DAO::Types::Line* line = dynamic_cast<const DAO::Types::Line*>(figure)) {
            drawLine(painter, line);
        }
    }
    std::cout << "END" << std::endl;
}

void RenderWidget::drawRect(QPainter &painter, const DAO::Types::Rect *data)
{
    painter.setBrush(QBrush(Qt::NoBrush));
    painter.setPen(QPen(QColor(data->getColorHex().c_str()), 2));
    painter.drawRect(QRect(data->getX(), data->getY(), data->getWidth(), data->getHeight()));
}

void RenderWidget::drawEllipse(QPainter &painter, const DAO::Types::Ellipse *data)
{
    painter.setBrush(QBrush(Qt::NoBrush));
    painter.setPen(QPen(QColor(data->getColorHex().c_str()), 2));
    painter.drawEllipse(QRect(data->getX(), data->getY(), data->getR1()*2, data->getR2()*2));
}

void RenderWidget::drawTriangle(QPainter &painter, const DAO::Types::Triangle *data)
{
    painter.setBrush(QBrush(Qt::NoBrush));
    painter.setPen(QPen(QColor(data->getColorHex().c_str()), 2));
    QPoint points[] = {QPoint(data->getX1(), data->getY1()), QPoint(data->getX2(), data->getY2()), QPoint(data->getX3(), data->getY3())};
    painter.drawPolygon(points, 3);
}

void RenderWidget::drawLine(QPainter &painter, const DAO::Types::Line *data)
{
    painter.setBrush(QBrush(Qt::NoBrush));
    painter.setPen(QPen(QColor(data->getColorHex().c_str()), 2));
    painter.drawLine(QPoint(data->getX1(), data->getY1()), QPoint(data->getX2(), data->getY2()));
}
