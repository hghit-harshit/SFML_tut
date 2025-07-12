#pragma once
//#include "utilities.hpp"
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
template <typename Derived, typename T>
class ResourceManager
{
public:
    ResourceManager(const std::string &l_pathfiles)
    {
        LoadPaths(l_pathfiles);
    }

    virtual ~ResourceManager() { PurgeResources(); }

    T *GetResource(const std::string &l_id);
    std::string GetPath(const std::string &l_id);

    bool RequireResource(const std::string &l_id);
    bool ReleaseResource(const std::string &l_id);
    void PurgeResources();

    T *Load(const std::string &l_path);
    std::pair<T *, unsigned int> *Find(const std::string &);
    bool Unload(const std::string &);
    void LoadPaths(const std::string &l_pathFile);

private:
    /**
     * @brief
     *
     */
    std::unordered_map<std::string, std::pair<T*, unsigned int>> m_resources;
    // we are storting resources as pair of resource name and pair of resource and its number of uses
    std::unordered_map<std::string, std::string> m_paths;
    // storting path as pair of resource name and path
};

//////////////////////////////////////////////////////////////////////////////////////////////////

// this is curiously recurring template pattern
template <typename Derived, typename T>
T* ResourceManager<Derived, T>::Load(const std::string &l_path)
{
    return static_cast<Derived*>(this)->Load(l_path);
}

/**
 * @return std::pair<T *, unsigned int>* - pair of resource and its number of uses of given name
 */
template <typename Derived, typename T>
std::pair<T*, unsigned int>* ResourceManager<Derived, T>::Find(const std::string &l_id)
{
    auto itr = m_resources.find(l_id);
    return (itr != m_resources.end() ? &itr->second : nullptr);
}

/**
 * @brief deletes resource of given name from m_resources
 * @return true resources unloaded
 * @return false unable to unload resource
 */
template <typename Derived, typename T>
bool ResourceManager<Derived, T>::Unload(const std::string &l_id)
{
    auto itr = m_resources.find(l_id);
    if (itr == m_resources.end())
    {
        return false;
    }
    delete itr->second.first;
    m_resources.erase(itr);
    return true;
}

/**
 * @return T* - Pointer to resource of given id
 */
template <typename Derived, typename T>
T *ResourceManager<Derived, T>::GetResource(const std::string &l_id)
{
    auto res = Find(l_id);
    return (res ? res->first : nullptr);
}

/**

 * @return std::string-Path to the resource of given id
 */
template <typename Derived, typename T>
std::string ResourceManager<Derived, T>::GetPath(const std::string &l_id)
{
    auto path = m_paths.find(l_id);
    return (path != m_paths.end() ? path->second : "");
}

/**
 * @brief Increases the count of resource required if it is already begin used
 * otherwise loads resource
 
 * @return true if resource is found
 * @return false if resourece in not found
 */

template <typename Derived, typename T>
bool ResourceManager<Derived, T>::RequireResource(const std::string &l_id)
{
    auto res = Find(l_id);
    if (res)
    {
        ++res->second;
        return true;
    }

    auto path = m_paths.find(l_id);
    if (path == m_paths.end())
    {
        return false;
    }
    auto resource = Load(path->second);
    if (!resource)
    {
        return false;
    }
    m_resources.emplace(l_id, std::make_pair(resource, 1));
    return true;
}

/**
 * @brief Decrease the count if the resource is begin used
 * if the count is zero then unloads the resource
 * @return true if resource is found
 * @return false if recsource is not found
 */
template <typename Derived, typename T>
bool ResourceManager<Derived, T>::ReleaseResource(const std::string &l_id)
{
    auto res = Find(l_id);
    if (!res)
    {
        return false;
    }

    --res->second;
    if (res->second)
    {
        Unload(l_id);
    }
    return true;
}

/**
 * @brief Delete all resources
 */
template <typename Derived, typename T>
void ResourceManager<Derived, T>::PurgeResources()
{
    while (m_resources.begin() != m_resources.end())
    {
        delete m_resources.begin()->second.first;
        m_resources.erase(m_resources.begin());
    }
}

/**
 * @brief  Loads pathe from file
 */

template <typename Derived, typename T>
void ResourceManager<Derived, T>::LoadPaths(const std::string &l_pathFile)
{
    std::ifstream paths;
    paths.open(l_pathFile);//paths.open(Utils::GetWorkingDirectory + l_pathFile);
    if(!paths.is_open())
    {
        std::cerr << "Cannot open path file " << l_pathFile << '\n';
        return;
    }

    std::string line;
    while (getline(paths, line))
    {
        std::stringstream keystream(line);
        std::string pathName;
        std::string path;
        keystream >> pathName;
        keystream >> path;
        m_paths.emplace(pathName, path);
    }
}
