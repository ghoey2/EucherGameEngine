//
// Created by ghoey on 4/17/2021.
//
#include <catch2/catch.hpp>
#include <core/game.h>

TEST_CASE("test dealing") {
    euchre::Game game;
    euchre::Deck deck;
    game.Deal(deck);
    for (size_t i = 0; i < 4; ++i) {
        REQUIRE(game.GetPlayer(i).GetHand().size() == 5);
    }

    SECTION("update tests") {
        euchre::Game game_;
        game_.Update();
        REQUIRE(1 == 2);
    }



}