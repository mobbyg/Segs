/*
 * Super Entity Game Server Project
 * http://segs.sf.net/
 * Copyright (c) 2006 Super Entity Game Server Team (see Authors.txt)
 * This software is licensed! (See License.txt for details)
 *
 */

#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <QtCore/QString>
#include <QtCore/QFile>
#include <fstream>
#include <map>

struct RGBA;

typedef glm::vec3 Vec3;
typedef glm::vec2 Vec2;
class BinStore // binary storage
{
    struct FileEntry {
        QString name;
        uint32_t date=0;
    };
    QFile m_str;
    size_t bytes_read=0;
    uint32_t bytes_to_read=0;
    std::vector<uint32_t> m_file_sizes; // implicit stack
    std::vector<FileEntry> m_entries;

    template<class V>
    size_t read_internal(V &res)
    {
        if(m_file_sizes.size()>0 && current_fsize()<sizeof(V))
            return 0;
        m_str.read((char *)&res,sizeof(V));
        if(m_file_sizes.size()>0)
        {
            bytes_read+=sizeof(V);
            (*m_file_sizes.rbegin())-=sizeof(V);
        }
        return sizeof(V);
    }
    QString     read_pstr(size_t maxlen);
    void        skip_pstr();
    bool        read_data_blocks(bool file_data_blocks);
    bool        check_bin_version_and_crc(uint32_t req_crc);
    uint32_t    current_fsize() {return *m_file_sizes.rbegin();}
    uint32_t    read_header(QString & name, size_t maxlen);
    void        fixup();
public:

    QString     source_name() {
        return read_str(12000);
    }
    bool        read_bytes(char *tgt,size_t sz);
    QString read_str(size_t maxlen);
    bool        read(uint32_t &v);
    bool        read(int32_t &v);
    bool        read(float &v);
    bool        read(uint16_t &v);
    bool        read(uint8_t &v);
    bool        read(Vec2 &v);
    bool        read(Vec3 &v);
    bool        read(RGBA &v);
    bool        read(std::vector<uint32_t> &v);
    bool        read(std::vector<int32_t> &res);
    bool        read(std::vector<float> &res);
    bool        read(std::vector<QString> &res);
    bool        read(std::vector<std::vector<QString>> &res);
    bool        read(uint8_t *&val, uint32_t length);
    bool        read(QString &val);
    void        prepare();
    bool        prepare_nested();
    bool        nesting_name(QString & name);
    void        nest_in() {  }
    void        nest_out() { m_file_sizes.pop_back(); }
    bool        end_encountered() const;
    bool        open(const QString & name, uint32_t required_crc);
    bool        findAndOpen(const QString & name, uint32_t reqcrc=0);
};
