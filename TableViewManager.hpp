#ifndef TABLEVIEWMANAGER_H
#define TABLEVIEWMANAGER_H

#include "_macros.hpp"

#include <QObject>
#include <QEvent>
#include <QTableView>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QString>
#include <QDir>

FM_BEGIN_NAMESPACE

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
    [[nodiscard]] auto GetCurrentPath  () const          -> QString;
    [[nodiscard]] auto GetTableView    () const noexcept -> QTableView*;
    [[nodiscard]] auto GetFileSysModel () const noexcept -> QFileSystemModel*;

    void SetRootPath      (const QString& path);
    void SetRootPath      (const QDir&    path);
    void NavigateToFolder (const QModelIndex& firstColumnIdx);


signals:
    void SelectedPathIsReady(const QString& filepath);


protected:
    virtual auto eventFilter(QObject* obj, QEvent* event) -> bool override;


private:
    void Setup_();


private:
    QString             m_root_path_;

    QTableView*         m_pTableView_;
    QFileSystemModel*   m_pFileSysModel_;


private slots:
    void OnDoubleClicked_(const QModelIndex& midx);
};

FM_END_NAMESPACE

#endif // TABLEVIEWMANAGER_H
