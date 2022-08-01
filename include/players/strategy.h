#pragma once
#ifndef FINAL_PROJECT_GHOEY2_PLAYER_H
#define FINAL_PROJECT_GHOEY2_PLAYER_H
#include <core/card.h>
#include <cstdlib>
#include <vector>
#include <core/round.h>

namespace euchre {
class Strategy {
public:

    /**
     * return what suit you want to call, kNoSuit if you dont want to call
     */
    virtual Suit
    CallTrump(std::vector<Card> hand, size_t dealer_position, size_t your_position, Suit turned_down_suit) = 0;

    /**
     * return the size_t corresponding to the index of the card you want to play
     */
    virtual size_t
    PlayCard(std::vector<CardPlayAction> played_cards, std::vector<Card> hand, Suit lead_suit, Suit trump) = 0;

    /**
     * return true if you want dealer to pick it up
     */

    virtual bool OrderDealerUp(Card top_card, std::vector<Card> your_hand, size_t dealer_position, size_t your_position) = 0;

    /**
     * return size_t corresponding to which cad you want to get rid of
     *
     */
    virtual size_t PickUpCard(Card card, std::vector<Card> hand, size_t who_called_it) = 0;

    virtual bool IsReady() = 0;

    virtual void SetIsReady(bool is_ready) = 0;

    virtual void SetCardIndex(size_t card) = 0;

    virtual void SetTrumpCall(Suit trump_call) = 0;

    virtual void SetIsCallingPickItUp(bool is_calling) = 0;



  };
}

#endif //FINAL_PROJECT_GHOEY2_PLAYER_H
