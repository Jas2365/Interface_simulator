#include <nova_filesystem.hpp>

// true => exists
bool is_entry_exists(n_folder *current, Name &name)
{
  if (!current)
  {
    std::cerr << "Error: current folder doesnt exist" << endline;
  }
  for (auto &entry : current->sub_n_entries)
  {
    if (entry->name == name)
      return true;
  }
  return false;
}
n_entry *get_entry(n_folder *current, Name &entry_name)
{
  /**
   * to do
   * should have an edge case: current == nullptr
   */

  auto it = std::find_if(current->sub_n_entries.begin(), current->sub_n_entries.end(), [entry_name](std::unique_ptr<n_entry> &f)
                         { return f && f->name == entry_name; });

  return it != current->sub_n_entries.end() ? it.base()->get()
                                            : nullptr;
}

void make_folder(n_folder *current, Name &folder_name)
{
  if (is_entry_exists(current, folder_name))
  {
    std::cerr << "mkdir: cannot create directory \'" << folder_name
              << "\': entryalredy exists"
              << endline;
    return;
  }

  std::unique_ptr<n_folder> n_temp(new n_folder);
  n_temp->name = folder_name;
  n_temp->parent = current;
  n_temp->path = current->path + "/" + folder_name;

  current->sub_n_entries.push_back(std::move(n_temp));
}

void display_folders_contents(const n_folder *current)
{

  if (current->sub_n_entries.size() != 0)
  {

    for (const auto &entry : current->sub_n_entries)
    {
      if (entry->is_folder())
        std::cout << entry->name << space;
      else
      {
        std::cout << entry->name << space;
      }
    }
    std::cout << endline;
  }
}

n_folder *open_folder(n_folder *current, Name &entry_name)
{

  if (entry_name == "..")
  {
    if (current->parent)
    {
      return (n_folder *)current->parent;
    }
    return current;
  }

  auto entry = get_entry(current, entry_name);

  if (!entry)
  {
    std::cout << "Entry \'" << entry_name << "\' doesnt exist" << endline;
    return current;
  }

  if (!entry->is_folder())
  {
    std::cout << "Entry \'" << entry_name << "\' isnt a folder" << endline;
    return current;
  }

  return (n_folder *)entry;
}

void display_tree(n_folder *current, int depth)
{
  for (auto &entry : current->sub_n_entries)
  {

    for (int i = 0; i < depth; i++)
      std::cout << trunk;

    if (entry->is_folder())
    {
      std::cout << branch << entry.get()->name << endline;
      display_tree((n_folder *)entry.get(), depth + 1);
    }
    else
    {
      std::cout << branch << entry->name << endline;
    }
  }
}

void remove_entry(n_folder *current, Name &folder_name)
{
  current->sub_n_entries.erase(
      std::remove_if(current->sub_n_entries.begin(), current->sub_n_entries.end(), [folder_name](auto &f)
                     { return f && f->name == folder_name; }),
      current->sub_n_entries.end());
}

void rename_entry_name(n_folder *current, Name &entry_name, Name &rename_entry_name)
{
  if (!is_entry_exists(current, entry_name))
  {
    std::cout << "rename: No Entry with name \'" << entry_name << "\' Found" << endline;
    return;
  }

  if (is_entry_exists(current, rename_entry_name))
  {
    std::cout << "rename: Entry with name \'" << entry_name << "\' alredy exists" << endline;
    return;
  }

  auto it = get_entry(current, entry_name);

  if (it->is_folder())
    update_path_recursively((n_folder *)it);
  else
  {
    n_file *file = (n_file *)it;
    file->name = rename_entry_name;
    file->path = file->parent->path + "/" + file->name;
  }
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

  for (auto &sub : current->sub_n_entries)
  {
    if (sub.get()->is_folder())
      update_path_recursively((n_folder *)sub.get());
    else
    {
      sub->path = sub->parent->path + "/" + sub->name;
    }
  }
}

void make_file(n_folder *current, Name &file_name)
{
  if (is_entry_exists(current, file_name))
  {
    std::cerr << "touch: cannot create file: \'" << file_name << "\' entry alredy exists" << endline;
    return;
  }

  std::unique_ptr<n_file> n_temp(new n_file);

  n_temp->name = file_name;
  n_temp->parent = current;
  n_temp->path = current->path + "/" + file_name;

  current->sub_n_entries.push_back(std::move(n_temp));
}

void display_path(n_folder *current, Name &entry_name)
{

  n_entry *entry = get_entry(current, entry_name);
  if (entry)
  {

    std::cout << "Name: " << entry->name << endline
              << "Path: " << entry->path << endline;
  }
  else
  {
    std::cerr << "Entry \'" << entry_name << "\' doesnt exist" << endline;
  }
}