
#ifndef ASTEROID_GAME_SHAPES_H
#define ASTEROID_GAME_SHAPES_H

#include <memory>
#include <vector>
#include "affichable.h"
#include "alphaNumClient.h"

class game_shapes {
public:
    static inline std::vector<std::shared_ptr<polyClient>> *get_shapes() {
        return &game_shapes::shapes;
    }

    static inline alphaNumClient &get_score() {
        return score;
    }

    static inline void emplace(std::vector<std::shared_ptr<polyClient>> &&new_shapes) {

        game_shapes::shapes = new_shapes;
    }

    static inline void update_score(const std::string &tireX, const std::string &tireV, const std::string &scoreE1,
                                    const std::string &scoreE2) {
        score.changeTexte(tireX, tireV, scoreE1, scoreE2);
    }

    static inline void on_game_end(std::string& _mode, std::string& _won, std::string& _scoreE1, std::string& _scoreE2){
        end_game = true;
        won = _mode;
        mode = _won;
        scoreE1 = _scoreE1;
        scoreE2 = _scoreE2;
    }
private:
    static std::vector<std::shared_ptr<polyClient>> shapes;
    static alphaNumClient score;
public:
    static bool end_game;
    static std::string won;
    static std::string mode;
    static std::string scoreE1;
    static std::string scoreE2;
};

#endif //ASTEROID_GAME_SHAPES_H
std::vector<std::shared_ptr<polyClient>> game_shapes::shapes{};
alphaNumClient game_shapes::score{};
bool game_shapes::end_game{false};
std::string game_shapes::won{};
std::string game_shapes::mode{};
std::string game_shapes::scoreE1{};
std::string game_shapes::scoreE2{};
