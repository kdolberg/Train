#ifndef INTERVAL_H
#define INTERVAL_H

template <typename T>
class Interval {
protected:
	T _start;
	T _stop;
public:
	Interval() {}
	~Interval() {}
protected:
	virtual T update() = 0;
public:
	virtual void start() {
		this->_start = this->update();
	}
	virtual Interval<T>& stop() {
		this->_stop = this->update();
		return (*this);
	}
	virtual std::string str() const = 0;
	const T& get_start() const {
		return this->_start;
	}
	const T& get_stop() const {
		return this->_stop;
	}
	virtual float delta() const = 0;
};

#endif // INTERVAL_H