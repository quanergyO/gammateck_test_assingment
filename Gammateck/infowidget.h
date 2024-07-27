#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QJsonObject>
#include <QJsonDocument>

#include "api_generated.h"

#include <iostream>

class InfoWidget : public QWidget
{
    Q_OBJECT

public:
    InfoWidget(QWidget *parent = nullptr);
    ~InfoWidget();
public slots:
    void addFigureInfo(const Figure *figure);

private:
    QString getPositionString(const Figure *figure);
    QString getRegionString(const Figure *figure);
    QString getFigureType(const Figure *figure);
signals:
    void deleteFigure(int row);
private:
    QTableWidget *tableWidget;
};

#endif // INFOWIDGET_H
