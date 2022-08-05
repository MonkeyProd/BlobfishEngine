#ifndef COMPOUND_EDITOR_H
#define COMPOUND_EDITOR_H

#include <blobfish.h>
#include "EditorLayer.h"
#include <Core/EntryPoint.h>

using namespace bf;

class Editor : public Application {
public:
    Editor() {
        PushOverlay(new EditorLayer);
    }
};

namespace bf {
    Application *create_application() {
        return new Editor;
    }
}

#endif //COMPOUND_EDITOR_H
