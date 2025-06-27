#include "TableViewManager.hpp"

#include <QHeaderView>
#include <QDesktopServices>
#include <QUrl>
#include <QtLogging>

TableViewManager::TableViewManager(QTableView* const tableView, QObject* const parent)
    :
    QObject{parent},
    m_root_path_(QDir::rootPath()),
    m_pTableView_(tableView),
    m_pFileSysModel_(new QFileSystemModel(this))
{
    Setup_();
}

TableViewManager::~TableViewManager()
{
    qDebug() << "Destructing TableViewManager...";
}


auto TableViewManager::GetRootPath() const -> QString
{
    return m_root_path_;
}

auto TableViewManager::GetCurrentPath() const -> QString
{
    const auto& current_path = GetFileSysModel()->filePath(GetTableView()->rootIndex());

    if (current_path.length() > 0)
    {
        return current_path;
    }
    else
    {
        return "\\\\";
    }
}

auto TableViewManager::GetTableView() const noexcept -> QTableView*
{
    return m_pTableView_;
}

auto TableViewManager::GetFileSysModel() const noexcept -> QFileSystemModel*
{
    return m_pFileSysModel_;
}

void TableViewManager::SetRootPath(const QDir& path)
{
    m_root_path_ = path.path();
}
void TableViewManager::SetRootPath(const QString& path)
{
    m_root_path_ = path;
}

void TableViewManager::NavigateToFolder(const QModelIndex& firstColumnIdx)
{
    if (GetFileSysModel()->hasChildren(firstColumnIdx))
    {
        GetTableView()->setRootIndex(firstColumnIdx);

        emit SelectedPathIsReady(GetFileSysModel()->filePath(firstColumnIdx));
    }
    else
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(GetFileSysModel()->filePath(firstColumnIdx)));
    }
}


auto TableViewManager::eventFilter(QObject* const obj, QEvent* const event) -> bool
{
    if ((obj == GetTableView()->viewport()) and (event->type() == QEvent::MouseButtonPress))
    {
        emit SelectedPathIsReady(GetCurrentPath());
    }

    return QObject::eventFilter(obj, event);
}


void TableViewManager::Setup_()
{
    GetTableView()->viewport()->installEventFilter(this);

    GetFileSysModel()->setRootPath(GetRootPath());

    GetTableView()->setModel(GetFileSysModel());
    GetTableView()->setHorizontalScrollMode(QTableView::ScrollMode::ScrollPerPixel);
    GetTableView()->setVerticalScrollMode(QTableView::ScrollMode::ScrollPerPixel);
    GetTableView()->setSortingEnabled(true);
    GetTableView()->sortByColumn(0, Qt::SortOrder::AscendingOrder);
    GetTableView()->verticalHeader()->setVisible(false);
    GetTableView()->horizontalHeader()->setStretchLastSection(true);

    connect(
        GetTableView(),
        &QTableView::doubleClicked,
        this,
        &TableViewManager::OnDoubleClicked_
    );

    connect(
        GetTableView(),
        &QTableView::clicked,
        this,
        &TableViewManager::OnTableClicked_
    );
}


void TableViewManager::OnTableClicked_(const QModelIndex&)
{
    emit SelectedPathIsReady(GetCurrentPath());
}

void TableViewManager::OnDoubleClicked_(const QModelIndex& midx)
{
    NavigateToFolder(midx.siblingAtColumn(0));
}
