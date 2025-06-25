#include "Tab.hpp"

#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>

Tab::Tab(QTableView* const pTableView, QObject* const parentForMgr)
    :
    m_pTableViewMgr_(new TableViewManager(pTableView, parentForMgr))
{

}

Tab::Tab(QTabWidget* const pTabWidget, QWidget* const pNewWidget)
    :
    Tab(new QTableView, pNewWidget)
{
    (new QVBoxLayout(pNewWidget))->addWidget(GetTableViewMgr()->GetTableView());

    pTabWidget->setCurrentIndex(
        pTabWidget->addTab(pNewWidget, "New Tab")
    );
}

Tab::~Tab()
{
    qDebug() << "Destructing Tab...";
}

auto Tab::GetTableViewMgr() -> TableViewManager*
{
    return m_pTableViewMgr_;
}
