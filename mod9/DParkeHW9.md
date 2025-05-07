# Homework Nine: Seaching Ordered Data and Search Trees

## Question One

> For questions 1 – 2, compare the efficiency of using sequential search on an 
> ordered table of size n and an unordered table of the same size for the key target: 
> a. If no record with the key target is present.
> b. If one record with the key target is present and only one is sought

a. For both an ordered and unordered table, it'll be a worst case of o(n), but for the ordered table, you can terminate if the record is not found by the time it would be expected, so you'll have a best case of early termination

b. For an unordered table, it'll still be a search with worst case o(n) and average case of o(n/2), just as the ordered table is, but it'll still be o(n), though it again may be able to terminate early, so it may have an advantage

## Question Two 

> a. If more than one record with the key target is present and it is desired to find 
> only the first one. 
> b. If more than one record with the key target is present and it is desired to find 
>them all.

a. For the unordered case, you'll still have to just check until you get a match, which can be anywhere in the tree - thus, you'll have o(n), with n/2 average elements searched to find assuming random distribution. For the ordered case, if there are multiple matches, you'll find the match earlier, since it'll be the first key you check once you trasverse the cluster. Thus, it'll have the same o(n) but on average, it should be a bit more efficient.

b. For the unordered case, you'll have to check every entry every time to ensure all cases are searched. In the oerdered table, you'll find the cluster of keys, and then know you've found them all whenver the key looked at is no longer the one you're searching for. Thus, the ordered will be slightly more performant

## Question Three

> Write a method delete(key1, key2) to delete all records with keys between key1 
> and key2 (inclusive) from a binary search tree whose nodes look like this:
> [left][key][right]

```
struct bst_node
    int key
    int left
    int right
end


function delete(root, key1, key2);

 if root->key < key1 begin
        root->right = delete(root->right, key1, key2)
        return root
    end
    else if root->key > key2 begin
        root->left = delete(root->left, key1, key2)
        return root
    end
    else begin
        if root->left == null begin
            return delete(root->right, key1, key2)
        end
        else if root->right == null begin
            return delete(root->left, key1, key2)
        end
        else begin 
            successor = find_min(root->right)
            root->key = successor->key
            root->right = delete_node(root->right, successor->key)
            root->left = delete(root->left, key1, key2)
            root->right = delete(root->right, key1, key2)
            return root
        end 
    end
endfunction: delete

function find_min(node)
    while node->left != null
        node = node->left
    endwhile
    return node
endfunction: find_min

function delete_node(root, key)
    if root == null
        return null
    endif

    if key < root->key
        root->left = delete_node(root->left, key)
    elseif key > root->key
        root->right = delete_node(root->right, key)
    else
        if root->left == null
            return root->right
        elseif root->right == null
            return root->left
        else
            successor = find_min(root->right)
            root->key = successor->key
            root->right = delete_node(root->right, successor->key)
        endif
    endif
    return root
endfunction: delete_node

```

## Question Four

> Write a method to delete a record from a B-tree in order n

```
function delete_from_btree(node, key)
    index = find_key_index(node, key)

    if index < node->key_count and node->keys[index] == key begin
        if node->leaf begin
            remove_key(node, index)
        end
        else begin
            if has_enough_keys(node->children[index]) begin
                pred = get_predecessor(node, index)
                node->keys[index] = pred
                delete_from_btree(node->children[index], pred)
            end
            else if has_enough_keys(node->children[index + 1]) begin
                succ = get_successor(node, index)
                node->keys[index] = succ
                delete_from_btree(node->children[index + 1], succ)
            end 
            else begin
                merge_children(node, index)
                delete_from_btree(node->children[index], key)
            end
        end
    else begin
        if node->leaf
            return // key not found
        end

        if node->children[index]->key_count == MIN_KEYS
            fix_child(node, index)
        end

        delete_from_btree(node->children[index], key)
    end
endfunction: delete_from_btree

function find_key_index(node, key)
    i = 0
    while i < node->key_count and node->keys[i] < key
        i = i + 1
    endwhile
    return i
endfunction: find_key_index

```