#ifndef TAB_HPP
#define TAB_HPP

#include "TableViewManager.hpp"

#include <QObject>
#include <QTabWidget>
#include <QTableView>

class Tab
{
public:
    explicit Tab(QTableView* pTableView, QObject* parent = nullptr);
    explicit Tab(QTabWidget* pTabWidget, QObject* parent = nullptr);

    explicit Tab()           = delete;
    explicit Tab(const Tab&) = delete;
    Tab(Tab&&) noexcept      = default;

    auto operator = (const Tab&)     -> Tab& = delete;
    auto operator = (Tab&&) noexcept -> Tab& = default;
    ~Tab() noexcept                          = default;


protected:


private:
    TableViewManager* m_pTableViewMgr_;
};

#endif // TAB_HPP
