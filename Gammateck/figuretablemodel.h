#ifndef FIGUREMODEL_H
#define FIGUREMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include "typesdao.h"

class FigureModel : public QAbstractTableModel {
    Q_OBJECT

public:
    explicit FigureModel(QObject *parent = nullptr);
    ~FigureModel();

    void addFigure(const Figure *figure);
    void removeFigure(int row);
    const DAO::Types::IFigure* getFigure(int index);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

signals:
    void figureRemoved(int row);
    void dataChange();

private:
    const DAO::Types::IFigure* convertRawFigureToDAO(const Figure* figure) const;

private:
    QList<const DAO::Types::IFigure*> figures;
};

#endif // FIGUREMODEL_H
