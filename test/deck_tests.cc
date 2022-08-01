//
// Created by ghoey on 4/17/2021.
//
#include <catch2/catch.hpp>
#include <core/deck.h>

TEST_CASE("test deck creation") {
    euchre::Deck deck;
    REQUIRE(deck.GetCards().size() == 24);
    std::vector<euchre::Card> full_deck;
    full_deck.push_back(euchre::Card(euchre::Suit::kHeart, euchre::Value::k9));
    full_deck.push_back(euchre::Card(euchre::Suit::kHeart, euchre::Value::k10));
    full_deck.push_back(euchre::Card(euchre::Suit::kHeart, euchre::Value::kJ));
    full_deck.push_back(euchre::Card(euchre::Suit::kHeart, euchre::Value::kQ));
    full_deck.push_back(euchre::Card(euchre::Suit::kHeart, euchre::Value::kK));
    full_deck.push_back(euchre::Card(euchre::Suit::kHeart, euchre::Value::kA));
    full_deck.push_back(euchre::Card(euchre::Suit::kSpade, euchre::Value::k9));
    full_deck.push_back(euchre::Card(euchre::Suit::kSpade, euchre::Value::k10));
    full_deck.push_back(euchre::Card(euchre::Suit::kSpade, euchre::Value::kJ));
    full_deck.push_back(euchre::Card(euchre::Suit::kSpade, euchre::Value::kQ));
    full_deck.push_back(euchre::Card(euchre::Suit::kSpade, euchre::Value::kK));
    full_deck.push_back(euchre::Card(euchre::Suit::kSpade, euchre::Value::kA));
    full_deck.push_back(euchre::Card(euchre::Suit::kDiamond, euchre::Value::k9));
    full_deck.push_back(euchre::Card(euchre::Suit::kDiamond, euchre::Value::k10));
    full_deck.push_back(euchre::Card(euchre::Suit::kDiamond, euchre::Value::kJ));
    full_deck.push_back(euchre::Card(euchre::Suit::kDiamond, euchre::Value::kQ));
    full_deck.push_back(euchre::Card(euchre::Suit::kDiamond, euchre::Value::kK));
    full_deck.push_back(euchre::Card(euchre::Suit::kDiamond, euchre::Value::kA));
    full_deck.push_back(euchre::Card(euchre::Suit::kClub, euchre::Value::k9));
    full_deck.push_back(euchre::Card(euchre::Suit::kClub, euchre::Value::k10));
    full_deck.push_back(euchre::Card(euchre::Suit::kClub, euchre::Value::kJ));
    full_deck.push_back(euchre::Card(euchre::Suit::kClub, euchre::Value::kQ));
    full_deck.push_back(euchre::Card(euchre::Suit::kClub, euchre::Value::kK));
    full_deck.push_back(euchre::Card(euchre::Suit::kClub, euchre::Value::kA));

    bool is_card_missing = false;

    for(euchre::Card card : full_deck) {
        if (!(std::find(full_deck.begin(), full_deck.end(), card) != full_deck.end())) {
            is_card_missing = true;
        }

    }
    REQUIRE(!is_card_missing);

/* comment out the shuffling part to run this test
    SECTION("test taking top card") {
        euchre::Card top_card = deck.TakeTopCard();
        REQUIRE(deck.GetCards().size() == 23);
        REQUIRE(top_card == euchre::Card(euchre::Suit::kDiamond, euchre::Value::kA));

    }
*/
    SECTION("test bauer suit") {
        euchre::Card spade = euchre::Card(euchre::Suit::kSpade, euchre::Value::k9);
        euchre::Card heart = euchre::Card(euchre::Suit::kHeart, euchre::Value::k9);
        euchre::Card diamond = euchre::Card(euchre::Suit::kDiamond, euchre::Value::k9);
        euchre::Card club = euchre::Card(euchre::Suit::kClub, euchre::Value::k9);
        REQUIRE(club.GetLeftBauerSuit() == euchre::Suit::kSpade);
        REQUIRE(heart.GetLeftBauerSuit() == euchre::Suit::kDiamond);
        REQUIRE(diamond.GetLeftBauerSuit() == euchre::Suit::kHeart);
        REQUIRE(spade.GetLeftBauerSuit() == euchre::Suit::kClub);

    }


}