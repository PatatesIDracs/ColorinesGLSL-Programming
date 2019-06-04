#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <QWidget>
#include <QVector>
#include <QListWidgetItem>

namespace Ui {
class Hierarchy;
}

class Inspector;
class GameObject;
class Resource;
class ResourceMesh;
class ResourceMaterial;
class QOpenGLWidget;

class Hierarchy : public QWidget
{
    Q_OBJECT

public:
    explicit Hierarchy(QWidget *parent = nullptr, QOpenGLWidget* openGl = nullptr);
    ~Hierarchy();

    void DrawHierarchy(QWidget* scene);

    QVector<ResourceMaterial*>* GerMatResource() { return &matResources; }

signals:
     void SigHierarchyUpdate(GameObject*);
     void SigResourceUpdate(GameObject*);
     void SigRemoveObject(GameObject*);

public slots:

     void InitBaseModel();

     void CreateNewGO();
     void RemoveGO();

     void OnItemClicked();
     void OnNameChanged();

     void CreateNewScene();
     void OpenScene();
     void SaveScene();

     void OpenFile();
     void LoadTexture();

public:
    Inspector* inspector;
    QOpenGLWidget* openGLWidget;
private:
    Ui::Hierarchy *ui;

    QVector<GameObject*> objects;
    GameObject* selected;
    uint count;

    QVector<ResourceMesh*> meshResources;
    QVector<ResourceMaterial*> matResources;

    // QVector<Resource*> resources;
    uint resourceCount;

private:
    void PrintObjects();

    ResourceMesh* CreateMesh(QString fileName);
    ResourceMaterial* CreateMaterial(QString fileName);

};

#endif // HIERARCHY_H
