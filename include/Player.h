#ifndef ASSASSINS_V2_PLAYER_H
#define ASSASSINS_V2_PLAYER_H

#define NUM_HINTS 2

#include <string>
#include <sstream>
#include <vector>

class Game;

/**
 * Represents the players of the game.
 */
class Player {
private:
    friend class Container;

    std::string pName;
    Player* pTarget;
    Player* pHunter;
    std::vector<std::string> pList;

    uint32_t numHints;
    uint32_t numKills;

    static void link(Player* hunter, Player* target);

public:
    /**
     * Default constructor.  Used for empty players.  Sets the target
     * and the hunter to themselves.  Not intended for long-term use.
     *
     * @param name
     */
    explicit Player(const std::string &name);

    /**
     * Destructor.  Used on player death.  Links the surrounding players.
     */
    ~Player();

    /**
     * Alternate constructor.  Takes the hunter and the target for the player
     * and automatically links them to the list.
     *
     * @param name
     * @param hunter
     * @param target
     */
    Player(const std::string &name, Player* hunter, Player *target);

    std::string getInfo() const noexcept;


};


#endif //ASSASSINS_V2_PLAYER_H
