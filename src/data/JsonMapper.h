#pragma once

#include <QJsonObject>

#include "FamilyTree.h"
#include "entities/PersonNode.h"

namespace data
{

    class JsonMapper
    {
    public:
        static core::FamilyTree *
        fromJson(const QJsonObject &root);

        static QJsonObject
        toJson(const core::FamilyTree *tree);

    private:
        static core::entities::PersonNode *
        parseMaleNode(const QJsonObject &obj,
                      core::FamilyTree *tree);

        static core::entities::PersonNode *
        parsePerson(const QJsonObject &obj);

        static QJsonObject
        personToJson(const core::entities::PersonNode *p);
    };

}
