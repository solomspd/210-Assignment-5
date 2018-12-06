#include <fstream>
#include <queue>

#include "binary_tree.h"

template<class key_type, class data_type>
binary_tree<key_type, data_type>::binary_tree()
{
	start = NULL;
	size = 0;
}

//template<class key_type, class data_type>
//bool binary_tree<key_type, data_type>::internal_search(node **& cursor, key_type query, int at, int length) {
//	if ((*cursor) == NULL || (*cursor)->left > query && at ) {
//		return false;
//	}else if ((*cursor)->key.at(at) == query) {
//		return true;
//	}
//	if ((*cursor)->key < query) {
//		cursor = &((*cursor)->left);
//		return internal_search(cursor, query);
//	}
//	else {
//		cursor = &((*cursor)->right);
//		return internal_search(cursor, query);
//	}
//}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::insert(std::string key_in, data_type data_in) {
	insert_priv(start, key_in, data_in, 0);
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::insert(std::string key_in) {
	insert_priv(start, key_in, 0);
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::insert_priv(node *& cursor, std::string key_in, data_type data_in, int at) {
	if (at < key_in.length()) {
		if (cursor->key == key_in[at]) {
			cursor = cursor->left;
		}
		else if (cursor->key > key_in[at]) {
			node * new_node = new node;
			new_node = cursor;
			cursor->key = key_in[at];
			cursor->left = new_node;
			cursor->right = NULL;
		}
		else if (cursor == NULL) {
			cursor = new node;
			cursor->key = key_in[at];
			cursor->data = NULL;
			cursor->left = NULL;
			cursor->right = NULL;
		}
		else if (cursor->key < key_in[at]) {
			cursor = cursor->right;
		}
		insert_priv(cursor, key_in, data_in, ++at);
	}
	else {
		cursor->data = data_in;
	}
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::insert_priv(node *& cursor, std::string key_in, int at) {
	if (at < key_in.length()) {
		if (key_in == "as") {
			std::cout << " ";
		}
		if (cursor == NULL) {
			cursor = new node;
			cursor->key = key_in[at];
			cursor->data = 0;
			cursor->left = NULL;
			cursor->right = NULL;
			if (at + 1 < key_in.length()) {
				cursor = cursor->left;
			}
		}
		else if (cursor->key == key_in[at]) {
			cursor = cursor->left;
		}
		else if (cursor->key > key_in[at]) {
			node * new_node = new node;
			new_node = cursor;
			cursor->key = key_in[at];
			cursor->left = new_node;
			cursor->right = NULL;
		}
		else if (cursor->key < key_in[at]) {
			cursor = cursor->right;
		}
		insert_priv(cursor, key_in, ++at);
	}
	else {
		cursor->data++;
	}
}

//template<class key_type, class data_type>
//void binary_tree<key_type, data_type>::insert(key_type key_in) {
//	node ** local_cursor = &start;
//	if (!internal_search(local_cursor, key_in)) {
//		*local_cursor = new node;
//		(*local_cursor)->key = key_in;
//		(*local_cursor)->data = 1;
//		(*local_cursor)->left = NULL;
//		(*local_cursor)->right = NULL;
//		size++;
//	}
//	else {
//		(*local_cursor)->data++;
//	}
//}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::min_val(node **& cursor) {
	if ((*cursor)->left != NULL) {
		min_val((*cursor)->left);
	}
	else {
		return cursor;
	}
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::remove(key_type key_in) {
	node ** local_cursor = &start;
	if (internal_search(local_cursor, key_in)) {
		if ((*local_cursor)->left == NULL && (*local_cursor)->right == NULL) {
			delete local_cursor;
		}
		else if ((*local_cursor)->left != NULL && (*local_cursor)->right == NULL) {
			node * temp_cursor = (*local_cursor);
			(*local_cursor) = (*local_cursor->left);
			delete temp_cursor;
		}
		else if ((*local_cursor)->left == NULL && (*local_cursor)->right != NULL) {
			node * temp_cursor = (*local_cursor);
			(*local_cursor) = (local_cursor->right);
			delete temp_cursor;
		}
		else {
			node * temp_cursor = *local_cursor;
			min_val(local_cursor->right);
			temp_cursor = local_cursor;
			delete local_cursor;
		}
	}
	else {
		std::cout << "there is no matching entry" << std::endl;
	}
	size--;
}

template<class key_type, class data_type>
bool binary_tree<key_type, data_type>::is_empty() {
	if (start == NULL) {
		return true;
	}
	return false;
}

template<class key_type, class data_type>
data_type binary_tree<key_type, data_type>::search(std::string query) {
	return search_priv(start, query, 0);
}

template<class key_type, class data_type>
data_type binary_tree<key_type, data_type>::search_priv(node *& cursor, std::string key_in, int at) {
	if (at < key_in.length()) {
		if (cursor->key == key_in[at]) {
			cursor = cursor->left;
		}
		else if (cursor->key > key_in[at]) {
			return NULL;
		}
		else if (cursor == NULL) {
			return NULL;
		}
		else if (cursor->key < key_in[at]) {
			cursor = cursor->right;
		}
		return search_priv(cursor, key_in, ++at);
	}
	else {
		return cursor->data;
	}



	/*if (at < key_in.length()) {
	if (cursor->key == key_in[at]) {
	return cursor->key + search(cursor->left, key_in, ++at);
	}
	else if (cursor->key > key_in[at]) {
	std::cout << "entry not found" << std::endl;
	}
	else if (cursor == NULL) {
	std::cout << "entry not found" << std::endl;
	}
	else if (cursor->key < key_in[at]) {
	cursor = cursor->right;
	}
	insert(cursor, key_in, data_in, ++at);
	}*/
}

//template<class key_type, class data_type>
//data_type binary_tree<key_type, data_type>::search(key_type query) {
//	node ** local_cursor = &start;
//	if (internal_search(local_cursor, query)) {
//		return (*local_cursor)->data;
//	}
//	else {
//		std::cout << std::endl <<std::endl << "search query not found" << std::endl;
//		return NULL;
//	}
//}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::print_preorder() {
	print_preorder(start);
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::print_preorder(node * cursor) {
	if (cursor != NULL) {
		std::cout << "key : " << cursor->key << "  data: " << cursor->data << std::endl;
		print_preorder(cursor->left);
		print_preorder(cursor->right);
	}
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::print_inorder() {
	print_inorder_pri(start);
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::print_inorder_pri(node * cursor) {
	if (cursor != NULL) {
		print_inorder_pri(cursor->left);
		std::cout << "key : " << cursor->key << "  data: " << cursor->data << std::endl;
		print_inorder_pri(cursor->right);
	}
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::print_postorder() {
	print_postorder(start);
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::print_postorder(node * cursor) {
	if (cursor != NULL) {
		print_postorder(cursor->left);
		print_postorder(cursor->right);
		std::cout << "key : " << cursor->key << "  data: " << cursor->data << std::endl;
	}
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::file_preorder(std::ofstream& out) {
	file_preorder(out, start);
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::file_preorder(std::ofstream& out, node * cursor) {
	if (cursor != NULL) {
		out << cursor->key << ' ' << cursor->data << std::endl;
		print_preorder(cursor->left);
		print_preorder(cursor->right);
	}
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::file_inorder_pri(std::ofstream& out) {
	file_inorder(out, start);
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::file_inorder(std::ofstream& out, node * cursor) {
	if (cursor != NULL) {
		file_inorder(out, cursor->left);
		out << cursor->key << " " << cursor->data << std::endl;
		file_inorder(out, cursor->right);
	}
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::file_postorder(std::ofstream& out) {
	file_postorder(out, start);
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::file_postorder(std::ofstream& out, node * cursor) {
	if (cursor != NULL) {
		print_postorder(cursor->left);
		print_postorder(cursor->right);
		out << cursor->key << ' ' << cursor->data << std::endl;
	}
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::save_file(std::string in_file_name) {
	std::ofstream out_file;
	in_file_name += ".txt";
	out_file.open(in_file_name.c_str());
	if (out_file.is_open()) {
		file_inorder_pri(out_file);
	}
	else {
		std::cout << "error: unable to open output file" << std::endl;
	}
	out_file.close();
}

template<class key_type, class data_type>
bool binary_tree<key_type, data_type>::load_file(std::string in_file_name) {
	std::ifstream in_file;
	in_file_name += ".txt";
	in_file.open(in_file_name.c_str());
	if (in_file.is_open()) {
		while (!in_file.eof()) {
			std::string word_temp, num_temp;
			in_file >> word_temp >> num_temp;
			if (in_file.eof()) {
				break;
			}
			insert(word_temp, std::stoi(num_temp));
		}
	}
	else {
		//std::cout << "file does not exist" << std::endl;
		return false;
	}
	return true;
	in_file.close();
}

template<class key_type, class data_type>
void binary_tree<key_type, data_type>::print_level() {
	node * local_cusor = start;
	std::queue<node*> temp_que;
	temp_key.push(local_cusor);
	while (!temp_que.empty()) {
		temp_que.pop(cursor);
		std::cout << cursor->key << " " << cursor->data << std::endl;
		if (cursor->left != NULL) {
			temp_que.push(cursor->left);
		}
		if (cursor->right != NULL) {
			temp_que.push(cursor->right);
		}
	}
}

template<class key_type, class data_type>
int binary_tree<key_type, data_type>::get_size() {
	return size;
}

template<class key_type, class data_type>
binary_tree<key_type, data_type>::~binary_tree()
{
}