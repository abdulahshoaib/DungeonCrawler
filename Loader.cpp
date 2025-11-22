
#include "Loader.h"

Loader::Loader(Font f) : font(f) {}
Loader::Loader() {}

Font *Loader::getFont() { return &font; } // just return a ref to the font

