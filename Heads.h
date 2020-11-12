#ifndef HEADS_H
#define HEADS_H

#include <iostream>
#include <list>
#include <string>
using namespace std;

typedef struct {
    string key;
    string value;
} IniItem;

typedef struct  {
    string section_name;
    list<IniItem*> items;
} IniSection;


class IniDataHandler {
  private:
  
  public:
    list<IniSection*> list_sections;
    explicit IniDataHandler();
    ~IniDataHandler();

    IniItem * GetItem(IniSection* sect_ptr, const string& key);
    int SetIntem(IniSection* sect_ptr, const string& key, const string& value);
    IniSection* GetSection(const string& section);
    int SetSection(const string& section, IniSection* sect_ptr);

    int GetValueFromSections(const string& section, const string& key, string* value);
    int SetValueIntoSections(const string& section, const string& key, const string& value);

    int DeleteSectionFromSections(const string& section);
    int DeleteItemFromSections(const string& section, const string& key);
    void ReleaseAllData();


};


#endif