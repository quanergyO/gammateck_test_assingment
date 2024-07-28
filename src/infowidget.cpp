#include "infowidget.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QTableView>
#include <QStyledItemDelegate>
#include <QPainter>

namespace {

class ImageDelegate : public QStyledItemDelegate
{
public:
    ImageDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if (index.column() == 4 || index.column() == 5) {
            QPixmap pixmap(index.data(Qt::UserRole).toString());
            if (!pixmap.isNull()) {
                painter->save();
                painter->setRenderHint(QPainter::Antialiasing);
                painter->setRenderHint(QPainter::SmoothPixmapTransform);

                QRect r = option.rect;
                int size = qMin(r.width(), r.height()) - 10;
                QSize imageSize(size, size);

                pixmap = pixmap.scaled(imageSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                QPoint p = r.center() - QPoint(pixmap.width()/2, pixmap.height()/2);
                painter->drawPixmap(p, pixmap);
                painter->restore();
            }
        } else {
            QStyledItemDelegate::paint(painter, option, index);
        }
    }

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        if (index.column() == 4 || index.column() == 5) {
            return QSize(30, 30);
        }
        return QStyledItemDelegate::sizeHint(option, index);
    }
};

}

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
    tableView->setItemDelegate(new ImageDelegate(this));

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(tableView);
    setLayout(layout);

    connect(model, &QAbstractTableModel::dataChanged, tableView, [this](const QModelIndex &topLeft, const QModelIndex &bottomRight) {
        Q_UNUSED(topLeft);
        Q_UNUSED(bottomRight);
        tableView->update();
    });

    connect(tableView, &QAbstractItemView::clicked, this, [this](const QModelIndex &index) {
        if (index.column() == 4) {
            this->model->toggleFigureVisibility(index.row());
            emit toggleVisibility(index.row());
        } else if (index.column() == 5) {
            this->model->removeFigure(index.row());
            emit deleteFigure(index.row());
        }
    });

}

InfoWidget::~InfoWidget()
{
}


