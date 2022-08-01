//
// Created by ghoey on 5/3/2021.
//

#ifndef FINAL_PROJECT_GHOEY2_EUCHRE_EXCEPTION_H
#define FINAL_PROJECT_GHOEY2_EUCHRE_EXCEPTION_H
#include <exception>
#include <string>

namespace euchre {
class EuchreException : public std::exception {
public :
    explicit EuchreException(std::string& msg);
    std::string GetMessage();

private:
      std::string msg_;
};
}

#endif //FINAL_PROJECT_GHOEY2_EUCHRE_EXCEPTION_H
