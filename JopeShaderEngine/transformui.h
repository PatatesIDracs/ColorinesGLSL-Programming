#ifndef TRANSFORMUI_H
#define TRANSFORMUI_H

#include <QWidget>
class CompTransform;

namespace Ui {
class TransformUI;
}

class TransformUI : public QWidget
{
    Q_OBJECT

public:
    explicit TransformUI(QWidget *parent = nullptr);
    ~TransformUI();

    void SetCompTransform(CompTransform* newCompTransform);


public slots:
    void ChangePosition();
    void ChangeRotation();
    void ChangeScale();

private:
    Ui::TransformUI *ui;
    CompTransform* compTransform;

signals:
    void SigTransformUpdate();
};

#endif // TRANSFORMUI_H
