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
//////////////////////////////////////////////////////////////////////////////////////////////
////Edits and bug fixes done by F0rbid Code
//////////////////////////////////////////////////////////////////////////////////////////////

#include "raylib.h"
#include "DataFile.h"

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    //set screen height and width
    int screenWidth = 800;
    int screenHeight = 450;
    int recordCount = 0;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    DataFile* data = new DataFile; //initialise data file 
    

    ///////////////////////////////////////////////
    /// CHANGE THIS FUNCTION
    ///////////////////////////////////////////////
    //data.Load("npc_data.dat"); //load the record file
    data->GetPositions("npc_data.dat");
    int currentRecordIdx = 0; //set current record to 0


    /////////////////////////////////////////////////
    ////Modify this to work with random reads
    /////////////////////////////////////////////////
    //DataFile::Record* currentRecord = data.GetRecord(currentRecordIdx); //load the first record from the record array
    recordCount = data->GetRecordCount();

   

    DataFile :: Record currentRecord = *(data->LoadRecord("npc_data.dat", currentRecordIdx)); //load the record based on the record index
    Texture2D recordTexture = LoadTextureFromImage(currentRecord.image); //load the texture from the current record
    


    SetTargetFPS(60); //sets target frame reate for raylib
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

       

        if (IsKeyPressed(KEY_LEFT)) ///when left key is pressed
        {
            currentRecordIdx--; //reduce current record index by 1
            if (currentRecordIdx < 0) //if current record index is less then 0
            {
                currentRecordIdx = 0; //set current record index to 0
            }
            //////////////////////////////////////////////////////////
            ////MODIFY TO WORK WITH RANDOM READS
            //////////////////////////////////////////////////////////
           
            currentRecord = *(data->LoadRecord("npc_data.dat", currentRecordIdx)); // load the record based on the record index

           // currentRecord = data.GetRecord(currentRecordIdx); //load the current record index from array
            recordTexture = LoadTextureFromImage(currentRecord.image);//load the texture from the current record image
        }

        if (IsKeyPressed(KEY_RIGHT))//if right key is pressed
        {
            currentRecordIdx++;//increase the current record index by 1
            if (currentRecordIdx >= (recordCount - 1)) //if current index is greater then record count - 1
            {
                currentRecordIdx = (recordCount - 1); //set current index to the total record count -1
            }

            currentRecord = *(data->LoadRecord("npc_data.dat", currentRecordIdx)); //load the record based on the record index

            //currentRecord = data.GetRecord(currentRecordIdx); //load the current record index from array
            recordTexture = LoadTextureFromImage(currentRecord.image);//load the texture from the current record image
        }


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE); //set background to white

        DrawTexture(recordTexture, 300, 50, WHITE); //display record picture

        //display record name
        DrawText("NAME", 10, 50, 20, LIGHTGRAY); 
        DrawText(currentRecord.name.c_str(), 10, 80, 20, LIGHTGRAY);

        //display record  name
        DrawText("AGE", 10, 120, 20, LIGHTGRAY);
        DrawText(to_string(currentRecord.age).c_str(), 10, 150, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    delete data;
    data = nullptr;
    //--------------------------------------------------------------------------------------

    return 0;
}