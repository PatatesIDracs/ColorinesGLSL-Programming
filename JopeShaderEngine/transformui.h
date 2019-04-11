#ifndef TRANSFORMUI_H
#define TRANSFORMUI_H

#include <QWidget>

namespace Ui {
class TransformUI;
}

class TransformUI : public QWidget
{
    Q_OBJECT

public:
    explicit TransformUI(QWidget *parent = nullptr);
    ~TransformUI();

private:
    Ui::TransformUI *ui;


signals:
    void SigTransformUpdate();
};

#endif // TRANSFORMUI_H
