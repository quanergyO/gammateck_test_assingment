#include "renderwidget.h"
#include <QPainter>

RenderWidget::RenderWidget(QWidget *parent)
    : QWidget(parent)
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
    for (const Figure *figure : figures) {
        switch (figure->type()) {
        case FigureType::FigureType_Rect:
            drawRect(painter, (const RectData*)figure->payload());
            break;
        case FigureType::FigureType_Ellipse:
            drawEllipse(painter, (const EllipseData*)figure->payload());
            break;
        case FigureType::FigureType_Triangle:
            drawTriangle(painter, (const TriangleData *)figure->payload());
            break;
        case FigureType::FigureType_Line:
            drawLine(painter, (const LineData *)figure->payload());
            break;
        }
    }
}
void RenderWidget::addFigure(const Figure *figure)
{
    std::cout << "Added figure in List" << std::endl;
    figures.append(figure);
    update();
}

void RenderWidget::drawRect(QPainter &painter, const RectData *data)
{
    std::cout << "drawRect not implemented" << std::endl;
}

void RenderWidget::drawEllipse(QPainter &painter, const EllipseData *data)
{
    std::cout << "drawEllipse not implemented" << std::endl;
}

void RenderWidget::drawTriangle(QPainter &painter, const TriangleData *data)
{
    std::cout << "drawTriangle not implemented" << std::endl;
}

void RenderWidget::drawLine(QPainter &painter, const LineData *data)
{
    std::cout << "drawLine not implemented" << std::endl;
}
