#ifndef TABWIDGETMANAGER_H
#define TABWIDGETMANAGER_H

#include "_macros.hpp"
#include "Tab.hpp"

#include <QObject>
#include <QTabWidget>
#include <QTableView>
#include <QString>
#include <QLabel>

#include <vector>

FM_BEGIN_NAMESPACE

class TabWidgetManager : public QObject
{
    Q_OBJECT

public:
    explicit TabWidgetManager(QTabWidget* tabWidget, QTableView* firstTable, QLabel* lineEditLabel, QObject* parent);

    explicit TabWidgetManager()                            = delete;
    explicit TabWidgetManager(const TabWidgetManager&)     = delete;
    explicit TabWidgetManager(TabWidgetManager&&) noexcept = delete;

    auto operator = (const TabWidgetManager&)     -> TabWidgetManager& = delete;
    auto operator = (TabWidgetManager&&) noexcept -> TabWidgetManager& = delete;
    ~TabWidgetManager() override;


public:
    [[nodiscard]] auto GetTabWidget       () const noexcept -> QTabWidget*;
    [[nodiscard]] auto GetTabCount        () const -> int;
    [[nodiscard]] auto GetCurrentTabIndex () const -> int;


signals:


protected:


private:
    auto GetCurrentTab_() -> Tab&;

    void Setup_(QTableView* firstTable);
    void InitAddButton_();
    void InitFilePathConnection_();
    void InitFirstTab_(QTableView* firstTable);
    void SetLabelText_(const QString& text);
    void SetLabelTextToCurrentPath_();


private:
    QTabWidget*        m_pTabWidget_;
    QLabel*            m_pLabel_;

    std::vector<Tab>   m_tabs_;

    // This flag is used only in the OnTabChanged_ slot to suppress unnecessary current changed signal because
    // QTabWidget::removeTab emits the currentChanged(int) signal BEFORE the tab is fully removed
    // which can cause the label text to be set using the path from the TableView of the tab that's about to be removed
    // QTabBar::setCurrentIndex also emits that signal, making it hard to add new tabs when tab vector is full, causing access violation
    bool               m_ignore_tab_change_signal_{};


private slots:
    void OnPlusTabAdd_();
    void OnTabClicked_(const int& index);
    void OnTabChange_(const int& index);
    void OnTabRemove_(const int& index);
    void OnTabSwap_(const int& from, const int& to);
    void OnFilePathReceived_(const QString& path);
};

FM_END_NAMESPACE

#endif // TABWIDGETMANAGER_H
