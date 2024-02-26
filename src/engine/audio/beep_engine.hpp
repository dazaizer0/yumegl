#include "../../config.h"

void print(const std::string& message) {
    std::cout << message;
}

void playBeep(const double frequency, int duration) {
    const double period = 1.0 / frequency * 1000000; // T = 1 / f

#ifdef _WIN32
    Beep(static_cast<int>(frequency), duration);
#else
    for (int i = 0; i < duration * 1000; i += period)
    {
        std::cout << "\a"; // play sound
        std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(period)));
    }
#endif
}

class BeepSound {
public:
    BeepSound() : frequency(0.0), duration(0) {} // default sound constructor
    BeepSound(const double f, const int d) : frequency(f), duration(d) {}

    [[nodiscard]] double getFrequency() const {
        return frequency;
    }
    [[nodiscard]] int getDuration() const {
        return duration;
    }

private:
    double frequency;
    int duration;
};

void playBeepMap(const std::map<int, BeepSound>& SOUNDS, const int base_sleep_time) {
    for (const auto& sound : SOUNDS) {
        playBeep(sound.second.getFrequency(), sound.second.getDuration());
        std::cout << std::flush;

        Sleep(base_sleep_time);
    }
}

void clearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}