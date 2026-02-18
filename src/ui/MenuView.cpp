#include "MenuView.h"

#include <QMenu>
#include <QKeySequence>

using namespace ui;

MenuView::MenuView(QWidget *parent)
    : QMenuBar(parent)
{
    buildMenus();
}

void MenuView::buildMenus()
{
    QMenu *fileMenu = addMenu("File");

    m_newAct = fileMenu->addAction("New Tree");
    m_saveAct = fileMenu->addAction("Save Tree");
    m_loadAct = fileMenu->addAction("Load Tree");
    m_deleteAct = fileMenu->addAction("Delete Tree");
    fileMenu->addSeparator();
    m_exportPdfAct = fileMenu->addAction("Export PDF");
    fileMenu->addSeparator();
    m_exitAct = fileMenu->addAction("Exit");

    // shortcuts
    m_newAct->setShortcut(QKeySequence::New);
    m_saveAct->setShortcut(QKeySequence::Save);
    m_loadAct->setShortcut(QKeySequence::Open);
    m_exitAct->setShortcut(QKeySequence::Quit);

    // forward signals
    connect(m_newAct, &QAction::triggered, this, &MenuView::newRequested);
    connect(m_saveAct, &QAction::triggered, this, &MenuView::saveRequested);
    connect(m_loadAct, &QAction::triggered, this, &MenuView::loadRequested);
    connect(m_deleteAct, &QAction::triggered, this, &MenuView::deleteRequested);
    connect(m_exitAct, &QAction::triggered, this, &MenuView::exitRequested);
    connect(m_exportPdfAct, &QAction::triggered, this, &MenuView::exportPdfRequested);
}
