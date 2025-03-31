#include <raylib.h>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int SCR_WIDTH = 1280;
const int SCR_HEIGHT = 720;


enum decay_type {
    alpha = 0,
    beta_pos = 1,
    beta_neg = 2,
    proton = 3,
    neutron = 4,
    diproton = 5,
    dineutron = 6,
    stable = 7,
    electron_capture = 8,
};


struct element{
    string name;
    bool stable;
    float halflife;
    int decay_type;
};

int main() {
    element element_grid[11][11];
    

    //element names
    for (int i = 0; i < 11; i++) {
        element_grid[0][i].name = to_string(i) + " Neutrons";
    }
    for (int i = 0; i < 11; i++) {
        element_grid[1][i].name = "Hydrogen-" + to_string(i+1);
    }
    element_grid[1][0].name = "Hydrogen";
    element_grid[1][1].name = "Deuterium";
    element_grid[1][2].name = "Tritium";
    for (int i = 0; i < 11; i++) {
        element_grid[2][i].name = "Helium-" + to_string(i+2);
    }
    element_grid[2][0].name = "diproton";
    element_grid[2][2].name = "Helium";
    for (int i = 0; i < 11; i++) {
        element_grid[3][i].name = "Lithium-" + to_string(i+3);
    }
    element_grid[3][4].name = "Lithium";
    for (int i = 0; i < 11; i++) {
        element_grid[4][i].name = "Beryllium-" + to_string(i+4);
    }
    element_grid[4][5].name = "Beryllium";
    for (int i = 0; i < 11; i++) {
        element_grid[5][i].name = "Boron-" + to_string(i+5);
    }
    element_grid[5][6].name = "Boron";
    for (int i = 0; i < 11; i++) {
        element_grid[6][i].name = "Carbon-" + to_string(i+6);
    }
    element_grid[6][6].name = "Carbon";
    for (int i = 0; i < 11; i++) {
        element_grid[7][i].name = "Nitrogen-" + to_string(i+7);
    }
    element_grid[7][7].name = "Nitrogen";
    for (int i = 0; i < 11; i++) {
        element_grid[8][i].name = "Oxygen-" + to_string(i+8);
    }
    element_grid[8][8].name = "Oxygen";
    for (int i = 0; i < 11; i++) {
        element_grid[9][i].name = "Florine-" + to_string(i+9);
    }
    element_grid[9][10].name = "Florine";
    for (int i = 0; i < 11; i++) {
        element_grid[10][i].name = "Neon-" + to_string(i+10);
    }
    element_grid[10][10].name = "Neon";

    for (int a = 0; a < 11; a++) {
        for (int b = 0; b < 11; b++) {
            element_grid[a][b].decay_type = stable;
        }
    }
    


    //element type and half-life (in seconds * 144)
    //hydrogen
    element_grid[1][2].halflife = 2334631248;
    element_grid[1][2].decay_type = beta_neg;
    element_grid[1][3].halflife = 1;
    element_grid[1][3].decay_type = neutron;
    element_grid[1][4].halflife = 1;
    element_grid[1][4].decay_type = dineutron;
    //helium
    element_grid[2][0].halflife = 1;
    element_grid[2][0].decay_type = proton;
    element_grid[2][3].halflife = 1;
    element_grid[2][3].decay_type = neutron;
    element_grid[2][4].halflife = 115;
    element_grid[2][4].decay_type = beta_neg;
    element_grid[2][5].halflife = 1;
    element_grid[2][5].decay_type = neutron;
    element_grid[2][6].halflife = 17;
    element_grid[2][6].decay_type = beta_neg;
    element_grid[2][7].halflife = 1;
    element_grid[2][7].decay_type = neutron;
    element_grid[2][8].halflife = 1;
    element_grid[2][8].decay_type = dineutron;   
    //lithium
    element_grid[3][1].halflife = 17230449600;
    element_grid[3][1].decay_type = proton;
    element_grid[3][2].halflife = 70057872000;
    element_grid[3][2].decay_type = proton;
    element_grid[3][5].halflife = 121;
    element_grid[3][5].decay_type = beta_neg;
    element_grid[3][6].halflife = 26;
    element_grid[3][6].decay_type = beta_neg;
    element_grid[3][7].halflife = 1;
    element_grid[3][7].decay_type = neutron;
    element_grid[3][8].halflife = 1;
    element_grid[3][8].decay_type = beta_neg;
    element_grid[3][9].halflife = 1;
    element_grid[3][9].decay_type = neutron;   
    element_grid[3][10].halflife = 1;
    element_grid[3][10].decay_type = dineutron;
    //beryllium
    element_grid[4][2].halflife = 1;
    element_grid[4][2].decay_type = diproton;
    element_grid[4][3].halflife = 662141952;
    element_grid[4][3].decay_type = electron_capture;
    element_grid[4][4].halflife = 1;
    element_grid[4][4].decay_type = alpha;
    element_grid[4][6].halflife = 1;
    element_grid[4][6].decay_type = beta_neg;
    element_grid[4][7].halflife = 1981;
    element_grid[4][7].decay_type = beta_neg;
    element_grid[4][8].halflife = 3;
    element_grid[4][8].decay_type = beta_neg;   
    element_grid[4][9].halflife = 1;
    element_grid[4][9].decay_type = neutron;
    element_grid[4][10].halflife = 1;
    element_grid[4][10].decay_type = beta_neg;






    for (int a = 0; a < 11; a++) {
        for (int b = 0; b < 11; b++) {
            if (element_grid[a][b].halflife != 0) {
                element_grid[a][b].stable = false;
            } else {
                element_grid[a][b].stable = true;
            }
        }
    }



    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Physics Element \"Game\"");
    SetTargetFPS(144);
    int i = 0;
    int protons = 2;
    int neutrons = 2;
    int electrons = 2;
    bool time_running = false;
    int frames = 0;
    int time = 0;
    bool electron_balence = false;
    while (!WindowShouldClose()) {
        frames++;
        if (frames >= 144) {
            time++;
            frames = 0;
        }


        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            float mouse_x = GetMousePosition().x;
            float mouse_y = GetMousePosition().y;
            //proton add
            if (mouse_x <= 90 && mouse_x >= 10 && mouse_y <= 90 && mouse_y >= 10 && protons < 10) {
                protons++;
                time = 0;
                frames = 0;
            }
            //proton remove
            if (mouse_x >= 100 && mouse_x <= 180 && mouse_y <= 90 && mouse_y >= 10 && protons > 0) {
                protons--;
                time = 0;
                frames = 0;
            }
            //neutron add
            if (mouse_x <= 90 && mouse_x >= 10 && mouse_y >= 100 && mouse_y <= 180 && neutrons < 10) {
                neutrons++;
                time = 0;
                frames = 0;
            }
            //neuton remove
            if (mouse_x >= 100 && mouse_x <= 180 && mouse_y >= 100 && mouse_y <= 180 && neutrons > 0) {
                neutrons--;
                time = 0;
                frames = 0;
            }
            //electron add
            if (mouse_x <= 90 && mouse_x >= 10 && mouse_y >= 190 && mouse_y <= 270 && electrons < 10 && !electron_balence) {
                electrons++;
                time = 0;
                frames = 0;
            }
            //electron remove
            if (mouse_x >= 100 && mouse_x <= 180 && mouse_y >= 190 && mouse_y <= 270 && electrons > 0 && !electron_balence) {
                electrons--;
                time = 0;
                frames = 0;
            }
            //electron balence
            if (mouse_x >= 10 && mouse_x <= 90 && mouse_y >= 310 && mouse_y <= 390) {
                if (electron_balence) {
                    electron_balence = false;
                } else {
                    electron_balence = true;
                }
                time = 0;
                frames = 0;
            }
        }

        if (electron_balence) {
            electrons = protons;
        }

       if (!element_grid[protons][neutrons].stable && time_running) {
            int random_num = rand() % 10;
            double pow_1 = powf(1./2., 1./element_grid[protons][neutrons].halflife);
            double pow_2 = powf(pow_1, time*144.+frames);
            double comparison_num = 10 * pow_2;
            if (random_num > comparison_num) {
                switch (element_grid[protons][neutrons].decay_type) {
                    case 0: //alpha
                    protons -= 2;
                    neutrons -= 2;
                    break;
                    case 1: //beta pos
                    protons--;
                    neutrons++;
                    break;
                    case 2: //beta neg
                    protons++;
                    neutrons--;
                    break;
                    case 3: //proton
                    protons--;
                    electrons--;
                    break;
                    case 4: //neutron
                    neutrons--;
                    break;
                    case 5: //diproton
                    protons -= 2;
                    electrons -= 2;
                    break;
                    case 6: //dineutron
                    neutrons -= 2;
                    break;
                    case 7: //stable
                    break;
                    case 8: //electron capture
                    protons--;
                    neutrons++;
                    break;
                    default:
                    cout << "something went wrong with the decay type lol";
                    return 1;

                }
                frames = 0;
                time = 0;
            }
            else {
                //cout << "not decayed" << endl;
            }
        }
        //cout << "time: " << time << endl;
        //cout << "frames: " << frames << endl;
        

        
        if (IsKeyPressed(KEY_SPACE)) {
            if (time_running) {time_running = false;}
            else {time_running = true;}
        }

        int electrons_shell_1 = min(electrons, 2);
        int electrons_shell_2 = min(electrons, 10)-2;


        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawRectangle(0, 0, 190, 280, GRAY);
        DrawRectangle(0, 300, 100, 100, GRAY);

        //proton button
        DrawRectangle(10, 10, 80, 80, GREEN);
        DrawRectangle(100, 10, 80, 80, RED);
        DrawText("P+", 40, 40, 20, WHITE);
        DrawText("P-", 130, 40, 20, WHITE);
        //neutron button
        DrawRectangle(10, 100, 80, 80, GREEN);
        DrawRectangle(100, 100, 80, 80, RED);
        DrawText("N+", 40, 130, 20, WHITE);
        DrawText("N-", 130, 130, 20, WHITE);
        //electrons buttons
        DrawRectangle(10, 190, 80, 80, GREEN);
        DrawRectangle(100, 190, 80, 80, RED);
        DrawText("e+", 40, 220, 20, WHITE);
        DrawText("e-", 130, 220, 20, WHITE);
        //electron balence button
        DrawText("Balence electrons", 1, 280, 20, WHITE);
        if (electron_balence) {
            DrawRectangle(10, 310, 80, 80, WHITE);
        } else {
            DrawRectangle(10, 310, 80, 80, BLACK);
        }



        if (electrons >= 3) {
            DrawCircle(SCR_WIDTH/2, SCR_HEIGHT/2, 240, GRAY);
            DrawCircle(SCR_WIDTH/2, SCR_HEIGHT/2, 235, BLACK);
        }
        if (electrons >= 1) {
            DrawCircle(SCR_WIDTH/2, SCR_HEIGHT/2, 160, GRAY);
            DrawCircle(SCR_WIDTH/2, SCR_HEIGHT/2, 155, BLACK);
        }

        if (electrons >= 1) {
            DrawCircle(SCR_WIDTH/2+155.5, SCR_HEIGHT/2, 20, GREEN);
        }
        if (electrons >= 3) {
            DrawCircle(SCR_WIDTH/2+235.5, SCR_HEIGHT/2, 20, GREEN);
        }
        
        for (int i = 1; i < electrons_shell_1; i++) {
            DrawCircle(155.5*cos(((2*PI)/electrons_shell_1)*i)+SCR_WIDTH/2, 155.5*sin(((2*PI)/electrons_shell_1)*i)+SCR_HEIGHT/2, 20, GREEN);
        }
        for (int i = 1; i < electrons_shell_2; i++) {
            DrawCircle(235.5*cos(((2*PI)/electrons_shell_2)*i)+SCR_WIDTH/2, 235.5*sin(((2*PI)/electrons_shell_2)*i)+SCR_HEIGHT/2, 20, GREEN);
        }



        DrawCircle(SCR_WIDTH/2, SCR_HEIGHT/2, 80, BLUE);
        DrawText(("P=" + to_string(protons)).c_str(), (SCR_WIDTH-(MeasureTextEx(GetFontDefault(), ("P=" + to_string(protons)).c_str(), 20, 1).x))/2, 330, 20, WHITE);
        DrawText(("N=" + to_string(neutrons)).c_str(), (SCR_WIDTH-(MeasureTextEx(GetFontDefault(), ("N=" + to_string(neutrons)).c_str(), 20, 1).x))/2, 370, 20, WHITE);



        
        DrawText(element_grid[protons][neutrons].name.c_str(), (SCR_WIDTH-(MeasureTextEx(GetFontDefault(), element_grid[protons][neutrons].name.c_str(), 40, 1).x))/2, 10, 40, WHITE);
        DrawText(("Electrons: " + to_string(electrons)).c_str(), (SCR_WIDTH-(MeasureTextEx(GetFontDefault(), ("Electrons: " + to_string(electrons)).c_str(), 30, 1).x))/2, SCR_HEIGHT-40, 30, WHITE);
        if (protons-electrons > 0) {
            DrawText(("Ion charge: +" + to_string(protons-electrons)).c_str(), SCR_WIDTH/2+200, SCR_HEIGHT-30, 20, WHITE);
        } else if (protons-electrons < 0) {
            DrawText(("Ion charge: " + to_string(protons-electrons)).c_str(), SCR_WIDTH/2+200, SCR_HEIGHT-30, 20, WHITE);
        }
        
        if (!time_running) {
            DrawPoly((Vector2){SCR_WIDTH-40, 40}, 3, 30, 0, WHITE);
        } else {
            DrawRectangle(SCR_WIDTH-50, 15, 15, 50, WHITE);
            DrawRectangle(SCR_WIDTH-30, 15, 15, 50, WHITE);
        }
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
