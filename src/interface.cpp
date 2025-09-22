#include <interface.hpp>
#include <sstream>
#include <util.hpp>
#include <algorithm>

Command to_Command(std::string &str)
{
  std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
                 { return static_cast<char>(std::tolower(c)); });

  auto it = cmd_map.find(str);
  return it != cmd_map.end() ? it->second : Command::Unknown;
}
void game_interface::__Help__Message__()
{
  std::cout << "Help: " << endline << endline
            << "  -exit    ==>  Exists the program" << endline
            << "  -hello   ==>  przints hello to console"
            << "  -restart ==>  restarts the program" << endline
            << "  -clear   ==>  clears screen" << endline
            << endline
            << endline
            << "  -mkdir   ==>  mkdir <folder_name>" << endline
            << "  -touch   ==>  touch <file_name>"
            << endline
            << endline
            << "  -cd      ==>  cd <folder_name>" << endline
            << "  -ls      ==>  displays all folders and files" << endline
            << "  -remove  ==>  removes an entry" << endline
            << "  -rename  ==>  rename an entry"
            << "  -path    ==>  path <entry_name>" << endline
            << endline
            << endline
            << "  -host    ==>  returns hostname" << endline
            << "  -tree    ==>  represents entries as a tree"
            << endline
            << endline;
}

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
    case Command::Enter:
      reset_arguments();
      break;
    case Command::Help:
      __Help__Message__();
      break;

    case Command::Mkdir:
      iss >> argument_0;
      if (!argument_0.empty())
        make_folder(current, argument_0);
      else
        std::cerr << "mkdir: missing operand" << endline;

      reset_arguments();
      break;
    case Command::Touch:
      iss >> argument_0;
      if (!argument_0.empty())
        make_file(current, argument_0);
      else
        std::cerr << "mkdir: missing operand" << endline;

      reset_arguments();
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
      reset_arguments();
      break;

    case Command::Remove:
      iss >> argument_0;
      if (!argument_0.empty())
        remove_entry(current, argument_0);
      else
        std::cerr << "folder doesnt exist: " << argument_0 << endline;

      reset_arguments();
      break;
    case Command::Rename:
      iss >> argument_0;
      iss >> argument_1;

      if (!argument_0.empty())
      {
        if (!argument_1.empty())
        {
          rename_entry_name(current, argument_0, argument_1);
        }
        else
        {
          std::cerr << "Missing operand" << endline;
        }
      }
      else
      {
        if (argument_0 == "")
          argument_0 = "null";
        std::cerr << "folder doesnt exist: " << argument_0 << endline;
      }

      reset_arguments();

      break;
    case Command::Ls:
      display_folders_contents(current);
      break;

    case Command::Path:
      iss >> argument_0;
      if (argument_0.empty())
      {
        std::cerr << "path: missing operand" << endline;
        break;
      }
      display_path(current, argument_0);
      reset_arguments();
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
      display_tree(current, 0); // depth 0
      break;
    case Command::Unknown:
    default:
      std::cout << "Unknown command: " << input_token << endline;
      break;
    }
  }
}
