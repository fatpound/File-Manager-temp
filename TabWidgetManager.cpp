#include "TabWidgetManager.hpp"

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>

TabWidgetManager::TabWidgetManager(QTabWidget* const tabWidget, QTableView* const firstTable, QObject* const parent)
    :
    QObject{parent},
    m_pTabWidget_(tabWidget)
{
    InitAddButton_();

    m_pTableViewMgr_vec_.push_back(new TableViewManager(firstTable, this));

    connect(
        m_pTabWidget_,
        &QTabWidget::tabCloseRequested,
        this,
        &TabWidgetManager::RemoveCurrentTab_
    );
}


auto TabWidgetManager::GetTabCount() -> int
{
    return m_pTabWidget_->count();
}

auto TabWidgetManager::GetCurrentTabIndex() -> int
{
    return m_pTabWidget_->currentIndex();
}

void TabWidgetManager::AddTab_()
{
    auto* pTableView = new QTableView;

    {
        auto* container = new QWidget;
        (new QVBoxLayout(container))->addWidget(pTableView);

        m_pTabWidget_->setCurrentIndex(
            m_pTabWidget_->addTab(container, "New Tab")
        );
    }

    m_pTableViewMgr_vec_.push_back(new TableViewManager(pTableView, this));
}

void TabWidgetManager::RemoveTab_(const int& index)
{
    m_pTabWidget_->removeTab(index);
}

void TabWidgetManager::RemoveCurrentTab_()
{
    if (GetTabCount() not_eq 1)
    {
        RemoveTab_(GetCurrentTabIndex());
    }
}

void TabWidgetManager::InitAddButton_()
{
    auto* const plusButton = new QToolButton(m_pTabWidget_->tabBar());

    plusButton->setText("+");
    plusButton->setAutoRaise(true);

    m_pTabWidget_->setCornerWidget(plusButton, Qt::Corner::TopLeftCorner);

    connect(
        plusButton,
        &QToolButton::clicked,
        this,
        &TabWidgetManager::AddTab_
    );
}
