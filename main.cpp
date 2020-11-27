#define OLC_PGE_APPLICATION
#include <vector>
#include "olcPixelGameEngine.h"
#include "physics.hpp"

class Gravity : public olc::PixelGameEngine {
public:
    Gravity() {
        sAppName = "Gravity Simulation";
        objects.reserve(5);
        objects.push_back(Particle(Vector2(640, 360), Vector2(), 10000, 20, olc::YELLOW)); // Sun
        objects.push_back(Particle(Vector2(640, 20), Vector2(4, 1), 20, 5)); // Planet
    }
    
public:
    std::vector<Particle> objects;
    int numObjects = 2; // This is so objects.size() doesn't need to be called multiple times each loop
    bool sunGravity = 0;
    
    bool OnUserCreate() override {return true;}
    
    bool OnUserUpdate(float fElapsedTime) override {
        
        // Get mouse input for UI
        if(GetMouse(0).bReleased) {
            if(GetMouseX() < 75 && GetMouseX() > 25) {
                if(GetMouseY() < 75 && GetMouseY() > 25) {
                    objects.push_back(Particle(Vector2(640, 20), Vector2(4, 1), 20, 5, olc::Pixel(rand() % 256, rand() % 256, rand()% 256)));
                } else if (GetMouseY() < 150 && GetMouseY() > 100) {
                    sunGravity = !sunGravity;
                    objects[0].setVelocity(Vector2());
                }
            }
        }
        
        numObjects = objects.size();
        
        // Apply gravity
        for(int i = !sunGravity; i < numObjects; i++) {
            for(int j = 0; j < numObjects; j++) {
                if(i == j) continue;
                objects[i].gravityTo(objects[j]);
            }
        }
        
        // Draw

        // Clear screen
        Clear(olc::BLACK);
        
        // Draw '+' button
        FillRect(25, 25, 50, 50, olc::BLUE);
        DrawString(35, 33, "+", olc::WHITE, 5);
        // Draw sun toggle button
        FillRect(25, 100, 50, 50, olc::BLUE);
        DrawString(27, 117, "SUN", olc::WHITE, 2);
        
        for(int i = 0; i < numObjects; i++) {
            if(objects[i].move(ScreenWidth(), ScreenHeight())) {
                FillCircle(objects[i].getX(), objects[i].getY(), objects[i].radius, objects[i].colour);
            }
            else {
                objects.erase(objects.begin() + i);
                numObjects--;
            }
            
        }
        
        return true;
    }
};

int main() {
    Gravity sim;
    if(sim.Construct(1280, 720, 1, 1))
        sim.Start();
    return 0;
}
