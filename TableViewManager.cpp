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

    connect(
        m_pTableView_,
        &QTableView::doubleClicked,
        this,
        &TableViewManager::ProcessDoubleClick_
    );
}

TableViewManager::~TableViewManager()
{

}


auto TableViewManager::GetRootPath() -> QString
{
    return m_root_path_;
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
    if (not m_pFileSysModel_->hasChildren(firstColumnIdx))
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(m_pFileSysModel_->filePath(firstColumnIdx)));
    }
    else
    {
        m_pTableView_->setRootIndex(firstColumnIdx);
    }
}

void TableViewManager::Setup_()
{
    m_pFileSysModel_->setRootPath(GetRootPath());
    m_pTableView_->setModel(m_pFileSysModel_);
    m_pTableView_->verticalHeader()->setVisible(false);
}

void TableViewManager::ProcessDoubleClick_(const QModelIndex& midx)
{
    NavigateToFolder(midx.siblingAtColumn(0));

    // const auto& path = static_cast<QFileSystemModel*>(ui->FileTreeView->model())->filePath(firstColumnIndex);

    // SetLabelText_(path);
    // leftTabIsReset_ = false;
    // isWorkingOnRightPane = false;
}
