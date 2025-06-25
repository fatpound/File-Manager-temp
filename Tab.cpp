#include "Tab.hpp"

#include <QWidget>
#include <QVBoxLayout>

Tab::Tab(QTableView* const pTableView, QObject* const parentForMgr)
    :
    m_pTableViewMgr_(new TableViewManager(pTableView, parentForMgr))
{

}

Tab::Tab(QTabWidget* const pTabWidget, QObject* const parentForMgr)
    :
    Tab(new QTableView, parentForMgr)
{
    auto* const tab = new QWidget;
    (new QVBoxLayout(tab))->addWidget(m_pTableViewMgr_->GetTableView());

    pTabWidget->setCurrentIndex(
        pTabWidget->addTab(tab, "New Tab")
    );
}
