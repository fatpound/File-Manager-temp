#include "TabWidgetManager.hpp"

#include <QWidget>
#include <QToolButton>
#include <QVBoxLayout>
#include <QTabBar>
#include <QFileIconProvider>
#include <QIcon>
#include <QFileInfo>
#include <QString>
#include <QtLogging>

#include <utility>

TabWidgetManager::TabWidgetManager(QTabWidget* const tabWidget, QTableView* const firstTable, QObject* const parent)
    :
    QObject{parent},
    m_pTabWidget_(tabWidget)
{
    m_tabs_.reserve(10U);
    m_tabs_.emplace_back(firstTable, GetTabWidget()->currentWidget());

    Setup_();
}

TabWidgetManager::~TabWidgetManager()
{
    qDebug() << "Destructing TabWidgetManager...";
}


auto TabWidgetManager::GetTabWidget() const noexcept -> QTabWidget*
{
    return m_pTabWidget_;
}

auto TabWidgetManager::GetTabCount() const -> int
{
    return GetTabWidget()->count();
}

auto TabWidgetManager::GetCurrentTabIndex() const -> int
{
    return GetTabWidget()->currentIndex();
}


auto TabWidgetManager::GetCurrentTab_() -> Tab&
{
    return m_tabs_[GetCurrentTabIndex()];
}

void TabWidgetManager::Setup_()
{
    InitAddButton_();

    connect(
        GetTabWidget(),
        &QTabWidget::tabCloseRequested,
        this,
        &TabWidgetManager::RemoveTab_
    );

    connect(
        GetTabWidget()->tabBar(),
        &QTabBar::tabMoved,
        this,
        &TabWidgetManager::SwapTabs_
    );

    connect(
        GetCurrentTab_().GetTableViewMgr(),
        &TableViewManager::SelectedPathIsReady,
        this,
        &TabWidgetManager::OnFilePathReceived
    );
}

void TabWidgetManager::InitAddButton_()
{
    auto* const plusButton = new QToolButton(GetTabWidget()->tabBar());

    plusButton->setText("+");
    plusButton->setAutoRaise(true);

    GetTabWidget()->setCornerWidget(plusButton, Qt::Corner::TopLeftCorner);

    connect(
        plusButton,
        &QToolButton::clicked,
        this,
        &TabWidgetManager::AddTab_
    );
}

void TabWidgetManager::AddTab_()
{
    m_tabs_.emplace_back(GetTabWidget());

    connect(
        GetCurrentTab_().GetTableViewMgr(),
        &TableViewManager::SelectedPathIsReady,
        this,
        &TabWidgetManager::OnFilePathReceived
    );
}

void TabWidgetManager::SwapTabs_(const int& from, const int& to)
{
    std::swap<>(m_tabs_[from], m_tabs_[to]);
}

void TabWidgetManager::RemoveTab_(const int& index)
{
    if (GetTabCount() == 1)
    {
        return;
    }

    GetTabWidget()->removeTab(index);
    m_tabs_.erase(m_tabs_.begin() + index);
}

void TabWidgetManager::OnFilePathReceived(const QString& path)
{
    GetTabWidget()->setTabIcon(GetCurrentTabIndex(), QFileIconProvider{}.icon(QFileInfo(path)));
}
