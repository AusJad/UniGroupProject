#pragma once

#include <vector>
#include <list>

#ifndef pair

/**
* @struct pair
* @brief Struct for holding data from the tree in
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
struct pair{
	float x;
	float z;
	pair(float x, float z){ this->x = x; this->z = z; };
	pair(){ this->x = 0; this->z = 0; };
	float & operator [] (int index) {
		if (index == 0) return x;
		else return z;
	};

	bool operator == (const pair & rhs) {
		return this->x == rhs.x && this->z == rhs.z;
	}
};

#endif 

/**
* @class QuadTree
* @brief Class for creating a quadtree data structure to store all data in
*
* @author Morgan Smolder
* @version 01
* @date 02/04/2018
*/
template <class T>
class QuadTree{
	public:
		QuadTree(pair topleft, pair bottomright, unsigned ceiling);
		QuadTree();
		~QuadTree();
		QuadTree(const QuadTree<T> & tocpy);

		/**
		* @brief Set the dimensions
		* 
		* @param TL - The top left pair.
		* @param BR - The bottom right pair.
		*/
		void setDimensions(pair TL, pair BR);

		/**
		* @brief Insert a new element
		*
		* @param newelement - The new element
		* @param getposfunc() - The get position function.
		*
		* @return bool - If the element was inserted.
		*/
		bool insert(const T & newelement, pair (*getposfunc)(const T & element));

		/**
		* @brief Traverse the quadtree structure.
		*
		* @param travfun() - The traverse function.
		*/
		void traverse(void(*travfunc)(const std::vector<std::list<T> > & elements, pair topleft, pair bottomright));

		/**
		* @brief Search for a element in the tree
		*
		* @param comparisonfunc() - The comparison function.
		* @param onFind() - The onfind function
		* @param getposfunc() - The get position function
		* @param tofind - The data to find.
		*
		* @return bool - If the target was found.
		*/
		bool search(bool(*comparisonfunc)(const T & element, const T & comparator), void(*onFind)(const std::vector<std::list<T> > & elements, pair topleft, pair bottomright), pair(*getposfunc)(const T& element), const T& tofind);

		/**
		* @brief Clear the tree.
		*/
		void clear();
		
		/**
		* @brief Overload for the = operator.
		* 
		* @param tocpy - The quadtree to be copied.
		*
		* @return QuadTree<T> - The quadtree.
		*/
		const QuadTree<T> & operator = (const QuadTree<T> & tocpy);
	private:
		/// The data bucket.
		std::vector<std::list<T> > bucket;
		/// The ceiling for the quadtree.
		unsigned ceiling;
		/// The top left element.
		pair topleft;
		/// The bottom right element.
		pair bottomright;
		/// Pointer to the top left data.
		QuadTree<T>* top_left;
		/// Pointer to the top right data.
		QuadTree<T>* top_right;
		/// Pointer to the bottom left data.
		QuadTree<T>* bottom_left;
		/// Pointer to the bottom right data.
		QuadTree<T>* bottom_right;

		/**
		* @brief Delete the root.
		*/
		void killTreeRoot();

		/**
		* @brief Delete the tree.
		*
		* @param currnode - The current node.
		*/
		void killTree(QuadTree<T>* & currnode);

		/**
		* @brief Copy the root.
		*
		* @param tocpyroot - The root to be copied.
		*/
		void cpyTreeRoot(const QuadTree<T>* tocpyroot);

		/**
		* @brief Copy a tree.
		*
		* @param curnode - The current node.
		* @param tocpy - The tree to be copied.
		*/
		void cpyTree(QuadTree<T>* & curnode, const QuadTree<T>* tocpy);

		/**
		* @brief Traverse the tree.
		*
		* @param currnode - The current node.
		* @param travfunc() - The traverse function.
		*/
		void traverse(QuadTree<T>* currnode, void(*travfunc)(const std::vector<std::list<T> >  & elements, pair topleft, pair bottomright));

		/**
		* @brief If the tree has any children.
		*
		* @param totest - The quadtree to test.
		*
		* @return bool - If the tree has children.
		*/
		bool noChildren(QuadTree<T>* totest);

		/**
		* @brief Split the tree.
		*
		* @param tosplit - The quad tree.
		* @param getposfunc() - Get position function.
		*/
		void splitTree(QuadTree<T>* tosplit, pair (*getposfunc)(const T & element));

		/**
		* @brief Insert a element into the tree
		*
		* @param curnode - The current node.
		* @param newelement - The new element.
		* @param getposfun() - Get position function.
		*
		* @return bool - If the element was inserted.
		*/
		bool insert(QuadTree<T>* curnode, const T & newelement, pair (*getposfunc)(const T & element));

		/**
		* @brief Duplicate the element.
		*
		* @param tosearch - A list of data to check.
		* @param target - The element to look for.
		* @param getposfunc() - The get position function.
		*
		* @return int - The new element
		*/
		int duplicateElement(const std::vector<std::list<T> >& tosearch, const T & target, pair(*getposfunc)(const T& element));
};

template <class T>
QuadTree<T>::QuadTree() {
	top_left = NULL;
	top_right = NULL;
	bottom_left = NULL;
	bottom_right = NULL;
	this->ceiling = 50;
	this->topleft = pair(0,100);
	this->bottomright = pair(100,0);
}

template <class T>
QuadTree<T>::QuadTree(pair topleft, pair bottomright, unsigned ceiling){
	top_left = NULL;
	top_right = NULL;
	bottom_left = NULL;
	bottom_right = NULL;
	this->ceiling = ceiling;
	this->topleft = topleft;
	this->bottomright = bottomright;
}

template <class T>
void QuadTree<T>::clear(){
	killTreeRoot();
}

template <class T>
QuadTree<T>::~QuadTree(){
	killTreeRoot();
}

template <class T>
void QuadTree<T>::killTreeRoot(){
	if (top_left != NULL) killTree(top_left);
	if (top_right != NULL) killTree(top_right);
	if (bottom_left != NULL) killTree(bottom_left);
	if (bottom_right != NULL) killTree(bottom_right);

	delete bottom_left;
	bottom_left = NULL;
	delete top_left;
	top_left = NULL;
	delete bottom_right;
	bottom_right = NULL;
	delete top_right;
	top_right = NULL;
	bucket.clear();
}

template <class T>
void QuadTree<T>::killTree(QuadTree<T>* & curnode){
	if (curnode->top_left != NULL) killTree(curnode->top_left);
	if (curnode->top_right != NULL) killTree(curnode->top_right);
	if (curnode->bottom_left != NULL) killTree(curnode->bottom_left);
	if (curnode->bottom_right != NULL) killTree(curnode->bottom_right);

	delete curnode->bottom_left;
	curnode->bottom_left = NULL;
	delete curnode->top_left;
	curnode->top_left = NULL;
	delete curnode->bottom_right;
	curnode->bottom_right = NULL;
	delete curnode->top_right;
	curnode->top_right = NULL;
	curnode->bucket.clear();
}

template <class T>
QuadTree<T>::QuadTree(const QuadTree<T> & tocpy){
	cpyTreeRoot(&tocpy);
}

template <class T>
void QuadTree<T>::setDimensions(pair TL, pair BR) {
	this->topleft = TL;
	this->bottomright = BR;
}

template <class T>
void QuadTree<T>::cpyTreeRoot(const QuadTree<T>* tocpyroot){
	bucket.clear();

	if (tocpyroot->bucket.empty() == false){
		for (unsigned i = 0; i < tocpyroot->bucket.size(); i++){
			bucket.push_back(tocpyroot->bucket.at(i));
		}
	}

	topleft = tocpyroot->topleft;
	bottomright = tocpyroot->bottomright;
	ceiling = tocpyroot->ceiling;

	if (tocpyroot->top_left != NULL){ cpyTree(top_left, tocpyroot->top_left); }
	else top_left = NULL;
	if (tocpyroot->top_right != NULL) cpyTree(top_right, tocpyroot->top_right);
	else top_right = NULL;
	if (tocpyroot->bottom_left != NULL) cpyTree(bottom_left, tocpyroot->bottom_left);
	else bottom_left = NULL;
	if (tocpyroot->bottom_right != NULL) cpyTree(bottom_right, tocpyroot->bottom_right);
	else bottom_right = NULL;
}

template <class T>
void QuadTree<T>::cpyTree(QuadTree<T>* & curnode, const QuadTree<T>* tocpy){
	curnode = new QuadTree<T>(tocpy->topleft, tocpy->bottomright, tocpy->ceiling);
	if (tocpy->bucket.empty() == false){
		for (unsigned i = 0; i < tocpy->bucket.size(); i++){
			curnode->bucket.push_back(tocpy->bucket.at(i));
		}
	}

	if (tocpy->top_left != NULL){ cpyTree(curnode->top_left, tocpy->top_left); }
	else curnode->top_left = NULL;
	if (tocpy->top_right != NULL) cpyTree(curnode->top_right, tocpy->top_right);
	else curnode->top_right = NULL;
	if (tocpy->bottom_left != NULL) cpyTree(curnode->bottom_left, tocpy->bottom_left);
	else curnode->bottom_left = NULL;
	if (tocpy->bottom_right != NULL) cpyTree(curnode->bottom_right, tocpy->bottom_right);
	else curnode->bottom_right = NULL;
}

template <class T>
const QuadTree<T> & QuadTree<T>::operator = (const QuadTree<T> & tocpy){
	killTreeRoot();
	cpyTree(this, &cpyTree);
	return this;
}

template <class T>
bool QuadTree<T>::search(bool(*comparisonfunc)(const T & element, const T & comparator), void(*onFind)(const std::vector<std::list<T> > & elements, pair topleft, pair bottomright), pair(*getposfunc)(const T& element), const T& tofind){
	bool found = false;
	
	for (unsigned i = 0; i < bucket.size() && !found; i++){
		for (std::list<T>::const_iterator listit = bucket.at(i).begin(); listit != bucket.at(i).end(); ++listit){
			if (comparisonfunc(*listit, tofind)){
				onFind(bucket, topleft, bottomright);
				found = true;
			}
		}
	}

	QuadTree<T>* curnode = this;

	pair temppos = getposfunc(tofind);

	while (!noChildren(curnode) && !found){
		if (temppos[0] <= curnode->top_left->bottomright[0] && temppos[0] >= curnode->top_left->topleft[0]
			&& temppos[1] >= curnode->top_left->bottomright[1] && temppos[1] <= curnode->top_left->topleft[1]){
			curnode = curnode->top_left;
		}
		else
		if (temppos[0] <= curnode->top_right->bottomright[0] && temppos[0] >= curnode->top_right->topleft[0]
			&& temppos[1] >= curnode->top_right->bottomright[1] && temppos[1] <= curnode->top_right->topleft[1]){
			curnode = curnode->top_right;
		}
		else
		if (temppos[0] <= curnode->bottom_left->bottomright[0] && temppos[0] >= curnode->bottom_left->topleft[0]
			&& temppos[1] >= curnode->bottom_left->bottomright[1] && temppos[1] <= curnode->bottom_left->topleft[1]){
			curnode = curnode->bottom_left;
		}
		else
		if (temppos[0] <= curnode->bottom_right->bottomright[0] && temppos[0] >= curnode->bottom_right->topleft[0]
			&& temppos[1] >= curnode->bottom_right->bottomright[1] && temppos[1] <= curnode->bottom_right->topleft[1]){
			curnode = curnode->bottom_right;
		}

		for (unsigned i = 0; i < curnode->bucket.size() && !found; i++){
			for (std::list<T>::const_iterator listit = curnode->bucket.at(i).begin(); listit != curnode->bucket.at(i).end() && !found; ++listit){
				if (comparisonfunc(*listit, tofind)){
					onFind(curnode->bucket, curnode->topleft, curnode->bottomright);
					found = true;
				}
			}
		}
	}

	return found;
}

template <class T>
void QuadTree<T>::traverse(void(*travfunc)(const std::vector<std::list<T> >  & elements, pair topleft, pair bottomright)){
	traverse(this, travfunc);
}

template <class T>
void QuadTree<T>::traverse(QuadTree<T>* currnode, void(*travfunc)(const std::vector<std::list<T> > & elements, pair topleft, pair bottomright)){
	if (currnode->bucket.empty() == false) travfunc(currnode->bucket, currnode->topleft, currnode->bottomright);

	if (currnode->top_left != NULL) traverse(currnode->top_left, travfunc);
	if (currnode->top_right != NULL) traverse(currnode->top_right, travfunc);
	if (currnode->bottom_left != NULL) traverse(currnode->bottom_left, travfunc);
	if (currnode->bottom_right != NULL) traverse(currnode->bottom_right, travfunc);
}

template <class T>
bool QuadTree<T>::noChildren(QuadTree<T>* totest){
	if (totest->top_left == NULL && totest->top_right == NULL
		&& totest->bottom_left == NULL && totest->bottom_right == NULL){
		return true;
	}

	return false;
}

template <class T>
void QuadTree<T>::splitTree(QuadTree<T>* tosplit, pair (*getposfunc)(const T & element)){
	tosplit->top_left = new QuadTree<T>(pair(tosplit->topleft[0], tosplit->topleft[1]), pair((tosplit->topleft[0] + tosplit->bottomright[0]) / 2, (tosplit->bottomright[1] + tosplit->topleft[1]) / 2 ), tosplit->ceiling);
	tosplit->top_right = new QuadTree<T>(pair((tosplit->topleft[0] + tosplit->bottomright[0])/2, tosplit->topleft[1]), pair(tosplit->bottomright[0], (tosplit->bottomright[1] + tosplit->topleft[1]) / 2), tosplit->ceiling);
	tosplit->bottom_left = new QuadTree<T>(pair(tosplit->topleft[0], (tosplit->bottomright[1] + tosplit->topleft[1]) / 2), pair((tosplit->topleft[0] + tosplit->bottomright[0]) / 2, tosplit->bottomright[1]), tosplit->ceiling);
	tosplit->bottom_right = new QuadTree<T>(pair((tosplit->topleft[0] + tosplit->bottomright[0]) / 2, (tosplit->bottomright[1] + tosplit->topleft[1]) / 2), pair(tosplit->bottomright[0], tosplit->bottomright[1]), tosplit->ceiling);

	pair temppos;

	std::list<T> tmplist;

	for (unsigned i = 0; i < tosplit->bucket.size(); i++){
		tmplist.clear();

		for (std::list<T>::iterator listit = tosplit->bucket.at(i).begin(); listit != tosplit->bucket.at(i).end(); ++listit){
			tmplist.push_back(*listit);
		}

		temppos = getposfunc(tosplit->bucket.at(i).front());
		if (temppos[0] <= tosplit->top_left->bottomright[0] && temppos[0] >= tosplit->top_left->topleft[0]
			&& temppos[1] >= tosplit->top_left->bottomright[1] && temppos[1] <= tosplit->top_left->topleft[1]){
			tosplit->top_left->bucket.push_back(tmplist);
		}
		else
		if (temppos[0] <= tosplit->top_right->bottomright[0] && temppos[0] >= tosplit->top_right->topleft[0]
			&& temppos[1] >= tosplit->top_right->bottomright[1] && temppos[1] <= tosplit->top_right->topleft[1]){
			tosplit->top_right->bucket.push_back(tmplist);
		}
		else
		if (temppos[0] <= tosplit->bottom_left->bottomright[0] && temppos[0] >= tosplit->bottom_left->topleft[0]
			&& temppos[1] >= tosplit->bottom_left->bottomright[1] && temppos[1] <= tosplit->bottom_left->topleft[1]){
			tosplit->bottom_left->bucket.push_back(tmplist);
		}
		else
		if (temppos[0] <= tosplit->bottom_right->bottomright[0] && temppos[0] >= tosplit->bottom_right->topleft[0]
			&& temppos[1] >= tosplit->bottom_right->bottomright[1] && temppos[1] <= tosplit->bottom_right->topleft[1]){
			tosplit->bottom_right->bucket.push_back(tmplist);
		}
	}

	tosplit->bucket.clear();

	if (tosplit->top_left->bucket.size() > tosplit->top_left->ceiling) splitTree(tosplit->top_left, getposfunc);
	if (tosplit->top_right->bucket.size() > tosplit->top_right->ceiling) splitTree(tosplit->top_right, getposfunc);
	if (tosplit->bottom_left->bucket.size() > tosplit->bottom_left->ceiling) splitTree(tosplit->bottom_left, getposfunc);
	if (tosplit->bottom_right->bucket.size() > tosplit->bottom_right->ceiling) splitTree(tosplit->bottom_right, getposfunc);
}

template <class T>
bool QuadTree<T>::insert(QuadTree<T>* curnode, const T & newelement, pair (*getposfunc)(const T & element)){
	pair temppos = getposfunc(newelement);

	if (curnode->bucket.size() < curnode->ceiling && noChildren(curnode)){
		int dupind;
		if ((dupind = duplicateElement(curnode->bucket, newelement, getposfunc)) != -1){
			curnode->bucket.at(dupind).push_back(newelement);
			return true;
		}
		else{
			std::list<T> tmplist;
			tmplist.push_back(newelement);
			curnode->bucket.push_back(tmplist);
			return true;
		}
	}
	else
	if (noChildren(curnode)){
		int dupind;
		if ((dupind = duplicateElement(curnode->bucket, newelement, getposfunc)) != -1){
			curnode->bucket.at(dupind).push_back(newelement);
			return true;
		}
		else{
			std::list<T> tmplist;
			tmplist.push_back(newelement);
			curnode->bucket.push_back(tmplist);
			splitTree(curnode, getposfunc);
			return true;
		}
	}
	else{
		if (temppos[0] <= curnode->top_left->bottomright[0] && temppos[0] >= curnode->top_left->topleft[0]
			&& temppos[1] >= curnode->top_left->bottomright[1] && temppos[1] <= curnode->top_left->topleft[1]){
			return insert(curnode->top_left, newelement, getposfunc);
		}
		else
		if (temppos[0] <= curnode->top_right->bottomright[0] && temppos[0] >= curnode->top_right->topleft[0]
			&& temppos[1] >= curnode->top_right->bottomright[1] && temppos[1] <= curnode->top_right->topleft[1]){
			return insert(curnode->top_right, newelement, getposfunc);
		}
		else
		if (temppos[0] <= curnode->bottom_left->bottomright[0] && temppos[0] >= curnode->bottom_left->topleft[0]
			&& temppos[1] >= curnode->bottom_left->bottomright[1] && temppos[1] <= curnode->bottom_left->topleft[1]){
			return insert(curnode->bottom_left, newelement, getposfunc);
		}
		else
		if (temppos[0] <= curnode->bottom_right->bottomright[0] && temppos[0] >= curnode->bottom_right->topleft[0]
			&& temppos[1] >= curnode->bottom_right->bottomright[1] && temppos[1] <= curnode->bottom_right->topleft[1]){
			return insert(curnode->bottom_right, newelement, getposfunc);
		}

		return false;
	}
}

template <class T>
int QuadTree<T>::duplicateElement(const std::vector<std::list<T> >& tosearch, const T & target, pair(*getposfunc)(const T& element)){
	int duplicate = -1;

	bool dupfound = false;

	pair targetpos = getposfunc(target);

	for (unsigned i = 0; i < tosearch.size() && !dupfound; i++){
		if (getposfunc(*tosearch.at(i).begin()) == targetpos){
			dupfound = true;
			duplicate = i;
		}
	}

	return duplicate;
}

template <class T>
bool QuadTree<T>::insert(const T& newelement, pair(*getposfunc)(const T& element)){
	
	pair temppos = getposfunc(newelement);
	
	if (!(temppos[0] > this->topleft[0] && temppos[0] < this->bottomright[0]
		&& temppos[1] < this->topleft[1] && temppos[1] > this->bottomright[1])){
		return false;
	}

	if (this->bucket.size() < this->ceiling && noChildren(this)){

		int dupind;
		if ((dupind = duplicateElement(this->bucket, newelement, getposfunc)) != -1){
			this->bucket.at(dupind).push_back(newelement);
		}
		else{
			std::list<T> tmplist;
			tmplist.push_back(newelement);
			this->bucket.push_back(tmplist);
		}
		return true;
	}
	else
	if(noChildren(this)){
		int dupind;
		if ((dupind = duplicateElement(this->bucket, newelement, getposfunc)) != -1){
			this->bucket.at(dupind).push_back(newelement);
			return true;
		}
		else{
			std::list<T> tmplist;
			tmplist.push_back(newelement);
			this->bucket.push_back(tmplist);
			splitTree(this, getposfunc);
			return true;
		}
	}
	else{
		if (temppos[0] <= this->top_left->bottomright[0] && temppos[0] >= this->top_left->topleft[0]
			&& temppos[1] >= this->top_left->bottomright[1] && temppos[1] <= this->top_left->topleft[1]){
			return insert(this->top_left, newelement, getposfunc);
		}
		else
		if (temppos[0] <= this->top_right->bottomright[0] && temppos[0] >= this->top_right->topleft[0]
			&& temppos[1] >= this->top_right->bottomright[1] && temppos[1] <= this->top_right->topleft[1]){
			return insert(this->top_right, newelement, getposfunc);
		}
		else
		if (temppos[0] <= this->bottom_left->bottomright[0] && temppos[0] >= this->bottom_left->topleft[0]
			&& temppos[1] >= this->bottom_left->bottomright[1] && temppos[1] <= this->bottom_left->topleft[1]){
			return insert(this->bottom_left, newelement, getposfunc);
		}
		else
		if (temppos[0] <= this->bottom_right->bottomright[0] && temppos[0] >= this->bottom_right->topleft[0]
			&& temppos[1] >= this->bottom_right->bottomright[1] && temppos[1] <= this->bottom_right->topleft[1]){
			return insert(this->bottom_right, newelement, getposfunc);
		}

		return false;
	}
}