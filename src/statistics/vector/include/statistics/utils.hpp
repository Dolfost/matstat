#include<map>
#include<utility>

namespace ss {

class Vector;

enum class Bound {
	Unknown = 0,
	Upper = 1,
	Lower = 2,
};

enum class Measure {
	Unknown = 0,
	Population = 1, // зсунута оцінка
	Sample = 2 // не зсунута оцінка
};

}

namespace ss::utils {

template<class T>
class Statistic {
public:
	Statistic() = delete;
	Statistic(Vector& vec): s_vector(vec) {};
	Statistic(Vector* vec): s_vector(*vec) {};
	const Vector& vector() const { return s_vector; };
	Vector& vector() { return s_vector; };
	virtual void invalidate() = 0;
protected:
	Vector& s_vector;
private:
};


template<class T>
class StatisticSingle: public Statistic<T> {
public:
	StatisticSingle() = delete;
	using Statistic<T>::Statistic;
	virtual void invalidate() override {
		s_valid = false;
	}
	virtual T value() {
		if (!s_valid) {
			adapt();
			s_valid = true;
		}
		return s_value;
	}
	T operator()() { return value(); };
protected:
	virtual void adapt() = 0;
	bool s_valid = false;
	T s_value;
};

template<class T>
class StatisticList: public Statistic<T> {
public:
	StatisticList() = delete;
	using Statistic<T>::Statistic;
	virtual void invalidate() override {
		s_value.clear();
		s_valid = false;
	}
	virtual const T& value() {
		if (!s_valid) {
			adapt();
			s_valid = true;
		}
		return s_value;
	}
	const T& operator()() { return value(); };
protected:
	virtual void adapt() = 0;
	bool s_valid = false;
	T s_value;
};

template<class T, class Switch>
class StatisticPair: public Statistic<T> {
public:
	StatisticPair() = delete;
	using Statistic<T>::Statistic;
	virtual void invalidate() override {
		s_valid = false;
	}
	virtual T value(Switch b = static_cast<Switch>(1)) {
		if (!s_valid) { 
			adapt();
			s_valid = true;
		}

		if (static_cast<int>(b) == 1) 
			return s_value.first;
		if (static_cast<int>(b) == 2) 
			return s_value.second;
		else
			throw std::logic_error("Invalid Switch.");
	}
	T operator()(Switch b = static_cast<Switch>(1)) { return value(b); };
protected:
	virtual void adapt() = 0;
	bool s_valid = false;
	std::pair<T, T> s_value;
};

template<class From, class To, class MapFrom=From>
class StatisticMap: public Statistic<To> {
public:
	StatisticMap() = delete;
	using Statistic<To>::Statistic;
	virtual void invalidate() override {
		s_values.clear();
	}
	virtual To value(From arg) {
		if (s_values.count(static_cast<From>(arg)) != 1)
			adapt(arg);

		return s_values[arg];
	}
	To operator()(From arg) { return value(arg); };
protected:
	virtual void adapt(MapFrom arg) = 0;
	std::map<MapFrom, To> s_values;
};

template<class From, class To, class Switch>
class StatisticPairMap: public Statistic<To> {
public:
	StatisticPairMap() = delete;
	using Statistic<To>::Statistic;
	virtual void invalidate() override {
		s_values.clear();
	}
	virtual To value(From arg, Switch s = static_cast<Switch>(1)) {
		if (s_values.count(arg) != 1)
			adapt(arg);

		if (static_cast<int>(s) == 1) 
			return s_values[arg].first;
		if (static_cast<int>(s) == 2) 
			return s_values[arg].second;
		else
			throw std::logic_error("Invalid Switch.");
	}
	To operator()(From arg, Switch s = static_cast<Switch>(1)) { return value(arg, s); };
protected:
	virtual void adapt(From arg) = 0;
	std::map<From, std::pair<To, To>> s_values;
};

template<class From, class To>
class Confidence: public StatisticPairMap<From, To, Bound> {
public:
	Confidence() = delete;
	using StatisticPairMap<From, To, Bound>::StatisticPairMap;
	virtual To value(From alpha, Bound b) {
		if (alpha < 0 or alpha > 1)
			throw std::logic_error("Alpha should be in range [0;1]");
		return StatisticPairMap<From, To, Bound>::value(alpha, b);
	};
};

}
