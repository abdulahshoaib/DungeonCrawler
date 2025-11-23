#include "UIEngine.h"
#include "Loader.h"
#include "MenuHUD.h"
#include "MenuInventory.h"
#include "MenuMain.h"
#include "MenuPause.h"

UIEngine::UIEngine()
{
  menus[PAUSE_MENU] = new MenuPause();
  menus[INVENTORY] = new MenuInventory();
  menus[MAIN_MENU] = new MenuMain();
  menus[HUD] = new MenuHUD();
}