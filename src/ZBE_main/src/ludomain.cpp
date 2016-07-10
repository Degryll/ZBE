
#include "ludomain.h"
#include "ZBE/core/events/Event.h"
#include "ZBE/core/events/EventStore.h"
#include "ZBE/core/events/InputEvent.h"
#include "ZBE/core/events/InputEventGenerator.h"
#include "ZBE/core/io/InputReader.h"
#include "ZBE/core/io/SDL/SDLInputReader.h"

int ludomain(int argc, char* argv[]) {
  printf("--- Ludo main ---\n\n");

  getchar();

  /*zbe::EventStore& store = zbe::EventStore::getInstance();
  zbe::InputReader& ir = new zbe::SDLInputReader::getInstance();
  zbe::InputEventGenerator* ieg = new zbe::InputEventGenerator(ir,1);*/

  bool keep = true;
  while(keep){

  }

  return 0;
}
