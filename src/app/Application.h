#pragma once

#include <QObject>

#include "FamilyTree.h"
#include "FamilyTreeView.h"
#include "FamilyController.h"
#include "MenuView.h"
#include "MenuController.h"
#include "PersonInspector.h"

class QMainWindow;
class QDockWidget;

class Application : public QObject
{
    Q_OBJECT

public:
    explicit Application(QObject *parent = nullptr);
    ~Application() override = default;

    void start();
    void showInspector();

private:
    // Core
    core::FamilyTree *m_tree = nullptr;

    // UI
    QMainWindow *m_window = nullptr;
    ui::FamilyTreeView *m_view = nullptr;
    ui::PersonInspector *m_inspector = nullptr;
    ui::MenuView *m_menuView = nullptr;
    QDockWidget *m_inspectorDock = nullptr;

    // Controllers
    ui::FamilyController *m_controller = nullptr;
    ui::MenuController *m_menuController = nullptr;

    // Helpers
    core::FamilyTree *createDemoTree();
    void setupWindow();
    void setupControllers();
};
