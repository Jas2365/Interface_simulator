#pragma once

#include <iostream>
#include <unistd.h> 
#include <qol.hpp>

inline void hello() { std::cout << "Hello!\n"; }

inline void ask(std::string &question)
{
  std::cout << question;
}
inline void ask(const char *question)
{
  std::cout << question;
}
inline void get_answer(std::string &ans)
{
  std::getline(std::cin, ans);
}

inline void restart(char *argv[])
{
  std::cout << "Restarting..." << endline;
  execvp(argv[0], argv);
  perror("execvp failed");
}