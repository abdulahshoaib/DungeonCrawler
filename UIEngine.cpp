
#include "UIEngine.h"
#include "Loader.h"
#include "MenuHUD.h"
#include "MenuInventory.h"
#include "MenuMain.h"
#include "MenuPause.h"
UIEngine::UIEngine(Loader *l) {
  Font *font = l->getFont();
  menus[PAUSE_MENU] = new MenuPause(font);
  menus[INVENTORY] = new MenuInventory(font);
  menus[MAIN_MENU] = new MenuMain(font);
  menus[HUD] = new MenuHUD(font);
}

UIEngine::UIEngine() {
  // avoid indeterminate pointers
  for (int i = 0; i < 4; ++i) menus[i] = nullptr;
}