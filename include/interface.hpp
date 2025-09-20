#pragma once
#include <iostream>
#include "nova_filesystem.hpp"

using INPUT = std::string;
using HOSTNAME = std::string;

struct game_config{
  HOSTNAME hostname;
  n_folder* root;
};

struct game_interface {
  INPUT input;
  HOSTNAME hostname;
  n_folder* root;
  n_folder* current;
  bool running;

  inline game_interface(game_config& game_cfg): hostname(game_cfg.hostname), root(game_cfg.root) {}
  inline ~game_interface()= default;

  void init(char* argv[]);
  void start(char* argv[]);
  
  void primary_prompt();
  inline void clear_screen() { system("clear"); }
};