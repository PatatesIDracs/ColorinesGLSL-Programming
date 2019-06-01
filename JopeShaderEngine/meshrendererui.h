#ifndef MESHRENDERERUI_H
#define MESHRENDERERUI_H

#include <QWidget>

class CompMeshRenderer;
class ResourceMesh;
class ResourceMaterial;
class QComboBox;
class QLabel;
class QHBoxLayout;

namespace Ui {
class MeshRendererUI;
}

class MeshRendererUI : public QWidget
{
    Q_OBJECT

public:
    explicit MeshRendererUI(QWidget *parent = nullptr);
    ~MeshRendererUI();

    void SetCompMeshRenderer(CompMeshRenderer* newCompMeshRenderer, QVector<ResourceMesh*>* meshResources, QVector<ResourceMaterial*>* matResources);
    void UpdateList();

private:


public slots:
    void ChangeResourceMesh();
    void ChangeResourceMaterials();

public:
    QVector<ResourceMesh*>* resourceMeshVector;
    QVector<ResourceMaterial*>* resourceMaterialvector;

    QVector<QComboBox*> materialComboBoxes;
    QVector<QLabel*> materialLabels;
    QVector<QHBoxLayout*> materialLayouts;

private:
    Ui::MeshRendererUI *ui;
    CompMeshRenderer* compMeshRenderer;
};

#endif // MESHRENDERERUI_H
