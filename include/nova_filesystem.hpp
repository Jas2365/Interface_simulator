#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <qol.hpp>
#include <memory>
#include <algorithm>

struct n_file
{
  std::string name;
  std::string extension;
  std::string path;
  std::string content;
};

struct n_folder
{
  std::string name;
  n_folder *parent;
  std::vector<std::unique_ptr<n_folder>> sub_n_folders;
  std::vector<std::unique_ptr<n_file>> sub_n_files;
  std::string path;
};

// folders
void make_folder(n_folder *current, std::string folder_name);
void display_folders_contents(const n_folder *current);
n_folder *open_folder(n_folder *current, std::string folder_name);
void remove_folder(n_folder *current, std::string folder_name);
void rename_folder_name(n_folder *current, std::string folder_name, std::string rename_folder_name);
void update_path_recursively(n_folder *current);

bool is_folder_exists(n_folder *current, std::string &name);
bool is_file_exists(n_folder *current, std::string &name);

// files
/**
 * to dos
 * rename file
 * update path of files ??
 * open file ??
 * extension enums ??
 */
void make_file(n_folder *current, std::string file_name);

// display utils

const std::string trunk = "|  ";
const std::string branch = "|__";
void display_tree(n_folder *root, int depth);
