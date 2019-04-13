#ifndef MESHRENDERERUI_H
#define MESHRENDERERUI_H

#include <QWidget>

namespace Ui {
class MeshRendererUI;
}

class MeshRendererUI : public QWidget
{
    Q_OBJECT

public:
    explicit MeshRendererUI(QWidget *parent = nullptr);
    ~MeshRendererUI();

private:
    Ui::MeshRendererUI *ui;
};

#endif // MESHRENDERERUI_H
