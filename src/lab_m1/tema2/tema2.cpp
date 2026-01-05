#include "lab_m1/tema2/tema2.h"
#include "rail.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    srand(time(nullptr));
    {
    vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(-0.5, -0.5,  0.5), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)), // 0
        VertexFormat(glm::vec3( 0.5, -0.5,  0.5), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)), // 1
        VertexFormat(glm::vec3(-0.5,  0.5,  0.5), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.6)), // 2
        VertexFormat(glm::vec3( 0.5,  0.5,  0.5), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)), // 3
        VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)), // 4
        VertexFormat(glm::vec3( 0.5, -0.5, -0.5), glm::vec3(1, 1, 1), glm::vec3(0.2, 0.8, 0.6)), // 5
        VertexFormat(glm::vec3(-0.5,  0.5, -0.5), glm::vec3(0, 0, 1), glm::vec3(0.2, 0.8, 0.6)), // 6
        VertexFormat(glm::vec3( 0.5,  0.5, -0.5), glm::vec3(1, 0, 0), glm::vec3(0.2, 0.8, 0.6))  // 7
    };

    vector<unsigned int> indices =
    {
        0, 1, 2,    1, 3, 2,    // Front face
        2, 3, 7,    2, 7, 6,    // Top face
        1, 7, 3,    1, 5, 7,    // Right face
        6, 7, 4,    7, 5, 4,    // Back face
        0, 4, 1,    1, 4, 5,    // Bottom face
        2, 6, 4,    0, 2, 4     // Left face
    };

    Mesh* mesh = new Mesh("cube");
    mesh->InitFromData(vertices, indices);
    meshes[mesh->GetMeshID()] = mesh;
    }
    
    {
    vector<VertexFormat> vertices;
    vector<unsigned int> indices;

    int sides = 17;
    float radius = 0.5f;
    float halfH = 0.5f;
    glm::vec3 color = glm::vec3(0.2, 0.8, 0.6);

    for (int i = 0; i < sides; ++i) {
        float theta = 2.0f * glm::pi<float>() * (float)i / (float)sides;
        float x = radius * cos(theta);
        float z = radius * sin(theta);
        
        glm::vec3 sideNormal = glm::normalize(glm::vec3(x, 0, z));

        vertices.push_back(VertexFormat(glm::vec3(x, -halfH, z), sideNormal, color));
        vertices.push_back(VertexFormat(glm::vec3(x, halfH, z), sideNormal, color));
    }

    int bottomCenterIndex = (int)vertices.size();
    vertices.push_back(VertexFormat(glm::vec3(0, -halfH, 0), glm::vec3(0, -1, 0), color));

    int topCenterIndex = (int)vertices.size();
    vertices.push_back(VertexFormat(glm::vec3(0, halfH, 0), glm::vec3(0, 1, 0), color));


    for (int i = 0; i < sides; ++i) {
        int b0 = i * 2;
        int t0 = i * 2 + 1;
        int b1 = ((i + 1) % sides) * 2;
        int t1 = ((i + 1) % sides) * 2 + 1;

        indices.push_back(b0); indices.push_back(b1); indices.push_back(t0);
        indices.push_back(t0); indices.push_back(b1); indices.push_back(t1);

        indices.push_back(bottomCenterIndex);
        indices.push_back(b1);
        indices.push_back(b0);

        indices.push_back(topCenterIndex);
        indices.push_back(t0);
        indices.push_back(t1);
    }

    Mesh* cylinder = new Mesh("cylinder");
    cylinder->InitFromData(vertices, indices);
    meshes[cylinder->GetMeshID()] = cylinder;
    }

    {
    vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(0, 1, 0),    glm::vec3(0.2, 0.8, 0.6)),
        
        VertexFormat(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1, -1, 1),  glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3(1, -1, 1),   glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3(1, -1, -1),  glm::vec3(0.2, 0.8, 0.6)),
        VertexFormat(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1, -1, -1), glm::vec3(0.2, 0.8, 0.6))
    };

    vector<unsigned int> indices =
    {
        0, 1, 2,    // Front face
        0, 2, 3,    // Right face
        0, 3, 4,    // Back face
        0, 4, 1,    // Left face

        1, 3, 2,    // Base triangle 1
        1, 4, 3     // Base triangle 2
    };

    Mesh* mesh = new Mesh("pyramid");
    mesh->InitFromData(vertices, indices);
    meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        lightPosition = glm::vec3(0, 1, 1);
        lightDirection = glm::vec3(0, -1, 0);
        lightPosition1 = glm::vec3(0, 1, 1);
        lightDirection1 = glm::vec3(0, -1, 0);
        materialShininess = 30;
        materialKd = 2;
        materialKs = 1;
    }

    spotlight = false;

    {
        rr.addRail(new Rail(glm::vec3(0, 0, 0), glm::vec3(2, 0, 0)));
        rr.addRail(new Rail(glm::vec3(2, 0, 0), glm::vec3(2, 0, 2), TUNNEL));
        rr.addRail(new Rail(glm::vec3(2, 0, 2), glm::vec3(0, 0, 2), BRIDGE));
        rr.addRail(new Rail(glm::vec3(0, 0, 2), glm::vec3(-2, 0, 2), BRIDGE));
        rr.addRail(new Rail(glm::vec3(-2, 0, 2), glm::vec3(-2, 0, 0), BRIDGE));
        rr.addRail(new Rail(glm::vec3(-2, 0, 0), glm::vec3(0, 0, 0), TUNNEL));
        rr.checkLoop();
        tr = new Train(rr.getStart(), 1.0f);
        tr->addCarriage();
        tr->addCarriage();
        tr->addCarriage();
    }

    mousePos = glm::vec3(0);
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{

    RenderWholeTrain();

    RenderRailroad();

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, mousePos);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        // TODO(student): Add or change the object colors
        RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix, glm::vec3(1, 0, 0));

    }

    GenerateNewStation();
    RenderStations();


    // Render ground
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        // TODO(student): Add or change the object colors
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, glm::vec3(0.2, 0.6, 0.22));

    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 0.02f, 3));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        // TODO(student): Add or change the object colors
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, glm::vec3(0.67, 0.51, 0.24));

    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.3, 0.02f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.04f, 1, 0.25f));
        // TODO(student): Add or change the object colors
        RenderSimpleMesh(meshes["plane"], shaders["LabShader"], modelMatrix, glm::vec3(0.17, 0.11, 0.74));

    }

    // Render the point light in the scene
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, lightPosition);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["Simple"], modelMatrix);
    }

    if(rr.canRide) tr->makeProgress(deltaTimeSeconds);
    if(tr->progress == 1 && !tr->stationDone)
        CheckStations();

}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem();
}


void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Set shader uniforms for light properties
    int light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

    int light_direction = glGetUniformLocation(shader->program, "light_direction");
    glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

    light_position = glGetUniformLocation(shader->program, "light_position1");
    glUniform3f(light_position, lightPosition1.x, lightPosition1.y, lightPosition1.z);

    light_direction = glGetUniformLocation(shader->program, "light_direction1");
    glUniform3f(light_direction, lightDirection1.x, lightDirection1.y, lightDirection1.z);

    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = GetSceneCamera()->m_transform->GetWorldPosition();
    int eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

    // Set material property uniforms (shininess, kd, ks, object color) 
    int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(material_shininess, materialShininess);

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, materialKd);

    int material_ks = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(material_ks, materialKs);

    int object_color = glGetUniformLocation(shader->program, "object_color");
    glUniform3f(object_color, color.r, color.g, color.b);

    int spotlight_path = glGetUniformLocation(shader->program, "spotlight");
    glUniform1i(spotlight_path, spotlight ? 1 : 0);

    // TODO(student): Set any other shader uniforms that you need

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float speed = 2;

    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 right = GetSceneCamera()->m_transform->GetLocalOXVector();
        glm::vec3 forward = GetSceneCamera()->m_transform->GetLocalOZVector();
        forward = glm::normalize(glm::vec3(forward.x, 0, forward.z));

        // Control light position using on W, A, S, D, E, Q
        if (window->KeyHold(GLFW_KEY_W)) lightPosition -= forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_A)) lightPosition -= right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_S)) lightPosition += forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_D)) lightPosition += right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_E)) lightPosition += up * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_Q)) lightPosition -= up * deltaTime * speed;

        // TODO(student): Set any other keys that you might need
        if (window->KeyHold(GLFW_KEY_U)) lightDirection -= forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_H)) lightDirection -= right * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_J)) lightDirection += forward * deltaTime * speed;
        if (window->KeyHold(GLFW_KEY_K)) lightDirection += right * deltaTime * speed;

    }

    if (window->KeyHold(GLFW_KEY_Z)) tr->speed = 5.0f;
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event

    // TODO(student): Set keys that you might need
    if(key == GLFW_KEY_F) {
        spotlight = !spotlight;
    }

}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
    if(key == GLFW_KEY_Z) {
        tr->speed = 1.0f;
    }
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    updateMouseGamePos(mouseX, mouseY);
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if(IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        //cout << "mouse: " << mousePos.x << " " << mousePos.z << endl;
        RailCheckAndPlace();
        for(auto& it : rr.railroad) {
            if(it.second->checkAndChange(mousePos)) return;
        }
    }

    if(IS_BIT_SET(button, GLFW_MOUSE_BUTTON_RIGHT)) {
        for(auto& it : rr.railroad) {
            if(it.second->checkAndChange(mousePos)) {
                bool trainOnRail = false;
                if(tr->rail == it.second) trainOnRail = true;
                rr.delRail(it.second);
                rr.checkLoop();
                if(trainOnRail) {
                    Rail* next = rr.getStart();
                    if(next == nullptr)
                        tr->noMove = true;
                    else {
                        tr->rail = next;
                        tr->initCarriagePositions();
                    }
                }
                return;
            }
        }
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}

void Tema2::updateMouseGamePos(int mouseX, int mouseY) {
    glm::ivec2 resolution = window->GetResolution();
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glm::vec3 cameraPos = GetSceneCamera()->m_transform->GetWorldPosition();

    float x = (2.0f * mouseX) / resolution.x - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / resolution.y;
    float z = 1.0f;

    glm::vec3 ray_nds = glm::vec3(x, y, z);

    glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.0f, 1.0f);

    glm::vec4 ray_eye = glm::inverse(projectionMatrix) * ray_clip;
    ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0f, 0.0f);

    glm::vec3 ray_world = glm::vec3(glm::inverse(viewMatrix) * ray_eye);
    ray_world = glm::normalize(ray_world);
    float t = -cameraPos.y / ray_world.y;

    if (t >= 0.0f) {
        glm::vec3 intersectionPoint = cameraPos + (t * ray_world);
        
        float finalX = intersectionPoint.x;
        float finalZ = intersectionPoint.z;

        mousePos.x = finalX;
        mousePos.z = finalZ;
    }
}

void Tema2::RenderBridge(Rail *rail) {
    RenderSimpleMesh(meshes["cube"], shaders["LabShader"], rail->modelMatrix, glm::vec3(0, 0, rail->working ? 1 : 0));
    RenderSimpleMesh(meshes["cube"], shaders["LabShader"], rail->bridgeMatrix1, glm::vec3(0, 0, rail->working ? 0 : 1));
    RenderSimpleMesh(meshes["cube"], shaders["LabShader"], rail->bridgeMatrix2, glm::vec3(0, 0, rail->working ? 0 : 1));
}

void Tema2::RenderTunnel(Rail *rail) {
    RenderSimpleMesh(meshes["cube"], shaders["LabShader"], rail->modelMatrix, glm::vec3(0, 0, rail->working ? 1 : 0));
    RenderSimpleMesh(meshes["cube"], shaders["LabShader"], rail->tunnelMatrix, glm::vec3(0, 0, rail->working ? 0 : 1));
}

void Tema2::RenderRail(Rail *rail) {
    switch(rail->type) {
    case LAND:
        RenderSimpleMesh(meshes["cube"], shaders["LabShader"], rail->modelMatrix, glm::vec3(0, 0, rail->working ? 1 : 0));
        break;
    case BRIDGE:
        RenderBridge(rail);
        break;
    case TUNNEL:
        RenderTunnel(rail);
        break;
    }
}

void Tema2::RenderTrain(glm::vec3 center, float rotationAngle, float scale) {
    glm::mat4 modelMatrix = glm::mat4(1);
    
    // 1. Move to position
    modelMatrix = glm::translate(modelMatrix, center);
    
    // 2. Rotate to face the movement direction
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationAngle), glm::vec3(0, 1, 0));
    
    // 3. Apply the global scale
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));

    // --- Base (The floor of the train) ---
    {
        glm::mat4 baseMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.05f, 0));
        baseMatrix = glm::scale(baseMatrix, glm::vec3(4.0f, 0.15f, 1.2f));
        RenderSimpleMesh(meshes["cube"], shaders["LabShader"], baseMatrix, glm::vec3(1, 1, 0));
    }

    // --- Cabin (The driver's room) ---
    {
        glm::mat4 cabinMatrix = glm::translate(modelMatrix, glm::vec3(-1.1f, 1.05f, 0));
        cabinMatrix = glm::scale(cabinMatrix, glm::vec3(1.4f, 1.8f, 1.2f));
        RenderSimpleMesh(meshes["cube"], shaders["LabShader"], cabinMatrix, glm::vec3(0, 1, 0));
    }

    // --- Boiler (Main body cylinder) ---
    {
        glm::mat4 boilerMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.65f, 0));
        boilerMatrix = glm::rotate(boilerMatrix, glm::radians(90.0f), glm::vec3(0, 0, 1));
        boilerMatrix = glm::scale(boilerMatrix, glm::vec3(1.0f, 2.4f, 1.0f));  
        RenderSimpleMesh(meshes["cylinder"], shaders["LabShader"], boilerMatrix, glm::vec3(0, 0, 1));
    }

    // --- Nose (The front tip) ---
    {
        glm::mat4 noseMatrix = glm::translate(modelMatrix, glm::vec3(1.8f, 0.65f, 0));
        noseMatrix = glm::rotate(noseMatrix, glm::radians(90.0f), glm::vec3(0, 0, 1));
        noseMatrix = glm::scale(noseMatrix, glm::vec3(0.3f, 0.25f, 0.3f));
        RenderSimpleMesh(meshes["cylinder"], shaders["LabShader"], noseMatrix, glm::vec3(1, 0, 1));
    }

    // --- Wheels ---
    float wheelRadius = 0.4f;
    float startX = -1.6f;
    float spacing = 0.68f;

    for (int i = 0; i < 6; i++) {
        for (float zOffset : {-0.6f, 0.6f}) {
            glm::mat4 wheelMatrix = glm::translate(modelMatrix, glm::vec3(startX + i * spacing, -0.25f, zOffset));
            wheelMatrix = glm::rotate(wheelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
            wheelMatrix = glm::scale(wheelMatrix, glm::vec3(wheelRadius * 2, 0.2f, wheelRadius * 2));
            RenderSimpleMesh(meshes["cylinder"], shaders["LabShader"], wheelMatrix, glm::vec3(1, 0, 0));
        }
    }
}

void Tema2::RenderRailroad() {
    for(auto& it : rr.railroad) {
        RenderRail(it.second);
    }
}


void Tema2::RailCheckAndPlace() {
    float width = 0.2f;
    bool added = false;

    int baseX = (int)glm::round(mousePos.x / 2) * 2;
    int baseZ = (int)glm::round(mousePos.z / 2) * 2;
    float x = mousePos.x;
    float z = mousePos.z;

    if(rr.railExists(glm::vec2(baseX, baseZ))) return;

    cout << baseX << ", " << baseZ << endl;

    if(abs(x - baseX) < width) {
        if(z > baseZ) {
            cout << baseX << ", " << baseZ << " - " << baseX << ", " << baseZ + 2 << endl;
            rr.addRail(new Rail(glm::vec3(baseX, 0, baseZ), glm::vec3(baseX, 0, baseZ + 2)));
            added = true;
        }else {
            cout << baseX << ", " << baseZ << " - " << baseX << ", " << baseZ - 2 << endl;
            rr.addRail(new Rail(glm::vec3(baseX, 0, baseZ), glm::vec3(baseX, 0, baseZ - 2)));
            added = true;
        }
    }else if(abs(z - baseZ) < width) {
        if(x > baseX) {
            cout << baseX << ", " << baseZ << " - " << baseX + 2 << ", " << baseZ << endl;
            rr.addRail(new Rail(glm::vec3(baseX, 0, baseZ), glm::vec3(baseX + 2, 0, baseZ)));
            added = true;
        }else {
            cout << baseX << ", " << baseZ << " - " << baseX - 2 << ", " << baseZ << endl;
            rr.addRail(new Rail(glm::vec3(baseX, 0, baseZ), glm::vec3(baseX - 2, 0, baseZ)));
            added = true;
        }
    }

    if(added) {
        if(rr.checkLoop()) {
            if(tr->noMove) {
                tr->rail = rr.getStart();
                tr->initCarriagePositions();
                tr->noMove = false;
            }
        }
    }
}

void Tema2::RenderStation(Station* station) {
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, station->globalPos + glm::vec3(0, 0.17f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.55f));
        // TODO(student): Add or change the object colors
        RenderSimpleMesh(meshes[station->type_s], shaders["LabShader"], modelMatrix, glm::vec3(1, station->dim * 1.0f / station->cap, 1));

    }

    float offset = 0.7f;

    for(auto& it : station->passengers) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, station->globalPos + glm::vec3(0, offset, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.15f));
        // TODO(student): Add or change the object colors
        RenderSimpleMesh(meshes[it->dest_s], shaders["LabShader"], modelMatrix, glm::vec3(0.5f, 0.5f, 1));
        offset += 0.3f;

    }
}

void Tema2::GenerateNewStation() {
    if(rand() % 10000 >= 20) return;

    Station *ns = new Station();

    if(stations.find(ns->position) != stations.end())
        return;

    stations[ns->position] = ns;
}

void Tema2::RenderStations() {
    for(auto& it : stations) {
        it.second->generatePassenger();
        RenderStation(it.second);
    }
}

void Tema2::CheckStations() {
    if(stations.find(tr->rail->end_pair) != stations.end()) {
        Station* station = stations[tr->rail->end_pair];
        station->unload(tr);
        station->load(tr);
        tr->stationWait = true;
        cout << "[CheckStations] " << tr->dim << " - " << tr->cap << " - c: " << tr->circle << ", s: " << tr->square << ", t: " << tr->triangle << endl;
    }

    tr->stationDone = true;
}

void Tema2::RenderCarriage(glm::vec3 center, float rotationAngle, float scale) {
    glm::mat4 modelMatrix = glm::mat4(1);
    
    // 1. Move to position
    modelMatrix = glm::translate(modelMatrix, center);
    
    // 2. Rotate to face the movement direction
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationAngle), glm::vec3(0, 1, 0));
    
    // 3. Apply the global scale
    modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));

    // --- Base (Yellow floor) ---
    // Matches the train's base dimensions for consistency
    {
        glm::mat4 baseMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.05f, 0));
        baseMatrix = glm::scale(baseMatrix, glm::vec3(4.0f, 0.15f, 1.2f));
        RenderSimpleMesh(meshes["cube"], shaders["LabShader"], baseMatrix, glm::vec3(1, 1, 0)); // Yellow
    }

    // --- Main Body (Green container) ---
    // Placed on top of the base. Height is increased to look like a carriage.
    {
        glm::mat4 bodyMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.95f, 0));
        bodyMatrix = glm::scale(bodyMatrix, glm::vec3(3.8f, 1.65f, 1.2f));
        RenderSimpleMesh(meshes["cube"], shaders["LabShader"], bodyMatrix, glm::vec3(0, 1, 0)); // Green
    }

    // --- Wheels (Red) ---
    // The image shows two wheels on the side view. 
    // Usually, carriages have wheels near the front and back.
    float wheelRadius = 0.45f;
    float wheelXOffset = 1.3f; // Distance from center to front/back wheels

    for (float xPos : {-wheelXOffset, wheelXOffset}) { // Front and Back pairs
        for (float zOffset : {-0.6f, 0.6f}) {        // Left and Right sides
            glm::mat4 wheelMatrix = glm::translate(modelMatrix, glm::vec3(xPos, -0.25f, zOffset));
            wheelMatrix = glm::rotate(wheelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
            // Using cylinder to match your train's wheel style
            wheelMatrix = glm::scale(wheelMatrix, glm::vec3(wheelRadius * 2, 0.2f, wheelRadius * 2));
            RenderSimpleMesh(meshes["cylinder"], shaders["LabShader"], wheelMatrix, glm::vec3(1, 0, 0)); // Red
        }
    }
}

void Tema2::RenderWholeTrain() {
    RenderTrain(tr->position + glm::vec3(0, 0.17f, 0), tr->rail->rotation, 0.1f);

    for(auto& it : tr->carriages) {
        RenderCarriage(it->position + glm::vec3(0, 0.17f, 0), it->rail->rotation, 0.1f);
    }
}

void Tema2::StationWait() {
    static int timer = 0;
    timer++;
    if(timer > 0 && !wait)
        wait = true;

    if(timer > 10000) {
        timer = 0;
        wait = false;
    }
}
