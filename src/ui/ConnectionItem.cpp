#include "ConnectionItem.h"
#include "PersonItem.h"

#include <QPainter>
#include <QPen>

namespace ui
{

    //////////////////////////////////////////////////////////////
    // Constructor: Marriage Only
    //////////////////////////////////////////////////////////////

    ConnectionItem::ConnectionItem(PersonItem *a,
                                   PersonItem *b,
                                   QGraphicsItem *parent)
        : QGraphicsObject(parent),
          m_a(a),
          m_b(b)
    {
        setZValue(0);

        updatePosition();

        connect(a, &PersonItem::positionChanged,
                this, &ConnectionItem::updatePosition);

        if (b)
        {
            connect(b, &PersonItem::positionChanged,
                    this, &ConnectionItem::updatePosition);
        }
    }

    //////////////////////////////////////////////////////////////
    // Constructor: Marriage + Children
    //////////////////////////////////////////////////////////////

    ConnectionItem::ConnectionItem(PersonItem *husband,
                                   PersonItem *wife,
                                   const QVector<PersonItem *> &children,
                                   QGraphicsItem *parent)
        : QGraphicsObject(parent),
          m_a(husband),
          m_b(wife),
          m_children(children),
          m_hasChildren(true)
    {
        setZValue(0);

        updatePosition();

        connect(m_a, &PersonItem::positionChanged,
                this, &ConnectionItem::updatePosition);

        if (m_b)
        {
            connect(m_b, &PersonItem::positionChanged,
                    this, &ConnectionItem::updatePosition);
        }

        for (auto *child : m_children)
        {
            connect(child, &PersonItem::positionChanged,
                    this, &ConnectionItem::updatePosition);
        }
    }

    //////////////////////////////////////////////////////////////
    // updatePosition()
    //////////////////////////////////////////////////////////////

    void ConnectionItem::updatePosition()
    {
        if (!m_a)
            return;

        QPainterPath path;

        QRectF ra = m_a->sceneBoundingRect();

        // Husband -> Wife
        if (m_b)
        {
            QRectF rb = m_b->sceneBoundingRect();

            QPointF rightA(ra.right(), ra.center().y());
            QPointF leftB(rb.left(), rb.center().y());

            path.moveTo(rightA);
            path.lineTo(leftB);
        }

        // Wife -> Children
        if (m_hasChildren && !m_children.isEmpty())
        {
            QRectF wifeRect = m_b ? m_b->sceneBoundingRect() : ra;

            QPointF wifeBottom(wifeRect.center().x(),
                               wifeRect.bottom());

            QRectF firstRect = m_children.first()->sceneBoundingRect();
            qreal branchY = firstRect.top() - 10;

            QPointF downPoint(wifeBottom.x(), branchY);

            // Vertical from wife
            path.moveTo(wifeBottom);
            path.lineTo(downPoint);

            // Horizontal sibling bar
            QRectF lastRect = m_children.last()->sceneBoundingRect();

            QPointF leftBar(m_children.first()->sceneBoundingRect().center().x(), branchY);
            QPointF rightBar(lastRect.center().x(), branchY);

            path.moveTo(leftBar);
            path.lineTo(rightBar);

            // Vertical drops to children
            for (auto *child : m_children)
            {
                QRectF rc = child->sceneBoundingRect();

                QPointF topChild(rc.center().x(), rc.top());

                path.moveTo(QPointF(rc.center().x(), branchY));
                path.lineTo(topChild);
            }
        }

        prepareGeometryChange();
        m_path = path;
        update();
    }

    //////////////////////////////////////////////////////////////
    // boundingRect()
    //////////////////////////////////////////////////////////////

    QRectF ConnectionItem::boundingRect() const
    {
        return m_path.boundingRect().adjusted(-2, -2, 2, 2);
    }

    //////////////////////////////////////////////////////////////
    // paint()
    //////////////////////////////////////////////////////////////

    void ConnectionItem::paint(QPainter *painter,
                               const QStyleOptionGraphicsItem *,
                               QWidget *)
    {
        painter->setPen(QPen(Qt::black, 1));
        painter->drawPath(m_path);
    }

} // namespace ui