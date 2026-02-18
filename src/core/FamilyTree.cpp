#include "FamilyTree.h"
#include "rules/FamilyRules.h"

namespace core
{

    using entities::Gender;
    using entities::Marriage;
    using entities::PersonNode;
    using rules::FamilyRules;

    FamilyTree::FamilyTree(PersonNode *ancestor)
        : m_ancestor(ancestor)
    {
    }

    FamilyTree::~FamilyTree()
    {
        cleanup(m_ancestor);
    }

    PersonNode *FamilyTree::ancestor() const
    {
        return m_ancestor;
    }

    void FamilyTree::setAncestor(PersonNode *ancestor)
    {
        m_ancestor = ancestor;
    }

    bool FamilyTree::addMarriage(PersonNode *husband,
                                 PersonNode *wife)
    {
        if (!husband || !wife)
            return false;

        if (!FamilyRules::canContinueLineage(husband))
            return false;

        husband->addMarriage(Marriage(wife));
        return true;
    }

    bool FamilyTree::addSon(PersonNode *father,
                            PersonNode *mother,
                            PersonNode *son,
                            int birthOrder)
    {
        if (!father || !mother || !son)
            return false;

        if (son->gender() != Gender::Male)
            return false;

        for (auto &marriage : father->m_marriages)
        {
            if (marriage.wife() == mother)
            {
                if (birthOrder < 0 ||
                    birthOrder > marriage.sons().size())
                    return false;

                son->m_father = father;
                son->m_mother = mother;
                marriage.addSon(son, birthOrder);
                return true;
            }
        }

        return false;
    }

    bool FamilyTree::addDaughter(PersonNode *father,
                                 PersonNode *mother,
                                 PersonNode *daughter)
    {
        if (!father || !mother || !daughter)
            return false;

        if (daughter->gender() != Gender::Female)
            return false;

        for (auto &marriage : father->m_marriages)
        {
            if (marriage.wife() == mother)
            {
                daughter->m_father = father;
                daughter->m_mother = mother;
                marriage.addDaughter(daughter);
                return true;
            }
        }

        return false;
    }

    bool FamilyTree::canRemove(const PersonNode *person) const
    {
        if (!person)
            return false;

        if (person == m_ancestor)
            return false;

        for (const auto &m : person->marriages())
        {
            if (!m.sons().isEmpty() ||
                !m.daughters().isEmpty())
                return false;
        }

        if (person->gender() == Gender::Male &&
            !person->marriages().isEmpty())
            return false;

        return true;
    }

    bool FamilyTree::removePerson(const PersonNode *person)
    {
        if (!person)
            return false;

        // CASE 1: Child
        if (person->father())
        {
            auto *parent =
                const_cast<PersonNode *>(person->father());

            for (auto &m : parent->m_marriages)
            {
                m.m_sons.removeAll(
                    const_cast<PersonNode *>(person));

                m.m_daughters.removeAll(
                    const_cast<PersonNode *>(person));
            }

            delete person;
            return true;
        }

        // CASE 2: Wife
        if (person->gender() == Gender::Female)
        {
            std::function<bool(PersonNode *)> removeFrom =
                [&](PersonNode *male) -> bool
            {
                for (int i = 0;
                     i < male->m_marriages.size();
                     ++i)
                {
                    auto &m = male->m_marriages[i];

                    if (m.wife() == person)
                    {
                        for (auto *s : m.m_sons)
                            cleanup(s);

                        for (auto *d : m.m_daughters)
                            delete d;

                        delete m.m_wife;
                        male->m_marriages.removeAt(i);
                        return true;
                    }
                }

                for (auto &m : male->m_marriages)
                    for (auto *s : m.m_sons)
                        if (removeFrom(s))
                            return true;

                return false;
            };

            return removeFrom(m_ancestor);
        }

        return false;
    }

    bool FamilyTree::removeWife(PersonNode *husband,
                                PersonNode *wife)
    {
        if (!husband || !wife)
            return false;

        for (int i = 0;
             i < husband->m_marriages.size();
             ++i)
        {
            auto &m = husband->m_marriages[i];

            if (m.wife() == wife)
            {
                for (auto *s : m.m_sons)
                    cleanup(s);

                for (auto *d : m.m_daughters)
                    delete d;

                delete m.m_wife;
                husband->m_marriages.removeAt(i);
                return true;
            }
        }

        return false;
    }

    void FamilyTree::cleanup(PersonNode *p)
    {
        if (!p)
            return;

        for (auto &m : p->m_marriages)
        {
            for (auto *s : m.m_sons)
                cleanup(s);

            for (auto *d : m.m_daughters)
                delete d;

            delete m.m_wife;
        }

        delete p;
    }
    QString FamilyTree::generateId()
    {
        while (m_usedIds.contains(m_nextId))
            ++m_nextId;

        int id = m_nextId;
        m_usedIds.insert(id);
        ++m_nextId;

        return QString::number(id);
    }

    void FamilyTree::registerId(const QString &id)
    {
        bool ok;
        int val = id.toInt(&ok);

        if (!ok)
            return;

        m_usedIds.insert(val);

        if (val >= m_nextId)
            m_nextId = val + 1;
    }
    void FamilyTree::rebuildIdRegistry()
    {
        m_usedIds.clear();
        m_nextId = 1;

        std::function<void(PersonNode *)> scan =
            [&](PersonNode *p)
        {
            if (!p)
                return;

            registerId(p->id());

            for (auto &m : p->m_marriages)
            {
                registerId(m.wife()->id());

                for (auto *s : m.m_sons)
                    scan(s);

                for (auto *d : m.m_daughters)
                    registerId(d->id());
            }
        };

        scan(m_ancestor);
    }

}
