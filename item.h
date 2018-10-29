#ifndef MQ_ITEM_H
#define MQ_ITEM_H

class Item{
	private:
		int profit;
		int weight;
	public:
		Item(int p, int w){this->profit=p; this->weight=w;};
		double respective() const {return ((double)profit)/weight;};
		int getProfit() const {return this->profit;};
		int getWeight() const {return this->weight;};
}

#endif