#include "Tab.hpp"

#include <QWidget>
#include <QVBoxLayout>

Tab::Tab(QTableView* const pTableView, QObject* const parent)
    :
    m_pTableViewMgr_(new TableViewManager(pTableView, parent))
{

}

Tab::Tab(QTabWidget* const pTabWidget, QObject* const parent)
    :
    Tab(new QTableView, parent)
{
    auto* const tab = new QWidget;
    (new QVBoxLayout(tab))->addWidget(m_pTableViewMgr_->GetTableView());

    pTabWidget->setCurrentIndex(
        pTabWidget->addTab(tab, "New Tab")
    );
}
