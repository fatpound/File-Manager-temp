#include "TabWidgetManager.hpp"

TabWidgetManager::TabWidgetManager(QTabWidget* tabWidget, QObject* parent)
    :
    QObject{parent},
    m_TabWidget_(tabWidget)
{

}

TabWidgetManager::~TabWidgetManager()
{

}
