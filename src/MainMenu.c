#include "raylib.h"
#include "stdio.h"

#include "MainMenu.h"
#include "Button.h"
#include "Constants.h"
#include "SceneManager.h"

// Características do Texto
const int TITLE_FontSize = 60;

// Variáveis dos botões
MenuButton playButton;
MenuButton exitButton;
MenuButton creditsButton;

// Características dos botões
const float BUTTON_WIDTH = 200;
const float BUTTON_HEIGHT = 50;
const float BUTTON_SPACING = 20;
const int FontSize = 30;

Color btn_Color = { 255, 255, 255, 60 };
Color btn_HoverColor = { 255, 255, 255, 255 };

Texture2D main_menu;


void MainMenu_Init(void) {
    main_menu = LoadTexture("backgrounds/main_menu.png");

    // Calcula a posição central dos botões
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float totalHeight = (BUTTON_HEIGHT * 2) + BUTTON_SPACING;
    float startY = (screenHeight - totalHeight) / 2;

    // Inicializa o botão Play
    playButton = (MenuButton){
        .Bounds = {
            .x = (screenWidth - BUTTON_WIDTH) / 2,
            .y = startY,
            .width = BUTTON_WIDTH,
            .height = BUTTON_HEIGHT
        },
        .Text = "JOGAR",
        .FontSize = FontSize,
        .Color = btn_Color,
        .HoverColor = btn_HoverColor
    };

    // Inicializa o botão Exit
    exitButton = (MenuButton){
        .Bounds = {
            .x = (screenWidth - BUTTON_WIDTH) / 2,
            .y = startY + 4* (BUTTON_HEIGHT + BUTTON_SPACING),
            .width = BUTTON_WIDTH,
            .height = BUTTON_HEIGHT
        },
        .Text = "SAIR",
        .FontSize = FontSize,
        .Color = btn_Color,
        .HoverColor = btn_HoverColor
    };

    creditsButton = (MenuButton) {
    .Bounds = {
        .x = (screenWidth - BUTTON_WIDTH) / 2,
        .y = startY + 1 * (BUTTON_HEIGHT + BUTTON_SPACING),
        .width = BUTTON_WIDTH,
        .height = BUTTON_HEIGHT
    },
    .Text = "CREDITOS",
    .FontSize = FontSize,
    .Color = btn_Color,
    .HoverColor = btn_HoverColor
    };

}

void MainMenu_Update(void) {

    bool game = CheckCollisionPointRec(GetMousePosition(), playButton.Bounds);
    bool exit = CheckCollisionPointRec(GetMousePosition(), exitButton.Bounds);
    bool credits = CheckCollisionPointRec(GetMousePosition(), creditsButton.Bounds);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (game) SceneManager_ChangeScene(SCENEREFERENCE_GAME);
        //else if (exit) ChangeScene(EXIT);
        //else if (credits) ChangeScene(CREDITS);
    }
}

void DrawMainMenuBackground(void) {
    Rectangle source = { 0.0f, 0.0f, (float)main_menu.width, (float)main_menu.height };
    Rectangle destination = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };
    Vector2 offset = { 0 };
    float rotation = 0.0f;
    Color Color = { 255, 255, 255, 90 };
    DrawTexturePro(main_menu, source, destination, offset, rotation, Color);
}

void MainMenu_Draw(void) {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawMainMenuBackground();
    int titleWidth = MeasureText(CONSTANTS_GAME_TITLE, TITLE_FontSize);
    
    DrawText(CONSTANTS_GAME_TITLE, (GetScreenWidth() - titleWidth) / 2, 100, FontSize * 2, WHITE);
    Button_Draw(&playButton);
	Button_Draw(&exitButton);
    Button_Draw(&creditsButton);

    EndDrawing();
}

void MainMenu_Unload(void) {
    UnloadTexture(main_menu);
}