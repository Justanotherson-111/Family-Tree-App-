#pragma once

#include <QMenuBar>
#include <QAction>

namespace ui
{

    class MenuView : public QMenuBar
    {
        Q_OBJECT

    public:
        explicit MenuView(QWidget *parent = nullptr);

    signals:
        void newRequested();
        void saveRequested();
        void loadRequested();
        void deleteRequested();
        void exitRequested();
        void exportPdfRequested();

    private:
        QAction *m_newAct = nullptr;
        QAction *m_saveAct = nullptr;
        QAction *m_loadAct = nullptr;
        QAction *m_deleteAct = nullptr;
        QAction *m_exitAct = nullptr;
        QAction *m_exportPdfAct = nullptr;

        void buildMenus();
    };

}
