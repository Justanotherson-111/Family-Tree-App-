#pragma once

#include <QDialog>

class QLineEdit;
class QDateEdit;
class QTextEdit;
class QComboBox;
class QLabel;
class QPushButton;

namespace core::entities
{
    class PersonNode;
}

namespace ui
{
    class PersonInfoWidget : public QDialog
    {
        Q_OBJECT

    public:
        explicit PersonInfoWidget(QWidget *parent = nullptr);
        void setPerson(core::entities::PersonNode *p);

    // private slots:
    //     void onNameEdited();
    //     void onGenderChanged();
    //     void onJobEdited();
    //     void onBirthDateChanged();
    //     void onDeathDateChanged();
    //     void onNoteChanged();

    private:
        void setEditMode(bool enabled);
        void updateUiFromPerson();

        core::entities::PersonNode *m_person = nullptr;

        QLineEdit *m_nameEdit;
        QLineEdit *m_jobEdit;
        QDateEdit *m_birthEdit;
        QDateEdit *m_deathEdit;
        QTextEdit *m_noteEdit;
        QComboBox *m_genderCombo;
        QLabel *m_ancestralLineLabel;

        bool m_editMode = false;

        QPushButton *m_editButton;
        QPushButton *m_saveButton;
        QPushButton *m_cancelButton;
    };
}