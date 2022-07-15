//
// Created by plasm on 15.07.2022.
//

#ifndef COMPOUND_INPUTUTILS_H
#define COMPOUND_INPUTUTILS_H

#include "BlobPCH.h"

namespace Blobfish{
        class Input{
            public:
            static bool IsKeyPressed(int key);

            static bool IsMouseButtonPressed(int button);

            static std::pair<float, float> GetMousePosition();

            static float GetMouseX();

            static float GetMouseY();
        };
}

#endif //COMPOUND_INPUTUTILS_H
