/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <random>
#include <time.h>
#include "Critter.h"
#include "ObjectPool.h"
#include "List.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    //SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    srand(time(NULL));


    ObjectPool critters = ObjectPool();
    List<Critter*> toBeRemoved = List<Critter*>();

    // create some critters
    const int CRITTER_COUNT = 50;
    const int MAX_VELOCITY = 80;

    Iterator<Critter> iter = critters.objects.begin();
    for (int i = 0; i < CRITTER_COUNT; i++)
    {
        // create a random direction vector for the velocity
        Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
        // normalize and scale by a random speed
        velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);

        // create a critter in a random location
        critters.Allocate({ (float)(5 + rand() % (screenWidth - 10)), (float)(5 + (rand() % screenHeight - 10)) },
            velocity,
            12, "res/10.png");

    }



    Critter* destroyer = new Critter();
    Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
    velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
    destroyer->Init(Vector2{ (float)(screenWidth >> 1), (float)(screenHeight >> 1) }, velocity, 20, "res/9.png");

    float timer = 1;
    Vector2 nextSpawnPos = destroyer->GetPosition();

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        float delta = GetFrameTime();

        // update the destroyer
        destroyer->Update(delta);
        // check each critter against screen bounds
        if (destroyer->GetX() < 0) {
            destroyer->SetX(0);
            destroyer->SetVelocity(Vector2{ -destroyer->GetVelocity().x, destroyer->GetVelocity().y });
        }
        if (destroyer->GetX() > screenWidth) {
            destroyer->SetX(screenWidth);
            destroyer->SetVelocity(Vector2{ -destroyer->GetVelocity().x, destroyer->GetVelocity().y });
        }
        if (destroyer->GetY() < 0) {
            destroyer->SetY(0);
            destroyer->SetVelocity(Vector2{ destroyer->GetVelocity().x, -destroyer->GetVelocity().y });
        }
        if (destroyer->GetY() > screenHeight) {
            destroyer->SetY(screenHeight);
            destroyer->SetVelocity(Vector2{ destroyer->GetVelocity().x, -destroyer->GetVelocity().y });
        }

        // update the critters
        // (dirty flags will be cleared during update)
        {
            if (toBeRemoved.GetLength() > 0)
            {
                critters.Deallocate(*toBeRemoved.First());
            }

            Iterator<Critter> iter = critters.objects.begin();
            for (int i = 0; i < critters.GetActiveCount(); i++)
            {
                (*iter).Update(delta);

                // check each critter against screen bounds
                if ((*iter).GetX() < 0) {
                    (*iter).SetX(0);
                    (*iter).SetVelocity(Vector2{ -(*iter).GetVelocity().x, (*iter).GetVelocity().y });
                }
                if ((*iter).GetX() > screenWidth) {
                    (*iter).SetX(screenWidth);
                    (*iter).SetVelocity(Vector2{ -(*iter).GetVelocity().x, (*iter).GetVelocity().y });
                }
                if ((*iter).GetY() < 0) {
                    (*iter).SetY(0);
                    (*iter).SetVelocity(Vector2{ (*iter).GetVelocity().x, -(*iter).GetVelocity().y });
                }
                if ((*iter).GetY() > screenHeight) {
                    (*iter).SetY(screenHeight);
                    (*iter).SetVelocity(Vector2{ (*iter).GetVelocity().x, -(*iter).GetVelocity().y });
                }

                // kill any critter touching the destroyer
                // simple circle-to-circle collision check
                float dist = Vector2Distance((*iter).GetPosition(), destroyer->GetPosition());
                if (dist < (*iter).GetRadius() + destroyer->GetRadius())
                {
                    int a = 23;
                    int* b = a;
                    Critter* pointer = *iter;
                    toBeRemoved.PushBack((*iter));
                    // this would be the perfect time to put the critter into an object pool
                }
                iter++;
            }
        }

        // ---
        // TO DO: make this collision loop not have a nested loop if you can
        // ---

        // check for critter-on-critter collisions
        {
            Iterator<Critter> iterA = critters.objects.begin();
            for (int i = 0; i < critters.GetActiveCount(); i++)
            {

                if ((*iterA).IsDead())
                {
                    iterA++;
                    continue;
                }

                Iterator<Critter> iterB = critters.objects.begin();
                for (int j = 0; j < critters.GetActiveCount(); j++) {
                    if (i == j || (*iterA).IsDirty() || (*iterB).IsDead()) // note: the other critter (j) could be dirty - that's OK
                    {
                        iterB++;
                        continue;
                    }
                    // check every critter against every other critter
                    float dist = Vector2Distance((*iterA).GetPosition(), (*iterB).GetPosition());
                    if (dist < (*iterA).GetRadius() + (*iterB).GetRadius())
                    {
                        // collision!
                        // do math to get critters bouncing
                        Vector2 normal = Vector2Normalize(Vector2Subtract((*iterB).GetPosition(), (*iterA).GetPosition()));

                        // not even close to real physics, but fine for our needs
                        (*iterA).SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));
                        // set the critter to *dirty* so we know not to process any more collisions on it
                        (*iterA).SetDirty();

                        // we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
                        // to make sure the other critter is clean before we do the collision response
                        if (!(*iterB).IsDirty()) {
                            (*iterB).SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
                            (*iterB).SetDirty();
                        }
                        iterB++;
                        break;
                    }
                }
                iterA++;
            }

        }

        timer -= delta;
        if (timer <= 0 && critters.GetInactiveCount() > 0)
        {
            timer = 1;
            Vector2 normal = Vector2Normalize(destroyer->GetVelocity());

            // get a position behind the destroyer, and far enough away that the critter won't bump into it again
            Vector2 pos = destroyer->GetPosition();
            pos = Vector2Add(pos, Vector2Scale(normal, -50));
            // its pretty ineficient to keep reloading textures. ...if only there was something else we could do
            critters.Allocate(pos, Vector2Scale(normal, -MAX_VELOCITY), 12, "res/10.png");

            nextSpawnPos = destroyer->GetPosition();
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // draw the critters
        {
            Iterator<Critter> iter = critters.objects.begin();
            for (int i = 0; i < critters.GetActiveCount(); i++)
            {
                (*iter).Draw();
                iter++;
            }
        }
        // draw the destroyer
        // (if you're wondering why it looks a little odd when sometimes critters are destroyed when they're not quite touching the 
        // destroyer, it's because the origin is at the top-left. ...you could fix that!)
        destroyer->Draw();

        DrawFPS(10, 10);
        //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    {
        Iterator<Critter> iter = critters.objects.begin();
        for (int i = 0; i < CRITTER_COUNT; i++)
        {
            (*iter).Unload();
        }
    }


    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}