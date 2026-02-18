#include "JsonMapper.h"

#include <QJsonArray>

using core::FamilyTree;
using core::entities::Gender;
using core::entities::PersonNode;

namespace data
{

    // ---------- JSON Keys ----------
    static const char *KEY_ID = "id";
    static const char *KEY_NAME = "name";
    static const char *KEY_GENDER = "gender";
    static const char *KEY_MARRIAGES = "marriages";
    static const char *KEY_WIFE = "wife";
    static const char *KEY_SONS = "sons";
    static const char *KEY_DAUGHTERS = "daughters";
    static const char *KEY_ANCESTOR = "ancestor";
    static const char *KEY_BIRTH = "birth";
    static const char *KEY_DEATH = "death";
    static const char *KEY_JOB = "job";

    // ---------- Parsing ----------

    PersonNode *JsonMapper::parsePerson(const QJsonObject &obj)
    {
        const QString id = obj[KEY_ID].toString();

        const QString name = obj[KEY_NAME].toString();

        const QString genderStr =
            obj[KEY_GENDER].toString();

        Gender gender = (genderStr == "Male") ? Gender::Male : Gender::Female;

        const QString job = obj[KEY_JOB].toString();

        const QDate birth = QDate::fromString(obj[KEY_BIRTH].toString(), Qt::ISODate);

        const QDate death = QDate::fromString(obj[KEY_DEATH].toString(), Qt::ISODate);

        return new PersonNode(
            id, name, gender, job, birth, death);
    }

    PersonNode *JsonMapper::parseMaleNode(const QJsonObject &obj, FamilyTree *tree)
    {
        PersonNode *father =
            parsePerson(obj);

        const auto marriages =
            obj[KEY_MARRIAGES].toArray();

        for (const auto &mVal : marriages)
        {
            const auto mObj =
                mVal.toObject();

            // Wife
            PersonNode *wife =
                parsePerson(
                    mObj[KEY_WIFE].toObject());

            tree->addMarriage(
                father, wife);

            // Sons
            int order = 0;

            for (const auto &sVal :
                 mObj[KEY_SONS].toArray())
            {
                PersonNode *son =
                    parseMaleNode(
                        sVal.toObject(),
                        tree);

                tree->addSon(
                    father,
                    wife,
                    son,
                    order++);
            }

            // Daughters
            for (const auto &dVal : mObj[KEY_DAUGHTERS].toArray())
            {
                PersonNode *daughter =
                    parsePerson(
                        dVal.toObject());

                tree->addDaughter(
                    father,
                    wife,
                    daughter);
            }
        }

        return father;
    }

    // ---------- From JSON ----------

    FamilyTree *
    JsonMapper::fromJson(const QJsonObject &root)
    {
        if (!root.contains(KEY_ANCESTOR))
            return nullptr;

        auto *tree =
            new FamilyTree(nullptr);

        PersonNode *realRoot =
            parseMaleNode(
                root[KEY_ANCESTOR].toObject(),
                tree);

        if (!realRoot)
        {
            delete tree;
            return nullptr;
        }

        tree->setAncestor(realRoot);

        return tree;
    }

    // ---------- To JSON ----------

    QJsonObject JsonMapper::personToJson(
        const PersonNode *p)
    {
        QJsonObject obj{
            {KEY_ID, p->id()},
            {KEY_NAME, p->name()},
            {KEY_GENDER,
             p->gender() == Gender::Male ? "Male" : "Female"}};

        if (!p->job().isEmpty())
            obj[KEY_JOB] = p->job();

        if (p->birthDate().isValid())
            obj[KEY_BIRTH] =
                p->birthDate().toString(Qt::ISODate);

        if (p->deathDate().isValid())
            obj[KEY_DEATH] =
                p->deathDate().toString(Qt::ISODate);

        return obj;
    }

    QJsonObject JsonMapper::toJson(const FamilyTree *tree)
    {
        const PersonNode *root =
            tree->ancestor();

        std::function<QJsonObject(
            const PersonNode *)>
            serializeMale =
                [&](const PersonNode *male)
        {
            QJsonObject obj =
                personToJson(male);

            QJsonArray marriages;

            for (const auto &m :
                 male->marriages())
            {
                QJsonObject mObj;

                mObj[KEY_WIFE] =
                    personToJson(
                        m.wife());

                QJsonArray sons;
                for (auto *s :
                     m.sons())
                    sons.append(
                        serializeMale(s));

                QJsonArray daughters;
                for (auto *d :
                     m.daughters())
                    daughters.append(
                        personToJson(d));

                mObj[KEY_SONS] =
                    sons;

                mObj[KEY_DAUGHTERS] =
                    daughters;

                marriages.append(
                    mObj);
            }

            obj[KEY_MARRIAGES] =
                marriages;

            return obj;
        };

        return {
            {KEY_ANCESTOR,
             serializeMale(root)}};
    }

}
