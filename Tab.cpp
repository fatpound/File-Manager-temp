#include "Tab.hpp"

#include <QVBoxLayout>
#include <QtLogging>

FM_BEGIN_NAMESPACE

Tab::Tab(QTableView* const pTableView, QWidget* const parentWidget)
    :
    m_pWidget_(parentWidget),
    m_pTableViewMgr_(new TableViewManager(pTableView, m_pWidget_))
{

}

Tab::Tab(QTabWidget* const pTabWidget)
    :
    Tab(new QTableView, new QWidget)
{
    (new QVBoxLayout(GetWidget()))->addWidget(GetTableViewMgr()->GetTableView());

    pTabWidget->setCurrentIndex(
        pTabWidget->addTab(GetWidget(), "New Tab")
    );
}

Tab::~Tab()
{
    qDebug() << "Destructing Tab...";
}


auto Tab::GetWidget() const noexcept -> QWidget*
{
    return m_pWidget_;
}

auto Tab::GetTableViewMgr() const noexcept -> TableViewManager*
{
    return m_pTableViewMgr_;
}

FM_END_NAMESPACE
