//
// Created by ghoey on 4/20/2021.
//

#include "core/round.h"
namespace euchre {
    Round::Round(Suit trump, bool is_trump_called_by_team_1, size_t dealer_position) {
        this->is_called_by_team_1 = is_trump_called_by_team_1;
        this->trump_ = trump;
        this->starting_player_ = dealer_position + 1;
        this->current_player_ = dealer_position + 1;

    }

    Suit Round::GetTrump() const {
        return trump_;
    }

    Round::Round() {

    }

    void Round::StartTrick() {
        if (!tricks_.empty()) {
            starting_player_ = tricks_.at(0).EvaluateTrick();
            current_player_ = starting_player_;

        }
        tricks_.insert(tricks_.cbegin() , Trick(trump_));

    }

    void Round::AddCard(CardPlayAction play) {
        tricks_.at(0).AddCard(play);
        current_player_++;
    }

    size_t Round::GetStartingPlayer() {
        return starting_player_;
    }

    std::vector<Trick> Round::GetTricks() const{
        return tricks_;
    }

    bool Round::GetIsCalledByTeam1() const {
        return is_called_by_team_1;
    }

    size_t Round::GetCurrentPlayer() {
        return current_player_;
    }

}