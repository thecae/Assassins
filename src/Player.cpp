#include "../include/Player.h"

Player::Player(const std::string &name) : pName(name), numHints(NUM_HINTS), numKills(0)
{
}

Player::~Player()
{
    // add the hunter's new target to his vector
    pHunter->pList.push_back(pTarget->pName);

    link(pHunter, pTarget);
}

Player::Player(const std::string &name, Player *hunter, Player *target) : pName(name)
{
    link(hunter, this);
    link(this, target);
}

void Player::link(Player *hunter, Player *target)
{
    hunter->pTarget = target;
    target->pHunter = hunter;
}

std::string Player::getInfo() const noexcept
{
    std::stringstream printer;

    printer << "Name: " << pName << std::endl;
    printer << "Kills: " << numKills << std::endl;
    printer << "Hints Used: " << (NUM_HINTS - numHints) << std::endl;
    printer << "Target(s): ";
    for (auto &i : pList) {
        if (i != *pList.end())
            printer << i << "->";
        else
            printer << i;
    }
    printer << std::endl;

    return printer.str();
}