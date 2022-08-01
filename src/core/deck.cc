//
// Created by ghoey on 4/19/2021.
//

#include "core/deck.h"
#include <algorithm>
#include <random>
#include <ctime>
#include <iostream>

namespace euchre {
    euchre::Deck::Deck() {
        for (size_t i = 0; i < kNumberOfSuits; ++i) {
            for (size_t j = 0; j < kNumberOfValues; ++j) {
                cards_.push_back(Card(static_cast<Suit>(i), static_cast<Value>(j)));
            }
        }

       std::shuffle(std::begin(cards_), std::end(cards_), std::default_random_engine(GetSeed()));
    }
// this function returns the seconds since 1970 and seeds the shuffling randomization from https://stackoverflow.com/questions/9483974/converting-time-t-to-int
    size_t Deck::GetSeed() const {
        std::tm epoch_strt;
        epoch_strt.tm_sec = 0;
        epoch_strt.tm_min = 0;
        epoch_strt.tm_hour = 0;
        epoch_strt.tm_mday = 1;
        epoch_strt.tm_mon = 0;
        epoch_strt.tm_year = 70;
        epoch_strt.tm_isdst = -1;

        std::time_t base_time = std::mktime(&epoch_strt);

        std::time_t current_time = std::time(0);

        return static_cast<size_t>(std::difftime(current_time, base_time));

    }

    std::vector<euchre::Card> Deck::GetCards() const {
        return cards_;
    }

    Card Deck::TakeTopCard() {
        Card top_card = cards_.at(cards_.size() - 1);
        cards_.pop_back();
        return top_card;
    }
}