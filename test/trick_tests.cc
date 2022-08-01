//
// Created by ghoey on 4/17/2021.
//
#include <catch2/catch.hpp>
#include <core/card.h>
#include <core/card_play_action.h>
#include <core/trick.h>

TEST_CASE("test trick evaluation") {
    euchre::Trick trick = euchre::Trick(euchre::Suit::kSpade);
    euchre::CardPlayAction play1;
    euchre::CardPlayAction play2;
    euchre::CardPlayAction play3;
    euchre::CardPlayAction play4;
    play1.player_id = 0;
    play2.player_id = 1;
    play3.player_id = 2;
    play4.player_id = 3;

    SECTION("no trump") {
        play1.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::kA);
        play2.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::k9);
        play3.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::k10);
        play4.card = euchre::Card(euchre::Suit::kHeart, euchre::Value::kJ);
        trick.AddCard(play1);
        trick.AddCard(play2);
        trick.AddCard(play3);
        trick.AddCard(play4);
        REQUIRE(trick.EvaluateTrick() == 0);

    }

    SECTION("no trump, leading card gets beat by non trump card") {
        play1.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::k9);
        play2.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::kA);
        play3.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::k10);
        play4.card = euchre::Card(euchre::Suit::kHeart, euchre::Value::kJ);
        trick.AddCard(play1);
        trick.AddCard(play2);
        trick.AddCard(play3);
        trick.AddCard(play4);
        REQUIRE(trick.EvaluateTrick() == 1);

    }

    SECTION("trumped lead suit") {
        play1.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::kA);
        play2.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::k9);
        play3.card = euchre::Card(euchre::Suit::kSpade, euchre::Value::k10);
        play4.card = euchre::Card(euchre::Suit::kHeart, euchre::Value::kJ);
        trick.AddCard(play1);
        trick.AddCard(play2);
        trick.AddCard(play3);
        trick.AddCard(play4);
        REQUIRE(trick.EvaluateTrick() == 2);

    }

    SECTION("trumped lead suit with left") {
        play1.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::kA);
        play2.card = euchre::Card(euchre::Suit::kClub, euchre::Value::kJ);
        play3.card = euchre::Card(euchre::Suit::kSpade, euchre::Value::k10);
        play4.card = euchre::Card(euchre::Suit::kHeart, euchre::Value::kJ);
        trick.AddCard(play1);
        trick.AddCard(play2);
        trick.AddCard(play3);
        trick.AddCard(play4);
        REQUIRE(trick.EvaluateTrick() == 1);
    }

    SECTION("trumped lead suit with right") {
        play1.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::kA);
        play2.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::k9);
        play3.card = euchre::Card(euchre::Suit::kSpade, euchre::Value::k10);
        play4.card = euchre::Card(euchre::Suit::kSpade, euchre::Value::kJ);
        trick.AddCard(play1);
        trick.AddCard(play2);
        trick.AddCard(play3);
        trick.AddCard(play4);
        REQUIRE(trick.EvaluateTrick() == 3);

    }

    SECTION("right beats left") {
        play1.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::kA);
        play2.card = euchre::Card(euchre::Suit::kSpade, euchre::Value::kJ);
        play3.card = euchre::Card(euchre::Suit::kClub, euchre::Value::kJ);
        play4.card = euchre::Card(euchre::Suit::kHeart, euchre::Value::kJ);
        trick.AddCard(play1);
        trick.AddCard(play2);
        trick.AddCard(play3);
        trick.AddCard(play4);
        REQUIRE(trick.EvaluateTrick() == 1);

    }
    SECTION("non jack trump over non jack trump") {
        play1.card = euchre::Card(euchre::Suit::kSpade, euchre::Value::k10);
        play2.card = euchre::Card(euchre::Suit::kDiamond, euchre::Value::k9);
        play3.card = euchre::Card(euchre::Suit::kSpade, euchre::Value::kK);
        play4.card = euchre::Card(euchre::Suit::kHeart, euchre::Value::kJ);
        trick.AddCard(play1);
        trick.AddCard(play2);
        trick.AddCard(play3);
        trick.AddCard(play4);
        REQUIRE(trick.EvaluateTrick() == 2);

    }
}