#include "infowidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTableView>

InfoWidget::InfoWidget(FigureModel* model, QWidget *parent)
    : QWidget(parent)
    , model(model)
    , tableView(new QTableView(this))
{
    tableView->setModel(model);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->verticalHeader()->setVisible(false);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::NoSelection);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tableView);
    setLayout(layout);

    connect(model, &QAbstractTableModel::dataChanged, tableView, [this](const QModelIndex &topLeft, const QModelIndex &bottomRight) {
        Q_UNUSED(topLeft);
        Q_UNUSED(bottomRight);
        tableView->update();
    });

    connect(tableView, &QAbstractItemView::clicked, this, [this](const QModelIndex &index) {
        if (index.column() == 5) {
            this->model->removeFigure(index.row());
            emit deleteFigure(index.row());
        }
    });

}

InfoWidget::~InfoWidget()
{
}


