#pragma once

#include <QSet>
#include "entities/PersonNode.h"

namespace core
{

    class FamilyTree
    {
    public:
        explicit FamilyTree(entities::PersonNode *ancestor);
        ~FamilyTree();

        entities::PersonNode *ancestor() const;
        void setAncestor(entities::PersonNode *ancestor);

        bool addMarriage(entities::PersonNode *husband,
                         entities::PersonNode *wife);

        bool addSon(entities::PersonNode *father,
                    entities::PersonNode *mother,
                    entities::PersonNode *son,
                    int birthOrder);

        bool addDaughter(entities::PersonNode *father,
                         entities::PersonNode *mother,
                         entities::PersonNode *daughter,
                         int birthOrder);

        bool canRemove(const entities::PersonNode *person) const;
        bool removePerson(const entities::PersonNode *person);
        bool removeWife(entities::PersonNode *husband,
                        entities::PersonNode *wife);

        QString generateId();
        void registerId(const QString &id);
        void rebuildIdRegistry();

    private:
        entities::PersonNode *m_ancestor = nullptr;

        void cleanup(entities::PersonNode *person);

        QSet<int> m_usedIds;
        int m_nextId = 1;
    };

}
