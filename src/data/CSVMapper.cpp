#include "CSVMapper.h"

using core::FamilyTree;
using core::entities::Gender;
using core::entities::PersonNode;

namespace data
{

    // ------------------------------------------------
    // TO CSV
    // ------------------------------------------------

    static void collect(const PersonNode *p,
                        QMap<QString, const PersonNode *> &map)
    {
        if (!p || map.contains(p->id()))
            return;

        map[p->id()] = p;

        for (const auto &m : p->marriages())
        {
            auto *wife = m.wife();
            if (wife)
                map[wife->id()] = wife;

            for (auto *s : m.sons())
                collect(s, map);

            for (auto *d : m.daughters())
                collect(d, map);
        }
    }

    bool CSVMapper::toCSV(QTextStream &ts,
                          const PersonNode *root)
    {
        if (!root)
            return false;

        QMap<QString, const PersonNode *> map;

        std::function<void(const PersonNode *)> dfs =
            [&](const PersonNode *p)
        {
            if (!p || map.contains(p->id()))
                return;

            map[p->id()] = p;

            for (const auto &m : p->marriages())
            {
                if (m.wife())
                    map[m.wife()->id()] = m.wife();

                for (auto *s : m.sons())
                    dfs(s);
                for (auto *d : m.daughters())
                    dfs(d);
            }
        };

        dfs(root);

        for (const PersonNode *p : map)
        {
            QString father =
                p->father() ? p->father()->id() : "";
            QString mother =
                p->mother() ? p->mother()->id() : "";

            QStringList spouses;

            if (p->gender() == Gender::Male)
                for (const auto &m : p->marriages())
                    if (m.wife())
                        spouses << m.wife()->id();

            ts << p->id() << ","
               << p->name() << ","
               << (p->gender() == Gender::Male ? "Male" : "Female") << ","
               << p->birthDate().toString(Qt::ISODate) << ","
               << p->deathDate().toString(Qt::ISODate) << ","
               << p->job() << ","
               << father << ","
               << mother << ","
               << spouses.join(";") << "\n";
        }

        return true;
    }

    // ------------------------------------------------
    // FROM CSV
    // ------------------------------------------------

    FamilyTree *CSVMapper::fromCSV(QTextStream &ts)
    {
        struct Row
        {
            QString id, name, gender, birth, death, job, father, mother, spouses;
        };

        QList<Row> rows;
        QMap<QString, PersonNode *> people;

        ts.readLine(); // header

        // PASS 1 — Create nodes
        while (!ts.atEnd())
        {
            auto parts =
                ts.readLine().split(",", Qt::KeepEmptyParts);

            if (parts.size() < 9)
                continue;

            Row r{
                parts[0], parts[1], parts[2],
                parts[3], parts[4], parts[5],
                parts[6], parts[7], parts[8]};

            rows.append(r);

            Gender g =
                (r.gender == "Male") ? Gender::Male : Gender::Female;

            auto *p = new PersonNode(
                r.id,
                r.name,
                g,
                r.job,
                QDate::fromString(r.birth, Qt::ISODate),
                QDate::fromString(r.death, Qt::ISODate));

            people[r.id] = p;
        }

        auto *tree = new FamilyTree(nullptr);

        // PASS 2 — marriages
        for (const Row &r : rows)
        {
            if (r.spouses.isEmpty())
                continue;

            auto *man = people.value(r.id);
            if (!man || man->gender() != Gender::Male)
                continue;

            for (const auto &sid :
                 r.spouses.split(";", Qt::SkipEmptyParts))
            {
                auto *wife = people.value(sid);
                if (wife)
                    tree->addMarriage(man, wife);
            }
        }

        // PASS 3 — children
        QMap<QString, int> birthOrderMap;
        for (const Row &r : rows)
        {
            if (r.father.isEmpty() || r.mother.isEmpty())
                continue;

            auto *father = people.value(r.father);
            auto *mother = people.value(r.mother);
            auto *child = people.value(r.id);

            if (!father || !mother || !child)
                continue;

            QString key = father->id() + "_" + mother->id();

            int order = birthOrderMap.value(key, 0);

            if (child->gender() == Gender::Male)
            {
                tree->addSon(father, mother, child, order);

                birthOrderMap[key] = order + 1;
            }
            else
                tree->addDaughter(father, mother, child);
        }

        // PASS 4 — ancestor
        for (const Row &r : rows)
            if (r.father.isEmpty() && r.gender == "Male")
            {
                tree->setAncestor(
                    people.value(r.id));
                break;
            }

        return tree;
    }

}