#include "TableViewManager.hpp"

TableViewManager::TableViewManager(QTableView* tableView, QObject* parent)
    :
    QObject{parent},
    m_root_path_(QDir::rootPath()),
    m_TableView_(tableView),
    m_FileSysModel_(new QFileSystemModel(this))
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
    m_FileSysModel_->setRootPath(GetRootPath());
    m_TableView_->setModel(m_FileSysModel_);
}
