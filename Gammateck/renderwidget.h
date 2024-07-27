#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>
#include "api_generated.h"

#include <iostream>

class RenderWidget : public QWidget
{
    Q_OBJECT

public:
    RenderWidget(QWidget *parent = nullptr);
    ~RenderWidget();

public slots:
    void addFigure(const Figure *figure);

protected:
    void paintEvent(QPaintEvent *event) override;


private:
    void drawRect(QPainter &painter, const RectData *data);
    void drawEllipse(QPainter &painter, const EllipseData *data);
    void drawTriangle(QPainter &painter, const TriangleData *data);
    void drawLine(QPainter &painter, const LineData *data);

private:
    QVector<const Figure *> figures;
};

#endif // RENDERWIDGET_H
