#include <utility>
#include <thread>

#include "../../config.h"

namespace audio::beep {
    // essential beep function in beep_engine which allows you to play single beep on windows and linux
    void playBeep(const double frequency, int duration) {
        const double period = (1.0 / frequency * 1000000); // T = 1 / f

        #ifdef _WIN32
        Beep(static_cast<int>(frequency), duration);
        #else
        const double period = (1.0 / frequency * 1000000);

        for (int i = 0; i < duration * 1000; i += period) {
            std::cout << "\a"; // play sound
            std::this_thread::sleep_for(std::chrono::microseconds(static_cast<int>(period)));
        }
        #endif
    }

#pragma region BEEP_SOUND
    // The single beep that can be played or use in more advanced beep lists/vectors
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

        void play() const;

    private:
        double frequency;
        int duration;
    };

    void BeepSound::play() const {
        playBeep(frequency, duration);
    }
#pragma endregion

    [[maybe_unused]] void playBeepMap(const std::map<int, BeepSound>& SOUNDS, const int base_sleep_time) {
        for (const auto& sound : SOUNDS) {
            playBeep(sound.second.getFrequency(), sound.second.getDuration());
            std::cout << std::flush;

            Sleep(base_sleep_time);
        }
    }

#pragma region BEEP_MUSIC
    // BeepMusic is complex assemblage of BeepSounds
    class BeepMusic {
    public:
        std::vector<BeepSound> beeps;
        bool played{ false };
        bool loop{ false };

        explicit BeepMusic(std::vector<BeepSound> beeps_in);

        void play();
    };

    BeepMusic::BeepMusic(std::vector<BeepSound> beeps_in) {
        beeps = std::move(beeps_in);
    }

    void BeepMusic::play() {
        if (!played || loop) {
            for (BeepSound beep : beeps) {
                std::thread playThread(audio::beep::playBeep, beep.getFrequency(), beep.getDuration());
                playThread.detach();

                std::this_thread::sleep_for(std::chrono::seconds(beep.getDuration() / 1000));
            }
            played = true;
        }
    }
#pragma endregion
}