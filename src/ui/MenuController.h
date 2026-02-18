#pragma once

#include <QObject>

namespace core
{
    class FamilyTree;
}
namespace ui
{
    class MenuView;
    class FamilyTreeView;
}

namespace ui
{

    class MenuController : public QObject
    {
        Q_OBJECT

    public:
        MenuController(MenuView *view,
                       core::FamilyTree *&treeRef,
                       FamilyTreeView *treeView,
                       QObject *parent = nullptr);

    signals:
        void treeReplaced(core::FamilyTree *);

    private:
        MenuView *m_view = nullptr;
        core::FamilyTree *&m_tree;

        FamilyTreeView *m_treeView = nullptr;
        void replaceTree(core::FamilyTree *newTree);

        void onNew();
        void onSave();
        void onLoad();
        void onDelete();
        void onExportPdf();
    };

}
