# Project 2 - OpenGL model viewer
made by Joan Pareja Piñol and Pere Rifà Planelles

**NOTE:** Look at the readme.PDF to see images and render techniques

## User Guide:
**Load models/textures:** The engine can load .obj files as models and load .png and .jpg as textures. 
To load models use the File->Open File button in the main menu and select the model you want to load, when it’s 
loaded it will ask if you want to create a game object with the loaded model, select yes to do so or no to just 
load the model as a resource. To load a texture use the File->Load Texture button and simply select the texture to 
load and it will load the texture as a resource.

**Change Render techniques:** You can change which technique is used to render the final image at any time using the 
Display menu in the toolbar. Open the menu and simply select the technique you want to be use at the render.

**Pre loaded models:** There are 2 preloaded models with textures to test the rendering techniques, one is Patrick from spongebob and the other is a castle (sponza.obj).
**Note:** Castle model (sponza.obj) is to big and it must be resized to 0,01 scale in all axis in order to be displayed correctly.

**Adding and removing GO:** To add or remove game objects from the scene simply use the buttons below the Hierarchy display,
note that remove Entity will only work it a gameobject is selected.

**Transform Inspector:** It is possible to change the transformation of any game object using the transformation window in the inspector.

**Mesh renderer:** When selecting a game object you can change their model and textures using the inspector. When selecting a mesh you may have to reselect the game object in order for the inspector to update and show all the submeshes in the mesh, with each submesh you can select a texture to use for rendering.
Loading a new model won’t set the texture so you must set them manually.

**Scene navigation:** 
 - W/A/S/D: Move the camera
 - Left mouse-click: Rotate the camera.
 
 
 ## Render techniques:

**Color:** Simple color render.     
**Normals:** Render of the model normals.     
**Position:** Render of the scene position.      
**Depth:** Depth buffer of the scene rendered.     
**Final Ligth:** Combination of the color, normal and position renders to obtain the lighting values, light used is a static directional light.     
**Blur:** Blured render of the final light render, used to compute depth of field.     
**Depth of Field:** Blur the objects too close or too far from the camera, focusing on one spot.      
