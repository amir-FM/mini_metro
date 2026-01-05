#pragma once

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <map>
#include "components/simple_scene.h"
#include "components/transform.h"
#include "train.h"
#include "railroad.h"
#include "station.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void updateMouseGamePos(int mouseX, int mouseY);
        void RenderTrain(glm::vec3 center, float rotationAngle, float scale);
        void RenderCarriage(glm::vec3 center, float rotationAngle, float scale);
        void RenderBridge(Rail *rail);
        void RenderTunnel(Rail *rail);
        void RenderRail(Rail *rail);
        void RenderRailroad();
        void CreateCylinderMesh();
        void RailCheckAndPlace();
        void RenderStation(Station* station);
        void RenderStations();
        void GenerateNewStation();
        void CheckStations();
        void RenderWholeTrain();
        void StationWait();

        glm::vec3 lightPosition;
        glm::vec3 lightDirection;
        glm::vec3 lightPosition1;
        glm::vec3 lightDirection1;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
        bool wait;

        // TODO(student): If you need any other class variables, define them here.
        bool spotlight;
        glm::vec3 mousePos;

        Train *tr;
        Rail *r, *r1, *r2, *r3;
        Railroad rr;
        map<pair<int, int>, Station*> stations;
    };
}   // namespace m1
