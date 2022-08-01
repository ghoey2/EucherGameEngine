#include <players/human_player.h>


size_t euchre::HumanStrategy::PickUpCard(euchre::Card card, std::vector<Card> hand, size_t who_called_it) {
    is_ready_ = false;
    return card_index_;
}

bool euchre::HumanStrategy::OrderDealerUp(euchre::Card top_card, std::vector<Card> your_hand, size_t dealer_position,
                                          size_t your_position) {
    is_ready_ = false;
    return is_calling_pick_it_up_;
}

size_t
euchre::HumanStrategy::PlayCard(std::vector<CardPlayAction> played_cards, std::vector<Card> hand, euchre::Suit lead_suit,
                                euchre::Suit trump) {
    is_ready_ = false;
    return card_index_;
}

euchre::Suit euchre::HumanStrategy::CallTrump(std::vector<Card> hand, size_t dealer_position, size_t your_position,
                                              euchre::Suit turned_down_suit) {
    is_ready_ = false;
    return trump_call_;
}

void euchre::HumanStrategy::SetIsReady(bool is_ready) {
    is_ready_ = is_ready;
}

bool euchre::HumanStrategy::IsReady() {
    return is_ready_;
}

void euchre::HumanStrategy::SetCardIndex(size_t card) {
    card_index_ = card;
    is_ready_ = true;

}

void euchre::HumanStrategy::SetIsCallingPickItUp(bool is_calling) {
    is_calling_pick_it_up_ = is_calling;
    is_ready_ = true;

}

void euchre::HumanStrategy::SetTrumpCall(Suit trump_call) {
    trump_call_ = trump_call;
    is_ready_ = true;


}

