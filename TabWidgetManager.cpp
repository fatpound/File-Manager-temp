#include "TabWidgetManager.hpp"

#include <QToolButton>
#include <QTabBar>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QString>
#include <QtLogging>

#include <utility>

FM_BEGIN_NAMESPACE

TabWidgetManager::TabWidgetManager(QTabWidget* const tabWidget, QTableView* const firstTable, QLabel* lineEditLabel, QObject* const parent)
    :
    QObject{parent},
    m_pTabWidget_(tabWidget),
    m_pLabel_(lineEditLabel)
{
    Setup_(firstTable);
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

void TabWidgetManager::Setup_(QTableView* const firstTable)
{
    m_tabs_.reserve(10U);

    InitAddButton_();
    InitFirstTab_(firstTable);

    connect(
        GetTabWidget(),
        &QTabWidget::currentChanged,
        this,
        &TabWidgetManager::OnTabChange_
    );

    connect(
        GetTabWidget(),
        &QTabWidget::tabBarClicked,
        this,
        &TabWidgetManager::OnTabClicked_
    );

    connect(
        GetTabWidget(),
        &QTabWidget::tabCloseRequested,
        this,
        &TabWidgetManager::OnTabRemove_
    );

    connect(
        GetTabWidget()->tabBar(),
        &QTabBar::tabMoved,
        this,
        &TabWidgetManager::OnTabSwap_
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
        &TabWidgetManager::OnPlusTabAdd_
    );
}

void TabWidgetManager::InitFilePathConnection_()
{
    connect(
        GetCurrentTab_().GetTableViewMgr(),
        &TableViewManager::SelectedPathIsReady,
        this,
        &TabWidgetManager::OnFilePathReceived_
    );
}

void TabWidgetManager::InitFirstTab_(QTableView* const firstTable)
{
    if (firstTable == nullptr)
    {
        return;
    }

    m_tabs_.emplace_back(firstTable, GetTabWidget()->currentWidget());

    InitFilePathConnection_();
}

void TabWidgetManager::SetLabelText_(const QString& text)
{
    m_pLabel_->setText(text);
}

void TabWidgetManager::SetLabelTextToCurrentPath_()
{
    SetLabelText_(GetCurrentTab_().GetTableViewMgr()->GetCurrentPath());
}


void TabWidgetManager::OnPlusTabAdd_()
{
    const auto& is_tab_vector_full = m_tabs_.size() == m_tabs_.capacity();

    if (is_tab_vector_full)
    {
        m_ignore_tab_change_signal_ = true;
    }

    m_tabs_.emplace_back(GetTabWidget());

    if (is_tab_vector_full)
    {
        m_ignore_tab_change_signal_ = false;

        SetLabelTextToCurrentPath_();
    }

    InitFilePathConnection_();
}

void TabWidgetManager::OnTabClicked_(const int&)
{
    SetLabelTextToCurrentPath_();
}

void TabWidgetManager::OnTabChange_(const int&)
{
    if (not m_ignore_tab_change_signal_)
    {
        SetLabelTextToCurrentPath_();
    }
}

void TabWidgetManager::OnTabRemove_(const int& index)
{
    if (GetTabCount() == 1)
    {
        return;
    }

    m_ignore_tab_change_signal_ = true;
    GetTabWidget()->removeTab(index);
    m_ignore_tab_change_signal_ = false;

    m_tabs_.erase(m_tabs_.begin() + index);

    SetLabelTextToCurrentPath_();
}

void TabWidgetManager::OnTabSwap_(const int& from, const int& to)
{
    std::swap<>(m_tabs_[from], m_tabs_[to]);
}

void TabWidgetManager::OnFilePathReceived_(const QString& path)
{
    SetLabelText_(path);

    if (path not_eq "\\\\")
    {
        GetTabWidget()->setTabIcon(GetCurrentTabIndex(), QFileIconProvider{}.icon(QFileInfo(path)));
    }
}

FM_END_NAMESPACE
