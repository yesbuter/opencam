#ifndef CACHE_H
#define CACHE_H

#include <iostream>
#include <map>
#include <string>
#include <util.h>
using namespace std;


class CacheNode
{
public:
    string key;
    Mat *value;
    CacheNode *next, *pre;

    CacheNode(string k_);
};

class LRUCache
{
private:
    int size;
    CacheNode *head, *tail;
    map<string, CacheNode*> mp;
public:
    LRUCache(int capacity);
    Mat* get(string key);
    void set(string key, Mat value);
    void remove(CacheNode *node);
    void setHead(CacheNode *node);
};

#endif // CACHE_H
