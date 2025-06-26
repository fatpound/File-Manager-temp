#ifndef TAB_HPP
#define TAB_HPP

#include "TableViewManager.hpp"

#include <QWidget>
#include <QTableView>
#include <QTabWidget>

class Tab
{
public:
    explicit Tab(QTableView* pTableView, QWidget* parentForMgr);
    explicit Tab(QTabWidget* pTabWidget);

    explicit Tab()           = delete;
    explicit Tab(const Tab&) = delete;
    Tab(Tab&&) noexcept      = default;

    auto operator = (const Tab&)     -> Tab& = delete;
    auto operator = (Tab&&) noexcept -> Tab& = default;
    ~Tab();


public:
    auto GetWidget       () const noexcept -> QWidget*;
    auto GetTableViewMgr () const noexcept -> TableViewManager*;


protected:


private:
    QWidget*          m_pWidget_;

    TableViewManager* m_pTableViewMgr_;
};

#endif // TAB_HPP
