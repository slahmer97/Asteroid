
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

    static inline void update_score(const std::string &tireX, const std::string &tireV, const std::string &scoreEquipe,
                                    const std::string &viesEquipe) {
        score.changeTexte(tireX, tireV, scoreEquipe, viesEquipe);
    }

    static inline void on_game_end(std::string& mode, std::string& won, std::string& score1, std::string& score2){
        score.texteDeFin(mode,won,score1,score2);
    }
private:
    static std::vector<std::shared_ptr<polyClient>> shapes;
    static alphaNumClient score;
};

#endif //ASTEROID_GAME_SHAPES_H
std::vector<std::shared_ptr<polyClient>> game_shapes::shapes{};
alphaNumClient game_shapes::score{};
