#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QJsonObject>
#include <QJsonDocument>

#include "figuretablemodel.h"


class InfoWidget : public QWidget
{
    Q_OBJECT

public:
    InfoWidget(FigureModel* model, QWidget *parent = nullptr);
    ~InfoWidget();

signals:
    void deleteFigure(int row);
    void toggleVisibility(int index);

private:
    FigureModel *model;
    QTableView *tableView;
};

#endif // INFOWIDGET_H
