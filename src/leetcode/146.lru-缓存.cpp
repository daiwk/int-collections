/*
 * @lc app=leetcode.cn id=146 lang=cpp
 *
 * [146] LRU 缓存
 */

// @lc code=start

struct DLinkeList {
    int key;
    int value;
    DLinkeList* pre;
    DLinkeList* next;
    DLinkeList(): key(0), value(0), pre(nullptr), next(nullptr) {}
    DLinkeList(int k, int v): key(k), value(v), pre(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkeList*> cache;  
    DLinkeList* head;
    DLinkeList* tail;
    int capacity;
    int size; // 还要存实际size

public:    
    // 这里记得加上初始化列表！！！！
    LRUCache(int capacity): capacity(capacity), size(0) {
        head = new DLinkeList();
        tail = new DLinkeList();
        head->next = tail;// 把head和tail连起来
        tail->pre = head;
    }
    
    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        } else {
            DLinkeList* node = cache[key];
            move_to_head(node);
            return node->value;
        }
    }

    void remove_node(DLinkeList* node) {
        node->pre->next = node->next;
        node->next->pre = node->pre;
    }

    void add_to_head(DLinkeList* node) {
        // 标准答案是别的顺序，效果应该一样吧。。
        node->next = head->next;
        head->next->pre = node;
        head->next = node;
        node->pre = head;     
    }

    void move_to_head(DLinkeList* node) {
        // 先把node删了，这样node就是孤立的节点了
        remove_node(node);
        // 然后把这个node插入头部
        add_to_head(node);
    }

    DLinkeList* remove_tail() {
        // 直接复用前面写的remove_node
        // 这样也方便return
        DLinkeList* node = tail->pre;
        remove_node(node);
        return node;
    }

    void put(int key, int value) {
        if(!cache.count(key)) {
            DLinkeList* node = new DLinkeList(key, value);
            add_to_head(node);
            cache[key] = node;
            ++size; //记得更新size
            // 开始LRU的操作
            if (size > capacity) {
                DLinkeList* remove_node = remove_tail();
                cache.erase(remove_node->key);
                delete remove_node; // 防止内存泄漏
                --size;
            }
        } else {
            DLinkeList* node = cache[key];
            node->value = value;
            move_to_head(node); // 记得扔到最前面去，这样才能lru
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
// @lc code=end

