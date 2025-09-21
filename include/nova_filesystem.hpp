#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <qol.hpp>
#include <memory>
#include <algorithm>

//
// todo: making a new file struct
//
// template <typename T>
// struct n_file {
//   std::string name;
//   std::vector<T> content;
//   bool readonly;
// };

struct n_folder
{
  std::string name;
  n_folder *parent;
  std::vector<std::unique_ptr<n_folder>> sub_n_folders;
  // contain files here
  std::string path;
};

void make_folder(n_folder *root, std::string folder_name);
void display_folders_contents(const n_folder *root);
n_folder *open_folder(n_folder *current, std::string folder_name);
void remove_folder(n_folder *current, std::string folder_name);
void update_folder_name(n_folder *current, std::string folder_name, std::string update_folder_name);

const std::string trunk = "|  ";
const std::string branch = "|__";
void display_tree(n_folder *root, int depth);
