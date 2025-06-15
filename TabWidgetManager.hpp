#ifndef TABWIDGETMANAGER_H
#define TABWIDGETMANAGER_H

#include <QObject>
#include <QTabWidget>

class TabWidgetManager : public QObject
{
    Q_OBJECT

public:
    explicit TabWidgetManager(QTabWidget* tabWidget, QObject* parent = nullptr);

    explicit TabWidgetManager(const TabWidgetManager&)     = delete;
    explicit TabWidgetManager(TabWidgetManager&&) noexcept = delete;

    auto operator = (const TabWidgetManager&)     -> TabWidgetManager& = delete;
    auto operator = (TabWidgetManager&&) noexcept -> TabWidgetManager& = delete;
    ~TabWidgetManager() override;


signals:


protected:


private:
    QTabWidget* m_TabWidget_;
};

#endif // TABWIDGETMANAGER_H
