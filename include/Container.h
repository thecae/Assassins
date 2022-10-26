#ifndef ASSASSINS_V2_CONTAINER_H
#define ASSASSINS_V2_CONTAINER_H

#include "Log.h"
#include "Player.h"
#include <fstream>
#include <vector>

/**
 * Represents the game.
 */
class Container {
private:
  void removePlayer(Player *player, const std::string &type) noexcept;

  void assignTargets(std::vector<std::string> &players);

  uint32_t gSize;
  /** The list that holds the game **/
  std::unique_ptr<Player> gFirst;
  /** The log **/
  Log gameLog;

public:
  /**
   * Should only need to make the game once.  Takes filename input and will
   * read the data from that file.
   */
  explicit Container();

  ~Container() noexcept;

  const Player &getPlayer(const std::string &name) const noexcept;
  Player &getPlayer(const std::string &name) noexcept;

  void kill(const std::string &name);
  void wither(const std::string &name);

  std::string getMap() const noexcept;
};

#endif // ASSASSINS_V2_CONTAINER_H
