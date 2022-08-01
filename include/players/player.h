
#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include <core/card.h>
#include <players/strategy.h>

namespace euchre {
    class Player {
    public:
        Strategy* strategy_;
        explicit Player(Strategy* strategy, bool is_team_one, size_t id);
        void AddCard(euchre::Card card);
        void RemoveCard(euchre::Card card);
        void ClearHand();
        std::vector<Card> GetHand();
        bool GetIsTeamOne();
        Suit CallTrump(size_t dealer_position, Suit turned_down_suit);
        Card PlayCard(std::vector<CardPlayAction> played_cards, Suit lead_suit, Suit trump);
        bool OrderDealerUp(Card top_card, size_t dealer_position);
        void PickItUp(Card top_card, size_t who_called_it);
    private:
        size_t id_;
        std::vector<euchre::Card> hand_;
        bool is_team_one_;
    };
}
#endif //PLAYER_H

