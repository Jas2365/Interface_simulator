#include <interface.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{

  n_folder *root = new n_folder;
  root->name = "nova";
  root->parent = nullptr;
  root->path = root->name;

  game_config game_cfg = {"Nova", root};

  game_interface game(game_cfg);
  game.init(argv);

  return 0;
}

