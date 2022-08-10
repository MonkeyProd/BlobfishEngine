#ifndef COMPOUND_ENTITYEDITOR_H
#define COMPOUND_ENTITYEDITOR_H

#include <blobfish.h>

using namespace bf;

class EntityEditor {
public:
    void DisplayEntityEditorWindow(Scene &scene, glm::vec2 &viewportSize);

private:
    Entity m_SelectedEntity;

    template<class T, class F>
    bool DisplayComponent(F UIfunction, const char *title);

};


#endif //COMPOUND_ENTITYEDITOR_H
