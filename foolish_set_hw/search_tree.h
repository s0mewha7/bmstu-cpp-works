#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <algorithm>

/*
   _____ ______          _____   _____ _    _   _______ _____  ______ ______
  / ____|  ____|   /\   |  __ \ / ____| |  | | |__   __|  __ \|  ____|  ____|
 | (___ | |__     /  \  | |__) | |    | |__| |    | |  | |__) | |__  | |__
  \___ \|  __|   / /\ \ |  _  /| |    |  __  |    | |  |  _  /|  __| |  __|
  ____) | |____ / ____ \| | \ \| |____| |  | |    | |  | | \ \| |____| |____
 |_____/|______/_/    \_\_|  \_\\_____|_|  |_|    |_|  |_|  \_\______|______|

*/

namespace bmstu {
template<typename T>
class search_tree {
 public:
    struct TreeNode;
    using uptr_tn = std::unique_ptr<TreeNode>;
    struct TreeNode {
        explicit TreeNode(T key)
                : data(key), left(nullptr), right(nullptr), height(1) { }

        T data;
        uint8_t height;
        uptr_tn left;
        uptr_tn right;
    };

    class iterator {
     public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        iterator() : current_(nullptr) { }

        explicit iterator(TreeNode* node) {
            while (node) {
                nodes_.push(node);
                node = node->left.get();
            }
            inorder();
        }

        reference operator*() const {
            assert(current_);
            return current_->data;
        }

        pointer operator->() const {
            assert(current_);
            return &(current_->data);
        }

        iterator& operator++() {
            inorder();
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return current_ != other.current_;
        }

        bool operator==(const iterator& other) const {
            return current_ == other.current_;
        }

     private:
        void inorder() {
            if (!nodes_.empty()) {
                current_ = nodes_.top();
                nodes_.pop();
                TreeNode* node = current_->right.get();
                while (node) {
                    nodes_.push(node);
                    node = node->left.get();
                }
            } else {
                current_ = nullptr;
            }
        }

        TreeNode* current_;
        std::stack<TreeNode*> nodes_;
    };

    search_tree() : root_(nullptr), size_(0) { }

    void insert(T value) { this->insert(value, this->root_); }

    bool contains(T value) { return this->contains_(value, this->root_); }

    void remove(T value) {
        this->remove(value, this->root_);
        balance(this->root_);
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }

    [[nodiscard]] size_t height() const {
        return height_(this->root_);
    }

    void print() const {
        print_tree_(this->root_, std::cout);
    }

    template<typename CharT>
    std::basic_ostream<CharT> &draw(
            std::basic_ostream<CharT> &os) const {  // NOLINT
        print_tree_(this->root_, os);
        return os;
    }

    template<typename CharT>
    void inorderTraversal(std::basic_ostream<CharT> &os) const {  // NOLINT
        inorderTraversal(this->root_, os);
    }

    template<typename CharT>
    void preorderTraversal(std::basic_ostream<CharT> &os) const {  // NOLINT
        preorderTraversal(this->root_, os);
    }

    template<typename CharT>
    void postorderTraversal(std::basic_ostream<CharT> &os) const {  // NOLINT
        postorderTraversal(this->root_, os);
    }

    TreeNode *find(T value) { return find(value, this->root_); }


    iterator begin() {
        return iterator(root_.get());
    }

    iterator end() {
        return iterator();
    }

 private:
    template<typename CharT>
    void print_tree_(const uptr_tn &node,
                     std::basic_ostream<CharT> &os) const {  // NOLINT
        std::vector<std::string> buffer;
        int space = 0;
        this->draw_node_(buffer, node, space, 0);
        for (auto &i : buffer) {
            os << i << "\n";
        }
    }

    void draw_node_(std::vector<std::string> &buffer,      // NOLINT
                    const uptr_tn &node, int &all_spaces,  // NOLINT
                    int level) const {                     // NOLINT
        if (node == nullptr) return;
        if (buffer.size() < level * 2 + 1) {
            buffer.emplace_back("");
            buffer.emplace_back("");
        }
        if (node->left != nullptr) {
            draw_node_(buffer, node->left, all_spaces, level + 1);
            buffer[level * 2 + 1] +=
                    std::string(all_spaces - buffer[level * 2 + 1].size() - 1, ' ') + "/";
        }
        buffer[level * 2] +=
                std::string(all_spaces - buffer[level * 2].size(), ' ') +
                std::to_string(node->data);
        all_spaces += std::to_string(node->data).size() + 1;
        if (node->right != nullptr) {
            buffer[level * 2 + 1] +=
                    std::string(all_spaces - buffer[level * 2 + 1].size() - 1, ' ') +
                    "\\";
            draw_node_(buffer, node->right, all_spaces, level + 1);
        }
    }

    bool contains_(T value, const uptr_tn &node) {
        if (node == nullptr) {
            return false;
        } else if (node->data == value) {
            return true;
        } else if (value < node->data) {
            return contains_(value, node->left);
        } else {
            return contains_(value, node->right);
        }
    }

    uptr_tn &insert(T value, uptr_tn &node) {  // NOLINT
        if (node == nullptr) {
            node = std::make_unique<TreeNode>(value);
            ++size_;
            return node;
        }

        if (value < node->data) {
            this->insert(value, node->left);
        } else if (value > node->data) {
            this->insert(value, node->right);
        }
        updateheight(node);
        balance(node);
        return node;
    }

    size_t height_(const uptr_tn &node) const {
        return (node != nullptr) ? node->height : 0;
    }

    int get_balance(const uptr_tn &node) const {  // NOLINT
        return (node != nullptr) ? height_(node->left) - height_(node->right) : 0;
    }

    void rotate_with_left_child(uptr_tn &k2) {  // NOLINT
        k2 = std::move(right_rotate(k2));
    }

    void rotate_with_right_child(uptr_tn &k1) {  // NOLINT
        k1 = std::move(left_rotate(k1));
    }

    void double_with_left_child(uptr_tn &k3) {  // NOLINT
        rotate_with_right_child(k3->left);
        rotate_with_left_child(k3);
    }

    void double_with_right_child(uptr_tn &k3) {  // NOLINT
        rotate_with_left_child(k3->right);
        rotate_with_right_child(k3);
    }

    void balance(uptr_tn &t) {  // NOLINT
        if (t == nullptr) {
            return;
        }
        balance(t->left);
        balance(t->right);
        updateheight(t);
        if (get_balance(t) < -1) {
            if (get_balance(t->right) <= 0) {
                rotate_with_right_child(t);
            } else {
                double_with_right_child(t);
            }
            updateheight(t);
        }
        if (get_balance(t) > 1) {
            if (get_balance(t->left) >= 0) {
                rotate_with_left_child(t);
            } else {
                double_with_left_child(t);
            }
            updateheight(t);
        }
    }

    uptr_tn &right_rotate(uptr_tn &y) {  // NOLINT
        uptr_tn x = std::move(y);
        y = std::move(x->left);
        x->left = std::move(y->right);
        y->right = std::move(x);
        updateheight(y->right);
        updateheight(y);
        return y;
    }

    uptr_tn &left_rotate(uptr_tn &y) {  // NOLINT
        uptr_tn x = std::move(y);
        y = std::move(x->right);
        x->right = std::move(y->left);
        y->left = std::move(x);
        updateheight(y->left);
        updateheight(y);
        return y;
    }

    uptr_tn &find_max(uptr_tn &node) {  // NOLINT
        if (node->right == nullptr) {
            return node;
        }
        return find_max(node->right);
    }

    uptr_tn &find_min(uptr_tn &node) {  // NOLINT
        if (node->left == nullptr) {
            return node;
        }
        return find_min(node->left);
    }

    void remove(T value, uptr_tn &node) {  // NOLINT
        if (node == nullptr) {
            return;
        }
        if (value == node->data) {
            if (node->right == nullptr && node->left == nullptr) {
                auto old_node = std::move(node);
            } else if (node->right != nullptr) {
                if (node->right->left == nullptr) {
                    auto old_node = std::move(node->right);
                    std::swap(node->data, old_node->data);
                    node->right = std::move(old_node->right);
                    updateheight(node);
                } else {
                    auto old_node = std::move(find_min(node->right));
                    std::swap(node->data, old_node->data);
                    updateheight(node);
                }
            } else if (node->left != nullptr) {
                if (node->left->right == nullptr) {
                    auto old_node = std::move(node->left);
                    std::swap(node->data, old_node->data);
                    node->left = std::move(old_node->left);
                    updateheight(node);
                } else {
                    auto old_node = std::move(find_max(node->left));
                    std::swap(node->data, old_node->data);
                    updateheight(node);
                }
            }
            --size_;
        } else if (value < node->data) {
            remove(value, node->left);
            updateheight(node);
        } else if (value > node->data) {
            remove(value, node->right);
            updateheight(node);
        }
    }

    void updateheight(uptr_tn &node) {  // NOLINT
        if (node == nullptr) return;
        node->height = std::max(height_(node->left), height_(node->right)) + 1;
    }

    template<typename CharT>
    void inorderTraversal(const uptr_tn &node,
                          std::basic_ostream<CharT> &os) const {  // NOLINT
        if (node == nullptr) {
            return;
        }
        inorderTraversal(node->left, os);
        os << node->data << " ";
        inorderTraversal(node->right, os);
    }

    template<typename CharT>
    void preorderTraversal(const uptr_tn &node,
                           std::basic_ostream<CharT> &os) const {  // NOLINT
        if (node == nullptr) {
            return;
        }
        os << node->data << " ";
        preorderTraversal(node->left, os);
        preorderTraversal(node->right, os);
    }

    template<typename CharT>
    void postorderTraversal(const uptr_tn &node,
                            std::basic_ostream<CharT> &os) const {  // NOLINT
        if (node == nullptr) {
            return;
        }
        postorderTraversal(node->left, os);
        postorderTraversal(node->right, os);
        os << node->data << " ";
    }

    TreeNode *find(T value, uptr_tn &node) {  // NOLINT
        if (node == nullptr) {
            return nullptr;
        }
        if (value == node->data) {
            return &(*node);
        } else if (value > node->data) {
            return find(value, node->right);
        } else if (value < node->data) {
            return find(value, node->left);
        }
        return nullptr;
    }

    uptr_tn root_;
    size_t size_;
};
}  // namespace bmstu
