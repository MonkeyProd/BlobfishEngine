#pragma once

// CORE
#include <Core/Application.h>
#include <Core/Window.h>

// LAYERS
#include <Core/Layer.h>
#include <Core/LayerStack.h>
#include <ImGui/ImGuiLayer.h>

// EVENTS
#include <Event/Event.h>
#include <Event/KeyEvent.h>
#include <Event/MouseEvent.h>
#include <Event/WindowEvent.h>
#include <Event/CustomEvent.h>

// UTIL
#include <Core/InputUtils.h>
#include <Core/KeyCodes.h>
#include <Core/Logger.h>
#include <Core/Timestep.h>
#include <Core/TimeUtils.h>

// SCENE
#include <Scene/Scene.h>
#include <Scene/Entity.h>
#include <Scene/Components.h>

// RENDERER
#include <Renderer/Renderer.h>
#include <Renderer/Renderer2D.h>
#include <Renderer/RendererAPI.h>
#include <Renderer/RenderCommand.h>
#include <Renderer/RenderContext.h>
#include <Renderer/OrthographicCamera.h>
#include <Renderer/OrthographicCameraController.h>
#include <Renderer/Shader.h>
#include <Renderer/Texture.h>
#include <Renderer/SubTexture2D.h>
#include <Renderer/Buffer.h>               // TODO: do we need this????
#include <Renderer/VertexArray.h>          // TODO: and this
#include <Renderer/Framebuffer.h>