#ifndef MAINVIEW_H_
#define MAINVIEW_H_

#include "View.h"

#include "Entity.h"
#include "Map.h"
#include "ObjectManager.h"
#include "Player.h"

class MainView : public View {
public:
  MainView(sf::RenderWindow &window, ObjectManager &objectManager, Map &map);
  ~MainView();

  void render(float delta);

  void set(std::string name);

private:
  ObjectManager &objectManager_;

  Map &map_;

  void renderPlayer(float delta);
  void renderMap(float delta);
};

#endif