/*
 * Super Entity Game Server Project 
 * http://segs.sf.net/
 * Copyright (c) 2006 - 2016 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *
 
 */

#include "MapManager.h"

#include "MapTemplate.h"

#include <QString>
#include <QDir>

using namespace std;
MapManager::MapManager( ) : m_max_instances(2)
{
}
//! \brief Loads all templates available in given directory, will populate m_templates attribute
bool MapManager::load_templates( const QString &template_directory )
{

    //TODO: actually implement this, use boost path support ?
    // (template_directory / "tutorial.bin")
    m_templates[0] = new MapTemplate("tutorial.bin");
    return true;
}
//! \brief Retrieves template specified by it's id
MapTemplate * MapManager::get_template( uint32_t id )
{
    if(m_templates.find(id)==m_templates.end())
        return 0;
    return m_templates[id];
}

size_t MapManager::num_templates()
{
    return m_templates.size();
}

size_t MapManager::max_instances()
{
    return m_max_instances;
}
