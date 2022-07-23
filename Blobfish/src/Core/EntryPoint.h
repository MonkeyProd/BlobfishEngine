#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

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
    delete app;
    return 0;
}

#endif //ENTRYPOINT_H
