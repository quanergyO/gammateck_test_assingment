#ifndef RENDERWIDGET_H
#define RENDERWIDGET_H

#include <QWidget>
#include "api_generated.h"
#include "figuretablemodel.h"

#include <iostream>

class RenderWidget : public QWidget
{
    Q_OBJECT

public:
    RenderWidget(FigureModel* model, QWidget *parent = nullptr);
    ~RenderWidget();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void drawRect(QPainter &painter, const DAO::Types::Rect *data);
    void drawEllipse(QPainter &painter, const DAO::Types::Ellipse *data);
    void drawTriangle(QPainter &painter, const DAO::Types::Triangle *data);
    void drawLine(QPainter &painter, const DAO::Types::Line *data);

private:
    FigureModel* model;
};

#endif // RENDERWIDGET_H
