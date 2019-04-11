#include "inspector.h"
#include "gameobject.h"

#include <QLayout>
#include <QBoxLayout>
#include <QSpacerItem>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <iostream>
#include "transformui.h"


Inspector::Inspector(QWidget *parent) :
    QWidget(parent)
{

    //Subwidgets --> Add transform and others
    name = new QLineEdit();
    spacer = new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Expanding);

    //Set the layout
    layout = new QVBoxLayout;
    layout->addWidget(name);
    layout->addItem(spacer);
    setLayout(layout);

    //Slot connections
    connect(name,SIGNAL(editingFinished()),this, SLOT(TextChanged()));
}

Inspector::~Inspector()
{
}

void Inspector::SetSelectedGO(GameObject *selected)
{
    if(current_go != nullptr)
    {
        layout->removeItem(spacer);
        current_go->HideInspectorLayout(layout);
        layout->addItem(spacer);
    }

    current_go = selected;
    name->setText(current_go->name);
    layout->removeItem(spacer);
    current_go->SetInspectorLayout(layout);

    layout->addItem(spacer);

}

void Inspector::ItemSelected(GameObject *selected)
{
    SetSelectedGO(selected);
}

void Inspector::TextChanged()
{
    if(current_go != nullptr)
    {
        current_go->name = name->text();
        emit SigNameChanged();
    }
}

