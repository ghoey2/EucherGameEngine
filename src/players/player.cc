//
// Created by ghoey on 4/19/2021.
//

#include <players/strategy.h>
#include <players/player.h>

namespace euchre {

    Player::Player(Strategy* strategy, bool is_team_one, size_t id) {
        this->strategy_ = strategy;
        this->is_team_one_ = is_team_one;
        this->id_ = id;
    }

    void Player::AddCard(euchre::Card card) {
        hand_.push_back(card);
    }

    void Player::ClearHand() {
        hand_.clear();
    }

    std::vector<Card> Player::GetHand() {
        return hand_;
    }

    bool Player::GetIsTeamOne() {
        return is_team_one_;
    }

    void Player::PickItUp(Card top_card, size_t who_called_it) {
        Card to_remove = hand_.at(strategy_->PickUpCard(top_card, hand_, who_called_it));
        RemoveCard(to_remove);
        hand_.push_back(top_card);
    }

    void Player::RemoveCard(euchre::Card card) {
        for (size_t i = 0; i < hand_.size(); ++i) {
            if (card == hand_.at(i)) {
               hand_.erase(hand_.cbegin() + i);
               break;
            }

        }

    }

    Suit Player::CallTrump(size_t dealer_position, Suit turned_down_suit) {
        return strategy_->CallTrump(hand_, dealer_position, id_, turned_down_suit);
    }

    Card Player::PlayCard(std::vector<CardPlayAction> played_cards, Suit lead_suit, Suit trump) {
        Card card = hand_.at(strategy_->PlayCard(played_cards, hand_, lead_suit, trump));
        RemoveCard(card);
        return card;
    }

    bool Player::OrderDealerUp(Card top_card, size_t dealer_position) {
        return strategy_->OrderDealerUp(top_card, hand_, dealer_position, id_);
    }

}
