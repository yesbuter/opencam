#include <cache.h>

CacheNode::CacheNode(string v_)
{
    key = v_;
    *value = imread(key, -1);
}

LRUCache::LRUCache(int capacity)
{
    size = capacity;
    head = NULL;
    tail = NULL;
}

//取图片
Mat *LRUCache::get(string key_)
{
    map<string, CacheNode *>::iterator it = mp.find(key_);
    if(it != mp.end())
    {
        CacheNode *node = it -> second;
        return node->value;
    }
    else
        return NULL;
}


void LRUCache::set(string key_)
{
    map<string, CacheNode *>::iterator it = mp.find(key_);
    //更新图片顺序
    if(it != mp.end())
    {
       CacheNode *node = it->second;
       remove(node);
       setHead(node);
    }
    //存图片
    else
    {
        CacheNode *newnode = new CacheNode(key_);
        if(mp.size() >= size)
        {
            if(tail != NULL)
                delete tail;
            map<string, CacheNode *>::iterator it = mp.find(tail->key);
            remove(tail);
            mp.erase(it);
        }
        setHead(newnode);
        mp[key_] = newnode;
    }
}

void LRUCache::remove(CacheNode *node)
{
    if(node->pre != NULL)
    {
        node->pre->next = node->next;
    }
    else
    {
        head = node->next;
    }
    if(node->next != NULL)
    {
        node->next->pre = node->pre;
    }
    else
    {
        tail = node->pre;
        tail->next = NULL;
    }
}

void LRUCache::setHead(CacheNode *node)
{
    node->next = head;
    node->pre = NULL;
    if(head != NULL)
    {
        head->pre = node;
    }
    head = node;
    if(tail == NULL)
    {
        tail = head;
    }
}
