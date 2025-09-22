#include <interface.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{

  n_folder *root = new n_folder;
  root->name = "nova";
  root->parent = nullptr;
  root->path = root->name;

  std::vector<std::string> nova = {
      "bin",
      "boot",
      "dev",
      "etc",
      "home",
      "media",
      "mnt",
      "opt",
      "proc",
      "root",
      "run",
      "srv",
      "sys",
      "usr",
      "var",
  };

  for (auto &folder_name : nova)
  {
    make_folder(root, folder_name);
  }

  game_config game_cfg = {"Nova", root};

  game_interface game(game_cfg);
  game.init(argv);

  return 0;
}
