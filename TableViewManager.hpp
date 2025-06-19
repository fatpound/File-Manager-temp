#ifndef TABLEVIEWMANAGER_H
#define TABLEVIEWMANAGER_H

#include <QObject>
#include <QTableView>
#include <QFileSystemModel>
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


signals:


protected:


private:
    void Setup_();


private:
    QString           m_root_path_;

    QTableView*       m_pTableView_;
    QFileSystemModel* m_pFileSysModel_;
};

#endif // TABLEVIEWMANAGER_H
