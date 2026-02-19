#pragma once

#include <QDialog>

namespace core::entities
{
    class PersonNode;
}

class QLabel;
class QTextEdit;

namespace ui
{
    class PersonInfoWidget : public QDialog
    {
        Q_OBJECT

    public:
        explicit PersonInfoWidget(QWidget *parent = nullptr);
        void setPerson(const core::entities::PersonNode *p);

    private:
        QLabel *m_nameLabel;
        QLabel *m_birthLabel;
        QLabel *m_deathLabel;
        QLabel *m_jobLabel;
        QTextEdit *m_noteEdit;
    };
}