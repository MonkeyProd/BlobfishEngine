//
// Created by plasm on 14.07.2022.
//

#ifndef COMPOUND_ENTRYPOINT_H
#define COMPOUND_ENTRYPOINT_H

#include "BlobPCH.h"
#include "Application.h"
#include "ImGui/ImGuiLayer.h"

extern bf::Application *bf::create_application();

int main() {
    spdlog::set_level(spdlog::level::trace);
    bf::Application *app = bf::create_application();
    BF_LOG_DEBUG("APPLICATION CREATED");
    app->run();
    BF_LOG_DEBUG("SUCCESSFUL EXIT");
    return 0;
}

#endif //COMPOUND_ENTRYPOINT_H
