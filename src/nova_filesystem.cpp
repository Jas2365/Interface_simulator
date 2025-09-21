#include <nova_filesystem.hpp>

void make_folder(n_folder *current, std::string folder_name)
{
  if (is_folder_exists(current, folder_name))
  {
    std::cerr << "mkdir: cannot create directory \'" << folder_name
              << "\': Folder exists"
              << endline;
    return;
  }

  std::unique_ptr<n_folder> n_temp(new n_folder);
  n_temp->name = folder_name;
  n_temp->parent = current;
  n_temp->path = current->path + "/" + folder_name;

  current->sub_n_folders.push_back(std::move(n_temp));
}

void display_folders_contents(const n_folder *current)
{
  if (current->sub_n_folders.size() != 0)
  {

    std::cout << "Folders: " << endline;
    for (const auto &folder : current->sub_n_folders)
    {
      std::cout << folder->name << space;
    }
    std::cout << endline;
  }
  if (current->sub_n_files.size() != 0)
  {
    std::cout << "Files: " << endline;
    for (const auto &file : current->sub_n_files)
    {
      std::cout << file->name << "." << file->extension << space;
    }
    std::cout << endline;
  }
}

n_folder *open_folder(n_folder *current, std::string folder_name)
{

  if (folder_name == "..")
  {
    if (current->parent)
    {
      return current->parent;
    }
    return current;
  }

  for (auto &folder : current->sub_n_folders)
  {
    if (folder->name == folder_name)
    {
      return folder.get();
    }
  }

  std::cout << "No such directory: " << folder_name << endline;
  return current;
}

void display_tree(n_folder *root, int depth)
{
  for (auto &folder : root->sub_n_folders)
  {

    for (int i = 0; i < depth; i++)
      std::cout << trunk;

    std::cout << branch << folder.get()->name << endline;
    display_tree(folder.get(), depth + 1);
  }
}

void remove_folder(n_folder *current, std::string folder_name)
{
  current->sub_n_folders.erase(
      std::remove_if(current->sub_n_folders.begin(), current->sub_n_folders.end(), [folder_name](auto &f)
                     { return f && f->name == folder_name; }),
      current->sub_n_folders.end());
}

void rename_folder_name(n_folder *current, std::string folder_name, std::string rename_folder_name)
{
  auto it = std::find_if(current->sub_n_folders.begin(), current->sub_n_folders.end(), [folder_name](std::unique_ptr<n_folder> &f)
                         { return f && f->name == folder_name; });
  if (it == current->sub_n_folders.end())
    std::cout << "Folder Not found: " << folder_name << endline;

  for (const auto &folder : current->sub_n_folders)
  {
    if (folder->name == rename_folder_name)
    {
      std::cerr << "rename: name alredy exist" << endline;
      return;
    }
  }

  (*it)->name = rename_folder_name;
  update_path_recursively((*it).get());
  std::cout << "Renamed to: " << (*it)->name << endline;
}

void update_path_recursively(n_folder *current)
{
  if (current->parent)
  {
    current->path = current->parent->path + "/" + current->name;
  }
  else
  {
    current->path = current->name; // root;
  }

  for (auto &sub : current->sub_n_folders)
  {
    update_path_recursively(sub.get());
  }
}
// true => exists
bool is_folder_exists(n_folder *current, std::string &name)
{
  if (!current)
  {
    std::cerr << "Error: current folder doesnt exist" << endline;
  }
  for (auto &folder : current->sub_n_folders)
  {
    if (folder->name == name)
      return true;
  }
  return false;
}
// true => exists
bool is_file_exists(n_folder *current, std::string &name)
{
  if (!current)
  {
    std::cerr << "Error: current folder doesnt exist" << endline;
  }

  for (auto &file : current->sub_n_files)
  {
    if (file->name == name)
      return true;
  }
  return false;
}

void make_file(n_folder *current, std::string file_name)
{
  if (is_file_exists(current, file_name))
  {
    std::cerr << "File: alredy exist with name \'" << file_name << "\'" << endline;
    return;
  }

  std::unique_ptr<n_file> n_temp(new n_file);
  auto pos = file_name.find('.');
  if (pos != std::string::npos)
  {
    n_temp->name = file_name.substr(0, pos);
    n_temp->extension = file_name.substr(pos + 1);
    n_temp->path = current->path + "/" + file_name;

    current->sub_n_files.push_back(std::move(n_temp));
  }
  else
  {
    std::cerr << "file Extension is not given: " << file_name << endline;
  }
}
