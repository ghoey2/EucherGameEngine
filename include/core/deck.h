//
// Created by ghoey on 4/19/2021.
//

#ifndef FINAL_PROJECT_GHOEY2_DECK_H
#define FINAL_PROJECT_GHOEY2_DECK_H


#include <vector>
#include "card.h"
namespace euchre {

class Deck {
  public :
    Deck();
    Card TakeTopCard();
    size_t GetSeed() const;
    const size_t kNumberOfSuits = 4;
    const size_t kNumberOfValues = 6;
    std::vector<euchre::Card> GetCards() const;

  private:
      std::vector<euchre::Card> cards_;

};

}


#endif //FINAL_PROJECT_GHOEY2_DECK_H
