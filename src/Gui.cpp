#include "Gui.h"
#include "SceneGame.h"

void Gui::SetImGuiDarkStyleMode()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);

    colors[ImGuiCol_WindowBg] = ImVec4(0.07f, 0.07f, 0.07f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);

    colors[ImGuiCol_Border] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    colors[ImGuiCol_FrameBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);

    colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);

    colors[ImGuiCol_Header] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);

    colors[ImGuiCol_Tab] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

    colors[ImGuiCol_TitleBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);

    colors[ImGuiCol_SliderGrab] = ImVec4(0.55f, 0.55f, 0.55f, 1.0f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.75f, 0.75f, 0.75f, 1.0f);

    style.WindowRounding = 6.0f;
    style.FrameRounding = 4.0f;
    style.PopupRounding = 4.0f;
    style.TabRounding = 4.0f;
}

void Gui::init(SDL_Renderer* renderer, SDL_Window* window)
{
    m_window = window;
    m_renderer = renderer;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    SetImGuiDarkStyleMode();

    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    ImGuiIO& io = ImGui::GetIO();

    ImFontConfig cfg;
    cfg.SizePixels = 11.0f;
    m_smallFont = io.Fonts->AddFontDefault(&cfg);
}

Gui::Gui(SceneGame& game, EntityManager& entityManager, MovementSystem& movementSystem, PhysicsSystem& physicsSystem, AudioSystem& audioSystem) : 
    m_game(game), m_entityManager(entityManager), m_movementSystem(movementSystem), m_physicsSystem(physicsSystem), m_audioSystem(audioSystem)
{
    init(m_game.getWindow().getRenderer(), m_game.getWindow().getWindow());
}

Gui::~Gui()
{
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void Gui::render()
{
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    static bool gui = true;

    if (ImGui::IsKeyPressed(ImGuiKey_G))
    {
        gui = !gui;
    }

    if (gui)

    {
        ImGui::Begin("Game");

        static int currentTab = 0;

        if (ImGui::BeginTabBar("MainTabs"))
        {
            if (ImGui::BeginTabItem("Systems"))
            {
                currentTab = 0;
                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Entity Manager"))
            {
                currentTab = 1;
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }

        if (currentTab == 0)
        {
            if (ImGui::Checkbox("Movement", &movement))
            {
                m_movementSystem.setMovementEnabled(movement);
            }

            if (ImGui::Checkbox("LifeSpan", &lifeSpan))
            {
                m_movementSystem.setTimeEnabled(lifeSpan);
            }
            
            if (ImGui::Checkbox("Collision", &collision))
            {
                m_physicsSystem.setPhysicsEnabled(collision);
            }

            if (ImGui::Checkbox("Spawning", &spawning))
            {

            }

            if (ImGui::SliderFloat("Seconds/Spawn", &spawnRate, 0.2f, 5.f))
            {

            }

            bool sound = !m_audioSystem.getAudioDisabled();

            if (ImGui::Checkbox("Sound", &sound))
            {
                m_audioSystem.setAudioDisabled(!sound);
            }

            ImGui::SameLine();

            ImGui::PushFont(m_smallFont);
            ImGui::Text(" (press 'M' to Mute/UnMute)");
            ImGui::PopFont();

            if (ImGui::Button("Manual Spawn"))
            {
                m_game.spawnEnemy(true);
            }

            if (ImGui::Checkbox("Gui", &gui))
            {

            }

            ImGui::SameLine();

            ImGui::PushFont(m_smallFont);
            ImGui::Text(" (Press 'G' to ON/OFF)");
            ImGui::PopFont();
        }

        if (currentTab == 1)
        {
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);

            if (ImGui::TreeNode("Entities"))
            {
                auto& players = m_entityManager.getEntities("Player");
                auto& enemies = m_entityManager.getEntities("Enemy");
                auto& bullets = m_entityManager.getEntities("Bullet");

                ImGui::PushID("Players");
                ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                if (ImGui::TreeNode("Players"))
                {
                    for (size_t i = 0; i < players.size(); ++i)
                    {
                        auto& player = players[i];

                        auto& position = player->getComponent<CTransform>().m_position;
                        auto& velocity = player->getComponent<CVelocity>().m_velocity;
                        auto& rotation = player->getComponent<CTransform>().m_rotation;
                        auto& scale = player->getComponent<CTransform>().m_scale;

                        float pos[2] = { position.x, position.y };
                        float vel[2] = { velocity.x, velocity.y };
                        float sc[2] = { scale.x, scale.y };

                        ImGui::PushID((int)i);

                        if (ImGui::SmallButton("D"))
                        {
                            m_entityManager.removeEntity(player);
                        }

                        ImGui::SameLine();

                        std::string label = "Player: " + std::to_string(i + 1);

                        if (ImGui::TreeNode(label.c_str()))
                        {
                            ImGui::Text("Position: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            if (ImGui::SliderFloat2("##Position", pos, -1000.f, 1000.f))
                            {
                                position.x = pos[0];
                                position.y = pos[1];
                            }
                            ImGui::PopItemWidth();

                            ImGui::Text("Velocity: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            if (ImGui::SliderFloat2("##Velocity", vel, -500.f, 500.f))
                            {
                                velocity.x = vel[0];
                                velocity.y = vel[1];
                            }
                            ImGui::PopItemWidth();

                            ImGui::Text("Rotation: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            ImGui::SliderFloat("##Rotation", &rotation, -360.f, 360.f);
                            ImGui::PopItemWidth();

                            ImGui::Text("Scale: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            if (ImGui::SliderFloat2("##Scale", sc, 0.f, 5.f))
                            {
                                scale.x = sc[0];
                                scale.y = sc[1];
                            }
                            ImGui::PopItemWidth();

                            ImGui::TreePop();
                        }

                        ImGui::PopID();
                    }

                    ImGui::TreePop();
                }

                ImGui::PopID();

                ImGui::PushID("Enemy");
                ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                if (ImGui::TreeNode("Enemies"))
                {
                    for (size_t i = 0; i < enemies.size(); ++i)
                    {
                        auto& enemy = enemies[i];

                        auto& position = enemy->getComponent<CTransform>().m_position;
                        auto& velocity = enemy->getComponent<CVelocity>().m_velocity;
                        auto& rotation = enemy->getComponent<CTransform>().m_rotation;
                        auto& scale = enemy->getComponent<CTransform>().m_scale;
                        auto& color = enemy->getComponent<CColor>().m_color;

                        float pos[2] = { position.x, position.y };
                        float vel[2] = { velocity.x, velocity.y };
                        float sc[2] = { scale.x, scale.y };

                        ImVec4 col = ImVec4(
                            color.r / 255.0f,
                            color.g / 255.0f,
                            color.b / 255.0f,
                            color.a / 255.0f
                        );

                        ImGui::PushID((int)i);

                        ImGui::PushStyleColor(ImGuiCol_Button, col);
                        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, col);
                        ImGui::PushStyleColor(ImGuiCol_ButtonActive, col);

                        if (ImGui::SmallButton("D"))
                        {
                            m_entityManager.removeEntity(enemy);
                        }

                        ImGui::PopStyleColor(3);
                        ImGui::SameLine();

                        std::string label = "Enemy: " + std::to_string(i + 1);

                        if (ImGui::TreeNode(label.c_str()))
                        {
                            ImGui::Text("Position: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            if (ImGui::SliderFloat2("##Position", pos, -1000.f, 1000.f))
                            {
                                position.x = pos[0];
                                position.y = pos[1];
                            }
                            ImGui::PopItemWidth();

                            ImGui::Text("Velocity: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            if (ImGui::SliderFloat2("##Velocity", vel, -500.f, 500.f))
                            {
                                velocity.x = vel[0];
                                velocity.y = vel[1];
                            }
                            ImGui::PopItemWidth();

                            ImGui::Text("Rotation: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            ImGui::SliderFloat("##Rotation", &rotation, -360.f, 360.f);
                            ImGui::PopItemWidth();

                            ImGui::Text("Scale: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            if (ImGui::SliderFloat2("##Scale", sc, 0.f, 5.f))
                            {
                                scale.x = sc[0];
                                scale.y = sc[1];
                            }
                            ImGui::PopItemWidth();

                            ImGui::Text("Color: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);

                            float colArr[4] = { col.x, col.y, col.z, col.w };

                            if (ImGui::ColorEdit4("##Color", colArr))
                            {
                                color.r = (Uint8)(colArr[0] * 255);
                                color.g = (Uint8)(colArr[1] * 255);
                                color.b = (Uint8)(colArr[2] * 255);
                                color.a = (Uint8)(colArr[3] * 255);
                            }

                            ImGui::PopItemWidth();

                            ImGui::TreePop();
                        }

                        ImGui::PopID();
                    }

                    ImGui::TreePop();
                }

                ImGui::PopID();

                // Bullets section
                ImGui::PushID("Bullet");
                ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                if (ImGui::TreeNode("Bullets"))
                {
                    for (size_t i = 0; i < bullets.size(); ++i)
                    {
                        auto& bullet = bullets[i];

                        auto& position = bullet->getComponent<CTransform>().m_position;
                        auto& velocity = bullet->getComponent<CVelocity>().m_velocity;
                        auto& rotation = bullet->getComponent<CTransform>().m_rotation;
                        auto& scale = bullet->getComponent<CTransform>().m_scale;

                        float pos[2] = { position.x, position.y };
                        float vel[2] = { velocity.x, velocity.y };
                        float sc[2] = { scale.x, scale.y };

                        ImGui::PushID((int)i);

                        if (ImGui::SmallButton("D"))
                        {
                            m_entityManager.removeEntity(bullet);
                        }

                        ImGui::SameLine();

                        std::string label = "Bullet: " + std::to_string(i + 1);

                        if (ImGui::TreeNode(label.c_str()))
                        {
                            ImGui::Text("Position: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            if (ImGui::SliderFloat2("##Position", pos, -1000.f, 1000.f))
                            {
                                position.x = pos[0];
                                position.y = pos[1];
                            }
                            ImGui::PopItemWidth();

                            ImGui::Text("Velocity: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            if (ImGui::SliderFloat2("##Velocity", vel, -500.f, 500.f))
                            {
                                velocity.x = vel[0];
                                velocity.y = vel[1];
                            }
                            ImGui::PopItemWidth();

                            ImGui::Text("Rotation: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            ImGui::SliderFloat("##Rotation", &rotation, -360.f, 360.f);
                            ImGui::PopItemWidth();

                            ImGui::Text("Scale: ");
                            ImGui::SameLine();
                            ImGui::PushItemWidth(200.f);
                            if (ImGui::SliderFloat2("##Scale", sc, 0.f, 5.f))
                            {
                                scale.x = sc[0];
                                scale.y = sc[1];
                            }
                            ImGui::PopItemWidth();

                            ImGui::TreePop();
                        }

                        ImGui::PopID();
                    }

                    ImGui::TreePop();
                }

                ImGui::PopID();

                ImGui::TreePop();
            }
        }

        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_renderer);
}