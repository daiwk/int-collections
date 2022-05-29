/*
 * @lc app=leetcode.cn id=208 lang=cpp
 *
 * [208] 实现 Trie (前缀树)
 */

// @lc code=start
class Trie {
private:
    vector<Trie*> children;
    bool is_end;

    Trie* search_prefix(string prefix) {
        Trie* node = this;
        for (char ch: prefix) {
            ch -= 'a';
            if (node->children[ch] == nullptr) {
                return nullptr;
            }
            node = node->children[ch];
        }
        // 遍历完prefix了
        return node;
    }

public:
    Trie(): children(26), is_end(false) {
        // 直接用26初始化vector就行了
    }
    
    void insert(string word) {
        Trie* node = this; // 根，这里用this!!
        for (char ch: word) {
            ch -= 'a'; //变成数字
            if (node->children[ch] == nullptr) {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        // 处理完最后一个字符，赋值true
        node->is_end = true;
    }
    
    bool search(string word) {
        Trie* node = this->search_prefix(word);
        return node != nullptr && node->is_end;
    }
    
    bool startsWith(string prefix) {
        Trie* node = this->search_prefix(prefix);
        return node != nullptr;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// @lc code=end

