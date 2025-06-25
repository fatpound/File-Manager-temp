#include "TableViewManager.hpp"

#include <QHeaderView>
#include <QDesktopServices>
#include <QUrl>

TableViewManager::TableViewManager(QTableView* const tableView, QObject* const parent)
    :
    QObject{parent},
    m_root_path_(QDir::rootPath()),
    m_pTableView_(tableView),
    m_pFileSysModel_(new QFileSystemModel(this))
{
    Setup_();
}


auto TableViewManager::GetRootPath() const -> QString
{
    return m_root_path_;
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
    }
    else
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(GetFileSysModel()->filePath(firstColumnIdx)));
    }
}

void TableViewManager::Setup_()
{
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
        &TableViewManager::ProcessDoubleClick_
    );
}

void TableViewManager::ProcessDoubleClick_(const QModelIndex& midx)
{
    NavigateToFolder(midx.siblingAtColumn(0));
}
