#include "MenuController.h"
#include "MenuView.h"
#include "FamilyTreeView.h"

#include "../data/Repository.h"
#include "../core/FamilyTree.h"
#include "../core/entities/PersonNode.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QPrinter>
#include <QPainter>
#include <QGraphicsScene>

using namespace ui;
using namespace core;
using core::entities::Gender;
using core::entities::PersonNode;

////////////////////////////////////////////////////////

MenuController::MenuController(MenuView *view,
                               FamilyTree *&treeRef,
                               FamilyTreeView *treeView,
                               QObject *parent)
    : QObject(parent),
      m_view(view),
      m_tree(treeRef),
      m_treeView(treeView)
{
    Q_ASSERT(m_view);

    connect(view, &MenuView::newRequested,
            this, &MenuController::onNew);

    connect(view, &MenuView::saveRequested,
            this, &MenuController::onSave);

    connect(view, &MenuView::loadRequested,
            this, &MenuController::onLoad);

    connect(view, &MenuView::deleteRequested,
            this, &MenuController::onDelete);

    connect(view, &MenuView::exportPdfRequested,
            this, &MenuController::onExportPdf);
}

////////////////////////////////////////////////////////
// Helpers
////////////////////////////////////////////////////////

void MenuController::replaceTree(FamilyTree *newTree)
{
    if (m_tree == newTree)
        return;

    delete m_tree;
    m_tree = newTree;

    emit treeReplaced(m_tree);
}

////////////////////////////////////////////////////////
// Actions
////////////////////////////////////////////////////////

void MenuController::onNew()
{
    auto *root =
        new PersonNode("1",
                       tr("Tổ tiên"),
                       Gender::Male);

    auto *tree = new FamilyTree(root);

    tree->registerId("1");

    replaceTree(tree);
}

void MenuController::onSave()
{
    if (!m_tree)
        return;

    QString selectedFilter;

    QString path =
        QFileDialog::getSaveFileName(
            m_view,
            tr("Save Tree"),
            {},
            tr("JSON (*.json);;CSV (*.csv)"), &selectedFilter);

    if (path.isEmpty())
        return;

    if (selectedFilter.contains("*.json") && !path.endsWith(".json", Qt::CaseInsensitive))
    {
        path += ".json";
    }
    else if (selectedFilter.contains("*.csv") && !path.endsWith(".csv", Qt::CaseInsensitive))
    {
        path += ".csv";
    }
    bool savingStatus = false;

    if (selectedFilter.contains("*.json"))
    {
        savingStatus = data::Repository::saveJson(m_tree, path);
    }
    else if (selectedFilter.contains("*.csv"))
    {
        savingStatus = data::Repository::saveCSV(m_tree, path);
    }

    if (!savingStatus)
    {
        QMessageBox::warning(
            m_view,
            tr("Error"),
            tr("Failed to save file"));
    }
}

void MenuController::onLoad()
{
    QString selectedFilter;

    const QString path =
        QFileDialog::getOpenFileName(
            m_view,
            tr("Load Tree"),
            {},
            tr("JSON (*.json);;CSV (*.csv)"),
            &selectedFilter);

    if (path.isEmpty())
        return;

    FamilyTree *loaded = nullptr;

    if (selectedFilter.contains("*.json"))
        loaded = data::Repository::loadJson(path);
    else if (selectedFilter.contains("*.csv"))
        loaded = data::Repository::loadCSV(path);

    if (!loaded)
    {
        QMessageBox::warning(
            m_view,
            tr("Error"),
            tr("Failed to load tree"));
        return;
    }

    // IMPORTANT
    loaded->rebuildIdRegistry();

    replaceTree(loaded);
}

void MenuController::onDelete()
{
    const QString path =
        QFileDialog::getOpenFileName(
            m_view,
            tr("Delete Tree"),
            {},
            tr("JSON (*.json)"));

    if (path.isEmpty())
        return;

    if (!QFile::remove(path))
    {
        QMessageBox::warning(
            m_view,
            tr("Error"),
            tr("Delete failed"));
    }
}
void MenuController::onExportPdf()
{
    if (!m_treeView)
        return;

    QString path = QFileDialog::getSaveFileName(
        m_view,
        tr("Export PDF"),
        {},
        tr("PDF (*.pdf)"));

    if (path.isEmpty())
        return;

    if (!path.endsWith(".pdf"))
        path += ".pdf";

    QGraphicsScene *scene = m_treeView->scenePtr();

    // Get tight bounds of the tree
    QRectF sceneRect = scene->itemsBoundingRect();

    // Optional margin (looks nicer)
    const qreal margin = 20;
    sceneRect.adjust(-margin, -margin, margin, margin);

    scene->setSceneRect(sceneRect);

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(path);

    // ✅ Page size equals scene size
    QPageSize pageSize(
        QSizeF(sceneRect.width(), sceneRect.height()),
        QPageSize::Point);
    printer.setPageSize(pageSize);

    QPainter painter(&printer);
    if (!painter.isActive())
        return;

    // ✅ 1:1 render (no scaling)
    scene->render(&painter);

    painter.end();
}
