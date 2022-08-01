//
// Created by ghoey on 4/17/2021.
//
#include <catch2/catch.hpp>
#include <core/card.h>

TEST_CASE("test == ") {
    SECTION("test equal cards") {
        euchre::Card card_1 = euchre::Card(euchre::Suit::kSpade, euchre::Value::k9);
        euchre::Card card_2 = euchre::Card(euchre::Suit::kSpade, euchre::Value::k9);
        REQUIRE(card_1 == card_2);
    }
    SECTION("test different suit same value") {
        euchre::Card card_1 = euchre::Card(euchre::Suit::kSpade, euchre::Value::k9);
        euchre::Card card_2 = euchre::Card(euchre::Suit::kHeart, euchre::Value::k9);
        REQUIRE(!(card_1 == card_2));
    }
    SECTION("test different value same suit") {
        euchre::Card card_1 = euchre::Card(euchre::Suit::kSpade, euchre::Value::k9);
        euchre::Card card_2 = euchre::Card(euchre::Suit::kSpade, euchre::Value::kA);
        REQUIRE(!(card_1 == card_2));
    }
    SECTION("test different value different suit") {
        euchre::Card card_1 = euchre::Card(euchre::Suit::kSpade, euchre::Value::k9);
        euchre::Card card_2 = euchre::Card(euchre::Suit::kHeart, euchre::Value::kA);
        REQUIRE(!(card_1 == card_2));
    }



}