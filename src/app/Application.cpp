#include "Application.h"

#include <QMainWindow>
#include <QDockWidget>

using namespace core;
using namespace core::entities;

////////////////////////////////////////////////////////

Application::Application(QObject *parent)
    : QObject(parent)
{
}

////////////////////////////////////////////////////////

FamilyTree *Application::createDemoTree()
{
    auto *toTien =
        new PersonNode("1", "A", Gender::Male);

    auto *tree =
        new FamilyTree(toTien);

    // register ancestor
    tree->registerId("1");

    auto *vo =
        new PersonNode(tree->generateId(), "B", Gender::Female);

    tree->addMarriage(toTien, vo);

    auto *con1 =
        new PersonNode(tree->generateId(), "AAB", Gender::Male);

    auto *con2 =
        new PersonNode(tree->generateId(), "ABB", Gender::Male);

    auto *con3 =
        new PersonNode(tree->generateId(), "BBA", Gender::Female);

    tree->addSon(toTien, vo, con1, 0);
    tree->addSon(toTien, vo, con2, 1);
    tree->addDaughter(toTien, vo, con3,2);

    auto *vo2 =
        new PersonNode(tree->generateId(), "C", Gender::Female);

    tree->addMarriage(con1, vo2);

    auto *chau =
        new PersonNode(tree->generateId(), "AABC", Gender::Male);

    tree->addSon(con1, vo2, chau, 0);

    return tree;
}

////////////////////////////////////////////////////////

void Application::setupWindow()
{
    m_window = new QMainWindow();

    // ===== Views =====
    m_view = new ui::FamilyTreeView(m_window);
    m_inspector = new ui::PersonInspector(m_window);
    m_menuView = new ui::MenuView(m_window);

    // ===== Central =====
    m_window->setCentralWidget(m_view);

    // ===== Inspector Dock =====
    m_inspectorDock = new QDockWidget("Inspector", m_window);
    m_inspectorDock->setWidget(m_inspector);

    m_inspectorDock->setAllowedAreas(
        Qt::LeftDockWidgetArea |
        Qt::RightDockWidgetArea);

    m_window->addDockWidget(
        Qt::RightDockWidgetArea,
        m_inspectorDock);

    m_window->setMenuBar(m_menuView);
    // ===== Window config =====
    m_window->resize(1200, 800);
}

////////////////////////////////////////////////////////

void Application::setupControllers()
{
    m_controller =
        new ui::FamilyController(
            m_view,
            m_inspector,
            m_window);

    m_controller->setFamilyTree(m_tree);

    m_menuController =
        new ui::MenuController(
            m_menuView,
            m_tree,
            m_view);

    // ===== Connections =====
    connect(m_menuController,
            &ui::MenuController::treeReplaced,
            m_controller,
            &ui::FamilyController::setFamilyTree);

    connect(m_menuView,
            &ui::MenuView::exitRequested,
            m_window,
            &QMainWindow::close);
    connect(m_controller,
            &ui::FamilyController::inspectorRequested,
            this,
            &Application::showInspector);
}

////////////////////////////////////////////////////////

void Application::start()
{
    m_tree = createDemoTree();

    setupWindow();
    setupControllers();

    m_window->show();
}
void Application::showInspector()
{
    if (!m_inspectorDock)
        return;

    m_inspectorDock->show();
    m_inspectorDock->raise();
}
