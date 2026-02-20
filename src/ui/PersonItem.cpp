#include "PersonItem.h"
#include "entities/PersonNode.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QMenu>
#include <QGraphicsScene>
#include <QApplication>

namespace ui
{

    using core::entities::Gender;
    using core::entities::Marriage;
    using core::entities::PersonNode;

    PersonItem::PersonItem(
        const PersonNode *person,
        QGraphicsItem *parent)
        : QGraphicsObject(parent),
          m_person(person)
    {
        setFlags(ItemIsSelectable |
                 ItemIsMovable |
                 ItemSendsGeometryChanges);

        setAcceptedMouseButtons(Qt::AllButtons);
    }

    const PersonNode *PersonItem::person() const
    {
        return m_person;
    }

    void PersonItem::setSelected(bool s)
    {
        m_selected = s;
        update();
    }

    void PersonItem::setMainLine(bool m)
    {
        m_mainLine = m;
        update();
    }

    void PersonItem::setExtinct(bool e)
    {
        m_extinct = e;
        setOpacity(e ? 0.75 : 1.0);
        update();
    }

    QRectF PersonItem::boundingRect() const
    {
        return QRectF(0, 0, WIDTH, HEIGHT);
    }

    ////////////////////////////////////////////////////////////
    // Painting
    ////////////////////////////////////////////////////////////

    void PersonItem::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *,
        QWidget *)
    {
        painter->setRenderHint(QPainter::Antialiasing);

        painter->setPen(currentPen());
        painter->setBrush(currentBrush());

        const QRectF r = boundingRect();

        // Female = rounded
        if (m_person->gender() == Gender::Female)
            painter->drawRoundedRect(r, 8, 8);
        else
            painter->drawRect(r);

        // ===== Text =====
        painter->setPen(Qt::black);

        QString name = m_person->name();

        QString birth =
            m_person->birthDate().isValid()
                ? m_person->birthDate().toString("dd-MM-yyyy")
                : "?";

        QString line2 = QString("birth. %1").arg(birth);

        QString text = name + "\n" + line2;

        if (m_person->isDeceased())
        {
            QString death =
                m_person->deathDate().toString("dd-MM-yyyy");

            text += "\ndeath. " + death;
        }

        // Smaller font for multi-line
        QFont f = painter->font();
        f.setPixelSize(HEIGHT * 0.18);
        painter->setFont(f);

        painter->drawText(
            r.adjusted(4, 4, -4, -4),
            Qt::AlignCenter,
            text);

        // ===== Collapse indicator =====
        if (hasChildren())
        {
            const QString symbol =
                m_person->isCollapsed() ? "+" : "−";

            painter->setFont(QFont("", 10, QFont::Bold));

            painter->drawText(
                r.adjusted(4, 2, -6, -2),
                Qt::AlignTop | Qt::AlignRight,
                symbol);
        }
    }

    ////////////////////////////////////////////////////////////
    // Mouse
    ////////////////////////////////////////////////////////////

    void PersonItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *e)
    {
        if (e->button() == Qt::LeftButton)
        {
            emit infoRequested(m_person);
            e->accept();
            return;
        }

        QGraphicsObject::mouseDoubleClickEvent(e);
    }

    void PersonItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
    {
        if (e->button() == Qt::LeftButton)
        {
            // SHIFT + Click → collapse / expand
            if (e->modifiers() & Qt::ShiftModifier)
            {
                emit requestToggleCollapse(m_person);
                e->accept();
                return;
            }

            // Normal click → highlight
            emit clicked(m_person);

            QGraphicsObject::mousePressEvent(e); // allow selection
            return;
        }

        QGraphicsObject::mousePressEvent(e);
    }

    ////////////////////////////////////////////////////////////
    // Context Menu
    ////////////////////////////////////////////////////////////

    void PersonItem::contextMenuEvent(
        QGraphicsSceneContextMenuEvent *e)
    {
        QMenu menu;

        QAction *addSon =
            menu.addAction("Add Son");

        QAction *addDaughter =
            menu.addAction("Add Daughter");

        QAction *addWife =
            menu.addAction("Add Wife");

        menu.addSeparator();

        QAction *edit =
            menu.addAction("Edit");

        QAction *remove =
            menu.addAction("Remove");

        // Gender rules
        if (m_person->gender() == Gender::Male)
        {
            addSon->setEnabled(false);
            addDaughter->setEnabled(false);
        }
        else
        {
            addWife->setEnabled(false);
        }

        QAction *chosen =
            menu.exec(e->screenPos());

        if (!chosen)
            return;

        if (chosen == addSon)
            emit requestAddSon();
        else if (chosen == addDaughter)
            emit requestAddDaughter();
        else if (chosen == addWife)
            emit requestAddWife();
        else if (chosen == edit)
            emit requestEdit();
        else if (chosen == remove)
            emit requestRemove();
    }

    ////////////////////////////////////////////////////////////
    // Style helpers
    ////////////////////////////////////////////////////////////

    QPen PersonItem::currentPen() const
    {
        if (m_selected)
            return QPen(Qt::blue, 2);

        if (m_mainLine)
            return QPen(QColor(180, 140, 0), 3);

        return QPen(Qt::black, 1);
    }

    QBrush PersonItem::currentBrush() const
    {
        if (m_extinct)
            return QBrush(QColor(240, 240, 240));

        return QBrush(QColor(245, 245, 245));
    }

    ////////////////////////////////////////////////////////////
    // Helpers
    ////////////////////////////////////////////////////////////

    bool PersonItem::hasChildren() const
    {
        for (const auto &m : m_person->marriages())
        {
            if (!m.children().isEmpty())
                return true;
        }
        return false;
    }
    QVariant PersonItem::itemChange(GraphicsItemChange change,
                                    const QVariant &value)
    {
        if (change == ItemPositionChange)
        {
            QPointF newPos = value.toPointF();

            // Only restrict during mouse drag
            if (QApplication::mouseButtons() != Qt::NoButton)
            {
                newPos.setY(pos().y());
            }

            return newPos;
        }

        if (change == ItemPositionHasChanged)
            emit positionChanged(m_person, pos());

        if (change == ItemSelectedChange)
        {
            m_selected = value.toBool();
            update();
        }

        return QGraphicsObject::itemChange(change, value);
    }
}
