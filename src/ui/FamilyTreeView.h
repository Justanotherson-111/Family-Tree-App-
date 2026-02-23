#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>
#include <QSet>

#include "FamilyTree.h"
#include "PersonItem.h"

namespace ui
{

    class FamilyTreeView : public QGraphicsView
    {
        Q_OBJECT

    public:
        explicit FamilyTreeView(QWidget *parent = nullptr);

        void setFamilyTree(const core::FamilyTree *tree);
        void setMainLine(const QList<const core::entities::PersonNode *> &line);
        void updatePerson(const core::entities::PersonNode *p);

        const QMap<const core::entities::PersonNode *, PersonItem *> &
        items() const { return m_items; }

        QGraphicsScene *scenePtr() const { return m_scene; }
        void zoomToFit();

    signals:
        void personClicked(const core::entities::PersonNode *);
        void personAddSonRequested(const core::entities::PersonNode *, const core::entities::PersonNode *);
        void personAddDaughterRequested(const core::entities::PersonNode *, const core::entities::PersonNode *);
        void personAddWifeRequested(const core::entities::PersonNode *);
        void personRemoveRequested(const core::entities::PersonNode *);
        void personEditRequested(const core::entities::PersonNode *);

    protected:
        void wheelEvent(QWheelEvent *event) override;

    private:
        // ===== Layout constants =====
        static constexpr int NODE_W = 220;
        static constexpr int NODE_H = 110;

        static constexpr int GAP_HUSBAND_WIFE = 30;
        static constexpr int GAP_BETWEEN_WIVES = 30;
        static constexpr int GAP_SIBLING = 30;
        static constexpr int GAP_GENERATION = 140;
        static constexpr int CHILD_BAR_OFFSET = 20;
        static constexpr int MARRIAGE_MARGIN = 10;
        static constexpr int VERTICAL_MARGIN = 8;
        QGraphicsScene *m_scene = nullptr;
        const core::FamilyTree *m_tree = nullptr;

        QMap<const core::entities::PersonNode *, PersonItem *> m_items;
        QSet<const core::entities::PersonNode *> m_mainLine;

        // ===== Layout =====
        int subtreeWidth(const core::entities::PersonNode *node) const;
        int layoutMale(const core::entities::PersonNode *node, int x, int y);

        // ===== Helpers =====
        PersonItem *createItem(const core::entities::PersonNode *p, int x, int y);
        void connectCommonSignals(PersonItem *item, const core::entities::PersonNode *p);

        void rebuild();
        };

}
