#include "PersonNode.h"

namespace core::entities
{

    ////////////////////////////////////////////////////////////
    /// PersonNode
    ////////////////////////////////////////////////////////////

    PersonNode::PersonNode(const QString &id,
                           const QString &name,
                           Gender gender,
                           const QString &job,
                           const QDate &birthDate,
                           const QDate &deathDate,
                           const QString &note)
        : m_id(id),
          m_name(name),
          m_gender(gender),
          m_job(job),
          m_birthDate(birthDate),
          m_deathDate(deathDate),
          m_note(note)
    {
    }

    ////////////////////////////////////////////////////////////
    // Getters
    ////////////////////////////////////////////////////////////

    const QString &PersonNode::id() const { return m_id; }
    const QString &PersonNode::name() const { return m_name; }
    Gender PersonNode::gender() const { return m_gender; }
    PersonNode *PersonNode::father() const { return m_father; }
    PersonNode *PersonNode::mother() const { return m_mother; }

    const QList<Marriage> &PersonNode::marriages() const
    {
        return m_marriages;
    }

    const QString &PersonNode::job() const
    {
        return m_job;
    }

    const QDate &PersonNode::birthDate() const
    {
        return m_birthDate;
    }

    const QDate &PersonNode::deathDate() const
    {
        return m_deathDate;
    }

    bool PersonNode::isDeceased() const
    {
        return m_deathDate.isValid();
    }

    ////////////////////////////////////////////////////////////
    // Logic
    ////////////////////////////////////////////////////////////

    bool PersonNode::canContinueLineage() const
    {
        return m_gender == Gender::Male;
    }

    bool PersonNode::hasChildren() const
    {
        for (const auto &m : m_marriages)
        {
            if (!m.children().isEmpty())
                return true;
        }
        return false;
    }

    ////////////////////////////////////////////////////////////
    // Mutations
    ////////////////////////////////////////////////////////////

    void PersonNode::rename(const QString &newName)
    {
        if (!newName.trimmed().isEmpty())
            m_name = newName;
    }

    void PersonNode::setGender(Gender g)
    {
        if (m_gender != g)
            m_gender = g;
    }

    void PersonNode::setJob(const QString &job)
    {
        m_job = job;
    }

    void PersonNode::setBirthDate(const QDate &date)
    {
        m_birthDate = date;
    }

    void PersonNode::setDeathDate(const QDate &date)
    {
        m_deathDate = date;
    }

    void PersonNode::clearDeathDate()
    {
        m_deathDate = QDate();
    }
    const QString &PersonNode::note() const
    {
        return m_note;
    }

    void PersonNode::setNote(const QString &note)
    {
        m_note = note;
    }

    ////////////////////////////////////////////////////////////
    // UI State
    ////////////////////////////////////////////////////////////

    bool PersonNode::isCollapsed() const
    {
        return m_collapsed;
    }

    void PersonNode::toggleCollapsed()
    {
        m_collapsed = !m_collapsed;
    }

    void PersonNode::addMarriage(const Marriage &m)
    {
        if (canContinueLineage())
            m_marriages.append(m);
    }

    ////////////////////////////////////////////////////////////
    /// Marriage
    ////////////////////////////////////////////////////////////

    Marriage::Marriage(PersonNode *wife)
        : m_wife(wife)
    {
    }

    PersonNode *Marriage::wife() const { return m_wife; }

    void Marriage::addChild(PersonNode *child, int birthOrder)
    {
        if (!child)
            return;

        if (birthOrder < 0 || birthOrder > m_children.size())
            birthOrder = m_children.size();

        m_children.insert(birthOrder, child);
    }

    const QList<PersonNode *> &Marriage::children() const
    {
        return m_children;
    }

} // namespace core::entities
