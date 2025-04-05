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
    gamma_ray = 9,
};


enum changed_particals {
	add_electron = 12,
};


struct element{
    string name;
    bool stable;
    float halflife;
    int decay_types[10];
    int decay_chances[10];
};

enum feed_offsets {
    electron_offset = 40,
    alpha_offset = 97,
    proton_neutron_offset = 60,
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
    element_grid[4][3].halflife = 1;//662141952;
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




	
    int partical_feed[5] = {7,7,7,7,7};
    int partical_feed_pos_neg[5] = {0,0,0,0,0};
    InitWindow(SCR_WIDTH, SCR_HEIGHT, "Physics Element \"Game\"");
    SetTargetFPS(144);
    int i = 0;
    int protons = 2;
    int neutrons = 2;
    int electrons = 2;
    bool time_running = false;
    int locked_frames = 0;
    int locked_time = 0;
    int true_frames = 0;
    int true_time = 0;
    int electron_change = 0;
    bool electron_balence = false;

    int feed_offset = 0;

    while (!WindowShouldClose()) {
	if (time_running) {
            locked_frames++;
            if (locked_frames >= 144) {
                locked_time++;
                locked_frames = 0;
            }
	}
	true_frames++;
        if (true_frames >= 144) {
            true_time++;
            true_frames = 0;
        }

	if (true_frames == 0) {
	    for (int i = 3; i >= 0; i--) {
		partical_feed[i+1] = partical_feed[i];
		partical_feed_pos_neg[i+1] = partical_feed_pos_neg[i];
	    }
	    partical_feed[0] = 7;
	}


        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            float mouse_x = GetMousePosition().x;
            float mouse_y = GetMousePosition().y;
            //proton add
            if (mouse_x <= 90 && mouse_x >= 10 && mouse_y <= 90 && mouse_y >= 10 && protons < 10) {
                protons++;
                locked_time = 0;
                locked_frames = 0;
		if (!(partical_feed[0] == 7)) {
  	            for (int i = 3; i >= 0; i--) {
		    	partical_feed[i+1] = partical_feed[i];
		   	partical_feed_pos_neg[i+1] = partical_feed_pos_neg[i];
	            }
		}
		partical_feed[0] = proton;
		partical_feed_pos_neg[0] = 1;
            }
            //proton remove
            if (mouse_x >= 100 && mouse_x <= 180 && mouse_y <= 90 && mouse_y >= 10 && protons > 0) {
                protons--;
                locked_time = 0;
                locked_frames = 0;
		if (!(partical_feed[0] == 7)) {
  	            for (int i = 3; i >= 0; i--) {
		    	partical_feed[i+1] = partical_feed[i];
		   	partical_feed_pos_neg[i+1] = partical_feed_pos_neg[i];
	            }
		}
		partical_feed[0] = proton;
		partical_feed_pos_neg[0] = 0;
            }
            //neutron add
            if (mouse_x <= 90 && mouse_x >= 10 && mouse_y >= 100 && mouse_y <= 180 && neutrons < 10) {
                neutrons++;
                locked_time = 0;
                locked_frames = 0;
		if (!(partical_feed[0] == 7)) {
  	            for (int i = 3; i >= 0; i--) {
		    	partical_feed[i+1] = partical_feed[i];
		   	partical_feed_pos_neg[i+1] = partical_feed_pos_neg[i];
	            }
		}
		partical_feed[0] = neutron;
		partical_feed_pos_neg[0] = 1;
            }
            //neuton remove
            if (mouse_x >= 100 && mouse_x <= 180 && mouse_y >= 100 && mouse_y <= 180 && neutrons > 0) {
                neutrons--;
                locked_time = 0;
                locked_frames = 0;
		if (!(partical_feed[0] == 7)) {
  	            for (int i = 3; i >= 0; i--) {
		    	partical_feed[i+1] = partical_feed[i];
		   	partical_feed_pos_neg[i+1] = partical_feed_pos_neg[i];
	            }
		}
		partical_feed[0] = neutron;
		partical_feed_pos_neg[0] = 0;
            }
            //electron add
            if (mouse_x <= 90 && mouse_x >= 10 && mouse_y >= 190 && mouse_y <= 270 && electrons < 10 && !electron_balence) {
                electrons++;
                locked_time = 0;
                locked_frames = 0;
		if (!(partical_feed[0] == 7)) {
  	            for (int i = 3; i >= 0; i--) {
		    	partical_feed[i+1] = partical_feed[i];
		   	partical_feed_pos_neg[i+1] = partical_feed_pos_neg[i];
	            }
		}
		partical_feed[0] = add_electron;
		partical_feed_pos_neg[0] = 1;
            }
            //electron remove
            if (mouse_x >= 100 && mouse_x <= 180 && mouse_y >= 190 && mouse_y <= 270 && electrons > 0 && !electron_balence) {
                electrons--;
                locked_time = 0;
                locked_frames = 0;
		if (!(partical_feed[0] == 7)) {
  	            for (int i = 3; i >= 0; i--) {
		    	partical_feed[i+1] = partical_feed[i];
		   	partical_feed_pos_neg[i+1] = partical_feed_pos_neg[i];
	            }
		}
		partical_feed[0] = add_electron;
		partical_feed_pos_neg[0] = 0;
            }
            //electron balence
            if (mouse_x >= 10 && mouse_x <= 90 && mouse_y >= 310 && mouse_y <= 390) {
                if (electron_balence) {
                    electron_balence = false;
                } else {
                    electron_balence = true;
                }
                locked_time = 0;
                locked_frames = 0;
            }
        } 
        if (electron_balence) {
   	    electron_change = protons-electrons;
	    for (int a = 0; a < abs(electron_change); a++) {
		if (!(partical_feed[0] == 7)) {
  	            for (int i = 3; i >= 0; i--) {
		    	partical_feed[i+1] = partical_feed[i];
		   	partical_feed_pos_neg[i+1] = partical_feed_pos_neg[i];
	            }
		}
		partical_feed[0] = add_electron;
		if (electron_change < 0) {
		    partical_feed_pos_neg[0] = 0;
		} else {
                    partical_feed_pos_neg[0] = 1;
		}

	    }
            electrons = protons;
        }
	int random_num = rand() % 10;
        double pow_1 = powf(1./2., 1./element_grid[protons][neutrons].halflife);
        double pow_2 = powf(pow_1, locked_time*144.+locked_frames);
        double comparison_num = 10 * pow_2;
       if (!element_grid[protons][neutrons].stable && time_running) {
            if (random_num > comparison_num) {
            	for (int i = 2; i > 1; i--) {
		    partical_feed[i+1] = partical_feed[i];
		}
		partical_feed_pos_neg[0] = 0;
		random_num = rand() % 100;
		if random_num < element_grid[protons][neutrons].decay_chances[i]
                switch (element_grid[protons][neutrons].decay_type) {
                    case 0: //alpha
                    protons -= 2;
                    neutrons -= 2;
		    partical_feed[0] = alpha;
		    partical_feed_pos_neg[0] = 0;
                    break;
                    case 1: //beta pos
                    protons--;
                    neutrons++;
		    partical_feed[0] = beta_pos;
		    partical_feed_pos_neg[0] = 0;
                    break;
                    case 2: //beta neg
                    protons++;
                    neutrons--;
		    partical_feed[0] = beta_neg;
                    break;
                    case 3: //proton
                    protons--;
		    partical_feed[0] = proton;
                    break;
                    case 4: //neutron
                    neutrons--;
		    partical_feed[0] = neutron;
                    break;
                    case 5: //diproton
                    protons -= 2;
		    partical_feed[0] = diproton;
                    break;
                    case 6: //dineutron
                    neutrons -= 2;
		    partical_feed[0] = dineutron;
                    break;
                    case 7: //stable
                    break;
                    case 8: //electron capture
                    protons--;
                    neutrons++;
		    partical_feed[0] = electron_capture;
                    break;
                    default:
                    cout << "something went wrong with the decay type lol";
                    return 1;

                }
                locked_frames = 0;
                locked_time = 0;
            }
            else {
                //cout << "not decayed" << endl;
            }
        }
        //cout << "locked_time: " << time << endl;
        //cout << "locked_frames: " << frames << endl;
        

        
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
            DrawText(("Ion charge: +" + to_string(protons-electrons)).c_str(), SCR_WIDTH/2-400, SCR_HEIGHT-30, 20, WHITE);
        } else if (protons-electrons < 0) {
            DrawText(("Ion charge: " + to_string(protons-electrons)).c_str(), SCR_WIDTH/2-400, SCR_HEIGHT-30, 20, WHITE);
        }
	if (!element_grid[protons][neutrons].stable) {
		DrawText(("Chance of decay: " + to_string(ceil((1-comparison_num/10.)*10000.)/10000*100) + "%").c_str(), 900, 80, 20, WHITE);
		DrawText("(This frame)", 900, 100, 10, WHITE);
	} else {
	    DrawText("Stable", 900, 80, 30, WHITE);
	}
        
        if (!time_running) {
            DrawPoly((Vector2){SCR_WIDTH-40, 40}, 3, 30, 0, WHITE);
        } else {
            DrawRectangle(SCR_WIDTH-50, 15, 15, 50, WHITE);
            DrawRectangle(SCR_WIDTH-30, 15, 15, 50, WHITE);
        }

	//partical feed
	feed_offset = -100;
	for (int i = 4; i >= 0; i--) {
	    switch (partical_feed[i]) {
		    case 0: //alpha
			feed_offset += alpha_offset;
			if (partical_feed_pos_neg[i] == 0) {
				DrawText("- Alpha partical", 900, SCR_HEIGHT-feed_offset, 10, WHITE);
			} else {
				DrawText("+ Alpha partical", 900, SCR_HEIGHT-feed_offset, 10, WHITE);
			}
			DrawCircle(1050, SCR_HEIGHT-feed_offset, 40, RED);
			DrawCircle(80*cos(PI/4)+1050, 80*sin(PI/4)+(SCR_HEIGHT-feed_offset), 40, GRAY);
			DrawCircle(1050+2*(80*cos(PI/4)), SCR_HEIGHT-feed_offset, 40, RED);
			DrawCircle(80*cos(-1*(PI/4))+1050, 80*sin(-1*(PI/4))+(SCR_HEIGHT-feed_offset), 40, GRAY);
			DrawText("P+", 1050 - (MeasureTextEx(GetFontDefault(), ("P+" + to_string(electrons)).c_str(), 20, 1).x)/4, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			DrawText("P+", (1050+2*(80*cos(PI/4))) - (MeasureTextEx(GetFontDefault(), ("P+" + to_string(electrons)).c_str(), 20, 1).x)/4, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			DrawText("N", (80*cos(PI/4)+1050) - (MeasureTextEx(GetFontDefault(), ("N" + to_string(electrons)).c_str(), 20, 1).x)/4, 80*sin(PI/4)+(SCR_HEIGHT-feed_offset)-10, 20, WHITE);
			DrawText("N", (80*cos(-1*(PI/4))+1050) - (MeasureTextEx(GetFontDefault(), ("N" + to_string(electrons)).c_str(), 20, 1).x)/4, 80*sin(-1*(PI/4))+(SCR_HEIGHT-feed_offset)-10, 20, WHITE);
			feed_offset += alpha_offset;
			break;

		    	case 1: //beta_pos
			feed_offset += electron_offset;
			if (partical_feed_pos_neg[i] == 0) {
			    DrawText("- Positron", 900, SCR_HEIGHT-feed_offset-5, 10, WHITE);
			} else {
			    DrawText("+ Positron", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			}
			DrawCircle(1010+20, SCR_HEIGHT-feed_offset, 20, GREEN);
			DrawText("e+", (1010+20) - (MeasureTextEx(GetFontDefault(), ("e+" + to_string(electrons)).c_str(), 20, 1).x)/4, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			DrawText("-  v", 1070, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			feed_offset += electron_offset;
			break;
			case 2: //beta_neg
			feed_offset += electron_offset;
			if (partical_feed_pos_neg[i] == 0) {
			    DrawText("- Electron", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			} else {
			    DrawText("+ Electron", 900, SCR_HEIGHT-5+feed_offset, 10, WHITE);
			}
			DrawCircle(1010+20, SCR_HEIGHT-feed_offset, 20, GREEN);
			DrawText("e-", (1010+20) - (MeasureTextEx(GetFontDefault(), ("e-" + to_string(electrons)).c_str(), 20, 1).x)/4, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			DrawText("-  v", 1070, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			DrawText("_", 1097, SCR_HEIGHT-feed_offset-25, 20, WHITE);
			feed_offset += electron_offset;
			break;
			case 3: //proton
			feed_offset += proton_neutron_offset;
			if (partical_feed_pos_neg[i] == 0) {
			    DrawText("- Proton", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			} else {
			    DrawText("+ Proton", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			}
			DrawCircle(1010+20, SCR_HEIGHT-feed_offset, 40, RED);
			DrawText("P+", (1010+20) - (MeasureTextEx(GetFontDefault(), ("P+" + to_string(electrons)).c_str(), 20, 1).x)/4, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			feed_offset += proton_neutron_offset;
			break;
			case 4: // neutron
			feed_offset += proton_neutron_offset;
			if (partical_feed_pos_neg[i] == 0) {
			    DrawText("- Neutron", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			} else {
			    DrawText("+ Neutron", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			}
			DrawCircle(1010+20, SCR_HEIGHT-feed_offset, 40, GRAY);
			DrawText("N", (1010+20) - (MeasureTextEx(GetFontDefault(), ("N" + to_string(electrons)).c_str(), 20, 1).x)/4, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			feed_offset += proton_neutron_offset;
			break;

			case 5: // diproton
			feed_offset += proton_neutron_offset;
			if (partical_feed_pos_neg[i] == 0) {
			    DrawText("- diProton", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			} else {
			    DrawText("+ diProton", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			}
			DrawCircle(1010+20, SCR_HEIGHT-feed_offset, 40, RED);
			DrawCircle(1010+20+40, SCR_HEIGHT-feed_offset, 40, RED);

			DrawText("P+", (1010+20) - (MeasureTextEx(GetFontDefault(), ("P+" + to_string(electrons)).c_str(), 20, 1).x)/4, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			DrawText("P+", (1010+20+40) - (MeasureTextEx(GetFontDefault(), ("P+" + to_string(electrons)).c_str(), 20, 1).x)/4, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			feed_offset += proton_neutron_offset;
			break;
			case 6: // dineutron
			feed_offset += proton_neutron_offset;
			if (partical_feed_pos_neg[i] == 0) {
			    DrawText("- diNeutron", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			} else {
			    DrawText("+ diNeutron", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			}
			DrawCircle(1010+20, SCR_HEIGHT-feed_offset, 40, GRAY);
			DrawCircle(1010+20+40, SCR_HEIGHT-feed_offset, 40, GRAY);

			DrawText("N", (1010+20) - (MeasureTextEx(GetFontDefault(), ("N" + to_string(electrons)).c_str(), 20, 1).x)/4, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			DrawText("N", (1010+20+40) - (MeasureTextEx(GetFontDefault(), ("N" + to_string(electrons)).c_str(), 20, 1).x)/4, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			feed_offset += proton_neutron_offset;
			break;
			case 8: // electron_capture
			feed_offset += electron_offset;
			DrawText("- Anti-Neutrino", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			DrawText("v", 1027, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			DrawText("_", 1027, SCR_HEIGHT-feed_offset-25, 20, WHITE);
			case 12: //electron
			feed_offset += electron_offset;
			if (partical_feed_pos_neg[i] == 0) {
			    DrawText("- Electron", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			} else {
			    DrawText("+ Electron", 900, SCR_HEIGHT-5-feed_offset, 10, WHITE);
			}
			DrawCircle(1010+20, SCR_HEIGHT-feed_offset, 20, GREEN);
			DrawText("e-", (1010+20) - (MeasureTextEx(GetFontDefault(), ("e-" + to_string(electrons)).c_str(), 20, 1).x)/4, SCR_HEIGHT-feed_offset-10, 20, WHITE);
			feed_offset += electron_offset;
			break;


			default:
			feed_offset += 150;
			break;
	    }
	}



        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
