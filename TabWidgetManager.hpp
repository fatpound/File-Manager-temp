#ifndef TABWIDGETMANAGER_H
#define TABWIDGETMANAGER_H

#include "TableViewManager.hpp"

#include <QObject>
#include <QTabWidget>
#include <QTableView>

#include <vector>

class TabWidgetManager : public QObject
{
    Q_OBJECT

public:
    explicit TabWidgetManager(QTabWidget* tabWidget, QTableView* firstTable, QObject* parent = nullptr);

    explicit TabWidgetManager()                            = delete;
    explicit TabWidgetManager(const TabWidgetManager&)     = delete;
    explicit TabWidgetManager(TabWidgetManager&&) noexcept = delete;

    auto operator = (const TabWidgetManager&)     -> TabWidgetManager& = delete;
    auto operator = (TabWidgetManager&&) noexcept -> TabWidgetManager& = delete;
    ~TabWidgetManager() override                                       = default;


public:
    auto GetTabCount        () -> int;
    auto GetCurrentTabIndex () -> int;


signals:


protected:


private:
    void Setup_();
    void InitAddButton_();
    void AddTab_();
    void RemoveTab_(const int& index);


private:
    QTabWidget*                    m_pTabWidget_;

    std::vector<TableViewManager*> m_pTableViewMgr_vec_;
};

#endif // TABWIDGETMANAGER_H
