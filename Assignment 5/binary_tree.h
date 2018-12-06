#pragma once

template <class key_type, class data_type>
class binary_tree
{
private:
	struct node {
		key_type key;
		data_type data;
		node * left;
		node * right;
	};
	node * start;
	int size;
	//bool internal_search(node **&, key_type, int);

	void insert_priv(node *&, std::string, data_type, int);
	void insert_priv(node *&, std::string, int);
	data_type search_priv(node *&, std::string, int);

	void min_val(node **&);

	void print_preorder(node *);
	void file_preorder(std::ofstream&, node *);

	void file_inorder(std::ofstream&, node *);
	void print_inorder_pri(node *);

	void print_postorder(node *);
	void file_postorder(std::ofstream&, node *);

public:
	binary_tree();
	void insert(std::string, data_type);
	void insert(std::string);
	//void insert(key_type);
	void remove(key_type);
	bool is_empty();
	data_type search(std::string);
	void print_preorder();
	void file_preorder(std::ofstream&);
	void print_inorder();
	void file_inorder_pri(std::ofstream&);
	void print_postorder();
	void file_postorder(std::ofstream&);
	void print_level();
	bool load_file(std::string);
	void save_file(std::string);
	int get_size();
	~binary_tree();
};