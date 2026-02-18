#pragma once

#include <QString>
#include <QList>
#include <QDate>
namespace core
{
    class FamilyTree;
}

namespace core::entities
{

    class PersonNode;

    enum class Gender
    {
        Male,
        Female
    };

    ////////////////////////////////////////////////////////////
    /// Marriage
    ////////////////////////////////////////////////////////////

    class Marriage
    {
    public:
        explicit Marriage(PersonNode *wife);

        PersonNode *wife() const;

        const QList<PersonNode *> &sons() const;
        const QList<PersonNode *> &daughters() const;

    private:
        PersonNode *m_wife = nullptr;

        QList<PersonNode *> m_sons;
        QList<PersonNode *> m_daughters;

        friend class core::FamilyTree;

        void addSon(PersonNode *child, int index);
        void addDaughter(PersonNode *child);
    };

    ////////////////////////////////////////////////////////////
    /// PersonNode
    ////////////////////////////////////////////////////////////

    class PersonNode
    {
    public:
        PersonNode(const QString &id,
                   const QString &name,
                   Gender gender,
                   const QString &job = QString(),
                   const QDate &birthDate = QDate(),
                   const QDate &deathDate = QDate());

        // getters
        const QString &id() const;
        const QString &name() const;
        Gender gender() const;
        PersonNode *father() const;
        PersonNode *mother() const;

        const QList<Marriage> &marriages() const;

        const QString &job() const;
        const QDate &birthDate() const;
        const QDate &deathDate() const;
        bool isDeceased() const;

        // logic
        bool canContinueLineage() const;
        bool hasChildren() const;

        // mutations
        void rename(const QString &newName);
        void setGender(Gender g);

        void setJob(const QString &job);
        void setBirthDate(const QDate &date);
        void setDeathDate(const QDate &date);
        void clearDeathDate(); // mark alive again if needed

        // UI state
        bool isCollapsed() const;
        void toggleCollapsed();

    private:
        QString m_id;
        QString m_name;
        Gender m_gender;

        QString m_job;
        QDate m_birthDate;
        QDate m_deathDate; // invalid = alive

        PersonNode *m_father = nullptr;
        PersonNode *m_mother = nullptr;
        QList<Marriage> m_marriages;

        bool m_collapsed = false;

        friend class core::FamilyTree;

        void addMarriage(const Marriage &m);
    };

} // namespace core::entities
