#pragma once

#include <QGraphicsObject>
#include <QPainterPath>
#include <QVector>

namespace ui
{

    class PersonItem;

    class ConnectionItem : public QGraphicsObject
    {
        Q_OBJECT

    public:
        ConnectionItem(PersonItem *a,
                       PersonItem *b,
                       QGraphicsItem *parent = nullptr);

        ConnectionItem(PersonItem *husband,
                       PersonItem *wife,
                       const QVector<PersonItem *> &children,
                       QGraphicsItem *parent = nullptr);

        void updatePosition();

        QRectF boundingRect() const override;
        void paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *,
                   QWidget *) override;

    private:
        QPainterPath m_path;

        PersonItem *m_a = nullptr;
        PersonItem *m_b = nullptr;
        QVector<PersonItem *> m_children;
        bool m_hasChildren = false;
    };

}