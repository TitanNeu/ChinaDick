#include "Heads.h"

IniDataHandler::IniDataHandler()
{
    cout << "Hello World" << endl;
}
IniDataHandler::~IniDataHandler()
{
}

//返回IniSection指针
IniSection *IniDataHandler::GetSection(const string &section)
{
    if (&list_sections == NULL)
    {
        return NULL;
    }

    if(list_sections.size() == 0) {
        return NULL;
    }

    for (list<IniSection *>::iterator it = list_sections.begin(); it != list_sections.end(); ++it)
    {
        if ((*it)->section_name == section)
        {
            return *it;
        }
    }

    return NULL;
}
//创建IniSection
int IniDataHandler::SetSection(const string &section, IniSection *sect_ptr)
{
    //section为输入, sect_ptr为输出
    if (&section == NULL || &sect_ptr == NULL)
    {
        //失败
        return -1;
    }
    //创建一个IniSection结构
    IniSection *ini_ptr = new IniSection();
    //给内部的section_name赋值
    ini_ptr->section_name = section;
    //把指针放到list_sections
    list_sections.push_back(ini_ptr);
    sect_ptr = ini_ptr;
    return 0;
}

//查找IniSection结构内部items的值
int IniDataHandler::GetValueFromSections(const string &section, const string &key, string *value)
{
    if (&section == NULL || &key == NULL || &value == NULL)
    {
        return -1;
    }
    if(list_sections.size() == 0){
        return -1;
    }

    for (list<IniSection *>::iterator it = list_sections.begin(); it != list_sections.end(); ++it)
    {
        if ((*it)->section_name == section)
        {
            //it2是items的迭代器
            for (list<IniItem *>::iterator it2 = (*it)->items.begin(); it2 != (*it)->items.end(); ++it2)
            {
                if ((*it2)->key == key)
                {
                    *value = (*it2)->value;
                    //成功
                    return 0;
                }
            }
        }
    }
    //失败
    return -1;
}

int IniDataHandler::SetValueIntoSections(const string &section, const string &key, const string &value)
{

    if (&section == NULL || &key == NULL || &value == NULL)
    {
        return -1;
    }
    if(list_sections.size() == 0) {
        return -1;
    }
    for(auto it = list_sections.begin(); it != list_sections.end(); ++it) {
        if((*it)->section_name == section) {
            //堆上 创建IniItem结构实体,放进key-value
            IniItem* item_ptr = new IniItem();
            item_ptr->key = key;
            item_ptr->value = value;
            //把指针放进it指向的IniSection节点的items链表
            (*it)->items.push_back(item_ptr);
            //成功
            return 0;
        }
    }
    //失败
    return -1;
}
//删除IniSection节点
int IniDataHandler::DeleteSectionFromSections(const string &section)
{
    if (&section == NULL)
    {
        return -1;
    }
    if(list_sections.size() == 0) {
        return -1;
    }

    for(auto it =  list_sections.begin(); it != list_sections.end(); ++it) {
        if((*it)->section_name == section) {
            //释放(*it)的内存
            delete (*it);
            //删除it指向的链表节点
            list_sections.erase(it);
            //成功
            return 0;
        }
    }
    //失败
    return -1;
}

int IniDataHandler::DeleteItemFromSections(const string &section, const string &key)
{
    if (&section == NULL || &key == NULL)
    {
        return -1;
    }

    if(list_sections.size() == 0) {
        return -1;
    }
    for(auto it = list_sections.begin(); it != list_sections.end(); ++it) {
        if((*it)->section_name == section) {
            for(auto it2 = (*it)->items.begin(); it2 != (*it)->items.end(); ++it2) {
                if((*it2)->key == key) {
                    //删除满足条件的item
                    delete (*it2);
                    //删除items链表的对应节点存放的指针
                    (*it)->items.erase(it2);
                    //成功
                    return 0;
                }
            }
        }
    }
    //失败
    return -1;
}

int main()
{
    IniDataHandler *ini_ptr = new IniDataHandler();
    
}
