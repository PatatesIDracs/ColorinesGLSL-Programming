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

void Inspector::TextChanged()
{
    if(current_go != nullptr)
    {
        current_go->name = name->text();
        emit SigNameChanged();
    }
}

