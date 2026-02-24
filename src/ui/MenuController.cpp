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
#include <QInputDialog>

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

    connect(m_treeView, &FamilyTreeView::cropAreaSelected,
            this, &MenuController::handleCropExport);
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

    QStringList options;
    options << "Whole Tree"
            << "Selected Area"
            << "Visible Area"
            << "Multi-page (A4 Tiled)";

    bool ok = false;

    QString choice = QInputDialog::getItem(
        m_view,
        tr("Export Mode"),
        tr("Choose export type:"),
        options,
        0,
        false,
        &ok);

    if (!ok)
        return;

    if (choice == "Whole Tree")
        exportWholeScene();
    else if (choice == "Selected Area")
        exportSelectedArea();
    else if (choice == "Visible Area")
        exportVisibleArea();
    else
        exportTiled();
}

//////////////////////////////////////////////////////
// HELPERS
//////////////////////////////////////////////////////
void MenuController::exportWholeScene()
{
    QString path = QFileDialog::getSaveFileName(
        m_view,
        tr("Export PDF"),
        {},
        tr("PDF (*.pdf)"));

    if (path.isEmpty())
        return;

    if (!path.endsWith(".pdf"))
        path += ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(path);

    QGraphicsScene *scene = m_treeView->scenePtr();

    QRectF rect =
        scene->itemsBoundingRect().adjusted(-20, -20, 20, 20);

    printer.setPageSize(QPageSize(
        QSizeF(rect.width(), rect.height()),
        QPageSize::Point));

    QPainter painter(&printer);
    scene->render(&painter, QRectF(), rect);
}
void MenuController::exportVisibleArea()
{
    QString path = QFileDialog::getSaveFileName(
        m_view,
        tr("Export PDF"),
        {},
        tr("PDF (*.pdf)"));

    if (path.isEmpty())
        return;

    if (!path.endsWith(".pdf"))
        path += ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(path);

    QRectF visible =
        m_treeView->mapToScene(
                      m_treeView->viewport()->rect())
            .boundingRect();

    printer.setPageSize(QPageSize(
        QSizeF(visible.width(), visible.height()),
        QPageSize::Point));

    QPainter painter(&printer);
    m_treeView->scenePtr()->render(&painter,
                                   QRectF(),
                                   visible);
}
void MenuController::handleCropExport(const QRectF &rect)
{
    if (rect.width() < 10 || rect.height() < 10)
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

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(path);
    printer.setFullPage(true);
    printer.setPageMargins(QMarginsF(0, 0, 0, 0));

    // 🔥 Correct DPI conversion
    double dpi = printer.resolution();
    double widthPoints = (rect.width() / dpi) * 72.0;
    double heightPoints = (rect.height() / dpi) * 72.0;

    printer.setPageSize(QPageSize(
        QSizeF(widthPoints, heightPoints),
        QPageSize::Point));

    QPainter painter(&printer);
    if (!painter.isActive())
        return;

    scene->render(
        &painter,
        QRectF(0, 0, rect.width(), rect.height()),
        rect);
}
void MenuController::exportTiled()
{
    QString path = QFileDialog::getSaveFileName(
        m_view,
        tr("Export PDF"),
        {},
        tr("PDF (*.pdf)"));

    if (path.isEmpty())
        return;

    if (!path.endsWith(".pdf"))
        path += ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(path);

    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setFullPage(true);

    QGraphicsScene *scene = m_treeView->scenePtr();
    QRectF full = scene->itemsBoundingRect();

    QPainter painter(&printer);
    if (!painter.isActive())
        return;
    QRectF pageRect = printer.pageRect(QPrinter::Point);

    for (qreal y = full.top(); y < full.bottom(); y += pageRect.height())
    {
        for (qreal x = full.left(); x < full.right(); x += pageRect.width())
        {
            QRectF tile(x, y,
                        pageRect.width(),
                        pageRect.height());

            scene->render(&painter,
                          pageRect,
                          tile);

            bool isLastTile =
                (x + pageRect.width() >= full.right()) &&
                (y + pageRect.height() >= full.bottom());

            if (!isLastTile)
                printer.newPage();
        }
    }
}
void MenuController::exportSelectedArea()
{
    if (!m_treeView)
        return;

    QMessageBox::information(
        m_view,
        tr("Select Area"),
        tr("Drag to select export area."));

    m_treeView->enableCropMode(true);
}
