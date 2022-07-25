#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include "BlobPCH.h"
#include "KeyCodes.h"

namespace bf{
        class Input{
            public:
            static bool IsKeyPressed(Key key);

            static bool IsMouseButtonPressed(int button);

            static std::pair<float, float> GetMousePosition();

            static float GetMouseX();

            static float GetMouseY();
        };
}

#endif //INPUTUTILS_H
