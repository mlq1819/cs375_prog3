#ifndef MQ_ITEM_H
#define MQ_ITEM_H

class Item{
	private:
		unsigned int profit;
		unsigned int weight;
	public:
		Item(unsigned int p, unsigned int w){this->profit=p; this->weight=w;};
		Item();
		Item(const Item &);
		double respective() const {return ((double)profit)/weight;};
		unsigned int getProfit() const {return this->profit;};
		unsigned int getWeight() const {return this->weight;};
		bool operator==(const Item &) const;
		bool operator=(const Item &);
		bool operator>(const Item &) const;
		bool operator<(const Item &) const;
		bool operator>=(const Item &o) const {return !this->operator<(o);};
		bool operator<=(const Item &o) const {return !this->operator>(o);};
};

#endif