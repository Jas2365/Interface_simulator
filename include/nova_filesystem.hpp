#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <qol.hpp>

//
// todo: making a new file struct
//
// template <typename T>
// struct n_file {
//   std::string name;
//   std::vector<T> content;
//   bool readonly;
// };


struct n_folder {
  std::string name;
  n_folder* parent;
  std::vector<n_folder*> sub_n_folders;
  // contain files here
  std::string path;
};

inline void make_folder(n_folder* root, std::string folder_name){
  for(auto& folder : root->sub_n_folders){
    if(folder->name == folder_name)
    std::cerr << "mkdir: cannot create directory \'"<< folder_name 
              << "\': Folder exists" 
              << endline;
    return;
  }
  
  std::cout << "made folder: "<<folder_name<<endline;
  n_folder n_temp;
  n_temp.name = folder_name;
  n_temp.sub_n_folders = {};
  n_temp.parent = root;
  n_temp.path = root->path + "/" + folder_name;
  // problem fix the double n_temp issue
  // n_temp can only make one folder in each folder
  // root->sub_n_folders.push_back();

}

inline void display_folders_contents(const n_folder* root){
  if(!root->sub_n_folders.size())  return;
  int i = 1;
  for(const auto& folder: root->sub_n_folders){
    std::cout<< folder->name << space << i++<<space;
  }
  std::cout << endline;
}
inline n_folder* open_folder(n_folder* current, std::string folder_name) {
  if(folder_name == ".."){
    if(current->parent){
      return current->parent;
    }
    return current;
  }

  for(auto& folder : current->sub_n_folders){
    if(folder->name == folder_name){
      return folder;
    }
  }

  std::cout<<"No such directory: "<< folder_name << endline;
  return current;
}