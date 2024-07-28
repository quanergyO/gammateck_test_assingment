#include "renderwidget.h"
#include <QPainter>

RenderWidget::RenderWidget(FigureModel* model, QWidget *parent)
    : QWidget(parent)
    , model(model)
{
    connect(model, &FigureModel::dataChange, this, [this]() {
        update();
    });
    connect(model, &FigureModel::figuresMoved, this, [this]() {
        update();
    });
}

RenderWidget::~RenderWidget()
{

}

void RenderWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int row = 0; row < model->rowCount(); ++row) {
        const DAO::Types::IFigure* figure = model->getFigure(row);
        if (!figure->isVisible()) {
            continue;
        }

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
}

void RenderWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        for (int i = model->rowCount() - 1; i >= 0; --i) {
            const DAO::Types::IFigure* figure = model->getFigure(i);
            if (figure->isVisible() && figure->contains(event->pos())) {
                selectedFigureIndex = i;
                lastMousePos = event->pos();
                isDragging = true;
                break;
            }
        }
    }
}

void RenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging && selectedFigureIndex != -1) {
        QPoint delta = event->pos() - lastMousePos;
        model->moveFigure(selectedFigureIndex, delta.x(), delta.y());
        lastMousePos = event->pos();
        update();
    }
}

void RenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isDragging = false;
        selectedFigureIndex = -1;
    }
}

void RenderWidget::drawRect(QPainter &painter, const DAO::Types::Rect *data)
{
    painter.setBrush(QBrush(QColor(data->getColorHex().c_str())));
    painter.setPen(QPen(QColor(data->getColorHex().c_str()), 2));
    painter.drawRect(QRect(data->getX(), data->getY(), data->getWidth(), data->getHeight()));
}

void RenderWidget::drawEllipse(QPainter &painter, const DAO::Types::Ellipse *data)
{
    painter.setBrush(QBrush(QColor(data->getColorHex().c_str())));
    painter.setPen(QPen(QColor(data->getColorHex().c_str()), 2));
    painter.drawEllipse(QRect(data->getX(), data->getY(), data->getR1()*2, data->getR2()*2));
}

void RenderWidget::drawTriangle(QPainter &painter, const DAO::Types::Triangle *data)
{
    painter.setBrush(QBrush(QColor(data->getColorHex().c_str())));
    painter.setPen(QPen(QColor(data->getColorHex().c_str()), 2));
    QPoint points[] = {QPoint(data->getX1(), data->getY1()), QPoint(data->getX2(), data->getY2()), QPoint(data->getX3(), data->getY3())};
    painter.drawPolygon(points, 3);
}

void RenderWidget::drawLine(QPainter &painter, const DAO::Types::Line *data)
{
    painter.setBrush(QBrush(QColor(data->getColorHex().c_str())));
    painter.setPen(QPen(QColor(data->getColorHex().c_str()), 2));
    painter.drawLine(QPoint(data->getX1(), data->getY1()), QPoint(data->getX2(), data->getY2()));
}
