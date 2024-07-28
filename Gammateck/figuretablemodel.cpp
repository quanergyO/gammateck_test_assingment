#include "figuretablemodel.h"
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QPushButton>

#include <iostream>

FigureModel::FigureModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

FigureModel::~FigureModel()
{
    for (auto* figure : figures) {
        delete figure;
    }
}

void FigureModel::addFigure(const Figure *figure)
{
    beginInsertRows(QModelIndex(), figures.size(), figures.size());
    figures.append(convertRawFigureToDAO(figure));
    endInsertRows();
    emit dataChange();
}

void FigureModel::removeFigure(int row)
{
    if (row < 0 || row >= figures.size())
        return;
    beginRemoveRows(QModelIndex(), row, row);
    const DAO::Types::IFigure* figure = figures.at(row);
    delete figure;
    figures.removeAt(row);
    endRemoveRows();
    emit figureRemoved(row);
    emit dataChange();
}

const DAO::Types::IFigure* FigureModel::getFigure(int index)
{
    if (index < 0 || index >= figures.size()) {
        return nullptr;
    }
    return figures[index];
}

int FigureModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return figures.size();
}

int FigureModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 6;
}

QVariant FigureModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const auto *figure = figures.at(index.row());

    switch (index.column()) {
    case 0:
        return index.row();
    case 1:
        return QString::fromStdString(figure->getType());
    case 2:
        return QString::fromStdString(figure->getPosition());
    case 3:
        return QString::fromStdString(figure->getRegion());
    case 4:
        return "Скрыть";
    case 5:
        return "Удалить";
    default:
        return QVariant();
    }
}

QVariant FigureModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("ID");
        case 1:
            return QString("Type");
        case 2:
            return QString("Position(X, Y)");
        case 3:
            return QString("Region(Width, Height)");
        case 4:
            return QString("Hide");
        case 5:
            return QString("Remove");
        default:
            return QVariant();
        }
    }
    return QVariant();
}

const DAO::Types::IFigure* FigureModel::convertRawFigureToDAO(const Figure* figure) const
{
    DAO::Types::IFigure* figureToAppend = nullptr;
    switch(figure->type()) {
    case FigureType::FigureType_Rect:
        figureToAppend = new DAO::Types::Rect(figure);
        break;
    case FigureType::FigureType_Ellipse:
        figureToAppend = new DAO::Types::Ellipse(figure);
        break;
    case FigureType::FigureType_Triangle:
        figureToAppend = new DAO::Types::Triangle(figure);
        break;
    case FigureType::FigureType_Line:
        figureToAppend = new DAO::Types::Line(figure);
        break;
    }
    return figureToAppend;
}
