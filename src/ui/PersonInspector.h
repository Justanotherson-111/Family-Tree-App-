#pragma once

#include <QWidget>
#include <QDate>

class QLabel;
class QLineEdit;
class QComboBox;
class QDateEdit;

namespace core::entities
{
    class PersonNode;
}

namespace ui
{

    class PersonInspector : public QWidget
    {
        Q_OBJECT

    public:
        explicit PersonInspector(QWidget *parent = nullptr);

        void setPerson(core::entities::PersonNode *person);

    signals:
        void personEdited(
            core::entities::PersonNode *,
            bool requiresRelayout);

    private slots:
        void onNameEdited();
        void onGenderChanged();
        void onJobEdited();
        void onBirthDateChanged();
        void onDeathDateChanged();

    private:
        void updateUiFromPerson();
        void setEditorsEnabled(bool enabled);

        core::entities::PersonNode *m_person = nullptr;

        QLabel *m_idLabel = nullptr;
        QLineEdit *m_nameEdit = nullptr;
        QComboBox *m_genderCombo = nullptr;

        QLineEdit *m_jobEdit = nullptr;
        QDateEdit *m_birthDateEdit = nullptr;
        QDateEdit *m_deathDateEdit = nullptr;
        QLineEdit *m_noteEdit = nullptr;
        QLabel *m_ancestralLineLabel = nullptr;

    };

}
