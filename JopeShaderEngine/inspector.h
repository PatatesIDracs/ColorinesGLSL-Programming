#ifndef INSPECTOR_H
#define INSPECTOR_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class Transform;
class QVBoxLayout;
class QSpacerItem;
class GameObject;
class Renderer;

class Inspector : public QWidget
{
    Q_OBJECT

public:
    explicit Inspector(QWidget *parent = nullptr);
    ~Inspector();

signals:

    void SigNameChanged();

public:
    QLineEdit* name;
    QVBoxLayout* layout;
    QSpacerItem* spacer;

    GameObject* current_go = nullptr;

public slots:

    void TextChanged();
};

#endif // INSPECTOR_H
