#include "TableViewManager.hpp"

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

void TableViewManager::Setup_()
{
    m_pFileSysModel_->setRootPath(GetRootPath());
    m_pTableView_->setModel(m_pFileSysModel_);
}
