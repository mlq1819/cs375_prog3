#include "item.h"

Item::Item(const Item &o){
	this->profit=o.getProfit();
	this->weight=o.getWeight();
}

Item::Item(){
	this->profit=0;
	this->weight=0;
}

bool Item::operator==(const Item &o) const {
	return this->respective()==o.respective();
}

bool Item::operator=(const Item &o){
	this->profit=o.getProfit();
	this->weight=o.getWeight();
	return true;
}

bool Item::operator>(const Item &o) const {
	return this->respective()>o.respective();
}

bool Item::operator<(const Item &o) const {
	return this->respective()<o.respective();
}