#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>
#include <glm/gtc/random.hpp>

#include "lab_m1/tema1/transform2D.h"


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
   
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);
    CreateMeshes();
    spawnDuck();
    score = 0;
    lives = 3;
    
}

void Tema1::CreateMeshes() {
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5f, 0.25f, 0), glm::vec3(0.32157f, 0.19216f, 0.02745f), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(-0.5f, -0.25f, 0), glm::vec3(0.32157f, 0.19216f, 0.02745f), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(0.5f, 0, 0), glm::vec3(0.32157f, 0.19216f, 0.02745f), glm::vec3(1, 1, 1))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2
        };

        meshes["body"] = new Mesh("body");
        meshes["body"]->InitFromData(vertices, indices);
    }
    {

        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.16863f, 0.10196f, 0.01176)),
            VertexFormat(glm::vec3(0, 0.5f, 0), glm::vec3(0.16863f, 0.10196f, 0.01176)),
            VertexFormat(glm::vec3(-0.25f, 0, 0), glm::vec3(0.16863f, 0.10196f, 0.01176))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2
        };

        meshes["leftw"] = new Mesh("leftw");
        meshes["leftw"]->InitFromData(vertices, indices);


    }
    {

        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.16863f, 0.10196f, 0.01176)),
            VertexFormat(glm::vec3(0, -0.5f, 0), glm::vec3(0.16863f, 0.10196f, 0.01176)),
            VertexFormat(glm::vec3(-0.25f, 0, 0), glm::vec3(0.16863f, 0.10196f, 0.01176))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2
        };

        meshes["rightw"] = new Mesh("rightw");
        meshes["rightw"]->InitFromData(vertices, indices);

    }

    {

        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0.3f, 0, 1), glm::vec3(1, 0, 0))
        };

        vector<unsigned int> indices =
        {
            0
        };

        for (int i = 0; i < 30; i++) {
            float angle = i / 30.f * 2 * M_PI;
            vertices.push_back(VertexFormat(glm::vec3(glm::cos(angle) * 0.2 + 0.3, glm::sin(angle) * 0.2, 1), glm::vec3(1, 0, 0)));
            indices.push_back(i + 1);
        }

        indices.push_back(1);

        meshes["live"] = new Mesh("live");
        meshes["live"]->SetDrawMode(GL_TRIANGLE_FAN);
        meshes["live"]->InitFromData(vertices, indices);

    }
    {

        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0.3f, 0, 1), glm::vec3(0.12941, 0.16078, 0.12157))
        };

        vector<unsigned int> indices =
        {
            0
        };

        for (int i = 0; i < 30; i++) {
            float angle = i / 30.f * 2 * M_PI;
            vertices.push_back(VertexFormat(glm::vec3(glm::cos(angle) * 0.2 + 0.3, glm::sin(angle) * 0.2, 1), glm::vec3(0.12941, 0.16078, 0.12157)));
            indices.push_back(i + 1);
        }

        indices.push_back(1);

        meshes["bullet"] = new Mesh("bullet");
        meshes["bullet"]->SetDrawMode(GL_TRIANGLE_FAN);
        meshes["bullet"]->InitFromData(vertices, indices);

    }
    {

        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0.3f, 0, 1), glm::vec3(0.05098, 0.21176, 0.02745))
        };

        vector<unsigned int> indices =
        {
            0
        };

        for (int i = 0; i < 30; i++) {
            float angle = i / 30.f * 2 * M_PI;
            vertices.push_back(VertexFormat(glm::vec3(glm::cos(angle)*0.2+0.3, glm::sin(angle)*0.2, 1), glm::vec3(0.05098, 0.21176, 0.02745)));
            indices.push_back(i + 1);
        }

        indices.push_back(1);

        meshes["head"] = new Mesh("head");
        meshes["head"]->SetDrawMode(GL_TRIANGLE_FAN);
        meshes["head"]->InitFromData(vertices, indices);

    }
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0.6f, 0, 0), glm::vec3(0.78824f, 0.54118f, 0.00784f), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(0.4f, 0.05f, 0), glm::vec3(0.78824f, 0.54118f, 0.00784f), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(0.4f, -0.05f, 0), glm::vec3(0.78824f, 0.54118f, 0.00784f), glm::vec3(1, 1, 1))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2
        };

        meshes["beak"] = new Mesh("beak");
        meshes["beak"]->InitFromData(vertices, indices);
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0.5, 1), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(0, -0.5f, 1), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(1, -0.5f, 1), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(1, 0.5f, 1), glm::vec3(0, 1, 1), glm::vec3(1, 1, 1))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 3, 0
        };

        meshes["score"] = new Mesh("score");
        meshes["score"]->InitFromData(vertices, indices);
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0.5, 2), glm::vec3(0, 1, 0), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(0, -0.5f, 2), glm::vec3(0, 1, 0), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(1, -0.5f, 2), glm::vec3(0, 1, 0), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(1, 0.5f, 2), glm::vec3(0, 1, 0), glm::vec3(1, 1, 1))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 3, 0
        };

        meshes["grass"] = new Mesh("grass");
        meshes["grass"]->InitFromData(vertices, indices);
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0.5, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(0, -0.5f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(1, -0.5f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(1, 0.5f, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1))
        };

        vector<unsigned int> indices =
        {
            0, 1, 2,
            2, 3, 0
        };

        meshes["scorebg"] = new Mesh("scorebg");
        meshes["scorebg"]->InitFromData(vertices, indices);
    }

}

void Tema1::spawnDuck() {
    pos = glm::vec2(glm::linearRand(0, window->GetResolution().x), 0);
    rotation = glm::linearRand(RADIANS(15), RADIANS(165));
    if (rotation > RADIANS(85) && RADIANS(95) > rotation) {
        rotation += RADIANS(10);
    }
    timeUntilRun = 5;
    isDead = false;
    bullets = 3;
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.60392f, 0.91765f, 0.92941f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    timeUntilRun -= deltaTimeSeconds;
    if (timeUntilRun < 0 && !isDead) {
        cout << "escape" << endl;
        isDead = true;
        rotation = RADIANS(90);
        lives--;
    }
    wingAnim += deltaTimeSeconds * 10;
    pos.x += cos(rotation) * deltaTimeSeconds * speed;
    pos.y += sin(rotation) * deltaTimeSeconds * speed;

    if (!isDead) {
        if (pos.x < 0) {
            pos.x = 0;
            rotation = RADIANS(180) - rotation;
        }
        if (pos.x > window->GetResolution().x) {
            pos.x = window->GetResolution().x;
            rotation = RADIANS(180) - rotation;
        }
        if (pos.y < 0) {
            pos.y = 0;
            rotation = -rotation;
        }
        if (pos.y > window->GetResolution().y) {
            pos.y = window->GetResolution().y;
            rotation = -rotation;
        }
    }
    else {
        if (pos.y < 0 || pos.y > window->GetResolution().y) {
            spawnDuck();
        }
    }

    for (int i = 0; i < lives; i++) {
        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(30 + i * 60, window->GetResolution().y - 20);
        modelMatrix *= transform2D::Scale(100, 100);
        RenderMesh2D(meshes["live"], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < bullets; i++) {
        glm::mat3 modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(30 + i * 60, window->GetResolution().y - 80);
        modelMatrix *= transform2D::Scale(100, 100);
        RenderMesh2D(meshes["bullet"], shaders["VertexColor"], modelMatrix);
    }

    {glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(window->GetResolution().x - 300, window->GetResolution().y - 80);
    modelMatrix *= transform2D::Scale(score * 10, 20);
    RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix); }

    {glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(window->GetResolution().x - 305, window->GetResolution().y - 80);
    modelMatrix *= transform2D::Scale(maxScore * 10 +5, 30);
    RenderMesh2D(meshes["scorebg"], shaders["VertexColor"], modelMatrix); }

    glm::mat3 modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(pos.x, pos.y);
    modelMatrix *= transform2D::Scale(duckScale, duckScale);
    modelMatrix *= transform2D::Rotate(rotation);
        
    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);


    modelMatrix *= transform2D::Rotate(cos(wingAnim) * 0.25f);
    RenderMesh2D(meshes["leftw"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Rotate(-2* cos(wingAnim) * 0.25f);
   RenderMesh2D(meshes["rightw"], shaders["VertexColor"], modelMatrix);

   modelMatrix = glm::mat3(1);
   modelMatrix *= transform2D::Scale(window->GetResolution().x, 200);
   RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    if (!lives) {
        cout << "No more lives!" << endl;
        exit(0);
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (!bullets || isDead) {
        return;
    }
    bullets--;
    mouseY = window->GetResolution().y;
    if ((glm::abs(pos.x - mouseX)<(duckScale/2) || glm::abs(pos.y - mouseY) < (duckScale / 2)) && !isDead) {
        cout << "hit" << endl;
        isDead = true;
        rotation = RADIANS(-90);
        score++;
        speed += 20;
        if (score == maxScore) {
            cout << "Max score!" << endl;
            exit(0);
     
        }
    }
    else
    {
        //cout << "miss";
        if (bullets == 0) {
            lives--;
            isDead = true;
            rotation = RADIANS(90);
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
