#include "figuretablemodel.h"
#include <QVariant>
#include <QString>
#include <QDebug>
#include <QPushButton>
#include <QStandardItem>

namespace {
namespace Config {
namespace Images {
static const QString hideImage = ":/images/hide.png";
static const QString hideImage2 =":/images/hide2.png";
static const QString deleteImage =  ":/images/delete.png";
}
namespace TableHeader {
static const QString id = "ID";
static const QString type = "Type";
static const QString position = "Position(X, Y)";
static const QString reginon = "Region(Width, Height)";
static const QString hide = "Hide";
static const QString remove = "Remove";
}
} // namespace Config
}

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
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
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
        case 5:
            return QString();
        default:
            return QVariant();
        }
    }
    else if (role == Qt::UserRole)
    {
        if (index.column() == 4) {
            const auto *figure = figures.at(index.row());
            return figure->isVisible() ?
                       Config::Images::hideImage :
                       Config::Images::hideImage2;
        }
        else if (index.column() == 5)
            return Config::Images::deleteImage;
    }
    return QVariant();
}

QVariant FigureModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return Config::TableHeader::id;
        case 1:
            return Config::TableHeader::type;
        case 2:
            return Config::TableHeader::position;
        case 3:
            return Config::TableHeader::reginon;
        case 4:
            return Config::TableHeader::hide;
        case 5:
            return Config::TableHeader::remove;
        default:
            return QVariant();
        }
    }
    return QVariant();
}

DAO::Types::IFigure* FigureModel::convertRawFigureToDAO(const Figure* figure) const
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

void FigureModel::toggleFigureVisibility(int row) {
    if (row >= 0 && row < figures.size()) {
        DAO::Types::IFigure* figure = figures[row];
        figure->setVisible(!figure->isVisible());
        emit dataChanged(index(row, 0), index(row, columnCount() - 1));
        emit dataChange();
    }
}

void FigureModel::moveFigure(int index, int dx, int dy) {
    if (index >= 0 && index < figures.size()) {
        figures[index]->move(dx, dy);
        emit dataChanged(this->index(index, 0), this->index(index, columnCount() - 1));
        emit figuresMoved();
    }
}
