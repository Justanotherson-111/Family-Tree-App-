#include "FamilyTreeView.h"
#include <QWheelEvent>
#include <QPainter>
#include "PersonInfoWidget.h"

namespace ui
{

    using core::entities::Gender;
    using core::entities::Marriage;
    using core::entities::PersonNode;
    ////////////////////////////////////////////////////////

    FamilyTreeView::FamilyTreeView(QWidget *parent)
        : QGraphicsView(parent),
          m_scene(new QGraphicsScene(this))
    {
        setScene(m_scene);
        setRenderHint(QPainter::Antialiasing);
        setDragMode(QGraphicsView::ScrollHandDrag);

        m_scene->setBackgroundBrush(Qt::white);
    }

    ////////////////////////////////////////////////////////
    // Zoom
    ////////////////////////////////////////////////////////

    void FamilyTreeView::wheelEvent(QWheelEvent *e)
    {
        constexpr double S = 1.15;
        double s = e->angleDelta().y() > 0 ? S : 1 / S;
        scale(s, s);
    }

    ////////////////////////////////////////////////////////

    void FamilyTreeView::setFamilyTree(const core::FamilyTree *tree)
    {
        m_tree = tree;
        rebuild();
    }

    void FamilyTreeView::setMainLine(
        const QList<const PersonNode *> &line)
    {
        m_mainLine = QSet<const PersonNode *>(line.begin(), line.end());
    }

    ////////////////////////////////////////////////////////
    // Scene rebuild
    ////////////////////////////////////////////////////////

    void FamilyTreeView::rebuild()
    {
        // Save current view state
        QTransform oldTransform = transform();
        QPointF oldCenter = mapToScene(viewport()->rect().center());

        m_scene->clear();
        m_items.clear();

        if (!m_tree || !m_tree->ancestor())
            return;

        layoutMale(m_tree->ancestor(), 0, 0);

        m_scene->setSceneRect(m_scene->itemsBoundingRect());

        // Restore zoom
        setTransform(oldTransform);

        // Restore center
        centerOn(oldCenter);
    }

    ////////////////////////////////////////////////////////
    // Item helpers
    ////////////////////////////////////////////////////////

    PersonItem *FamilyTreeView::createItem(
        const PersonNode *p, int x, int y)
    {
        auto *item = new PersonItem(p);
        item->setPos(x, y);

        item->setMainLine(m_mainLine.contains(p));

        m_scene->addItem(item);
        m_items[p] = item;

        connectCommonSignals(item, p);
        return item;
    }

    void FamilyTreeView::connectCommonSignals(
        PersonItem *item,
        const PersonNode *p)
    {
        connect(item, &PersonItem::clicked,
                this, &FamilyTreeView::personClicked);

        connect(item, &PersonItem::requestRelayout,
                this, &FamilyTreeView::rebuild);

        connect(item, &PersonItem::requestEdit,
                this, [=]
                { emit personEditRequested(p); });

        connect(item, &PersonItem::requestRemove,
                this, [=]
                { emit personRemoveRequested(p); });

        connect(item, &PersonItem::requestToggleCollapse,
                this, [=](const PersonNode *node)
                {
                    // Toggle collapse in model
                    const_cast<PersonNode *>(node)->toggleCollapsed();

                    // Rebuild layout
                    rebuild(); });

        connect(item, &PersonItem::infoRequested,
                this, [=](const PersonNode *p)
                {
            auto *dialog = new PersonInfoWidget(this);

            dialog->setPerson(p);

            dialog->exec(); });
    }

    ////////////////////////////////////////////////////////
    // Subtree width
    ////////////////////////////////////////////////////////

    int FamilyTreeView::subtreeWidth(const PersonNode *node) const
    {
        if (!node || node->isCollapsed())
            return NODE_W;

        int total = 0;

        for (const Marriage &m : node->marriages())
        {
            int w = 0;

            const auto &children = m.children();

            for (auto *child : children)
                w += subtreeWidth(child) + GAP_SIBLING;

            if (!children.isEmpty())
                w -= GAP_SIBLING; // remove last extra gap
            else
                w = NODE_W;

            total += w + GAP_BETWEEN_WIVES;
        }

        if (!node->marriages().isEmpty())
            total -= GAP_BETWEEN_WIVES;

        return std::max(total, NODE_W);
    }

    ////////////////////////////////////////////////////////
    // Layout
    ////////////////////////////////////////////////////////

    int FamilyTreeView::layoutMale(
        const PersonNode *node, int x, int y)
    {
        if (!node)
            return 0;

        // ===== Male item =====
        auto *maleItem = createItem(node, x, y);

        connect(maleItem, &PersonItem::requestAddWife,
                this, [=]
                { emit personAddWifeRequested(node); });

        if (node->isCollapsed())
            return NODE_W;

        const auto &marriages = node->marriages();
        if (marriages.isEmpty())
            return NODE_W;

        int wx = x + NODE_W + GAP_HUSBAND_WIFE;
        int childY = y + GAP_GENERATION;
        int prevRightX = x + NODE_W;

        for (const Marriage &m : marriages)
        {
            const PersonNode *wifeNode = m.wife();

            // ===== Wife =====
            auto *wife = createItem(wifeNode, wx, y);

            connect(wife, &PersonItem::requestAddSon,
                    this, [=]
                    { emit personAddSonRequested(node, wifeNode); });

            connect(wife, &PersonItem::requestAddDaughter,
                    this, [=]
                    { emit personAddDaughterRequested(node, wifeNode); });

            // ===== Marriage line =====
            qreal husbandRightX = maleItem->pos().x() + NODE_W;
            qreal centerY = maleItem->pos().y() + NODE_H / 2;

            qreal wifeLeftX = wife->pos().x();

            auto *marriageLine = m_scene->addLine(
                husbandRightX,
                centerY,
                wifeLeftX,
                centerY);

            marriageLine->setZValue(0);

            // ===== Children =====
            QVector<PersonItem *> children;
            int cx = wx;

            for (auto *child : m.children())
            {
                if (child->gender() == Gender::Male)
                {
                    int used = layoutMale(child, cx, childY);
                    children.push_back(m_items[child]);
                    cx += used + GAP_SIBLING;
                }
                else
                {
                    auto *di = createItem(child, cx, childY);
                    children.push_back(di);
                    cx += NODE_W + GAP_SIBLING;
                }
            }

            // ===== Connectors =====
            if (!children.isEmpty())
            {
                // Mother bottom center
                qreal motherCenterX = wife->pos().x() + NODE_W / 2;
                qreal motherBottomY = wife->pos().y() + NODE_H;

                qreal barY = childY - CHILD_BAR_OFFSET;

                // Vertical line: mother bottom → horizontal bar
                m_scene->addLine(motherCenterX,
                                 motherBottomY,
                                 motherCenterX,
                                 barY);

                qreal firstChildCenter =
                    children.first()->pos().x() + NODE_W / 2;

                qreal lastChildCenter =
                    children.last()->pos().x() + NODE_W / 2;

                m_scene->addLine(firstChildCenter,
                                 barY,
                                 lastChildCenter,
                                 barY);

                for (auto *c : children)
                {
                    qreal childCenterX =
                        c->pos().x() + NODE_W / 2;

                    qreal childTopY =
                        c->pos().y();

                    m_scene->addLine(childCenterX,
                                     barY,
                                     childCenterX,
                                     childTopY);
                }
            }

            int wifeBlockW = std::max(NODE_W, cx - wx);
            wx += wifeBlockW + GAP_BETWEEN_WIVES;
        }

        return wx - x;
    }

    ////////////////////////////////////////////////////////

    void FamilyTreeView::zoomToFit()
    {
        QRectF r = m_scene->itemsBoundingRect();
        fitInView(r.adjusted(-40, -40, 40, 40),
                  Qt::KeepAspectRatio);
    }

    ////////////////////////////////////////////////////////

    void FamilyTreeView::updatePerson(const PersonNode *p)
    {
        if (auto it = m_items.find(p); it != m_items.end())
            it.value()->update();
    }

} // namespace ui
