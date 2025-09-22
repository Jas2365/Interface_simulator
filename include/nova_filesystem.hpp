#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <qol.hpp>
#include <memory>
#include <algorithm>

using Name = std::string;
using Path = std::string;
using Content = std::string;

struct n_entry
{

  Name name;
  n_entry *parent;
  Path path;

  virtual bool is_folder() const = 0;
};

struct n_file : n_entry
{
  Content content;

  bool is_folder() const { return false; }
};

struct n_folder : n_entry
{
  std::vector<std::unique_ptr<n_entry>> sub_n_entries;
  bool is_folder() const { return true; }
};

// folders
void make_folder(n_folder *current, Name &folder_name);
void display_folders_contents(const n_folder *current);
n_folder *open_folder(n_folder *current, Name &folder_name);
void remove_entry(n_folder *current, Name &folder_name);
void rename_entry_name(n_folder *current, Name &folder_name, Name &rename_folder_name);
void update_path_recursively(n_folder *current);

bool is_entry_exists(n_folder *current, Name &name);
n_entry *get_entry(n_folder *current, Name &name);

// files
/**
 * to dos
 * rename file
 * update path of files ??
 * open file ??
 */
void make_file(n_folder *current, Name &file_name);

// display utils
const std::string trunk = "|  ";
const std::string branch = "|__";
void display_tree(n_folder *root, int depth);
