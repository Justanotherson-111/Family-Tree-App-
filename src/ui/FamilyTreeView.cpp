#include "FamilyTreeView.h"
#include "ConnectionItem.h"
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

        // connect(item, &PersonItem::positionChanged,
        //         this,
        //         [=](const PersonNode *p, const QPointF &newPos)
        //         {
        //             if (!m_items.contains(p))
        //                 return;

        //             static bool adjusting = false;
        //             if (adjusting)
        //                 return;

        //             adjusting = true;

        //             QPointF finalPos = newPos;

        //             if (p->gender() == Gender::Male)
        //             {
        //                 for (const Marriage &m : p->marriages())
        //                 {
        //                     PersonNode *wife = m.wife();
        //                     if (!m_items.contains(wife))
        //                         continue;

        //                     QPointF wpos = m_items[wife]->pos();
        //                     wpos.setY(finalPos.y());
        //                     m_items[wife]->setPos(wpos);
        //                 }
        //             }
        //             if (PersonNode *father = p->father())
        //             {
        //                 for (const Marriage &marriage : father->marriages())
        //                 {
        //                     const auto &children = marriage.children();

        //                     if (!children.contains(const_cast<PersonNode *>(p)))
        //                         continue;

        //                     if (!children.isEmpty() && children.first() == p)
        //                     {
        //                         for (PersonNode *sibling : children)
        //                         {
        //                             if (sibling == p)
        //                                 continue;

        //                             if (!m_items.contains(sibling))
        //                                 continue;

        //                             QPointF spos = m_items[sibling]->pos();
        //                             spos.setY(finalPos.y());
        //                             m_items[sibling]->setPos(spos);
        //                         }
        //                     }

        //                     break;
        //                 }
        //             }

        //             adjusting = false;
        //         });
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

        PersonItem *previousWifeItem = nullptr;

        for (const Marriage &m : marriages)
        {
            const PersonNode *wifeNode = m.wife();

            // ===== Wife =====
            auto *wifeItem = createItem(wifeNode, wx, y);

            connect(wifeItem, &PersonItem::requestAddSon,
                    this, [=]
                    { emit personAddSonRequested(node, wifeNode); });

            connect(wifeItem, &PersonItem::requestAddDaughter,
                    this, [=]
                    { emit personAddDaughterRequested(node, wifeNode); });

            // Husband → First Wife
            //    Wife Chain for subsequent wives

            if (!previousWifeItem)
            {
                // Husband → First Wife
                auto *connector =
                    new ConnectionItem(maleItem, wifeItem);
                m_scene->addItem(connector);
            }
            else
            {
                // Wife(i-1) → Wife(i)
                auto *connector =
                    new ConnectionItem(previousWifeItem, wifeItem);
                m_scene->addItem(connector);
            }

            // Layout Children

            QVector<PersonItem *> children;
            int cx = wx;

            for (auto *child : m.children())
            {
                PersonItem *childItem = nullptr;

                if (child->gender() == Gender::Male)
                {
                    int used = layoutMale(child, cx, childY);
                    childItem = m_items[child];
                    cx += used + GAP_SIBLING;
                }
                else
                {
                    childItem = createItem(child, cx, childY);
                    cx += NODE_W + GAP_SIBLING;
                }

                children.push_back(childItem);
            }

            // Wife → Children Connection

            if (!children.isEmpty())
            {
                auto *childrenConnector =
                    new ConnectionItem(wifeItem,
                                       nullptr,
                                       children);

                m_scene->addItem(childrenConnector);
            }

            // Advance Horizontal Position

            int wifeBlockWidth =
                std::max(NODE_W, cx - wx);

            wx += wifeBlockWidth + GAP_BETWEEN_WIVES;

            previousWifeItem = wifeItem;
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
