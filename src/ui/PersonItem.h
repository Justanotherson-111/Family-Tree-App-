#pragma once

#include <QGraphicsObject>
#include <QPen>
#include <QBrush>

#include "entities/PersonNode.h"

namespace ui
{

    class PersonItem : public QGraphicsObject
    {
        Q_OBJECT

    public:
        explicit PersonItem(
            const core::entities::PersonNode *person,
            QGraphicsItem *parent = nullptr);

        const core::entities::PersonNode *person() const;

        void setSelected(bool selected);
        void setMainLine(bool mainLine);
        void setExtinct(bool extinct);

        QRectF boundingRect() const override;
        QVariant itemChange(GraphicsItemChange change,
                            const QVariant &value) override;

    signals:
        void requestAddSon();
        void requestAddDaughter();
        void requestAddWife();
        void requestRemove();
        void requestEdit();

        void clicked(const core::entities::PersonNode *);
        void infoRequested(const core::entities::PersonNode *);
        void requestToggleCollapse(const core::entities::PersonNode *);

        void requestRelayout();

    protected:
        void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
        void mousePressEvent(QGraphicsSceneMouseEvent *) override;
        void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *) override;
        void contextMenuEvent(QGraphicsSceneContextMenuEvent *) override;

    private:
        const core::entities::PersonNode *m_person;

        bool m_selected = false;
        bool m_mainLine = false;
        bool m_extinct = false;

        static constexpr int WIDTH = 220;
        static constexpr int HEIGHT = 110;

        QPen currentPen() const;
        QBrush currentBrush() const;

        bool hasChildren() const;
    };

}
