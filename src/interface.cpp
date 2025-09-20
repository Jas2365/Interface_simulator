#include <interface.hpp>
#include <sstream>
#include <util.hpp>
#include <algorithm>

void game_interface::init(char* argv[])
{
  running = true;
  start(argv);
}
void game_interface::primary_prompt(){
    ask(hostname);
    ask("@");
    ask(root->name);
    ask(":");
    ask(current->path);
    ask(">> ");
}


void game_interface::start(char* argv[])
{ 
  current = root;
  clear_screen();
  while(running){
    primary_prompt();

    get_answer(input);

    std::istringstream iss(input);

    std::string input_token;
    iss >> input_token;

    if(input_token == "exit") { clear_screen(); break; }
    if(input_token == "mkdir") {
      std::string folder_name;
      iss >> folder_name;
      if(folder_name.empty()){
        std::cerr << "spaces"<<endline;
      } else if(!folder_name.empty()) {
        make_folder(current,folder_name);
      } else {
        std::cerr <<"error mking folder"<<endline;
      }
      for(auto& folder : current->sub_n_folders)
      std::cout << folder->name << space;
      std::cout << endline;
    }
    if(input_token == "cd") {
      std::string folder_name;
      iss >> folder_name;
      if(!folder_name.empty()){
        current = open_folder(current, folder_name);
      }else {
        current = root;
      }
    } 
    if(input_token == "ls") {
      display_folders_contents(current);
    }
    if(input_token == "restart") {
      restart(argv);
    }
    if(input_token == "hello") std::cout <<"Hello!" <<endline;
    if(input_token == "host") std::cout<< "Hostname: "<< hostname << endline;
    if(input_token == "clear") clear_screen();
  }
}
