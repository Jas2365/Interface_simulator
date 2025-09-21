#include <nova_filesystem.hpp>

void make_folder(n_folder *root, std::string folder_name)
{
  if (folder_name.empty())
    std::cerr << "spaces" << endline;

  for (auto &folder : root->sub_n_folders)
  {
    if (folder->name == folder_name)
    {
      std::cerr << "mkdir: cannot create directory \'" << folder_name
                << "\': Folder exists"
                << endline;
      return;
    }
  }

  std::unique_ptr<n_folder> n_temp(new n_folder);
  n_temp->name = folder_name;
  n_temp->parent = root;
  n_temp->path = root->path + "/" + folder_name;

  root->sub_n_folders.push_back(std::move(n_temp));
}

void display_folders_contents(const n_folder *root)
{
  if (root->sub_n_folders.size() == 0)
    return;

  for (const auto &folder : root->sub_n_folders)
  {
    std::cout << folder->name << space;
  }
  std::cout << endline;
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

void update_folder_name(n_folder *current, std::string folder_name, std::string update_folder_name)
{
  auto it = std::find_if(current->sub_n_folders.begin(), current->sub_n_folders.end(), [folder_name](std::unique_ptr<n_folder> &f)
                         { return f && f->name == folder_name; });
  if (it == current->sub_n_folders.end())
    std::cout << "Folder Not found: " << folder_name << endline;

  for (const auto &folder : current->sub_n_folders)
  {
    if (folder->name == update_folder_name)
    {
      std::cerr << "update: name alredy exist" << endline;
      return;
    }
  }

  (*it)->name = update_folder_name;
  // todo
  // update path
  // update sub dirs path
  std::cout << "Updated to: " << (*it)->name << endline;
}
