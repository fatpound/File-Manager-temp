#ifndef TABLEVIEWMANAGER_H
#define TABLEVIEWMANAGER_H

#include <QObject>
#include <QTableView>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QString>
#include <QDir>

class TableViewManager : public QObject
{
    Q_OBJECT

public:
    explicit TableViewManager(QTableView* tableView, QObject* parent);

    explicit TableViewManager()                            = delete;
    explicit TableViewManager(const TableViewManager&)     = delete;
    explicit TableViewManager(TableViewManager&&) noexcept = delete;

    auto operator = (const TableViewManager&)     -> TableViewManager& = delete;
    auto operator = (TableViewManager&&) noexcept -> TableViewManager& = delete;
    ~TableViewManager() override;


public:
    [[nodiscard]] auto GetRootPath     () const          -> QString;
    [[nodiscard]] auto GetTableView    () const noexcept -> QTableView*;
    [[nodiscard]] auto GetFileSysModel () const noexcept -> QFileSystemModel*;

    void SetRootPath      (const QDir&    path);
    void SetRootPath      (const QString& path);
    void NavigateToFolder (const QModelIndex& firstColumnIdx);


signals:
    void SelectedPathIsReady(const QString& filepath);


protected:


private:
    void Setup_();
    void ProcessDoubleClick_(const QModelIndex& midx);


private:
    QString           m_root_path_;

    QTableView*       m_pTableView_;
    QFileSystemModel* m_pFileSysModel_;
};

#endif // TABLEVIEWMANAGER_H
