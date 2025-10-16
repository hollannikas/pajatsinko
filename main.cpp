#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>

// ================= Ball Class =================
class Ball {
public:
    Ball(int startX, int startY, int w, int h)
        : x(startX), y(startY), vx(0), vy(1), width(w), height(h)
    {
        rng.seed(std::random_device{}());
        dist = std::uniform_int_distribution<int>(0, 1);
    }

    void update(const std::vector<std::vector<int>>& pinRows) {
        // Move ball
        x += vx;
        y += vy;

        // Bounce off walls
        if (x <= 0) { x = 0; vx = 1; }
        if (x >= width - 1) { x = width - 1; vx = -1; }

        // Check each pin row
        for (size_t row = 0; row < pinRows.size(); ++row) {
            int rowY = 3 + static_cast<int>(row) * 2; // vertical spacing
            if (y == rowY) {
                if (row == 0) {
                    // First row: go straight onto the middle pin
                    vx = 0;
                    x = pinRows[0][pinRows[0].size() / 2]; // middle pin
                } else {
                    // Randomly deflect left or right
                    vx = (dist(rng) == 0) ? -1 : 1;
                }
            }
        }

        // Reset ball at bottom
        if (y >= height - 1) {
            y = 0;
            x = width / 2;
            vx = 0; // reset horizontal velocity
        }
    }

    int getX() const { return x; }
    int getY() const { return y; }

private:
    int x, y;
    int vx, vy;
    int width, height;

    std::mt19937 rng;
    std::uniform_int_distribution<int> dist;
};

// ================= Pachinko Machine =================
class PachinkoMachine {
public:
    PachinkoMachine(int w, int h)
        : width(w), height(h), ball(w / 2, 0, w, h)
    {
        // 4 pin rows (staggered positions for triangle-like pattern)
        pinRows = {
            {2, 5, 8, 11, 14},
            {1, 4, 7, 10, 13},
            {2, 5, 8, 11, 14},
            {1, 4, 7, 10, 13}
        };
    }

    void step() {
        ball.update(pinRows);
    }

    void render() const {
        std::cout << "\033[2J\033[1;1H"; // clear screen

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                bool isPin = false;

                // Check if a pin exists here
                for (size_t row = 0; row < pinRows.size(); ++row) {
                    int rowY = 3 + static_cast<int>(row) * 2;
                    if (y == rowY) {
                        for (int px : pinRows[row]) {
                            if (x == px) { isPin = true; break; }
                        }
                    }
                    if (isPin) break;
                }

                if (ball.getX() == x && ball.getY() == y)
                    std::cout << '*';
                else if (isPin)
                    std::cout << 'o';
                else
                    std::cout << ' ';
            }
            std::cout << '\n';
        }
    }

private:
    int width, height;
    Ball ball;
    std::vector<std::vector<int>> pinRows;
};

// ================= Main =================
int main() {
    PachinkoMachine machine(20, 12);

    while (true) {
        machine.step();
        machine.render();
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}
