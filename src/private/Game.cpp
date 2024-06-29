#include "raylib-cpp.hpp"
#include <iostream>


int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 600;

    raylib::Window window(screenWidth, screenHeight, "raylib [models] example - first person maze");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Reset roll

    char modelFileName[128] = "resources/Yakuza.iqm";
    Model model = LoadModel(modelFileName);  // Load model
    Texture2D texture = LoadTexture("resources/Yakuzombie_.png"); // Load model texture
    // Texture2D textureSpecular = LoadTexture("resources/world_war_zombie_specular.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture; // Set map diffuse texture
    // model.materials[0].maps[MATERIAL_MAP_SPECULAR].texture = textureSpecular; // Set map specular texture   

    // for (int i = 0; i < model.meshCount; ++i) {
    //     std::cout << "Mesh[" << i << "] name: " << model.meshes[i] << std::endl;
    // }

    int animCount = 0;
    ModelAnimation *anims = LoadModelAnimations(modelFileName, &animCount);

    int currentAnimation = 0;
    int currentFrame = 0;


    Vector3 position = { 0.0f, 0.0f, 0.0f };            // Set model position

    DisableCursor();

    //SetCameraMode(camera, CAMERA_FREE); // Set a free camera mode

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);          // Update camera
        //----------------------------------------------------------------------------------

        // cycle animations 
        if(IsKeyPressed(KEY_SPACE)){
            currentAnimation++;
            if(currentAnimation >= animCount) currentAnimation = 0;
            currentFrame = 0;
        }

        currentFrame++;
        UpdateModelAnimation(model, anims[currentAnimation], currentFrame);
        // reset animation
        if(currentFrame > anims[currentAnimation].frameCount) currentFrame = 0;



        if(animCount){
            std::cout << "Animation count: " << animCount << std::endl;
        }else{
            std::cout << "No animations found" << std::endl;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawModel(model, position, 0.01f, WHITE);   // Draw 3d model with texture

                DrawGrid(10, 1.0f);     // Draw a grid

            EndMode3D();

            DrawText("This is a raylib example", 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadModel(model);         // Unload model
    UnloadTexture(texture);     // Unload texture

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
