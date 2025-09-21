#include <interface.hpp>
#include <sstream>
#include <util.hpp>
#include <algorithm>

void game_interface::init(char *argv[])
{
  running = true;
  start(argv);
}
void game_interface::primary_prompt()
{
  ask(hostname);
  ask("@");
  ask(root->name);
  ask(":~");
  ask(current->path);
  ask(">> ");
}

void game_interface::start(char *argv[])
{
  current = root;
  clear_screen();
  while (running)
  {
    primary_prompt();

    get_answer(input);

    std::istringstream iss(input);

    std::string input_token;
    iss >> input_token;

    switch (to_Command(input_token))
    {
    case Command::Exit:
      running = false;
      clear_screen();
      break;

    case Command::Mkdir:
      iss >> argument_0;
      if (!argument_0.empty())
        make_folder(current, argument_0);
      else
        std::cerr << "mkdir: missing operand" << endline;
        
      argument_0 = "";
      break;

    case Command::Cd:
      iss >> argument_0;

      if (!argument_0.empty())
      {
        if (argument_0 == "/")
          current = root;
        else
          current = open_folder(current, argument_0);
      }
      else
        current = root;
      argument_0 = "";
      break;

    case Command::Ls:
      display_folders_contents(current);
      break;

    case Command::Restart:
      restart(argv);
      break;

    case Command::Hello:
      hello();
      break;
    case Command::Host:
      std::cout << "Hostname: " << hostname << endline;
      break;

    case Command::Clear:
      clear_screen();
      break;

    case Command::Tree:
      std::cout << current->name << endline;
      display_tree(current,0); // depth 0
      break;
    case Command::Unknown:
    default:
      std::cout << "Unknown command: " << input_token << endline;
      break;
    }
  }
}

Command to_Command(std::string &str)
{
  std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
                 { return static_cast<char>(std::tolower(c)); });

  auto it = cmd_map.find(str);
  return it != cmd_map.end() ? it->second : Command::Unknown;
}