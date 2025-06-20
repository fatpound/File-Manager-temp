#ifndef TABLEVIEWMANAGER_H
#define TABLEVIEWMANAGER_H

#include <QObject>
#include <QTableView>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QDir>

class TableViewManager : public QObject
{
    Q_OBJECT

public:
    explicit TableViewManager(QTableView* tableView, QObject* parent = nullptr);

    explicit TableViewManager()                            = delete;
    explicit TableViewManager(const TableViewManager&)     = delete;
    explicit TableViewManager(TableViewManager&&) noexcept = delete;

    auto operator = (const TableViewManager&)     -> TableViewManager& = delete;
    auto operator = (TableViewManager&&) noexcept -> TableViewManager& = delete;
    ~TableViewManager() override;


public:
    auto GetRootPath() -> QString;

    void SetRootPath(const QDir&    path);
    void SetRootPath(const QString& path);

    void NavigateToFolder(const QModelIndex& firstColumnIdx);


signals:


protected:


private:
    void Setup_();
    void ProcessDoubleClick_(const QModelIndex& midx);


private:
    QString           m_root_path_;

    QTableView*       m_pTableView_;
    QFileSystemModel* m_pFileSysModel_;

    int               m_tab_index_{-1};
};

#endif // TABLEVIEWMANAGER_H
