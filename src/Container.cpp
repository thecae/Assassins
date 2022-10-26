#include "../include/Container.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
#include <stdexcept>

Container::Container() : gSize(0) {
  std::string playerFile = "players-original.txt";

  std::ifstream file(playerFile.c_str());
  if (!file.is_open()) {
    std::cerr << "Unable to open player file [R]: " << playerFile << std::endl;
    exit(1);
  }

  // get the players and put them in a vector
  std::string name;
  std::vector<std::string> players;
  while (file >> name)
    players.push_back(name);
  file.close();

  // assign targets at random
  assignTargets(players);
}

Container::~Container() noexcept {
  while (gSize)
    removePlayer(gFirst.get(), "end game");
}

const Player &Container::getPlayer(const std::string &name) const noexcept {
  for (auto iter = gFirst->pTarget; iter != gFirst.get(); iter = iter->pTarget)
    if (iter->pName == name)
      return *iter;
  std::cerr << "Player " << name << " not found" << std::endl;
  exit(1);
}

Player &Container::getPlayer(const std::string &name) noexcept {
  return const_cast<Player &>(
      const_cast<const Container *>(this)->getPlayer(name));
}

std::string Container::getMap() const noexcept {
  std::stringstream map;
  auto node = gFirst->pTarget;
  while (node != gFirst.get()) {
    map << node->pName << "->";
    node = node->pTarget;
  }
  map << std::endl;

  return map.str();
}

void Container::kill(const std::string &name) {
  // go find the player
  auto currNode = gFirst.get();
  while (currNode->pName != name)
    currNode = currNode->pTarget;

  // add one to kill count for hunter
  ++currNode->pHunter->numKills;

  removePlayer(currNode, "kill");
}

void Container::wither(const std::string &name) {
  // go find the player
  auto currNode = gFirst.get();
  while (currNode->pName != name)
    currNode = currNode->pTarget;

  removePlayer(currNode, "wither");
}

void Container::removePlayer(Player *player, const std::string &type) noexcept {
  // log the kill
  std::string contents = "Player eliminated: " + player->pName;
  gameLog.activityLog(type, contents);

  // log the player
  gameLog.playerLog(player->getInfo());

  delete player;
  --gSize;
}

void Container::assignTargets(std::vector<std::string> &players) {
  std::vector<std::string> targets(players);

  // make sure nobody has themselves
  while (true) {
    std::cout << "Shuffle attempt\n";
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(targets.begin(), targets.end(), g);
    auto pIter = players.begin();
    auto tIter = targets.begin();
    for (; pIter != players.end(); ++pIter, ++tIter)
      if (*pIter == *tIter)
        continue;
    break;
  }

  // make a map with the targets
  std::map<std::string, std::string> map;
  auto pIter = players.begin();
  auto tIter = targets.begin();
  for (; pIter != players.end(); ++pIter, ++tIter)
    map.emplace(*pIter, *tIter);

  // start with the first node for a base point
  auto firstNode = new Player(map.begin()->first);
  auto secondNode = new Player(map.begin()->second);
  Player::link(firstNode, secondNode);

  // now do the rest iteratively
  auto current = secondNode;
  for (; current != firstNode; current = current->pTarget) {
    auto target = new Player(map[current->pName]);
    Player::link(current, target);
    ++gSize;

    // log
    std::string content = "Player added: " + current->pName;
    gameLog.activityLog("addition", content);

    // add the hunter's new target to his vector
    current->pList.push_back(target->pName);

    current = target;
  }

  // that should have worked, run two iters just in case
  auto forward = firstNode->pTarget;
  uint32_t fCount = 0;
  for (; forward != firstNode; forward = forward->pTarget)
    ++fCount;
  auto backward = firstNode->pHunter;
  uint32_t bCount = 0;
  for (; backward != firstNode; backward = backward->pHunter)
    ++bCount;
  if (not(gSize == fCount == bCount)) {
    std::cerr << "Players were not inserted properly" << std::endl;
    exit(1);
  }

  // we did it! just set the variable
  gFirst.reset(firstNode);
}