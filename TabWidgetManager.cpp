#include "TabWidgetManager.hpp"

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QTabBar>

#include <utility>

TabWidgetManager::TabWidgetManager(QTabWidget* const tabWidget, QTableView* const firstTable, QObject* const parent)
    :
    QObject{parent},
    m_pTabWidget_(tabWidget)
{
    Setup_();

    m_pTableViewMgr_vec_.push_back(new TableViewManager(firstTable, this));
}


auto TabWidgetManager::GetTabCount() -> int
{
    return m_pTabWidget_->count();
}

auto TabWidgetManager::GetCurrentTabIndex() -> int
{
    return m_pTabWidget_->currentIndex();
}

void TabWidgetManager::Setup_()
{
    InitAddButton_();

    connect(
        m_pTabWidget_,
        &QTabWidget::tabCloseRequested,
        this,
        &TabWidgetManager::RemoveTab_
    );

    connect(
        m_pTabWidget_->tabBar(),
        &QTabBar::tabMoved,
        this,
        &TabWidgetManager::SwapTabs_
    );
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

void TabWidgetManager::AddTab_()
{
    auto* const pTableView = new QTableView;

    {
        auto* const tab = new QWidget;
        (new QVBoxLayout(tab))->addWidget(pTableView);

        m_pTabWidget_->setCurrentIndex(
            m_pTabWidget_->addTab(tab, "New Tab")
        );
    }

    m_pTableViewMgr_vec_.push_back(new TableViewManager(pTableView, this));
}

void TabWidgetManager::SwapTabs_(const int& from, const int& to)
{
    std::swap(m_pTableViewMgr_vec_[from], m_pTableViewMgr_vec_[to]);
}

void TabWidgetManager::RemoveTab_(const int& index)
{
    if (GetTabCount() == 1)
    {
        return;
    }

    m_pTabWidget_->removeTab(index);
    m_pTableViewMgr_vec_.erase(m_pTableViewMgr_vec_.begin() + index);
}
