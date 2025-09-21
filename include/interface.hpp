#pragma once
#include <iostream>
#include "nova_filesystem.hpp"
#include <unordered_map>

using INPUT = std::string;
using HOSTNAME = std::string;

struct game_config
{
  HOSTNAME hostname;
  n_folder *root;
};

struct game_interface
{
  INPUT input;
  HOSTNAME hostname;
  n_folder *root;
  n_folder *current;
  bool running;

  std::string argument_0;
  std::string argument_1;

  inline game_interface(game_config &game_cfg) : hostname(game_cfg.hostname), root(game_cfg.root) {}
  inline ~game_interface() = default;

  void init(char *argv[]);
  void start(char *argv[]);

  void primary_prompt();
  inline void clear_screen() { system("clear"); }
};

enum class Command
{
  Unknown,
  Exit,
  Mkdir,
  Cd,
  Ls,
  Restart,
  Hello,
  Host,
  Clear,
  Tree,
  Remove,
  Update,
};

static const std::unordered_map<std::string, Command> cmd_map{
    {"unknown", Command::Unknown},
    {"exit", Command::Exit},
    {"mkdir", Command::Mkdir},
    {"cd", Command::Cd},
    {"ls", Command::Ls},
    {"restart", Command::Restart},
    {"hello", Command::Hello},
    {"host", Command::Host},
    {"clear", Command::Clear},
    {"tree", Command::Tree},
    {"remove", Command::Remove},
    {"update", Command::Update},
};

Command to_Command(std::string &str);