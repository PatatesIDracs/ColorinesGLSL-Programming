#ifndef MESHRENDERERUI_H
#define MESHRENDERERUI_H

#include <QWidget>

class CompMeshRenderer;
class ResourceMesh;

namespace Ui {
class MeshRendererUI;
}

class MeshRendererUI : public QWidget
{
    Q_OBJECT

public:
    explicit MeshRendererUI(QWidget *parent = nullptr);
    ~MeshRendererUI();

    void SetCompMeshRenderer(CompMeshRenderer* newCompMeshRenderer, QVector<ResourceMesh*>* meshResources);
    void UpdateList();

private:


public slots:
    void ChangeResourceMesh();


public:
    QVector<ResourceMesh*>* resourceVector;

private:
    Ui::MeshRendererUI *ui;
    CompMeshRenderer* compMeshRenderer;
};

#endif // MESHRENDERERUI_H
